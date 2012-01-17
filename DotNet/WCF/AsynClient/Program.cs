using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AsynClient.ServiceReference;

namespace AsynClient
{
    class Program
    {
        static Service1SoapClient client = new Service1SoapClient();
        static void Main(string[] args)
        {
            AsyncCallback callback = new AsyncCallback(CallBack);
            client.BeginAdd(1,2,callback,DateTime.Now.ToString());
            Console.WriteLine("异步调用完成");
            int r = client.Add(1, 2);
            Console.WriteLine("同步调用结果：" + r);
            Console.ReadKey();
        }

        private static void CallBack(IAsyncResult result)
        {
            Console.WriteLine(result.AsyncState);
            int r = client.EndAdd(result);
            Console.WriteLine("异步调用结果：" + r);
        }
    }
}
