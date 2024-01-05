using System;

class ServiceTest
{
   public static void Main(string[] argv)
   {
      MathService ms = new MathService();

      int x = Convert.ToInt16(argv[0]);
      int y = Convert.ToInt16(argv[1]);

      int sum = ms.Add(x, y);
      int sub = ms.Subtract(x, y);
      int mult = ms.Multiply(x, y);
      int div = ms.Divide(x, y);
      Console.WriteLine("The answers are:");
      Console.WriteLine("  {0} + {1} = {2}", x, y, sum);
      Console.WriteLine("  {0} - {1} = {2}", x, y, sub);
      Console.WriteLine("  {0} * {1} = {2}", x, y, mult);
      Console.WriteLine("  {0} / {1} = {2}", x, y, div);
   }
}