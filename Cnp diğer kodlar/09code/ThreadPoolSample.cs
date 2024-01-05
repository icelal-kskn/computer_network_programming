using System;
using System.Threading;

class ThreadPoolSample
{

   public static void Main()
   {
      ThreadPoolSample tps = new ThreadPoolSample();
   }

   public ThreadPoolSample()
   {
      int i;

      ThreadPool.QueueUserWorkItem(new WaitCallback(Counter));
      ThreadPool.QueueUserWorkItem(new WaitCallback(Counter2));

      for(i = 0; i < 10; i++)
      {
         Console.WriteLine("main: {0}", i);
         Thread.Sleep(1000);
      }
   }

   void Counter(object state)
   {
      int i;
      for (i = 0; i < 10; i++)
      {
         Console.WriteLine("  thread: {0}", i);
         Thread.Sleep(2000);
      }
   }

   void Counter2(object state)
   {
      int i;
      for (i = 0; i < 10; i++)
      {
         Console.WriteLine("    thread2: {0}", i);
         Thread.Sleep(3000);
      }
   }
}