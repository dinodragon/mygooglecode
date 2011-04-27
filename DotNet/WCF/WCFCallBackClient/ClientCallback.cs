using System;
using System.Collections.Generic;
using System.Text;
using WCFCallBackContract;

namespace WCFCallBackClient
{
    public class ClientCallBack:ICallBack
    {
        public void ReceiveTime(DateTime time)
        {
            Console.WriteLine("服务器收到消息的时间是：{0}", time.ToLongTimeString());
        }
    }
}
