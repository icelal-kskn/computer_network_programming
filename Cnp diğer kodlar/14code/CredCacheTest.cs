using System;
using System.Net;
using System.Text;

class CredCacheTest
{
   public static void Main()
   {
      WebClient wc = new WebClient();
      string website1 = "http://remote1.ispnet.net";
      string website2 = "http://remote2.ispnet.net";
      string website3 = "http://remote3.ispnet.net/login";


      NetworkCredential nc1 = new NetworkCredential("mike", "guitars");
      NetworkCredential nc2 = new NetworkCredential("evonne", "singing", "home");
      NetworkCredential nc3 = new NetworkCredential("alex", "drums");

      CredentialCache cc = new CredentialCache();
      cc.Add(new Uri(website1), "Basic", nc1);
      cc.Add(new Uri(website2), "Basic", nc2);
      cc.Add(new Uri(website3), "Digest", nc3);

      wc.Credentials = cc;

      wc.DownloadFile(website1, "website1.htm");
      wc.DownloadFile(website2, "website2.htm");
      wc.DownloadFile(website3, "website3.htm");
   }
}