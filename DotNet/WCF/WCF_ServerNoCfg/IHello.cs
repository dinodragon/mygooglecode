using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace WCF_Contract
{
    [ServiceContract]
    public interface IHello
    {
        [OperationContract]
        string Show(string str);
    }
}
