using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace LinqToSQL
{
    class Program
    {
        static void Main(string[] args)
        {
            NorthwindDataContext data = new NorthwindDataContext();
            var result = from c in data.Customers
                         where c.Country == "USA"
                         select new
                         {
                             ID = c.CustomerID,
                             Name = c.CompanyName
                         };
            Console.WriteLine(result);
            foreach (var item in result)
            {
                Console.WriteLine(item);
            }
            proc();
        }

        //调用存储过程
        static void proc()
        {
            NorthwindDataContext data = new NorthwindDataContext();
            var result = data.Ten_Most_Expensive_Products();
            foreach (var item in result)
            {
                Console.WriteLine(item.TenMostExpensiveProducts + " " + item.UnitPrice);
            }
         }
    }
}
