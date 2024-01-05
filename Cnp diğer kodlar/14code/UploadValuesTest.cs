using System;
using System.Collections.Specialized;
using System.Net;
using System.Text;

class UploadValuesTest
{
   public static void Main(string[] argv)
   {
      WebClient wc = new WebClient();
      string uri = "http://localhost/testform.aspx";

      NameValueCollection nvc = new NameValueCollection();

      nvc.Add("lastname", "Blum");
      nvc.Add("firstname", "Rich");

      byte[] response = wc.UploadValues(uri, nvc);
      Console.WriteLine(Encoding.ASCII.GetString(response));
   }
}