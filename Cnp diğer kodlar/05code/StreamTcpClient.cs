using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

class StreamTcpClient
{
   public static void Main()
   {
      string data;
      string input;
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


      NetworkStream ns = new NetworkStream(server);
      StreamReader sr = new StreamReader(ns);
      StreamWriter sw = new StreamWriter(ns);

      data = sr.ReadLine();
      Console.WriteLine(data);

      while(true)
      {
         input = Console.ReadLine();
         if (input == "exit")
            break;
         sw.WriteLine(input);
         sw.Flush();

         data = sr.ReadLine();
         Console.WriteLine(data);
      }
      Console.WriteLine("Disconnecting from server...");
      sr.Close();
      sw.Close();
      ns.Close();
      server.Shutdown(SocketShutdown.Both);
      server.Close();
   }
}