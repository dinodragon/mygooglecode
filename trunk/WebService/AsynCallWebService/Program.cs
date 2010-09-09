using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AsynCallWebService.ServiceReference;

namespace AsynCallWebService
{
    class Program
    {
        static void Main(string[] args)
        {
            MyServiceSoapClient client = new MyServiceSoapClient();
            client.AddCompleted +=new EventHandler<AddCompletedEventArgs>(client_AddCompleted);
            int result = client.Add(4, 5);
            Console.WriteLine("同步结果：" + result);
            client.AddAsync(5, 6);
            Console.ReadKey();
        }

        static protected void client_AddCompleted(object sender, AddCompletedEventArgs e)
        {
            Console.WriteLine("异步结果：" + e.Result);
        }
    }
}
