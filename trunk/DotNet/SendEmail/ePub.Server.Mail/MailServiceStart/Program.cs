using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using ePub.Server.Mail.Host;

namespace ePub.Server.Mail.Start
{
    class Program
    {
        static void Main(string[] args)
        {
            EpubMailService service = new EpubMailService();
            service.Start();
            Console.WriteLine("Press any key and continue!");
            Console.ReadLine();
            service.Stop();
            Console.ReadLine();
        }
    }
}
