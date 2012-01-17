using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Threading;

namespace DataConnectionTest
{
    class Program
    {
        static int count = 0;
        static void Main(string[] args)
        {
            for (int i = 0; i < 1;i++ )
            {
                Thread t = new Thread(fun1);
                t.Start();
            }
            Console.ReadLine();
        }

        static void fun1()
        {
            for (int i = 1; i < 200; i++)
            {
                try
                {
                    Console.WriteLine(string.Format("InThread:{0}", count++));
                    Dom d = new Dom();
                    d.Prepare();
                    d.Update();
                    //Thread.Sleep(1000);
                    d.Save();
                    d.End();
                    //Thread.Sleep(1000);
                }
                catch (System.Exception ex)
                {
                    Console.WriteLine(ex.Message);
                }
            }
        }
    }



    public class Dom
    {
        string conStr = ConfigurationManager.ConnectionStrings["connectionStrings"].ConnectionString;
        SqlConnection conn = null;
        //private SqlTransaction ts = null;

        public void Prepare()
        {
            conn = new SqlConnection(conStr);
            conn.Open();
            //ts = conn.BeginTransaction();
        }

        public void Update()
        {
            using (SqlCommand cmd = new SqlCommand())
            {
                cmd.CommandText = @"update yftest set AppId = AppId + 1 where id = @p1";
                cmd.Parameters.AddWithValue("@p1", 1);
                //cmd.Transaction = ts;
                cmd.Connection = conn;
                cmd.ExecuteNonQuery();
            }
        }

        public void Save()
        {
            //ts.Commit();
        }

        public void End()
        {
            //ts.Dispose();
            conn.Close();
            conn.Dispose();
            conn = null;
        }
    }
}
