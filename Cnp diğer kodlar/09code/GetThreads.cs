using System;
using System.Diagnostics;

class GetThreads
{
   public static void Main()
   {

      Process thisProc = Process.GetCurrentProcess();
      ProcessThreadCollection myThreads = thisProc.Threads;

      foreach(ProcessThread pt in myThreads)
      {
         DateTime startTime = pt.StartTime;
         TimeSpan cpuTime = pt.TotalProcessorTime;
         int priority = pt.BasePriority;
         ThreadState ts = pt.ThreadState;

         Console.WriteLine("thread:  {0}", pt.Id);
         Console.WriteLine("    started: {0}", startTime.ToString());
         Console.WriteLine("    CPU time: {0}", cpuTime);
         Console.WriteLine("    priority: {0}", priority);
         Console.WriteLine("    thread state: {0}", ts.ToString()); 
      }
   }
}