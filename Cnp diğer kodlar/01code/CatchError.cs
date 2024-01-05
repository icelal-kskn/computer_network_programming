using System;

class CatchError
{
    public static void Main()
    {
        int var1 = 1000, var2 = 0, var3;

        try
        {
            var3 = var1 / var2;
        }
        catch (ArithmeticException e)
        {
            Console.WriteLine("Exception: {0}", e.ToString());
	    var3 = -1;
        }
        catch (Exception e)
        {
            Console.WriteLine("Exception: {0}", e.ToString());
	    var3 = -2;
        }
	Console.WriteLine("The result is: {0}", var3);
    }
}
