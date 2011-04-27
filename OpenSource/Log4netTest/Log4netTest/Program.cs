using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using epub.Log;

namespace Log4netTest
{
    class Program
    {
        static void Main(string[] args)
        {
            double x = divide(1, 0);
        }

        static double divide(double x, double y)
        {
            try
            {
                int z = 0;
                return 1 / z;
            }
            catch (Exception ex)
            {
                DateTime t1 = DateTime.Now;
                for (int i = 0; i < 10; i++)
                {
                    Logger.WriteException("error", ex, "x={0},y={1}", new object[] { x, y });
                }
                TimeSpan ts = DateTime.Now - t1;
                Console.WriteLine(ts.ToString());
                return 0;
            }

        }
    }

}
