using System;
using System.Diagnostics;

class GetProc
{
   public static void Main()
   {
      Process thisProc = Process.GetCurrentProcess();

      string procName = thisProc.ProcessName;
      DateTime started = thisProc.StartTime;
      int procID = thisProc.Id;
      int memory = thisProc.VirtualMemorySize;
      int priMemory = thisProc.PrivateMemorySize;
      int physMemory = thisProc.WorkingSet;
      int priority = thisProc.BasePriority;
      ProcessPriorityClass priClass = thisProc.PriorityClass;
      TimeSpan cpuTime = thisProc.TotalProcessorTime;


      Console.WriteLine("Process: {0}, ID: {1}", procName, procID);
      Console.WriteLine("    started: {0}", started.ToString());
      Console.WriteLine("    CPU time: {0}", cpuTime.ToString());
      Console.WriteLine("    priority class: {0}  priority: {1}", priClass, priority);
      Console.WriteLine("    virtual memory: {0}", memory);
      Console.WriteLine("    private memory: {0}", priMemory);
      Console.WriteLine("    physical memory: {0}", physMemory);

      Console.WriteLine("\n    trying to change priority...");
      thisProc.PriorityClass = ProcessPriorityClass.High;
      priClass = thisProc.PriorityClass;
      Console.WriteLine("    new priority class: {0}", priClass);
   }
}