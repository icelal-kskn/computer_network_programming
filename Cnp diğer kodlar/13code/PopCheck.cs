using System;
using System.Drawing;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

class PopCheck : Form
{
   private TextBox hostname;
   private TextBox username;
   private TextBox password;
   private TextBox status;
   private ListBox messages;

   private TcpClient mailclient;
   private NetworkStream ns;
   private StreamReader sr;
   private StreamWriter sw;

   public PopCheck()
   {
      Text = "popcheck - A POP3 e-mail checker";
      Size = new Size(400, 380);

      Label label1 = new Label();
      label1.Parent = this;
      label1.Text = "Hostname:";
      label1.AutoSize = true;
      label1.Location = new Point(10, 33);

      hostname = new TextBox();
      hostname.Parent = this;
      hostname.Size = new Size(200, 2 * Font.Height);
      hostname.Location = new Point(75, 30);

      Label label2 = new Label();
      label2.Parent = this;
      label2.Text = "User name:";
      label2.AutoSize = true;
      label2.Location = new Point(10, 53);

      username = new TextBox();
      username.Parent = this;
      username.Size = new Size(200, 2 * Font.Height);
      username.Location = new Point(75, 50);

      Label label3 = new Label();
      label3.Parent = this;
      label3.Text = "Password:";
      label3.AutoSize = true;
      label3.Location = new Point(10, 73);

      password = new TextBox();
      password.Parent = this;
      password.PasswordChar = '*';
      password.Size = new Size(200, 2 * Font.Height);
      password.Location = new Point(75, 70);

      Label label4 = new Label();
      label4.Parent = this;
      label4.Text = "Status:";
      label4.AutoSize = true;
      label4.Location = new Point(10, 325);
     
      status = new TextBox();
      status.Parent = this;
      status.Text = "Not connected";
      status.Size = new Size(200, 2 * Font.Height);
      status.Location = new Point(50, 322);

      messages = new ListBox();
      messages.Parent = this;
      messages.Location = new Point(10, 108);
      messages.Size = new Size(360, 16 * Font.Height);
      messages.DoubleClick += new EventHandler(getmessagesDoubleClick);

      Button login = new Button();
      login.Parent = this;
      login.Text = "Login";
      login.Location = new Point(295, 32);
      login.Size = new Size(5 * Font.Height, 2 * Font.Height);
      login.Click += new EventHandler(ButtonloginOnClick);

      Button close = new Button();
      close.Parent = this;
      close.Text = "Close";
      close.Location = new Point(295, 62);
      close.Size = new Size(5 * Font.Height, 2 * Font.Height);
      close.Click += new EventHandler(ButtoncloseOnClick);
    }

   void ButtonloginOnClick(object obj, EventArgs ea)
   {
      status.Text = "Checking for messages...";
      Thread startlogin = new Thread(new ThreadStart(loginandretr));
      startlogin.IsBackground = true;
      startlogin.Start();
   }

   void ButtoncloseOnClick(object obj, EventArgs ea)
   {
      if (ns != null)
      {
         sw.Close();
         sr.Close();
         ns.Close();
         mailclient.Close();
      }
      Close();
   }

   void loginandretr()
   {
      string response;
      string from = null;
      string subject = null;
      int totmessages;

      try
      {
         mailclient = new TcpClient(hostname.Text, 110);
      } catch (SocketException)
      {
         status.Text = "Unable to connect to server";
         return;
      }

      ns = mailclient.GetStream();
      sr = new StreamReader(ns);
      sw = new StreamWriter(ns);

      response = sr.ReadLine(); //Get opening POP3 banner

      sw.WriteLine("User " + username.Text); //Send username
      sw.Flush();

      response = sr.ReadLine();
      if (response.Substring(0,4) == "-ERR")
      {
         status.Text = "Unable to log into server";
         return;
      }

      sw.WriteLine("Pass " + password.Text);  //Send password
      sw.Flush();

      try
      {
         response = sr.ReadLine();
      } catch (IOException)
      {
         status.Text = "Unable to log into server";
         return;
      }
      if (response.Substring(0,3) == "-ER")
      {
         status.Text = "Unable to log into server";
         return;
      }

      sw.WriteLine("stat"); //Send stat command to get number of messages
      sw.Flush();

      response = sr.ReadLine();
      string[] nummess = response.Split(' ');
      totmessages = Convert.ToInt16(nummess[1]);
      if (totmessages > 0)
      {
         status.Text = "you have " + totmessages + " messages";
      } else
      {
         status.Text = "You have no messages" ;
      }

      for (int i = 1; i <= totmessages; i++)
      {
         sw.WriteLine("top " + i + " 0"); //read header of each message
         sw.Flush();
         response = sr.ReadLine();

         while (true)
         {
            response = sr.ReadLine();
            if (response == ".")
               break;
            if (response.Length > 4)
            {
               if (response.Substring(0, 5) == "From:")
                  from = response;
               if (response.Substring(0, 8) == "Subject:")
                  subject = response;
            }
         }
         messages.Items.Add(i + "  " + from + "  " + subject);
      }

   }

   void getmessagesDoubleClick(object obj, EventArgs ea)
   {
      string text = (string)messages.SelectedItem;
      string[] textarray = text.Split(' ');
      ShowMessage sm = new ShowMessage(ns, textarray[0]);
      sm.ShowDialog();
   }

   public static void Main()
   {
      Application.Run(new PopCheck());
   }
}

class ShowMessage : Form
{
   public ShowMessage(NetworkStream ns, string messnumber)
   {
      StreamReader sr = new StreamReader(ns);
      StreamWriter sw = new StreamWriter(ns);
      string response;

      Text = "Message " + messnumber;
      Size = new Size(400, 380);
      ShowInTaskbar = false;

      TextBox display = new TextBox();
      display.Parent = this;
      display.Multiline = true;
      display.Dock = DockStyle.Fill;
      display.ScrollBars = ScrollBars.Both;

      sw.WriteLine("retr " + messnumber); //Retrieve entire message
      sw.Flush();
      response = sr.ReadLine();

      while (true)
      {
         response = sr.ReadLine();
         if (response == ".")
            break;
         display.Text += response + "\r\n";
      }
   }
}