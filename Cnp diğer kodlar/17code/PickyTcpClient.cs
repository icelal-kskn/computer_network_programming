using System;
using System.Net;
using System.Net.Sockets;
using System.Security;
using System.Security.Permissions;
using System.Text;

[SocketPermission(SecurityAction.Deny, Access="Connect", Host="127.0.0.1",
     Port="All", Transport="All")]
[SocketPermission(SecurityAction.Deny, Access="Connect", Host="192.168.0.2",
     Port="All", Transport="All")]
[SocketPermission(SecurityAction.Deny, Access="Connect", Host="192.168.1.100",
     Port="80", Transport="All")]


class PickyTcpClient
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      string input, stringData;
      TcpClient server = null;

      Console.Write("Enter a host to connect to: ");
      string stringHost = Console.ReadLine();
 
      try
      {
         server = new TcpClient(stringHost, 9050);
      } catch (SocketException)
      {
         Console.WriteLine("Unable to connect to server");
         return;
      } catch (SecurityException)
      {
         Console.WriteLine(
            "Sorry, you are restricted from connecting to this server");
         return;
      }
      NetworkStream ns = server.GetStream();

      int recv = ns.Read(data, 0, data.Length);
      stringData = Encoding.ASCII.GetString(data, 0, recv);
      Console.WriteLine(stringData);

      while(true)
      {
         input = Console.ReadLine();
         if (input == "exit")
            break;
         ns.Write(Encoding.ASCII.GetBytes(input), 0, input.Length);
         ns.Flush();

         data = new byte[1024];
         recv = ns.Read(data, 0, data.Length);
         stringData = Encoding.ASCII.GetString(data, 0, recv);
         Console.WriteLine(stringData);
      }
      Console.WriteLine("Disconnecting from server...");
      ns.Close();
      server.Close();
   }
}