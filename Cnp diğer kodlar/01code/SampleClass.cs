using System;

class DataClass
{
    private int a;
    private int b;

    public DataClass(int x, int y)
    {
	a = x;
	b = y;
    }

    public int addem()
    {
	return a + b;
    }
}

class SampleClass
{
    static int sampleX;
    static int sampleY;

    public SampleClass()
    {
	DataClass sample = new DataClass(sampleX, sampleY);
	Console.WriteLine("The result is: {0}", sample.addem());
    }

    public static void Main(string[] argv)
    {
	if (argv.Length != 2)
	{
	    System.Console.WriteLine("  Usage: SampleClass x y");
	    return;
	}
	sampleX = System.Convert.ToInt16(argv[0]);
	sampleY = System.Convert.ToInt16(argv[1]);
	SampleClass starthere = new SampleClass();
    }
}