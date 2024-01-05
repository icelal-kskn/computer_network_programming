using System;
using System.Runtime.Remoting;
using System.Runtime.Remoting.Channels;
using System.Runtime.Remoting.Channels.Http;


public class MathServer
{
   public static int Main()
   {
      HttpChannel chan = new HttpChannel(9050);
      ChannelServices.RegisterChannel(chan);
      RemotingConfiguration.RegisterWellKnownServiceType(
         Type.GetType("MathClass, MathClass"), "MyMathServer",
         WellKnownObjectMode.SingleCall);
      Console.WriteLine("Hit <enter> to exit...");
      Console.ReadLine();
      return 0;
    }
}