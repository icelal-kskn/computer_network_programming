using System;
using System.Drawing;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

class AdvPing : Form
{
   private static int pingstart, pingstop, elapsedtime;
   private static TextBox hostbox, databox;
   private static ListBox results;
   private static Thread pinger;
   private static Socket sock;

   public AdvPing()
   {
      Text = "Advanced Ping Program";
      Size = new Size(400, 380);

      Label label1 = new Label();
      label1.Parent = this;
      label1.Text = "Enter host to ping:";
      label1.AutoSize = true;
      label1.Location = new Point(10, 30);

      hostbox = new TextBox();
      hostbox.Parent = this;
      hostbox.Size = new Size(200, 2 * Font.Height);
      hostbox.Location = new Point(10, 55);

      results = new ListBox();
      results.Parent = this;
      results.Location = new Point(10, 85);
      results.Size = new Size(360, 18 * Font.Height);

      Label label2 = new Label();
      label2.Parent = this;
      label2.Text = "Packet data:";
      label2.AutoSize = true;
      label2.Location = new Point(10, 330);

      databox = new TextBox();
      databox.Parent = this;
      databox.Text = "test packet";
      databox.Size = new Size(200, 2 * Font.Height);
      databox.Location = new Point(80, 325);

      Button sendit = new Button();
      sendit.Parent = this;
      sendit.Text = "Start";
      sendit.Location = new Point(220,52);
      sendit.Size = new Size(5 * Font.Height, 2 * Font.Height);
      sendit.Click += new EventHandler(ButtonSendOnClick);

      Button stopit = new Button();
      stopit.Parent = this;
      stopit.Text = "Stop";
      stopit.Location = new Point(295,52);
      stopit.Size = new Size(5 * Font.Height, 2 * Font.Height);
      stopit.Click += new EventHandler(ButtonStopOnClick);

      Button closeit = new Button();
      closeit.Parent = this;
      closeit.Text = "Close";
      closeit.Location = new Point(300, 320);
      closeit.Size = new Size(5 * Font.Height, 2 * Font.Height);
      closeit.Click += new EventHandler(ButtonCloseOnClick);

      sock = new Socket(AddressFamily.InterNetwork, SocketType.Raw, ProtocolType.Icmp);
      sock.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, 3000);
   }

   void ButtonSendOnClick(object obj, EventArgs ea)
   {
      pinger = new Thread(new ThreadStart(sendPing));
      pinger.IsBackground = true;
      pinger.Start();
   }

   void ButtonStopOnClick(object obj, EventArgs ea)
   {
      pinger.Abort();
   }

   void ButtonCloseOnClick(object obj, EventArgs ea)
   {
      sock.Close();
      Close();
   }

   void sendPing()
   {
      IPHostEntry iphe = Dns.Resolve(hostbox.Text);
      IPEndPoint iep = new IPEndPoint(iphe.AddressList[0], 0);
      EndPoint ep = (EndPoint)iep;
      ICMP packet = new ICMP();
      int recv, i = 1;

      packet.Type = 0x08;
      packet.Code = 0x00;
      Buffer.BlockCopy(BitConverter.GetBytes(1), 0, packet.Message, 0, 2);
      byte[] data = Encoding.ASCII.GetBytes(databox.Text);
      Buffer.BlockCopy(data, 0, packet.Message, 4, data.Length);
      packet.MessageSize = data.Length + 4;
      int packetsize = packet.MessageSize + 4;

      results.Items.Add("Pinging " + hostbox.Text);
      while(true)
      {
         packet.Checksum = 0;
         Buffer.BlockCopy(BitConverter.GetBytes(i), 0, packet.Message, 2, 2);
         UInt16 chcksum = packet.getChecksum();
         packet.Checksum = chcksum;

         pingstart = Environment.TickCount;
         sock.SendTo(packet.getBytes(), packetsize, SocketFlags.None, iep);
         try
         {
            data = new byte[1024];
            recv = sock.ReceiveFrom(data, ref ep);
            pingstop = Environment.TickCount;
            elapsedtime = pingstop - pingstart;
            results.Items.Add("reply from: " + ep.ToString() + ", seq: " + i +
                      ", time = " + elapsedtime + "ms");
         } catch (SocketException)
         {
            results.Items.Add("no reply from host");
         }
         i++;
         Thread.Sleep(3000);
      }
   }

   public static void Main()
   {
      Application.Run(new AdvPing());
   }
}
