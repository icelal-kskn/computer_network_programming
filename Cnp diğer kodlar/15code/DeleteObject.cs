using System;
using System.DirectoryServices;

class DeleteObject
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
         badObject.DeleteTree();
         de.CommitChanges();
         Console.WriteLine("the object has been deleted");
      } catch (Exception e)
      {
         Console.WriteLine("the object was not found or deleted:");
         Console.WriteLine(e.ToString());
      }
   }
}