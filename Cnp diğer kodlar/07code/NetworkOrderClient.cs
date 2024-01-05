using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class NetworkOrderClient
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      string stringData;
      TcpClient server;

      try
      {
         server = new TcpClient("127.0.0.1", 9050);
      } catch (SocketException)
      {
         Console.WriteLine("Unable to connect to server");
         return;
      }
      NetworkStream ns = server.GetStream();

      int recv = ns.Read(data, 0, data.Length);
      stringData = Encoding.ASCII.GetString(data, 0, recv);
      Console.WriteLine(stringData);

      short test1 = 45;
      int test2 = 314159;
      long test3 = -123456789033452;

      short test1b = IPAddress.HostToNetworkOrder(test1);
      data = BitConverter.GetBytes(test1b);
      Console.WriteLine("sending test1 = {0}", test1);
      ns.Write(data, 0, data.Length);
      ns.Flush();

      int test2b = IPAddress.HostToNetworkOrder(test2);
      data = BitConverter.GetBytes(test2b);
      Console.WriteLine("sending test2 = {0}", test2);
      ns.Write(data, 0, data.Length);
      ns.Flush();

      long test3b = IPAddress.HostToNetworkOrder(test3);
      data = BitConverter.GetBytes(test3b);
      Console.WriteLine("sending test3 = {0}", test3);
      ns.Write(data, 0, data.Length);
      ns.Flush();

      ns.Close();
      server.Close();
   }
}