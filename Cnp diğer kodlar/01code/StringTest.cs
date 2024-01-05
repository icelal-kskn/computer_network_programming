using System;

class StringTest
{
    public static void Main()
    {
        string test1 = "This is a test string";
        string test2, test3;

        test2 = test1.Insert(15, "application ");
        test3 = test1.ToUpper();

	Console.WriteLine("test1: '{0}'", test1);
        Console.WriteLine("test2: '{0}'", test2);
        Console.WriteLine("test3: '{0}'", test3);

        if (test1 == test3)
            Console.WriteLine("test1 is equal to test3");
        else
            Console.WriteLine("test1 is not equal to test3");
        
        test2 = test1.Replace("test", "sample");
        Console.WriteLine("the new test2: '{0}'", test2);

    }
}
