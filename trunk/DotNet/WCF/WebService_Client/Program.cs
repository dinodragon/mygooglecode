using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WebService_Client.ServiceReference;
using System.ServiceModel.Channels;


using System.Diagnostics;
using System.ComponentModel;


namespace WebService_Client
{
    class Program
    {
        static void Main(string[] args)
        {
            DateTime t = DateTime.Now;
            //int i = 1;
            //try
            //{
            //    MyServiceSoapClient client = new MyServiceSoapClient();
            //    for (i = 1; i < 10000; i++)
            //    {
            //        //Console.WriteLine(client.HelloWorld());
            //        client.HelloWorld();
            //        GC.Collect();
            //    }
            //    client.Close();
            //}
            //catch (System.Exception ex)
            //{
            //    Console.WriteLine("i:" + i);
            //    Console.WriteLine(ex);
            //}

            //Console.WriteLine(DateTime.Now - t);


            //不依赖Config文件，直接根据url和方法名，参数列表调用
            WebServiceClient client2 = new WebServiceClient("http://localhost:2022/MyService.asmx");
            t = DateTime.Now;
            try
            {
                for (int i = 1; i < 10000; i++)
                {
                    //Console.WriteLine(client2.HelloWorld());
                    client2.HelloWorld();
                }

            }
            catch (System.Exception ex)
            {
                Console.WriteLine(ex);
            }
            Console.WriteLine(DateTime.Now - t);
        }
    }

    

}
