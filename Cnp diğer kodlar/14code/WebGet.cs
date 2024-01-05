using System;
using System.Drawing;
using System.IO;
using System.Net;
using System.Windows.Forms;

class WebGet : Form
{
   private TextBox uribox;
   private ListBox headers;
   private ListBox cookies;
   private ListBox response;

   public WebGet()
   {
      Text = "WebGet - a web page retriever";
      Size = new Size(500, 450);

      Label label1 = new Label();
      label1.Parent = this;
      label1.Text = "URI:";
      label1.AutoSize = true;
      label1.Location = new Point(10, 23);

      uribox = new TextBox();
      uribox.Parent = this;
      uribox.Size = new Size(200, 2 * Font.Height);
      uribox.Location = new Point(35, 20);

      Label label2 = new Label();
      label2.Parent = this;
      label2.Text = "Headers:";
      label2.AutoSize = true;
      label2.Location = new Point(10, 46);

      headers = new ListBox();
      headers.Parent = this;
      headers.HorizontalScrollbar = true;
      headers.Location = new Point(10, 65);
      headers.Size = new Size(450, 6 * Font.Height);

      Label label3 = new Label();
      label3.Parent = this;
      label3.Text = "Cookies:";
      label3.AutoSize = true;
      label3.Location = new Point(10, 70 + 6 * Font.Height);

      cookies = new ListBox();
      cookies.Parent = this;
      cookies.HorizontalScrollbar = true;
      cookies.Location = new Point(10, 70 + 7 * Font.Height);
      cookies.Size = new Size(450, 6 * Font.Height);

      Label label4 = new Label();
      label4.Parent = this;
      label4.Text = "HTML:";
      label4.AutoSize = true;
      label4.Location = new Point(10, 70 + 13 * Font.Height);

      response = new ListBox();
      response.Parent = this;
      response.HorizontalScrollbar = true;
      response.Location = new Point(10, 70 + 14 * Font.Height);
      response.Size = new Size(450, 12 * Font.Height);


      Button sendit = new Button();
      sendit.Parent = this;
      sendit.Text = "GetIt";
      sendit.Location = new Point(275, 18);
      sendit.Size = new Size(7 * Font.Height, 2 * Font.Height);
      sendit.Click += new EventHandler(ButtongetitOnClick);
   }

   void ButtongetitOnClick(object obj, EventArgs ea)
   {
      headers.Items.Clear();
      cookies.Items.Clear();
      response.Items.Clear();

      HttpWebRequest hwr = (HttpWebRequest)WebRequest.Create(uribox.Text);
      hwr.CookieContainer = new CookieContainer();
      HttpWebResponse hwrsp = (HttpWebResponse)hwr.GetResponse();
      WebHeaderCollection whc = hwrsp.Headers;
      for (int i = 0; i < whc.Count; i++)
      {
         headers.Items.Add(whc.GetKey(i) + " = " + whc.Get(i));
      }

      hwrsp.Cookies = hwr.CookieContainer.GetCookies(hwr.RequestUri);
      foreach(Cookie cky in hwrsp.Cookies)
      {
         cookies.Items.Add(cky.Name + " = " + cky.Value);
      }

      Stream strm = hwrsp.GetResponseStream();
      StreamReader sr = new StreamReader(strm);

      while (sr.Peek() > -1)
      {
         response.Items.Add(sr.ReadLine());
      }
      sr.Close();
      strm.Close();
   }

   public static void Main()
   {
      Application.Run(new WebGet());
   }
}