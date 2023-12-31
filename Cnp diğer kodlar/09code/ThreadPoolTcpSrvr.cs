using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

class ThreadPoolTcpSrvr
{
   private TcpListener client;

   public ThreadPoolTcpSrvr()
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
         ThreadPool.QueueUserWorkItem(new
                    WaitCallback(newconnection.HandleConnection));
      }
   }

   public static void Main()
   {
      ThreadPoolTcpSrvr tpts = new ThreadPoolTcpSrvr();
   }
}

class ConnectionThread
{
   public TcpListener threadListener;
   private static int connections = 0;

   public void HandleConnection(object state)
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