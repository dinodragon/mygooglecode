using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace WCF_WebService
{
    [ServiceContract]
    public interface IWCFInterface
    {
        [OperationContract]
        bool ShowOut(string str);
    }
}
