using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class NewMultiSend
{
   public static void Main()
   {
      Socket server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
      IPEndPoint iep = new IPEndPoint(IPAddress.Any, 9051);
      IPEndPoint iep2 = new IPEndPoint(IPAddress.Parse("224.100.0.1"), 9050);
      server.Bind(iep);
      
      byte[] data = Encoding.ASCII.GetBytes("This is a test message");
      server.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.AddMembership, new MulticastOption(IPAddress.Parse("224.100.0.1")));
      server.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.MulticastTimeToLive, 50);
      server.SendTo(data, iep2);
      server.Close();
   }
}