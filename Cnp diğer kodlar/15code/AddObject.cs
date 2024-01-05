using System;
using System.DirectoryServices;

class AddObject
{
   public static void Main()
   {
      DirectoryEntry de = new DirectoryEntry(
        "LDAP://192.168.1.100/ou=accounting, dc=ispnet1, dc=net",
         "cn=Administrator, dc=ispnet1, dc=net", "password",
         AuthenticationTypes.ServerBind);

      DirectoryEntries children = de.Children;
      DirectoryEntry newchild = children.Add("ou=auditing", de.SchemaClassName);
      newchild.Properties["ou"].Add("Auditing Department");
      newchild.CommitChanges();
      newchild.Close();
      de.Close();

      DirectoryEntry de2 = new DirectoryEntry(
       "LDAP://192.168.1.100/ou=auditing, dc=accounting, dc=ispnet1, dc=net");
      string newpath = de2.Path;
      Console.WriteLine("new path: {0}", newpath);
      de2.Close();
   }
}