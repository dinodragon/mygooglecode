using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace ePub.Server.Mail.Core
{
    public class Log
    {
        static public void Write(string msg)
        {
            Console.WriteLine(msg);
            //FileStream logfile = new FileStream(@"C:\MailService.txt", FileMode.Append, FileAccess.Write);
            //StreamWriter sw = new StreamWriter(logfile);
            //string str = "---------------------------------\r\n";
            //str += DateTime.Now.ToString() + "\r\n";
            //str += msg;
            //str += "\r\n---------------------------------\r\n";
            //sw.Write(str);
            //sw.Close();
        }
    }
}
