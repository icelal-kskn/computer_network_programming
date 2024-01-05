using System;
using System.DirectoryServices;

class SimpleSearch
{
   public static void Main()
   {
      DirectoryEntry root = new DirectoryEntry(
        "LDAP://192.168.1.100/DC=ispnet1,DC=net",
        "cn=Administrator, dc=ispnet1, dc=net", "password",
        AuthenticationTypes.ServerBind);

      DirectorySearcher searcher = new DirectorySearcher(root);
      searcher.Filter = "(&(objectClass=person)(sn=Blum))";
      searcher.PropertiesToLoad.Add("cn");
      searcher.PropertiesToLoad.Add("telephoneNumber");
      SearchResultCollection results = searcher.FindAll();

      foreach(SearchResult result in results)
      {
         string searchpath = result.Path;
         Console.WriteLine("path: {0}", searchpath);
         ResultPropertyCollection rpc = result.Properties;
         foreach(string property in rpc.PropertyNames)
         {
            foreach(object value in rpc[property])
               Console.WriteLine("  property = {0}  value = {1}", property, value);
         }
      } 
   }
}