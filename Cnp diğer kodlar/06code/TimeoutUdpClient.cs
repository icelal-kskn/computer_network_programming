using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class TimeoutUdpClient
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      string input, stringData;
      int recv;
      IPEndPoint ipep = new IPEndPoint(
                      IPAddress.Parse("127.0.0.1"), 9050);

      Socket server = new Socket(AddressFamily.InterNetwork,
                     SocketType.Dgram, ProtocolType.Udp);

      int sockopt = (int)server.GetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout);
      Console.WriteLine("Default timeout: {0}", sockopt);
      server.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, 3000);
      sockopt = (int)server.GetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout);
      Console.WriteLine("New timeout: {0}", sockopt);

      string welcome = "Hello, are you there?";
      data = Encoding.ASCII.GetBytes(welcome);
      server.SendTo(data, data.Length, SocketFlags.None, ipep);

      IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
      EndPoint tmpRemote = (EndPoint)sender;

      data = new byte[1024];
      recv = server.ReceiveFrom(data, ref tmpRemote);
      Console.WriteLine("Message received from {0}:", tmpRemote.ToString());
      Console.WriteLine(Encoding.ASCII.GetString(data, 0, recv));

      while(true)
      {
         input = Console.ReadLine();
         if (input == "exit")
            break;
         server.SendTo(Encoding.ASCII.GetBytes(input), tmpRemote);
         data = new byte[1024];
         recv = server.ReceiveFrom(data, ref tmpRemote);
         stringData = Encoding.ASCII.GetString(data, 0, recv);
         Console.WriteLine(stringData);
      }
      Console.WriteLine("Stopping client");
      server.Close();
   }
}