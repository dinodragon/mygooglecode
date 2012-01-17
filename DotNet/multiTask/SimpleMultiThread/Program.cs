using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace SimpleMultiThread
{
    class Program
    {
        static void Main(string[] args)
        {
            {
                Thread t1 = new Thread(fun1);
                Thread t2 = new Thread(fun2);
                t1.Start();
                t2.Start();
            }
            Console.ReadKey();
        }

        static void fun1()
        {
            for (int i = 0; i < 100;i++ )
            {
                Console.WriteLine("InThread 1  " + i.ToString());
                FrameWork.Logging.Log.Info(i.ToString());
                Thread.Sleep(10);
            }
        }

        static void fun2()
        {
            for (int i = 0; i < 100; i++)
            {
                Console.WriteLine("InThread 2  " + i.ToString());
                FrameWork.Logging.Log.Info(i.ToString());
                Thread.Sleep(10);
            }
        }
    }
}
