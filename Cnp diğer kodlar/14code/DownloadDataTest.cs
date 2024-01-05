using System;
using System.Net;
using System.Text;

class DownloadDataTest
{
   public static void Main(string[] argv)
   {
      WebClient wc = new WebClient();
      byte[] response = wc.DownloadData(argv[0]);
      Console.WriteLine(Encoding.ASCII.GetString(response));
   }
}