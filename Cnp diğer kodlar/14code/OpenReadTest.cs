using System;
using System.IO;
using System.Net;

class OpenReadTest
{
   public static void Main(string[] argv)
   {
      WebClient wc = new WebClient();
      string response;

      Stream strm = wc.OpenRead(argv[0]);

      StreamReader sr = new StreamReader(strm);

      while(sr.Peek() > -1)
      {
         response = sr.ReadLine();
         Console.WriteLine(response);
      }
      sr.Close();
   }
}