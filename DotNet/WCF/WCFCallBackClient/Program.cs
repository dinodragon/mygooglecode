using System;
using System.Collections.Generic;
using System.Text;
using System.ServiceModel;
using WCFCallBackContract;

namespace WCFCallBackClient
{
    class Program
    {
        static void Main(string[] args)
        {
            Hello();
            Console.Read();
        }

        static void Hello()
        {
            ClientCallBack callBack = new ClientCallBack();
            ClientCale hello = new ClientCale(new InstanceContext(callBack));
            string commandString = string.Empty;
            int x = 1;
            int y = 2;
            hello.Add(x,y);
        }
    }

    public class ClientCale : DuplexClientBase<ICale>, ICale
    {
        public ClientCale(InstanceContext instance) : base(instance) { }

        public int Add(int x, int y)
        {
            return base.Channel.Add(x, y);
        }
    }
}
