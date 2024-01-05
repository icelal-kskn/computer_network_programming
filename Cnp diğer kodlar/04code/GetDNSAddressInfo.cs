using System;
using System.Net;

class GetDNSAddressInfo
{
   public static void Main(string[] argv)
   {
      if (argv.Length != 1)
      {
         Console.WriteLine("Usage: GetDNSAddressInfo address");
         return;
      }

      IPAddress test = IPAddress.Parse(argv[0]);

      IPHostEntry iphe = Dns.GetHostByAddress(test);

      Console.WriteLine("Information for {0}",
                     test.ToString());

      Console.WriteLine("Host name: {0}", iphe.HostName);
      foreach(string alias in iphe.Aliases)
      {
         Console.WriteLine("Alias: {0}", alias);
      }
      foreach(IPAddress address in iphe.AddressList)
      {
         Console.WriteLine("Address: {0}", address.ToString());
      }
   }
}