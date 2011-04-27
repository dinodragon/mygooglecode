using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Runtime.InteropServices;

namespace CSharpCallCppDll
{

    class Program
    {
        [DllImport("CppDll.dll")] 
        public static extern int add(int a,int b);

        [DllImport("CppDll.dll")]
        public static extern int len(string str);

        [DllImport("CppDll.dll")]
        public static extern int wlen([MarshalAs(UnmanagedType.LPWStr)]String str);

        static void Main(string[] args)
        {
            String str = "1123123";
            Console.WriteLine(add(2, 3));
            Console.WriteLine(len(str));
            Console.WriteLine(wlen(str));


            //Thread thread1 = new Thread(CallDll1);
            //Thread thread2 = new Thread(CallDll2);
            //thread1.Start();
            //thread2.Start();
            Console.ReadKey();
        }

        static void CallDll1()
        {
            for (int i = 0; i < 100;i++ )
            {
                Console.WriteLine("InThread_1!" + add(0,i));
            }
        }

        static void CallDll2()
        {
            for (int i = 0; i < 100; i++)
            {
                Console.WriteLine("InThread_2!" + add(0, i));
            }
        }
    }
}
