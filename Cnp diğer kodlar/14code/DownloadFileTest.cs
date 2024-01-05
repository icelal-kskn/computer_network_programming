using System;
using System.Net;

class DownloadFileTest
{
   public static void Main(string[] argv)
   {
      WebClient wc = new WebClient();
      string filename = "webpage.htm";
      wc.DownloadFile(argv[0], filename);
      Console.WriteLine("file downloaded");
   }
}