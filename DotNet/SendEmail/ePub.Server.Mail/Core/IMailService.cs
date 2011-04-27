using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace ePub.Server.Mail.Core
{
    [ServiceContract]
    public interface IMailService
    {
        [OperationContract(IsOneWay = true)]
        void SendMail(string pattern);
    }
}
