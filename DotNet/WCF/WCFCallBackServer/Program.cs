using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using WCFCallBackContract;

namespace WCFCallBackServer
{
    class Program
    {
        static void Main(string[] args)
        {
            using (ServiceHost host = new ServiceHost(typeof(Cale)))
            {
                host.AddServiceEndpoint(typeof(ICale), new NetTcpBinding(), "net.tcp://localhost:5432/Fun");
                host.Open();
                while(true)
                {
                    ClientPool.call();
                    System.Threading.Thread.Sleep(1000);
                }
                //Console.Read();
            }
        }
    }
}
