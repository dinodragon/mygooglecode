using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;

namespace WCFCallBackContract
{
    [ServiceContract]
    public interface ICallBack
    {
        [OperationContract]
        void ReceiveTime(DateTime time);
    }
}
