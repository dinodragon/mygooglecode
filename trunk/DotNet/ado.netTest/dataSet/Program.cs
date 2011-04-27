using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;
using System.IO;

namespace dataSet
{
    class Program
    {
        static void Main(string[] args)
        {
            //设置DataDirectory值，详见以下页面。
            //http://msdn.microsoft.com/zh-cn/library/cc716756.aspx
            string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "..\\..\\..\\");
            DirectoryInfo info = new DirectoryInfo(path);
            AppDomain.CurrentDomain.SetData("DataDirectory", info.FullName);
           
            Read();
            Modify();
            DataRelationTest();
            ShowSql();
            ExecSql();//直接执行SQL,如删除，更新
            SqlStored();//使用存储过程
            CreateDataSet();//自定义一个数据集,说明数据集和数据库连接的无关性
        }

        //使用dataset读取数据
        static void Read()
        {
            string conStr = ConfigurationManager.ConnectionStrings["connectionStrings"].ConnectionString;
            SqlConnection conn = new SqlConnection(conStr);
            //不需打开连接，SqlDataAdapter负责打开，用完会自动关闭，SqlDataAdapter不会改变连接状态，
            //如果以前是打开的，用完还是打开的。
            SqlDataAdapter sda = new SqlDataAdapter("select * from Employees", conn);
            DataSet ds = new DataSet();
            sda.Fill(ds, "Employee");

            foreach (DataRow row in ds.Tables["Employee"].Rows)
            {
                int fieldCount = row.ItemArray.Count();
                for (int i = 0; i < fieldCount; i++)
                    Console.WriteLine(ds.Tables["Employee"].Columns[i].ToString() + ":" + row[i].ToString());
                Console.WriteLine("\n-------------------------------------");
            }
        }

        //修改数据
        static void Modify()
        {
            string conStr = ConfigurationManager.ConnectionStrings["connectionStrings"].ConnectionString;
            SqlConnection conn = new SqlConnection(conStr);
            SqlDataAdapter sda = new SqlDataAdapter("select * from Employees", conn);
            //怎么发挥作用的？
            //一旦设置SqlCommandBuilder的 DataAdapter 属性，
            //SqlCommandBuilder 就将其自身注册为 RowUpdating 事件的侦听器。
            //一次只能将一个 SqlDataAdapter 与一个 SqlCommandBuilder 对象（或相反）互相关联。
            SqlCommandBuilder sqlBuilder = new SqlCommandBuilder(sda);

            DataSet ds = new DataSet();
            sda.Fill(ds, "Employee");
            Console.WriteLine("Befor Modify BirthDate to now.");
            Console.WriteLine(ds.Tables["Employee"].Rows[0][5]);
            ds.Tables["Employee"].Rows[0][5] = DateTime.Now.ToString();
            sda.Update(ds, "Employee");
            Console.WriteLine("After Modify");
            Console.WriteLine(ds.Tables["Employee"].Rows[0][5]);
        }

        //DataSet中访问多个表,多表之间建立关系
        static void DataRelationTest()
        {
            string conStr = ConfigurationManager.ConnectionStrings["connectionStrings"].ConnectionString;
            SqlConnection conn = new SqlConnection(conStr);


            DataSet ds = new DataSet();
            SqlDataAdapter sda = new SqlDataAdapter("select * from Customers", conn);
            sda.Fill(ds, "Customers");
            SqlDataAdapter sda1 = new SqlDataAdapter("select * from Orders", conn);
            sda1.Fill(ds, "Orders");

            //ds.WriteXml("c:\\xml.xml"); 将数据写入到文件

            DataRelation dr = ds.Relations.Add("CustOrders", ds.Tables["Customers"].Columns["CustomerID"],
                ds.Tables["Orders"].Columns["CustomerID"]);

            foreach (DataRow custRow in ds.Tables["Customers"].Rows)
            {
                //dr.Nested = true;
                //ds.WriteXml("c:\\xml.xml");写入文件的数据含表间关系
                //dr对象的Nested属性通知WriteXml方法，将订单细节和订单嵌套在XML输出中的每个客户之下。
                Console.WriteLine("Customer ID:" + custRow["CustomerID"] + " Name: " + custRow["CompanyName"]);
                foreach (DataRow orderRow in custRow.GetChildRows(dr))
                {
                    Console.WriteLine(" Order ID:" + orderRow["OrderID"]);
                }
            }
        }

        static void ShowSql()
        {
            string conStr = ConfigurationManager.ConnectionStrings["connectionStrings"].ConnectionString;
            SqlConnection conn = new SqlConnection(conStr);
            conn.Open();
            SqlDataAdapter sda = new SqlDataAdapter("select CustomerID from Customers", conn);
            SqlCommandBuilder sqlBuilder = new SqlCommandBuilder(sda);

            Console.WriteLine("SQL Select Command is:\n{0}",sda.SelectCommand.CommandText);

            SqlCommand updateCommand = sqlBuilder.GetUpdateCommand();
            Console.WriteLine("SQL Update Command is:\n{0}", updateCommand.CommandText);

            SqlCommand InsertCommand = sqlBuilder.GetInsertCommand();
            Console.WriteLine("SQL Insert Command is:\n{0}", InsertCommand.CommandText);

            SqlCommand DeleteCommand = sqlBuilder.GetDeleteCommand();
            Console.WriteLine("SQL Delete Command is:\n{0}", DeleteCommand.CommandText);

            conn.Close();
        }

        //直接执行SQL，不用将数据读入到dataSet
        static void ExecSql()
        {
            string conStr = ConfigurationManager.ConnectionStrings["connectionStrings"].ConnectionString;
            SqlConnection conn = new SqlConnection(conStr);
            conn.Open();
            
            SqlCommand cmd = conn.CreateCommand();
            cmd.CommandText = @"select count(*) from customers";
            object countResult = cmd.ExecuteScalar(); //执行，返回单值
            Console.WriteLine("Count of Customers = {0}",countResult);

            SqlCommand updateCmd = conn.CreateCommand();
            updateCmd.CommandText = @"update Products set unitprice=unitprice*1.05 where supplierid = 12";
            object rowsAffected = updateCmd.ExecuteNonQuery(); //执行，返回单值
            Console.WriteLine("Rows Updated = {0}", rowsAffected);

            conn.Close();
        }

        //执行存储过程
        static void SqlStored()
        {
            string conStr = ConfigurationManager.ConnectionStrings["connectionStrings"].ConnectionString;
            SqlConnection conn = new SqlConnection(conStr);
            conn.Open();

            SqlCommand cmd = conn.CreateCommand();
            cmd.CommandType = CommandType.StoredProcedure;
            cmd.CommandText = "Ten Most Expensive Products";

            SqlDataReader sdr = cmd.ExecuteReader();

            while (sdr.Read())
            {
                Console.WriteLine("{0}\t{1}", sdr["TenMostExpensiveProducts"],sdr["UnitPrice"]);
            }

            sdr.Close();
            conn.Close();
        }

        /// <summary>手动创建DataSet</summary>
        /// <returns>void</returns>
        static void CreateDataSet()
        {
            DataSet ds = new DataSet();
            DataTable dt = new DataTable("Products");
            dt.Columns.Add(new DataColumn("ProductID",typeof(int)));
            dt.Columns.Add(new DataColumn("ProductName", typeof(string)));
            dt.Rows.Add(new object[]{12,"AA"});
            ds.Tables.Add(dt);
            
            //ds.DataSetName = "myDataSet";
            //ds.WriteXml(@"C:\aa.xml");

            foreach (DataRow row in ds.Tables["Products"].Rows)
            {
                int fieldCount = row.ItemArray.Count();
                for (int i = 0; i < fieldCount; i++)
                    Console.WriteLine(ds.Tables["Products"].Columns[i].ToString() + ":" + row[i].ToString());
                Console.WriteLine("\n-------------------------------------");
            }
            
        }
    }
}
