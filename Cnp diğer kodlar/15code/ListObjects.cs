using System;
using System.Collections;
using System.DirectoryServices;

class ListObjects
{
   public static void Main()
   {
      DirectoryEntry de = new DirectoryEntry(
        "LDAP://192.168.1.100/dc=ispnet1, dc=net");

      Console.WriteLine(de.Path);
      DirectoryEntries des = de.Children;
      foreach(DirectoryEntry entry in des)
      {
         Console.WriteLine("  child: " + entry.Name);
      }
   }
}
