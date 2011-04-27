using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;
using System.IO;
using WcfFileTransferService;

namespace WcfFileTransferServiceClient
{
    class Program
    {
        static void Main(string[] args)
        {
            ChannelFactory<IFileTransfer> channelFactory =
                new ChannelFactory<IFileTransfer>("WSHttpBinding_IFileTransfer");
            IFileTransfer serverClient = channelFactory.CreateChannel();
            string aa = serverClient.GetData(12);
            Console.WriteLine(DateTime.Now);
            Stream stream = new FileStream(@"E:\software\dotnetfx35(SP1_CN).exe", FileMode.Open);
            serverClient.UploadFile(stream);
            Console.WriteLine(DateTime.Now);
            Console.ReadKey();
        }
    }
}
