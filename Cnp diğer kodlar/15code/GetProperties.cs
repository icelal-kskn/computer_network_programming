using System;
using System.DirectoryServices;

class GetProperties
{
   public static void Main()
   {
      DirectoryEntry de = new DirectoryEntry(
         "LDAP://192.168.1.100/cn=kblum, ou=sales, dc=ispnet1, dc=net");
      Console.WriteLine("object: {0}", de.Path);
      PropertyCollection pc = de.Properties;
      foreach(string propName in pc.PropertyNames)
      {
         foreach(object value in de.Properties[propName])
            Console.WriteLine("  property = {0}   value = {1}",
               propName, value);
      }
   }
}