using System;
using Microsoft.Win32;

class FindDNSServers
{
   public static void Main()
   {
      RegistryKey start = Registry.LocalMachine;
      string DNSservers = @"SYSTEM\CurrentControlSet\Services\Tcpip\Parameters";

      RegistryKey DNSserverKey = start.OpenSubKey(DNSservers);
      if (DNSserverKey == null)
      {
         Console.WriteLine("Unable to open DNS servers key");
         return;
      }
  
      string serverlist = (string)DNSserverKey.GetValue("NameServer");

      Console.WriteLine("DNS Servers: {0}", serverlist);
      DNSserverKey.Close();
      start.Close();

      char[] token = new char[1];
      token[0] = ' ';
      string[] servers = serverlist.Split(token);

      foreach(string server in servers)
      {
         Console.WriteLine("DNS server: {0}", server);
      }
   }
}
