using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using WCF_Contract;
using System.ServiceModel;
using System.ServiceModel.Channels;

namespace WCF_ServerNoCfg
{
    class Hello : IHello
    {
        public string Show(string str)
        {
            //这样可以得到客户端的IP地址。
            OperationContext context = OperationContext.Current;
            MessageProperties messageProperties = context.IncomingMessageProperties;
            RemoteEndpointMessageProperty endpointProperty =
            messageProperties[RemoteEndpointMessageProperty.Name] as RemoteEndpointMessageProperty;
            str = string.Format("Hello {0}! Your IP is {1},your port is {2}", str, endpointProperty.Address, endpointProperty.Port);
            Console.WriteLine(str);
            return str;
        }
    }
}
