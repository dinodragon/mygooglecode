using System;
using System.Collections;
using System.Data;
using System.ComponentModel;
using System.Reflection;
using System.Text;
using System.Web.Mail;
using System.Data.SqlClient;
using System.IO;

using ePub.Server.Mail.Core;

namespace ePub.Server.Mail.Service
{
    public class Mail
    {
        private string mailServer = "";
        private string mailUser = "";
        private string mailPassword = "";
        private string mailFrom = "";

        public Mail(string server,string user,string password,string from)
        {
            mailServer = server;
            mailUser = user;
            mailPassword = password;
            mailFrom = from;
        }

        public Mail()
        {

        }

        public bool send(string to, string body, string subject)
        {
            return send(to, body, subject, new ArrayList());
        }

        public void ThreadPoolCallback(Object threadContext)
        {
            Log.Write("Mail.ThreadPoolCallback开始处理消息:" + threadContext.ToString());
            System.Threading.Thread.Sleep(3000);
            Log.Write("Mail.ThreadPoolCallback消息处理结束:" + threadContext.ToString());
            return;
        }

        private bool send(string to, string body, string subject, ArrayList attachments)
        {
            try
            {
                System.Web.Mail.MailMessage mailMessage = new System.Web.Mail.MailMessage();
                mailMessage.From = mailFrom;
                //mailMessage.To = to;
                mailMessage.Cc = to;
                mailMessage.Body = body;
                mailMessage.BodyFormat = MailFormat.Html;
                mailMessage.Subject = subject;
                for (int i = 0; i < attachments.Count; i++)
                {
                    if (!File.Exists(attachments[i].ToString()))
                    {
                        return false;
                    }
                }
                for (int i = 0; i < attachments.Count; i++)
                {
                    if (File.Exists(attachments[i].ToString()))
                    {
                        mailMessage.Attachments.Add(new System.Web.Mail.MailAttachment(attachments[i].ToString()));
                    }
                }
                mailMessage.Fields.Add("http://schemas.microsoft.com/cdo/configuration/smtpauthenticate", "1");
                mailMessage.Fields.Add("http://schemas.microsoft.com/cdo/configuration/sendusername", mailUser);
                mailMessage.Fields.Add("http://schemas.microsoft.com/cdo/configuration/sendpassword", mailPassword);
                System.Web.Mail.SmtpMail.SmtpServer = mailServer;
                System.Web.Mail.SmtpMail.Send(mailMessage);
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }

        private bool send(string from, string fromName, string to, string toName, string body, string subject, ArrayList attachments)
        {
            try
            {
                System.Web.Mail.MailMessage mailMessage = new System.Web.Mail.MailMessage();
                mailMessage.From = from;
                mailMessage.To = to;
                mailMessage.Body = body;
                mailMessage.BodyFormat = MailFormat.Html;
                mailMessage.Subject = subject;
                for (int i = 0; i < attachments.Count; i++)
                {
                    if (!File.Exists(attachments[i].ToString()))
                    {
                        return false;
                    }
                }
                for (int i = 0; i < attachments.Count; i++)
                {
                    if (File.Exists(attachments[i].ToString()))
                    {
                        mailMessage.Attachments.Add(new System.Web.Mail.MailAttachment(attachments[i].ToString()));
                    }
                }
                //是否需要验证，一般是要的 
                mailMessage.Fields.Add("http://schemas.microsoft.com/cdo/configuration/smtpauthenticate", "1");
                //自己邮箱的用户名 
                mailMessage.Fields.Add("http://schemas.microsoft.com/cdo/configuration/sendusername", mailUser);
                //自己邮箱的密码 
                mailMessage.Fields.Add("http://schemas.microsoft.com/cdo/configuration/sendpassword", mailPassword);
                System.Web.Mail.SmtpMail.SmtpServer = mailServer;
                System.Web.Mail.SmtpMail.Send(mailMessage);
            }
            catch (Exception /*ex*/)
            {
                return false;
            }
            return true;
        }

    }
}