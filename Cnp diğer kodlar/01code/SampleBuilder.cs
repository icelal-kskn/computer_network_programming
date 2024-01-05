using System;
using System.Text;

class SampleBuilder
{

    public static void Main()
    {

	StringBuilder sb = new StringBuilder("test string");
	int length = 0;

	length = sb.Length;
	Console.WriteLine("The result is: '{0}'", sb);
	Console.WriteLine("The length is: {0}", length);

	sb.Length = 4;
	length = sb.Length;
	Console.WriteLine("The result is: '{0}'", sb);
	Console.WriteLine("The length is: {0}", length);

	sb.Length = 20;
	length = sb.Length;
	Console.WriteLine("The result is: '{0}'", sb);
	Console.WriteLine("The length is: {0}", length);

    }
}