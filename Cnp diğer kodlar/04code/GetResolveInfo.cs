using System;
using System.Net;

class GetResolveInfo
{
   public static void Main(string[] argv)
   {
      if (argv.Length != 1)
      {
         Console.WriteLine("Usage: GetResolveInfo address");
         return;
      }

      IPHostEntry iphe = Dns.Resolve(argv[0]);

      Console.WriteLine("Information for {0}", argv[0]);

      Console.WriteLine("Host name: {0}", iphe.HostName);
      foreach(string alias in iphe.Aliases)
      {
         Console.WriteLine("Alias: {0}", alias);
      }
      foreach(IPAddress address in iphe.AddressList)
      {
         Console.WriteLine("Address: {0}",
                     address.ToString());
      }
   }
}