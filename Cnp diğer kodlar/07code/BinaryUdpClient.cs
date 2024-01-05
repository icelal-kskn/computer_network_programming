using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class BinaryUdpClient
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      string stringData;
      UdpClient server = new UdpClient("127.0.0.1", 9050);

      IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);

      string welcome = "Hello, are you there?";
      data = Encoding.ASCII.GetBytes(welcome);
      server.Send(data, data.Length);

      data = new byte[1024];
      data = server.Receive(ref sender);

      Console.WriteLine("Message received from {0}:", sender.ToString());
      stringData = Encoding.ASCII.GetString(data, 0, data.Length);
      Console.WriteLine(stringData);
   
      int test1 = 45;
      double test2 = 3.14159;
      int test3 = -1234567890;
      bool test4 = false;
      string test5 = "This is a test.";

      byte[] data1 = BitConverter.GetBytes(test1);
      server.Send(data1, data1.Length);

      byte[] data2 = BitConverter.GetBytes(test2);
      server.Send(data2, data2.Length);

      byte[] data3 = BitConverter.GetBytes(test3);
      server.Send(data3, data3.Length);

      byte[] data4 = BitConverter.GetBytes(test4);
      server.Send(data4, data4.Length);

      byte[] data5 = Encoding.ASCII.GetBytes(test5);
      server.Send(data5, data5.Length);

      Console.WriteLine("Stopping client");
      server.Close();
   }
}