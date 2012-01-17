using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace AsynCallWebService
{
    class Program
    {
        static void Main(string[] args)
        {

            AsynCallMethod1 m1 = new AsynCallMethod1();
            m1.Call();

            AsynCallMethod2 m2 = new AsynCallMethod2();
            m2.Call();
            Console.WriteLine("调用完成");
            Console.ReadKey();
        }
    }
}
