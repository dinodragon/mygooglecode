using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using WCFCallBackContract;

namespace WCFCallBackServer
{
    [ServiceBehavior(ConcurrencyMode = ConcurrencyMode.Reentrant)]
    class Cale : ICale
    {
        public int Add(int x, int y)
        {
            Console.WriteLine("x:" + x + " y:" + y);
            ClientPool.callback =  OperationContext.Current.GetCallbackChannel<ICallBack>();
            //ClientPool.call();
            return x + y;
        }
    }
}
