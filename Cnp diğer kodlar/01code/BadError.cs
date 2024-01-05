using System;

class BadError
{
    public static void Main()
    {
        int var1 = 1000, var2 = 0, var3;

        var3 = var1 / var2;
        Console.WriteLine("The result is: {0}", var3);
    }
}
