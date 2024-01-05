using System;
using System.DirectoryServices;

class RenameObject
{
   public static void Main()
   {
      DirectoryEntry de = new DirectoryEntry(
        "LDAP://192.168.1.100/ou=auditing, ou=accounting, dc=ispnet1, dc=net",
        "cn=Administrator, dc=ispnet1, dc=net", "password",
        AuthenticationTypes.ServerBind);

      DirectoryEntries des = de.Children;
      DirectoryEntry badObject = des.Find("cn=test");
      badObject.Rename("cn=testing");
      de.CommitChanges();
      de.Close();
   }
}