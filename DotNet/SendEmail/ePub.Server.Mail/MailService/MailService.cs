using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.Threading;

using ePub.Server.Mail.Core;

namespace ePub.Server.Mail.Service
{
    public class MailService : IMailService
    {
        public void SendMail(string pattern)
        {
            Log.Write("MailService.SendMail:开始处理消息：" + pattern);
            Thread.Sleep(3000);
            Log.Write("MailService.SendMail:处理消息结束：" + pattern);
            //ThreadPool.QueueUserWorkItem(new Mail().ThreadPoolCallback,pattern);
        }
    }
}
