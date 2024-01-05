using System;
using System.Drawing;
using System.Windows.Forms;


class WindowSample : Form
{
   private TextBox data;
   private ListBox results;

   public WindowSample()
   {
      Text = "Sample Window Program";
      Size = new Size(400, 380);

      Label label1 = new Label();
      label1.Parent = this;
      label1.Text = "Enter text string:";
      label1.AutoSize = true;
      label1.Location = new Point(10, 10);

      data = new TextBox();
      data.Parent = this;
      data.Size = new Size(200, 2 * Font.Height);
      data.Location = new Point(10, 35);

      results = new ListBox();
      results.Parent = this;
      results.Location = new Point(10, 65);
      results.Size = new Size(350, 20 * Font.Height);

      Button checkit = new Button();
      checkit.Parent = this;
      checkit.Text = "test";
      checkit.Location = new Point(235,32);
      checkit.Size = new Size(7 * Font.Height, 2 * Font.Height);
      checkit.Click += new EventHandler(ButtonOnClick);
   }

   void ButtonOnClick(object obj, EventArgs ea)
   {
      results.Items.Add(data.Text);
      data.Clear();
   }

   public static void Main()
   {
      Application.Run(new WindowSample());
   }
}