using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;


namespace WCFCallBackContract
{
    [ServiceContract(CallbackContract = typeof(ICallBack))]
    public interface ICale
    {
        [OperationContract]
        int Add(int x ,int y);
    }


}
