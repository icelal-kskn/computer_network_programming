using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

class ThreadedTcpSrvr
{
   private TcpListener client;

   public ThreadedTcpSrvr()
   {
      client = new TcpListener(9050);
      client.Start();

      Console.WriteLine("Waiting for clients...");
      while(true)
      {
         while (!client.Pending())
         {
            Thread.Sleep(1000);
         }

         ConnectionThread newconnection = new ConnectionThread();
         newconnection.threadListener = this.client;
         Thread newthread = new Thread(new
                   ThreadStart(newconnection.HandleConnection));
         newthread.Start();
      }
   }

   public static void Main()
   {
      ThreadedTcpSrvr server = new ThreadedTcpSrvr();
   }
}

class ConnectionThread
{
   public TcpListener threadListener;
   private static int connections = 0;

   public void HandleConnection()
   {
      int recv;
      byte[] data = new byte[1024];

      TcpClient client = threadListener.AcceptTcpClient();
      NetworkStream ns = client.GetStream();
      connections++;
      Console.WriteLine("New client accepted: {0} active connections",
                        connections);

      string welcome = "Welcome to my test server";
      data = Encoding.ASCII.GetBytes(welcome);
      ns.Write(data, 0, data.Length);

      while(true)
      {
         data = new byte[1024];
         recv = ns.Read(data, 0, data.Length);
         if (recv == 0)
            break;
      
         ns.Write(data, 0, recv);
      }
      ns.Close();
      client.Close();
      connections--;
      Console.WriteLine("Client disconnected: {0} active connections",
                         connections);
   }
}