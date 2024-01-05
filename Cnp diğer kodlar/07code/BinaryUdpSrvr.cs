using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class BinaryUdpSrvr
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 9050);
      UdpClient newsock = new UdpClient(ipep);

      Console.WriteLine("Waiting for a client...");

      IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);

      data = newsock.Receive(ref sender);

      Console.WriteLine("Message received from {0}:", sender.ToString());
      Console.WriteLine(Encoding.ASCII.GetString(data, 0, data.Length));

      string welcome = "Welcome to my test server";
      data = Encoding.ASCII.GetBytes(welcome);
      newsock.Send(data, data.Length, sender);

      byte[] data1 = newsock.Receive(ref sender);
      int test1 = BitConverter.ToInt32(data1, 0);
      Console.WriteLine("test1 = {0}", test1);

      byte[] data2 = newsock.Receive(ref sender);
      double test2 = BitConverter.ToDouble(data2, 0);
      Console.WriteLine("test2 = {0}", test2);

      byte[] data3 = newsock.Receive(ref sender);
      int test3 = BitConverter.ToInt32(data3, 0);      
      Console.WriteLine("test3 = {0}", test3);

      byte[] data4 = newsock.Receive(ref sender);
      bool test4 = BitConverter.ToBoolean(data4, 0);
      Console.WriteLine("test4 = {0}", test4.ToString());

      byte[] data5 = newsock.Receive(ref sender);
      string test5 = Encoding.ASCII.GetString(data5);
      Console.WriteLine("test5 = {0}", test5);

      newsock.Close();
   }
}