using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WCF_Server
{
    class WCFFunction : IWCFInterface
    {
        public bool ShowOut(string str)
        {
            Console.WriteLine("-----------------Recevice Message.");
            Console.WriteLine(str);
            //System.Threading.Thread.Sleep(2000);
            Console.WriteLine("-----------------Processed OK.");
            return true;
        }
    }
}
