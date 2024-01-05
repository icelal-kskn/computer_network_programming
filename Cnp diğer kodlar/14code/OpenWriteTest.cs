using System;
using System.IO;
using System.Net;

class OpenWriteTest
{
   public static void Main(string[] argv)
   {
      WebClient wc = new WebClient();
      string data = "Data up upload to server";

      Stream strm = wc.OpenWrite(argv[0]);
      StreamWriter sw = new StreamWriter(strm);

      sw.WriteLine(data);
      sw.Close();
      strm.Close();
   }
}