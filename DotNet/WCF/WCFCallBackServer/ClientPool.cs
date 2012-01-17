using System;
using System.Collections.Generic;
using System.Text;
using WCFCallBackContract;


namespace WCFCallBackServer
{
    public class ClientPool
    {
        public static ICallBack callback = null;
        public static void call()
        {
            if (callback != null)
            {
                callback.ReceiveTime(DateTime.Now);
                callback = null;
            }
        }
    }
}
