using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class UdpClientMultiSend
{
   public static void Main()
   {
      UdpClient sock = new UdpClient();
      IPEndPoint iep = new IPEndPoint(IPAddress.Parse("224.100.0.1"), 9050);
      byte[] data = Encoding.ASCII.GetBytes("This is a test message");
      sock.Send(data, data.Length, iep);
      sock.Close();
   }
}