using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Constructor
{
    /// <summary>
    /// 静态构造函数具有以下特点：
    /// 静态构造函数既没有访问修饰符，也没有参数。
    /// 在创建第一个实例或引用任何静态成员之前，将自动调用静态构造函数来初始化类。 
    /// 无法直接调用静态构造函数。
    /// 在程序中，用户无法控制何时执行静态构造函数。
    /// 静态构造函数的典型用途是：当类使用日志文件时，将使用这种构造函数向日志文件中写入项。
    /// 静态构造函数在为非托管代码创建包装类时也很有用，此时该构造函数可以调用 LoadLibrary 方法。
    /// 
    /// 静态构造函数只调用一次;先调用静态的再调用普通的，
    /// 调用顺序：子类静态-父类静态-父类普通-子类普通
    /// http://msdn.microsoft.com/zh-cn/library/k9x6w0hc(VS.80).aspx
    /// </summary>

    public class Base
    {
        public int a;
        public static int s;
        static Base()
        {
            Console.WriteLine("调用了Base静态构造函数");
        }

        public Base()
        {
            Console.WriteLine("调用了Base普通构造函数");
        }
    }

    public class D : Base
    {
        static D()
        {
            Console.WriteLine("调用了D静态构造函数");
        }

        public D()
        {
            Console.WriteLine("调用了D普通构造函数");
        }
    }

    class Program
    {
        /// <summary>
        /// 关于构造函数
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            //C.s = 1;
            Base c = new Base();
            D d = new D();
        }
    }
}
