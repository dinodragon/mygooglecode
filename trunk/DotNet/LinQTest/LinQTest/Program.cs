using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LinQTest
{
    class Program
    {
        public enum DataType
        {
            Byte = 0,
            SmallInt = 1,
            Int = 2,
            BigInt = 3,
            Float = 4,
            Double = 5,
            Decimal = 6,
            Bit = 7,
            DateTime = 8,
            Guid = 9,
            Char = 10,
            NChar = 11,
            VarChar = 12,
            NVarChar = 13,
            Text = 14,
            NText = 15,
            Binary = 16,
            VarBinary = 17,
            Blob = 18,
            Cursor = 19,
        }

        static void Main(string[] args)
        {
            string[] names = { "a", "b", "c", "ad" };
            //var result = from p in names where p.StartsWith("a") select p;
            var result = names.Where(n => n.StartsWith("a"));
            foreach (var item in result)
            {
                Console.WriteLine(item);
            }
            Test1();
            Test2();
            Test3();
        }

        //两个同类集合做差
        static void Test1()
        {
            string[] names1 = { "a", "b", "c", "ad" };
            string[] names2 = { "a", "b", "c", "ade" };

            var differ = (from n in names1 select n).Except(from n in names2 select n);
            string[] result = differ.ToArray();
        }

        //两个不同类集合条件做差
        static void Test2()
        {
            string[] names1 = { "a1", "b2", "c3", "ad4" };
            int[] len = { 1, 2 };

            var differ = (from n in names1 where (!len.Contains(n.Length)) select n);
            string[] result = differ.ToArray();
        }

        //枚举类型值转成类型
        static void Test3()
        {
            DataType[] dt = { DataType.BigInt, DataType.Binary, DataType.Bit };
            Console.WriteLine(dt.Contains((DataType)Enum.Parse(typeof(DataType), "3")));
        }
    }
}
