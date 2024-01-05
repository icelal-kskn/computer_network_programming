using System;
using System.IO;

class TestLog
{
     public static void Main()
    {
        string logFile = "LOGFILE.TXT";

        FileStream fs = new FileStream(logFile,
              FileMode.OpenOrCreate, FileAccess.Write);
        
        StreamWriter sw = new StreamWriter(fs);
        StreamReader sr = new StreamReader(fs);

        sw.WriteLine("First log entry");
        sw.WriteLine("Second log entry");

        while(sr.Peek() > -1)
        {
            Console.WriteLine(sr.ReadLine());
        }

        sw.Close();
        sr.Close();
        fs.Close();
    }
}
