using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ePub.Server.Mail.Core;

namespace MailServiceClient
{
    class Program
    {
        static void Main(string[] args)
        {
            IMailService service = ePub.Server.Mail.Core.ClientServices.GetService<IMailService>("SendMailClient");
            Console.WriteLine("Client Started,input Message,when input end to stop");
            string input;
            while ((input = Console.ReadLine()) != "end")
            {
                for (int i = 1; i < 101; i++)
                {
                    service.SendMail(i.ToString() + ". " + input);
                }
            }
        }
    }
}
