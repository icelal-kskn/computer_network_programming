using System;
using System.Net;

class GetDNSHostInfo
{
   public static void Main(string[] argv)
   {
      if (argv.Length != 1)
      {
       Console.WriteLine("Usage: GetDNSHostInfo hostname");
       return;
      }

      IPHostEntry results = Dns.GetHostByName(argv[0]);

      Console.WriteLine("Host name: {0}",
                       results.HostName);

      foreach(string alias in results.Aliases)
      {
         Console.WriteLine("Alias: {0}", alias);
      }
      foreach(IPAddress address in results.AddressList)
      {
         Console.WriteLine("Address: {0}",
                     address.ToString());
      }
   }
}