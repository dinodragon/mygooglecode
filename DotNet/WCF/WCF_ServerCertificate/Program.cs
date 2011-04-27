using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using WCF_Contract;

namespace WCF_ServerNoCfg
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is Server");
            using (ServiceHost serviceHost = new ServiceHost(typeof(Hello)))
            {
                serviceHost.Open();
                Console.ReadKey();
            }
        }
    }
}
