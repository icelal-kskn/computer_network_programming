using System;
using System.DirectoryServices;

class BindObject
{
   public static void Main()
   {
      DirectoryEntry de = new DirectoryEntry(
          "LDAP://192.168.1.100/dc=ispnet1, dc=net");

      string ldappath = de.Path;
      Console.WriteLine("The LDAP path is: {0}", ldappath);
      de.Close();
   }
}