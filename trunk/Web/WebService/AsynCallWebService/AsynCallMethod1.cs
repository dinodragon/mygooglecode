using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AsynCallWebService.ServiceReference;

namespace AsynCallWebService
{
    class AsynCallMethod1
    {
        public void Call()
        {
            MyServiceSoapClient client = new MyServiceSoapClient();
            int result = client.Add(4, 5);

            Console.WriteLine("同步结果：" + result);
            //这是微软推荐的方式。
            client.AddCompleted += new EventHandler<AddCompletedEventArgs>(client_AddCompleted);
            client.AddAsync(5, 6);
        }

        protected void client_AddCompleted(object sender, AddCompletedEventArgs e)
        {
            Console.WriteLine("异步结果：" + e.Result);
        }
    }
}
