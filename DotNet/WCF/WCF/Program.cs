using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace WCF_Server
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
            //m_ServiceHost = new ServiceHost(typeof(WCFFunction));

            m_ServiceHost = new ServiceHost(typeof(WCFFunction));
            //如果在配置文件中有名称为WCF_Server.WCFFunction的Service则，直接将其端点加入到该ServiceHost的端点中。

            //在代码中再添加一个端点。
            //对于该程序的示例，他同时开放了三个端点，即可使用三个不同的地址来访问该服务
            //其中一个可以当做WebService来访问
            m_ServiceHost.AddServiceEndpoint(typeof(IWCFInterface), new NetTcpBinding(), "net.tcp://localhost:5432/Fun");
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
