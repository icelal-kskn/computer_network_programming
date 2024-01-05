using System;
using System.Collections.Specialized;
using System.Net;

class ResponseHeadersTest
{
   public static void Main(string[] argv)
   {
      WebClient wc = new WebClient();

      byte[] response = wc.DownloadData(argv[0]);
      WebHeaderCollection whc = wc.ResponseHeaders;
      Console.WriteLine("header count = {0}", whc.Count);
      for (int i = 0; i < whc.Count; i++)
      {
         Console.WriteLine(whc.GetKey(i) + " = " + whc.Get(i));
      }
   }
}