using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class FindMask
{
   public static void Main()
   {
      byte[] data = new byte[1024];
      int recv;
      Socket host = new Socket(AddressFamily.InterNetwork, SocketType.Raw, ProtocolType.Icmp);
      IPEndPoint iep = new IPEndPoint(IPAddress.Broadcast, 0);
      EndPoint ep = (EndPoint)iep;
      ICMP packet = new ICMP();

      packet.Type = 0x11;
      packet.Code = 0x00;
      packet.Checksum = 0;
      Buffer.BlockCopy(BitConverter.GetBytes(1), 0, packet.Message, 0, 2);
      Buffer.BlockCopy(BitConverter.GetBytes(1), 0, packet.Message, 2, 2);
      Buffer.BlockCopy(BitConverter.GetBytes(0), 0, packet.Message, 4, 4);
      packet.MessageSize = 8;
      int packetsize = packet.MessageSize + 4;

      UInt16 chksm = packet.getChecksum();
      packet.Checksum = chksm;

      host.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, 3000);
      host.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Broadcast, 1);
      host.SendTo(packet.getBytes(), packetsize, SocketFlags.None, iep);
      try
      {
         data = new byte[1024];
         recv = host.ReceiveFrom(data, ref ep);
      } catch (SocketException)
      {
         Console.WriteLine("Unable to determine subnet mask for this subnet");
         return;
      }
      ICMP response = new ICMP(data, recv);
      Console.WriteLine("Received ICMP Type {0} packet", response.Type);
      long answer = BitConverter.ToUInt32(response.Message, 4);
      IPAddress netmask = new IPAddress(answer);
      Console.WriteLine("The subnet mask for this subnet is: {0}", netmask.ToString());
   }
}