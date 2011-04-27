using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using WCFServer;

namespace WCFClient
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                ChannelFactory<WCFServer.ICalculate> channelFactory = new ChannelFactory<ICalculate>("CalculatorClient");
                WCFServer.ICalculate calculate = channelFactory.CreateChannel();
                calculate.DealOrder("TEST");
            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine("Press <ENTER> to terminate service.");
                Console.ReadLine();
            }
        }
    }
}
