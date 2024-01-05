using System;
using System.Net;
using System.Text;

class BinaryDataTest
{
   public static void Main()
   {
      int test1 = 45;
      double test2 = 3.14159;
      int test3 = -1234567890;
      bool test4 = false;
      byte[] data = new byte[1024];
      string output;

      data = BitConverter.GetBytes(test1);
      output = BitConverter.ToString(data);
      Console.WriteLine("test1 = {0}, string = {1}", test1, output);

      data = BitConverter.GetBytes(test2);
      output = BitConverter.ToString(data);
      Console.WriteLine("test2 = {0}, string = {1}", test2, output);

      data = BitConverter.GetBytes(test3);
      output = BitConverter.ToString(data);
      Console.WriteLine("test3 = {0}, string = {1}", test3, output);

      data = BitConverter.GetBytes(test4);
      output = BitConverter.ToString(data);
      Console.WriteLine("test4 = {0}, string = {1}", test4, output);
   }
}