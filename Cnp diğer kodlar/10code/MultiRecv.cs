using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class MultiRecv
{
   public static void Main()
   {
      Socket sock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
      Console.WriteLine("Ready to receive...");

      IPEndPoint iep = new IPEndPoint(IPAddress.Any, 9050);
      EndPoint ep = (EndPoint)iep;
      sock.Bind(iep);
      sock.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.AddMembership,
            new MulticastOption(IPAddress.Parse("224.100.0.1")));

      byte[] data = new byte[1024];
      int recv = sock.ReceiveFrom(data, ref ep);
      string stringData = Encoding.ASCII.GetString(data, 0, recv);
      Console.WriteLine("received: {0}  from: {1}", stringData, ep.ToString());
      sock.Close();
   }
}