using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class SocketExcept
{
   public static void Main()
   {
      IPAddress host = IPAddress.Parse("192.168.1.1");
      IPEndPoint hostep = new IPEndPoint(host, 8000);
      Socket sock = new Socket(AddressFamily.InterNetwork,
                   SocketType.Stream, ProtocolType.Tcp);

      try
      {
         sock.Connect(hostep);
      } catch (SocketException e)
      {
         Console.WriteLine("Problem connecting to host");
         Console.WriteLine(e.ToString());
         sock.Close();
         return;
      }

      try
      {
         sock.Send(Encoding.ASCII.GetBytes("testing"));
      } catch (SocketException e)
      {
          Console.WriteLine("Problem sending data");
          Console.WriteLine( e.ToString());
          sock.Close();
          return;
      }
      sock.Close();
   }
}