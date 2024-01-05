class SampleClass2
{
    static int sampleX;
    static int sampleY;

    public SampleClass2()
    {
	DataClass sample = new DataClass(sampleX, sampleY);
	System.Console.WriteLine("The result is: {0}", sample.addem());
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
	SampleClass2 starthere = new SampleClass2();
    }
}