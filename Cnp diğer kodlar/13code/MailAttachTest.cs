using System;
using System.Web.Mail;

class MailAttachTest
{
   public static void Main()
   {

      MailAttachment myattach =
          new MailAttachment("c:\\temp\\MailAttachTest.exe", MailEncoding.Base64);
      MailMessage newmessage = new MailMessage();
      newmessage.From = "barbara@shadrach.ispnet1.net";
      newmessage.To = "rich@shadrach.ispnet1.net";
      newmessage.Subject = "A test mail attachment message";
      newmessage.Priority = MailPriority.High;
      newmessage.Headers.Add("Comments",
                 "This message attempts to send a binary attachment");
      newmessage.Attachments.Add(myattach);
      newmessage.Body = "Here's a test file for you to try";

      try
      {
         SmtpMail.SmtpServer = "192.168.1.100";
         SmtpMail.Send(newmessage);
      } catch (System.Web.HttpException)
      {
         Console.WriteLine("This device can not send Internet messages");
      }
   }
}