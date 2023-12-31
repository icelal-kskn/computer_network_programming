using System;
using System.Net;

class DNSName
{
   public static void Main()
   {
	string hostName = Dns.GetHostName();
	Console.WriteLine("Local hostname: {0}", hostName);
	IPHostEntry myself = Dns.GetHostByName(hostName);
	foreach (IPAddress address in myself.AddressList)
	{
	   Console.WriteLine("IP Address: {0}", address.ToString());
	}
   }
}