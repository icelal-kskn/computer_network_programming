using System;
using System.Drawing;
using System.IO;
using System.Threading;
using System.Windows.Forms;

class CiscoRouter : Form
{

   private TextBox host;
   private TextBox community;
   private ListBox results;
   private Thread monitor;
   private FileStream fs;
   private StreamWriter sw;

   public CiscoRouter()
   {
      Text = "Cisco Router Utilization";
      Size = new Size(400, 380);

      Label label1 = new Label();
      label1.Parent = this;
      label1.Text = "Host:";
      label1.AutoSize = true;
      label1.Location = new Point(10, 30);

      host = new TextBox();
      host.Parent = this;
      host.Size = new Size(170, 2 * Font.Height);
      host.Location = new Point(40, 27);

      Label label2 = new Label();
      label2.Parent = this;
      label2.Text = "Community:";
      label2.AutoSize = true;
      label2.Location = new Point(10, 60);

      community = new TextBox();
      community.Parent = this;
      community.Size = new Size(170, 2 * Font.Height);
      community.Location = new Point(75, 57);

      results = new ListBox();
      results.Parent = this;
      results.Location = new Point(10, 85);
      results.Size = new Size(360, 18 * Font.Height);

      Button start = new Button();
      start.Parent = this;
      start.Text = "Start";
      start.Location = new Point(250, 52);
      start.Size = new Size(5 * Font.Height, 2 * Font.Height);
      start.Click += new EventHandler(ButtonStartOnClick);

      Button stop = new Button();
      stop.Parent = this;
      stop.Text = "Stop";
      stop.Location = new Point(320, 52);
      stop.Size = new Size(5 * Font.Height, 2 * Font.Height);
      stop.Click += new EventHandler(ButtonStopOnClick);
   }

   void ButtonStartOnClick(Object obj, EventArgs ea)
   {
      monitor = new Thread(new ThreadStart(checkRouter));
      monitor.IsBackground = true;
      monitor.Start();
   }

   void ButtonStopOnClick(Object obj, EventArgs ea)
   {
      monitor.Abort();
      sw.Close();
      fs.Close();
   }

   void checkRouter()
   {
      int commlength, miblength, datastart, cpuUtil;
      SNMP conn = new SNMP();
      byte[] response = new byte[1024];
      DateTime time;
      string logFile = "routerlog.txt";
      fs = new FileStream(logFile, FileMode.OpenOrCreate,
            FileAccess.ReadWrite);
      sw = new StreamWriter(fs);

      while (true)
      {
         response = conn.get("get", host.Text,
             community.Text, "1.3.6.1.4.1.9.2.1.58.0");
         if (response[0] == 0xff)
         {
            results.Items.Add("No reponse from host");
            sw.WriteLine("No response from host");
            sw.Flush();
            break;
         }
         commlength = Convert.ToInt16(response[6]);
         miblength = Convert.ToInt16(response[23 + commlength]);
         datastart = 26 + commlength + miblength;

         cpuUtil = Convert.ToInt16(response[datastart]);
         time = DateTime.Now;
         results.Items.Add(time + " CPU Utilization: " + cpuUtil + "%");
         sw.WriteLine("{0} CPU Utilization: {1}%", time, cpuUtil);
         sw.Flush();
         Thread.Sleep(5 * 60000);
      }
   }

   public static void Main()
   {
      Application.Run(new CiscoRouter());
   }
}