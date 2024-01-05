using System;
using System.Drawing;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

class MulticastChat : Form
{
   TextBox newText;
   ListBox results;
   Socket sock;
   Thread receiver;
   IPEndPoint multiep = new IPEndPoint(IPAddress.Parse("224.100.0.1"), 9050);

   public MulticastChat()
   {
      Text = "Multicast Chat Program";
      Size = new Size(400, 380);

      Label label1 = new Label();
      label1.Parent = this;
      label1.Text = "Enter text string:";
      label1.AutoSize = true;
      label1.Location = new Point(10, 30);

      newText = new TextBox();
      newText.Parent = this;
      newText.Size = new Size(200, 2 * Font.Height);
      newText.Location = new Point(10, 55);

      results = new ListBox();
      results.Parent = this;
      results.Location = new Point(10, 85);
      results.Size = new Size(360, 18 * Font.Height);

      Button sendit = new Button();
      sendit.Parent = this;
      sendit.Text = "Send";
      sendit.Location = new Point(220,52);
      sendit.Size = new Size(5 * Font.Height, 2 * Font.Height);
      sendit.Click += new EventHandler(ButtonSendOnClick);

      Button closeit = new Button();
      closeit.Parent = this;
      closeit.Text = "Close";
      closeit.Location = new Point(290, 52);
      closeit.Size = new Size(5 * Font.Height, 2 * Font.Height);
      closeit.Click += new EventHandler(ButtonCloseOnClick);

      sock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
      IPEndPoint iep = new IPEndPoint(IPAddress.Any, 9050);
      sock.Bind(iep);
      sock.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.AddMembership, new MulticastOption(IPAddress.Parse("224.100.0.1")));
      receiver = new Thread(new ThreadStart(packetReceive));
      receiver.IsBackground = true;
      receiver.Start();
   }

   void ButtonSendOnClick(object obj, EventArgs ea)
   {
      byte[] message = Encoding.ASCII.GetBytes(newText.Text);
      newText.Clear();
      sock.SendTo(message, SocketFlags.None, multiep);
   }

   void ButtonCloseOnClick(object obj, EventArgs ea)
   {
      receiver.Abort();
      sock.Close();
      Close();
   }

   void packetReceive()
   {
      EndPoint ep = (EndPoint)multiep;
      byte[] data = new byte[1024];
      string stringData;
      int recv;
      while (true)
      {
         recv = sock.ReceiveFrom(data, ref ep);
         stringData = Encoding.ASCII.GetString(data, 0, recv);
         results.Items.Add("from " + ep.ToString() + ":  " + stringData);
      }
   }

   public static void Main()
   {
      Application.Run(new MulticastChat());
   }
}