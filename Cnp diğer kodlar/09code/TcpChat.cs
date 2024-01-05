using System;
using System.Drawing;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;


class TcpChat : Form
{
   private static TextBox newText;
   private static ListBox results;
   private static Socket client;
   private static byte[] data = new byte[1024];

   public TcpChat()
   {
      Text = "TCP Chat Program";
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

      Button connect = new Button();
      connect.Parent = this;
      connect.Text = "Connect";
      connect.Location = new Point(295, 20);
      connect.Size = new Size(6 * Font.Height, 2 * Font.Height);
      connect.Click += new EventHandler(ButtonConnectOnClick);

      Button listen = new Button();
      listen.Parent = this;
      listen.Text = "Listen";
      listen.Location = new Point(295,52);
      listen.Size = new Size(6 * Font.Height, 2 * Font.Height);
      listen.Click += new EventHandler(ButtonListenOnClick);
   }

   void ButtonListenOnClick(object obj, EventArgs ea)
   {
      results.Items.Add("Listening for a client...");
      Socket newsock = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
      IPEndPoint iep = new IPEndPoint(IPAddress.Any, 9050);
      newsock.Bind(iep);
      newsock.Listen(5);
      newsock.BeginAccept(new AsyncCallback(AcceptConn), newsock);
   }

   void ButtonConnectOnClick(object obj, EventArgs ea)
   {
      results.Items.Add("Connecting...");
      client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
      IPEndPoint iep = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 9050);
      client.BeginConnect(iep, new AsyncCallback(Connected), client);
   }

   void ButtonSendOnClick(object obj, EventArgs ea)
   {
      byte[] message = Encoding.ASCII.GetBytes(newText.Text);
      newText.Clear();
      client.BeginSend(message, 0, message.Length, 0, new AsyncCallback(SendData), client);
   }

   void AcceptConn(IAsyncResult iar)
   {
      Socket oldserver = (Socket)iar.AsyncState;
      client = oldserver.EndAccept(iar);
      results.Items.Add("Connection from: " + client.RemoteEndPoint.ToString());
      Thread receiver = new Thread(new ThreadStart(ReceiveData));
      receiver.Start();
   }

   void Connected(IAsyncResult iar)
   {
      try
      {
         client.EndConnect(iar);
         results.Items.Add("Connected to: " + client.RemoteEndPoint.ToString());
         Thread receiver = new Thread(new ThreadStart(ReceiveData));
         receiver.Start();

      } catch (SocketException)
      {
         results.Items.Add("Error connecting");
      }
   }

   void SendData(IAsyncResult iar)
   {
      Socket remote = (Socket)iar.AsyncState;
      int sent = remote.EndSend(iar);
   }

   void ReceiveData()
   {
      int recv;
      string stringData;
      while (true)
      {
         recv = client.Receive(data);
         stringData = Encoding.ASCII.GetString(data, 0, recv);
         if (stringData == "bye")
            break;
         results.Items.Add(stringData);
      }
      stringData = "bye";
      byte[] message = Encoding.ASCII.GetBytes(stringData);
      client.Send(message);
      client.Close();
      results.Items.Add("Connection stopped");
      return;
   }

   public static void Main()
   {
      Application.Run(new TcpChat());
   }
}