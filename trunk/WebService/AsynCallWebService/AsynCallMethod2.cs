using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AsynCallWebService.ServiceReference;

namespace AsynCallWebService
{
    //BeginEnd方式
    class AsynCallMethod2
    {
        public void Call()
        {
            MyServiceSoapClient client = new MyServiceSoapClient();
            AsyncCallback callback = new AsyncCallback(CallBack);
            IAsyncResult asyncResult = client.BeginAdd(1, 2, callback, client);
            //while (!asyncResult.IsCompleted)
            //{
            //    Console.WriteLine("BeginEnd方式调用没有完成。");
            //    System.Threading.Thread.Sleep(100);
            //}
        }

        private void CallBack(IAsyncResult result)
        {
            Console.WriteLine("BeginEnd方式调用完成。");
            MyServiceSoapClient client = result.AsyncState as MyServiceSoapClient;
            int r = client.EndAdd(result);
            Console.WriteLine("BeginEnd方式调用结果：" + r);
        }

    }
}
