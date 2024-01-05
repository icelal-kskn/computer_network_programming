using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class TestUdpClient
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      IPEndPoint ipep = new IPEndPoint(
                      IPAddress.Parse("127.0.0.1"), 9050);

      Socket server = new Socket(AddressFamily.InterNetwork,
                     SocketType.Dgram, ProtocolType.Udp);

      string welcome = "Hello, are you there?";
      data = Encoding.ASCII.GetBytes(welcome);
      server.SendTo(data, data.Length, SocketFlags.None, ipep);

      IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
      EndPoint tmpRemote = (EndPoint)sender;

      data = new byte[1024];
      int recv = server.ReceiveFrom(data, ref tmpRemote);

      Console.WriteLine("Message received from {0}:", tmpRemote.ToString());
      Console.WriteLine(Encoding.ASCII.GetString(data, 0, recv));


      server.SendTo(Encoding.ASCII.GetBytes("message 1"), tmpRemote);
      server.SendTo(Encoding.ASCII.GetBytes("message 2"), tmpRemote);
      server.SendTo(Encoding.ASCII.GetBytes("message 3"), tmpRemote);
      server.SendTo(Encoding.ASCII.GetBytes("message 4"), tmpRemote);
      server.SendTo(Encoding.ASCII.GetBytes("message 5"), tmpRemote);

      Console.WriteLine("Stopping client");
      server.Close();
   }
}