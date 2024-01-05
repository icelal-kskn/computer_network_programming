using System;
using System.DirectoryServices;

class RemoveObject
{
   public static void Main()
   {
      DirectoryEntry de = new DirectoryEntry(
        "LDAP://192.168.1.100/ou=accounting, dc=ispnet1, dc=net",
         "cn=Administrator, dc=ispnet1, dc=net", "password",
         AuthenticationTypes.ServerBind);

      DirectoryEntries children = de.Children;
      try
      {
         DirectoryEntry badObject = children.Find("ou=auditing");
         children.Remove(badObject);
         de.CommitChanges();
         Console.WriteLine("the object was removed");
      } catch (Exception)
      {
         Console.WriteLine("the object was not found");
      }
   }
}