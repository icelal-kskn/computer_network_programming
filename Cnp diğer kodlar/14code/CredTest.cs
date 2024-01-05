using System;
using System.Net;
using System.Text;

class CredTest
{
   public static void Main()
   {
      WebClient wc = new WebClient();

      NetworkCredential nc = new NetworkCredential("alex", "mypassword");

      wc.Credentials = nc;

      byte[] response = wc.DownloadData("http://localhost/testlogin");
      Console.WriteLine(Encoding.ASCII.GetString(response));
   }
}