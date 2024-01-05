using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class BadBroadcast
{
   public static void Main()
   {
      Socket sock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
      IPEndPoint iep = new IPEndPoint(IPAddress.Broadcast, 9050);

      byte[] data = Encoding.ASCII.GetBytes("This is a test message");
      sock.SendTo(data, iep);
      sock.Close();
   }
}