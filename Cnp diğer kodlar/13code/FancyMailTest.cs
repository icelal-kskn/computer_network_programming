using System;
using System.Web.Mail;

class FancyMailTest
{
   public static void Main()
   {
      MailMessage mm = new MailMessage();
      mm.From = "haley@myisp.net";
      mm.To = "riley@yourisp.net;rich@shadrach.ispnet1.net";
      mm.Cc = "matthew@anotherisp.net;chris@hisisp.net";
      mm.Bcc = "katie@herisp.net;jessica@herisp.net";
      mm.Subject = "This is a fancy test message";
      mm.Headers.Add("Reply-To", "haley@myisp.net");
      mm.Headers.Add("Comments", "This is a test HTML message");
      mm.Priority = MailPriority.High;
      mm.BodyFormat = MailFormat.Html;
      mm.Body = "<html><body><h1>This is a test message</h1><h2>This message should have HTML-type formatting</h2>Please use an HTML-capable viewer.";

      try
      {
         SmtpMail.Send(mm);
      } catch (System.Web.HttpException)
      {
         Console.WriteLine("This device is unable to send Internet messages");
      }
   }
}