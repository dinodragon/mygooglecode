using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;

namespace TransactionTest
{
    class Program
    {
        //使用了事务
        static void Main(string[] args)
        {
            //TransactionDemo();
            Dom.Instance.Prepare();
            Dom.Instance.Update();
            Dom.Instance.Save();
        }

        static void TransactionDemo()
        {
            string conStr = ConfigurationManager.AppSettings["connectionStrings"];
            using (SqlConnection conn = new SqlConnection(conStr))
            {
                conn.Open();
                SqlTransaction ts = conn.BeginTransaction();//开始事务
                SqlCommand cmd = new SqlCommand();
                cmd.CommandText = @"update Products set unitprice=unitprice + 1 where supplierid = @p1";
                cmd.Parameters.AddWithValue("@p1", 12);
                cmd.Transaction = ts;
                cmd.Connection = conn;
                cmd.ExecuteNonQuery();
                ts.Commit();//提交事务
                conn.Close();
            }
        }
    }

    class Dom
    {
        public static Dom Instance
        {
            get;
            private set;
        }

        string conStr = ConfigurationManager.AppSettings["connectionStrings"];
        SqlConnection conn = null;
        private SqlTransaction ts = null;

        static Dom()
        {
            Instance = new Dom();
        }

        public void Prepare()
        {
            conn = new SqlConnection(conStr);
            conn.Open();
            ts = conn.BeginTransaction();
        }

        public void Update()
        {
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText = @"update Products set unitprice=unitprice + 1 where supplierid = @p1";
            cmd.Parameters.AddWithValue("@p1", 12);
            cmd.Transaction = ts;
            cmd.Connection = conn;
            cmd.ExecuteNonQuery();
        }

        public void Save()
        {
            ts.Commit();
        }
    }
}
