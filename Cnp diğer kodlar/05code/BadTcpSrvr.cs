using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class BadTcpSrvr
{
   public static void Main()
   {
      int recv;
      byte[] data = new byte[1024];
      IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 9050);

      Socket newsock = new Socket(AddressFamily.InterNetwork,
                      SocketType.Stream, ProtocolType.Tcp);

      newsock.Bind(ipep);
      newsock.Listen(10);
      Console.WriteLine("Waiting for a client...");

      Socket client = newsock.Accept();
      string welcome = "Welcome to my test server";
      data = Encoding.ASCII.GetBytes(welcome);
      client.Send(data, data.Length,
                      SocketFlags.None);
      IPEndPoint newclient = (IPEndPoint)client.RemoteEndPoint;
      Console.WriteLine("Connected with {0} at port {1}",
                      newclient.Address, newclient.Port);


      for (int i = 0; i < 5; i++)
      {
         recv = client.Receive(data);   
         Console.WriteLine(Encoding.ASCII.GetString(data, 0, recv));
      }
      Console.WriteLine("Disconnecting from {0}", newclient.Address);
      client.Close();
      newsock.Close();
   }
}