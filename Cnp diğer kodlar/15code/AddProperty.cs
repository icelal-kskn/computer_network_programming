using System;
using System.DirectoryServices;

class AddProperty
{
   public static void Main()
   {
      DirectoryEntry de = new DirectoryEntry(
        "LDAP://192.168.1.100/cn=kblum, ou=sales, dc=ispnet1, dc=net",
        "cn=Administrator, dc=ispnet1, dc=net","password",
        AuthenticationTypes.ServerBind);

      de.Properties["telephoneNumber"].Add("(111)222-3333");
      de.Properties["telephoneNumber"].Add("(444)555-6666");
      de.CommitChanges();
      de.Close();
   }
}