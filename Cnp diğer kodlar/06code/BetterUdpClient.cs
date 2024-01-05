using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class BetterdUdpClient
{
   public static void Main()
   {
      byte[] data = new byte[30];
      string input, stringData;
      IPEndPoint ipep = new IPEndPoint(
                      IPAddress.Parse("127.0.0.1"), 9050);

      Socket server = new Socket(AddressFamily.InterNetwork,
                     SocketType.Dgram, ProtocolType.Udp);

      string welcome = "Hello, are you there?";
      data = Encoding.ASCII.GetBytes(welcome);
      server.SendTo(data, data.Length, SocketFlags.None, ipep);

      IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
      EndPoint tmpRemote = (EndPoint)sender;

      data = new byte[30];
      int recv = server.ReceiveFrom(data, ref tmpRemote);

      Console.WriteLine("Message received from {0}:", tmpRemote.ToString());
      Console.WriteLine(Encoding.ASCII.GetString(data, 0, recv));


      int i = 30;
      while(true)
      {
         input = Console.ReadLine();
         if (input == "exit")
            break;
         server.SendTo(Encoding.ASCII.GetBytes(input), tmpRemote);
         data = new byte[i];
         try
         {
            recv = server.ReceiveFrom(data, ref tmpRemote);
            stringData = Encoding.ASCII.GetString(data, 0, recv);
            Console.WriteLine(stringData);
         } catch (SocketException)
         {
            Console.WriteLine("WARNING: data lost, retry message.");
            i += 10;
         }
      }
      Console.WriteLine("Stopping client");
      server.Close();
   }
}