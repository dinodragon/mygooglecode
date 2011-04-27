using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WcfFileTransferService;
using System.ServiceModel;

namespace WcfFileTransferServiceHost
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceHost host = new ServiceHost(typeof(FileTransfer));
            host.Open();
            Console.WriteLine("服务启动...");
            Console.ReadKey();
            host.Close();
        }
    }
}
