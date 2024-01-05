using System;
using System.Net;
using System.Web.Mail;

class MailTest
{
   public static void Main()
   {
      string from = "jessica@myisp.net";
      string to = "katie@anotherisp.net";
      string subject = "This is a test mail message";
      string body = "Hi Katie, I hope things are going well today.";

      SmtpMail.SmtpServer = "192.168.1.150";
      SmtpMail.Send(from, to, subject, body);
   }
}