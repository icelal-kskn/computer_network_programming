using System;
using System.DirectoryServices;

class ModifyProperty
{
   public static void Main()
   {
      DirectoryEntry de = new DirectoryEntry(
         "LDAP://192.168.1.100/cn=kblum, ou=sales, dc=ispnet1, dc=net",
         "cn=Administrator, dc=ispnet1, dc=net", "password",
          AuthenticationTypes.ServerBind);

      de.Properties["sn"][0] = "Mullen";
      de.CommitChanges();
      Console.WriteLine("New property value: {0}", de.Properties["sn"][0]);
      de.Close();
   }
}
