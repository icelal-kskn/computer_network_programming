using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class OddUdpClient
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      string input, stringData;
      IPEndPoint ipep = new IPEndPoint(
                      IPAddress.Parse("127.0.0.1"), 9050);

      Socket server = new Socket(AddressFamily.InterNetwork,
                     SocketType.Dgram, ProtocolType.Udp);

      server.Connect(ipep);
      string welcome = "Hello, are you there?";
      data = Encoding.ASCII.GetBytes(welcome);
      server.Send(data);

      data = new byte[1024];
      int recv = server.Receive(data);

      Console.WriteLine("Message received from {0}:", ipep.ToString());
      Console.WriteLine(Encoding.ASCII.GetString(data, 0, recv));


      while(true)
      {
         input = Console.ReadLine();
         if (input == "exit")
            break;
         server.Send(Encoding.ASCII.GetBytes(input));
         data = new byte[1024];
         recv = server.Receive(data);
         stringData = Encoding.ASCII.GetString(data, 0, recv);
         Console.WriteLine(stringData);
      }
      Console.WriteLine("Stopping client");
      server.Close();
   }
}