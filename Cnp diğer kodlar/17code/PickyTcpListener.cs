using System;
using System.Net;
using System.Net.Sockets;
using System.Security;
using System.Security.Permissions;
using System.Text;

[SocketPermission(SecurityAction.Deny, Access="Accept", Host="0.0.0.0",
      Port="9050", Transport="All")]
[SocketPermission(SecurityAction.Deny, Access="Accept", Host="0.0.0.0",
      Port="9051", Transport="All")]
[SocketPermission(SecurityAction.Deny, Access="Accept", Host="0.0.0.0",
      Port="9052", Transport="All")]

class PickyTcpListener
{
   public static void Main()
   {
      int recv;
      TcpListener newsock = null;
      byte[] data = new byte[1024];

      Console.Write("Enter port number to use: ");
      string stringPort = Console.ReadLine();
      int port = Convert.ToInt32(stringPort);

      try
      {
         newsock = new TcpListener(port);
         newsock.Start();
      } catch (SecurityException)
      {
         Console.WriteLine("Sorry, that port is unavailable");
         return;
      }
      Console.WriteLine("Waiting for a client...");

      TcpClient client = newsock.AcceptTcpClient();
      NetworkStream ns = client.GetStream();

      string welcome = "Welcome to my test server";
      data = Encoding.ASCII.GetBytes(welcome);
      ns.Write(data, 0, data.Length);

      while(true)
      {
         data = new byte[1024];
         recv = ns.Read(data, 0, data.Length);
         if (recv == 0)
            break;
       
         Console.WriteLine(
                  Encoding.ASCII.GetString(data, 0, recv));
         ns.Write(data, 0, recv);
      }
      ns.Close();
      client.Close();
      newsock.Stop();
   }
}