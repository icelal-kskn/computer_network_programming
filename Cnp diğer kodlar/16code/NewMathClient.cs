using System;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Http;

public class NewMathClient
{
   public static int Main(string[] argv)
   {
      HttpChannel chan = new HttpChannel();
      ChannelServices.RegisterChannel(chan);
      MathClass obj = new MathClass();
      if (obj == null) 
         System.Console.WriteLine("Could not locate server");
      else
      {
         int a = Convert.ToInt32(argv[0]);
         int b = Convert.ToInt32(argv[1]);
         int c = obj.Add(a, b);
         Console.WriteLine("a + b = {0}", c);
         c = obj.Subtract(a, b);
         Console.WriteLine("a - b = {0}", c);
         c = obj.Multiply(a, b);
         Console.WriteLine("a * b = {0}", c);
         c = obj.Divide(a, b);
         Console.WriteLine("a / b = {0}", c);
      }
      return 0;
    } 
}