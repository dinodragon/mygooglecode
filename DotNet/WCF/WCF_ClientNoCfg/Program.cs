using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using WCF_Contract;

namespace WCF_ClientNoCfg
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                ChannelFactory<IHello> channelFactory = new ChannelFactory<IHello>("UseHttpClient");
                IHello serverClient = channelFactory.CreateChannel();
                DateTime start = DateTime.Now;
                for (int i = 0; i < 5000;i++ )
                {
                    serverClient.Show("From Client" + DateTime.Now.ToLongTimeString());
                }
                Console.WriteLine(DateTime.Now - start);
               
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }
    }
}
