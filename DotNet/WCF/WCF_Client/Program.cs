using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WCF_Server;
using System.ServiceModel;
using System.ServiceModel.Channels;

namespace WCF_Client
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is Client!");
            try
            {
                //用config文件配置的端点访问
                //ChannelFactory<IWCFInterface> channelFactory = new ChannelFactory<IWCFInterface>("UseHttpClient");
                //IWCFInterface serverClient = channelFactory.CreateChannel();


                //直接用代码配置端点访问 使用BasicHttpBinding
                //EndpointAddress address = new EndpointAddress(@"http://localhost:9593/Fun");
                //ChannelFactory<IWCFInterface> channelFactory = 
                //    new ChannelFactory<IWCFInterface>(new BasicHttpBinding(),address);
                //IWCFInterface serverClient = channelFactory.CreateChannel();

                //直接用代码配置端点访问 使用net.Tcp
                EndpointAddress address = new EndpointAddress(@"net.tcp://localhost:5432/Fun");
                ChannelFactory<IWCFInterface> channelFactory =
                    new ChannelFactory<IWCFInterface>(new NetTcpBinding(), address);
                IWCFInterface serverClient = channelFactory.CreateChannel();

                string str = "From Client!";
                while (str != "end")
                {
                    serverClient.ShowOut(str);
                    str = Console.ReadLine();
                }
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex);
            }
            Console.ReadKey();
        }
    }
}
