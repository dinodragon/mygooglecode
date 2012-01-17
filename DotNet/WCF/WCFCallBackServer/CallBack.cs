using System;
using System.Collections.Generic;
using System.Text;
using WCFCallBackContract;

namespace WCFCallBackServer
{
    class CallBack :ICallBack
    {
        public void ReceiveTime(DateTime time)
        {
            Console.WriteLine("Receive Callback:" + time.ToShortTimeString());
        }
    }
}
