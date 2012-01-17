using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace WCF_WebService
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is Server!");
            MainProgram obj = new MainProgram();
            obj.Run();
            Console.ReadKey();
            obj.Stop();
        }
    }

        
    class MainProgram
    {
        private static ServiceHost m_ServiceHost = null;

        public void Run()
        {
            m_ServiceHost = new ServiceHost(typeof(WCFFunction));

            try
            {
                Console.WriteLine("Server Open.");
                m_ServiceHost.Open();
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex);
            }
        }

        public void Stop()
        {
            try
            {
                Console.WriteLine("Server Stop.");
                if (m_ServiceHost != null)
                {
                    m_ServiceHost.Close();
                }
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex);
            }
        }
    }
}
