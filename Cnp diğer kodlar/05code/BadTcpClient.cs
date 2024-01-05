using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class BadTcpClient
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      string stringData;
      IPEndPoint ipep = new IPEndPoint(
                      IPAddress.Parse("127.0.0.1"), 9050);

      Socket server = new Socket(AddressFamily.InterNetwork,
                     SocketType.Stream, ProtocolType.Tcp);

      try
      {
         server.Connect(ipep);
      } catch (SocketException e)
      {
         Console.WriteLine("Unable to connect to server.");
         Console.WriteLine(e.ToString());
         return;
      }


      int recv = server.Receive(data);
      stringData = Encoding.ASCII.GetString(data, 0, recv);
      Console.WriteLine(stringData);

      server.Send(Encoding.ASCII.GetBytes("message 1"));
      server.Send(Encoding.ASCII.GetBytes("message 2"));
      server.Send(Encoding.ASCII.GetBytes("message 3"));
      server.Send(Encoding.ASCII.GetBytes("message 4"));
      server.Send(Encoding.ASCII.GetBytes("message 5"));
      Console.WriteLine("Disconnecting from server...");
      server.Shutdown(SocketShutdown.Both);
      server.Close();
   }
}