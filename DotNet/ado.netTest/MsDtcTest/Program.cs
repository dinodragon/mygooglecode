using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Transactions;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;

namespace MsDtcTest
{
    class Program
    {
        public void add1()
        {
            string conStr = ConfigurationManager.AppSettings["connectionStrings"];
            using (SqlConnection conn = new SqlConnection(conStr))
            {
                conn.Open();
                SqlCommand cmd = conn.CreateCommand();
                cmd.CommandText = @"update Products set unitprice=unitprice + 1 where supplierid = 12";
                cmd.ExecuteNonQuery();
                conn.Close();
            }
        }

        public void add2()
        {
            string conStr = ConfigurationManager.AppSettings["connectionStrings"];
            using (SqlConnection conn = new SqlConnection(conStr))
            {
                conn.Open();
                SqlCommand cmd = conn.CreateCommand();
                cmd.CommandText = @"update Products set unitprice=unitprice + 1 where supplierid = 12";
                cmd.ExecuteNonQuery();
                conn.Close();
            }
        }

        static void Main(string[] args)
        {
            //如果存在事务则使用该事务，不存在则创建新事务
            using (TransactionScope scope = new TransactionScope(TransactionScopeOption.Required))
            {
                try
                {
                    Program p = new Program();
                    p.add1();
                    p.add2();
                    //没有异常则提交
                    scope.Complete();
                    Console.WriteLine("插入成功");
                    //Console.ReadLine();
                }
                catch (Exception ex)
                {
                    //出现异常则回滚
                    scope.Dispose();
                    Console.WriteLine("插入失败");
                    Console.WriteLine(ex.ToString());
                    //Console.ReadLine();
                }
            }
            Console.WriteLine("按任意键继续！");
            Console.ReadLine();
        }
    }
}
