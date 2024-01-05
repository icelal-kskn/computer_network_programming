using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class NetworkOrderSrvr
{
   public static void Main()
   {
      int recv;
      byte[] data = new byte[1024];

      TcpListener server = new TcpListener(9050);
      server.Start();
      Console.WriteLine("waiting for a client...");

      TcpClient client = server.AcceptTcpClient();
      NetworkStream ns = client.GetStream();

      string welcome = "Welcome to my test server";
      data = Encoding.ASCII.GetBytes(welcome);
      ns.Write(data, 0, data.Length);
      ns.Flush();

      data = new byte[2];
      recv = ns.Read(data, 0, data.Length);
      short test1t = BitConverter.ToInt16(data, 0);
      short test1 = IPAddress.NetworkToHostOrder(test1t);
      Console.WriteLine("received test1 = {0}", test1);

      data = new byte[4];
      recv = ns.Read(data, 0, data.Length);
      int test2t = BitConverter.ToInt32(data, 0);
      int test2 = IPAddress.NetworkToHostOrder(test2t);
      Console.WriteLine("received test2 = {0}", test2);

      data = new byte[8];
      recv = ns.Read(data, 0, data.Length);
      long test3t = BitConverter.ToInt64(data, 0);
      long test3 = IPAddress.NetworkToHostOrder(test3t);
      Console.WriteLine("received test3 = {0}", test3);

      ns.Close();
      client.Close();
      server.Stop();
   }
}