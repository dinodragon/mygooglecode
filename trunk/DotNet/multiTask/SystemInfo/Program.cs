using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading;

namespace SystemInfo
{
    class Program
    {
        static void Main(string[] args)
        {
            PerformanceMoniter pm = new PerformanceMoniter();
            while (true)
            {
                Thread.Sleep(2000);
                Console.WriteLine(pm.GetUse());
            }
        }
    }

    public class PerformanceMoniter
    {
        List<double> useValue = new List<double>();
        PerformanceCounter pc = new PerformanceCounter("Processor", "% Processor Time", "_Total");

        public PerformanceMoniter()
        {
            new Thread(CountValue).Start();
        }

        public double GetUse()
        {
            return 100 - useValue.Average();
        }

        void CountValue()
        {
            while (true)
            {
                Thread.Sleep(1000);
                float value = pc.NextValue();
                //Console.WriteLine("CPU Use:" + value + "%");
                useValue.Add(value);
                if (useValue.Count > 10)
                {
                    useValue.RemoveAt(0);
                }
            }
        }
    }
}
