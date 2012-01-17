using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;
using System.Configuration;
using System.IO;
using System.Xml;
using System.Threading;

namespace XQuery
{
    class Program
    {
        static string conStr = ConfigurationManager.AppSettings["connectionStrings"];
        
        static SqlConnection conn = new SqlConnection(conStr);
        
        static void Main(string[] args)
        {
            DateTime start = DateTime.Now;
            conn.Open();
            ReadXMLData();
            Console.WriteLine(DateTime.Now - start);
            Console.ReadKey();
            conn.Close();
        }

        //小XML十万条
        //以XML里的字段值做为查询条件
        static void ReadXMLData()
        {

            SqlCommand cmd = conn.CreateCommand();
            cmd.CommandText = "SELECT XmlData FROM  [XQueryData] where XmlData.value('(/Root/书名)[1]','varchar(255)') = '高中试题精解33525'";
            //cmd.CommandText = "SELECT XmlData FROM [XQueryData] where CONTAINS(XmlData, '*525*');";
            SqlDataReader thisReader = cmd.ExecuteReader();
            while (thisReader.Read())
            {
                int fieldCount = thisReader.FieldCount;
                for (int i = 0; i < fieldCount; i++)
                    Console.WriteLine(thisReader.GetName(i) + ":" + thisReader[i].ToString());
                Console.WriteLine("\n-------------------------------------");
            }
            thisReader.Close();
        }

        //小XML百万条
        //以XML里的字段值做为查询条件
        static void ReadXMLDataM()
        {
            SqlCommand cmd = conn.CreateCommand();
            cmd.CommandText = "SELECT XmlData FROM [XQueryDataM] where XmlData.value('(/Root/书名)[1]','varchar(255)') = '高中试题精解23525'";
            SqlDataReader thisReader = cmd.ExecuteReader();
            while (thisReader.Read())
            {
                int fieldCount = thisReader.FieldCount;
                for (int i = 0; i < fieldCount; i++)
                    Console.WriteLine(thisReader.GetName(i) + ":" + thisReader[i].ToString());
                Console.WriteLine("\n-------------------------------------");
            }
            thisReader.Close();
        }



        //大XML 十万
        //以XML里的字段值做为查询条件
        static void ReadXMLData2()
        {
            SqlCommand cmd = conn.CreateCommand();
            cmd.CommandText = "SELECT XmlData FROM  [XQueryData2] where XmlData.value('(/Root/章/例/题干/例结构)[1]','varchar(255)') = '例23525'";
            SqlDataReader thisReader = cmd.ExecuteReader();
            while (thisReader.Read())
            {
                int fieldCount = thisReader.FieldCount;
                for (int i = 0; i < fieldCount; i++)
                    Console.WriteLine(thisReader.GetName(i) + ":" + thisReader[i].ToString());
                Console.WriteLine("\n-------------------------------------");
            }
            thisReader.Close();
        }

        //大XML 百万
        //以XML里的字段值做为查询条件
        static void ReadXMLData2M()
        {
            SqlCommand cmd = conn.CreateCommand();
            cmd.CommandText = "SELECT XmlData FROM  [XQueryData2M] where XmlData.value('(/Root/章/例/题干/例结构)[1]','varchar(255)') = '例23525'";
            SqlDataReader thisReader = cmd.ExecuteReader();
            while (thisReader.Read())
            {
                int fieldCount = thisReader.FieldCount;
                for (int i = 0; i < fieldCount; i++)
                    Console.WriteLine(thisReader.GetName(i) + ":" + thisReader[i].ToString());
                Console.WriteLine("\n-------------------------------------");
            }
            thisReader.Close();
        }



        //小Xml数据添加 十万条
        static void WriteData()
        {
            Console.WriteLine("小Xml数据添加 十万条");
            XmlDocument doc = new XmlDocument();
            for (int i = 1; i < 100001; i++)
            {
                doc.Load(@"..\..\小xml.xml");
                XmlNode node = doc.DocumentElement.SelectSingleNode("//书名");
                node.InnerText += i.ToString();
                string xmlData = doc.InnerXml;
                string sqlCmd = String.Format("INSERT INTO [XQueryData] ([XmlData]) VALUES ('{0}')", xmlData);
                SqlCommand cmd = conn.CreateCommand();
                cmd.CommandText = sqlCmd;
                int n = cmd.ExecuteNonQuery();
            }
        }

        //小Xml数据添加 百万条
        static void WriteDataM()
        {
            Console.WriteLine("小Xml数据添加 百万条");
            XmlDocument doc = new XmlDocument();
            for (int i = 1; i < 1000001; i++)
            {
                doc.Load(@"..\..\小xml.xml");
                XmlNode node = doc.DocumentElement.SelectSingleNode("//书名");
                node.InnerText += i.ToString();
                string xmlData = doc.InnerXml;
                string sqlCmd = String.Format("INSERT INTO [XQueryDataM] ([XmlData]) VALUES ('{0}')", xmlData);
                SqlCommand cmd = conn.CreateCommand();
                cmd.CommandText = sqlCmd;
                int n = cmd.ExecuteNonQuery();
            }
        }

        //大Xml数据添加 十万条
        static void WriteData2()
        {
            Console.WriteLine("大Xml数据添加 十万条");
            XmlDocument doc = new XmlDocument();
            for (int i = 1; i < 100001; i++)
            {
                doc.Load(@"..\..\大xml.xml");
                XmlNode node = doc.DocumentElement.SelectSingleNode("//例//题干//例结构");
                node.InnerText += i.ToString();
                string xmlData = doc.InnerXml;
                string sqlCmd = String.Format("INSERT INTO [XQueryData2] ([XmlData]) VALUES ('{0}')", xmlData);
                SqlCommand cmd = conn.CreateCommand();
                cmd.CommandText = sqlCmd;
                int n = cmd.ExecuteNonQuery();
            }
        }

        //大Xml数据添加 百万条
        static void WriteData2M()
        {
            Console.WriteLine("大Xml数据添加 百万条");
            XmlDocument doc = new XmlDocument();
            for (int i = 1; i < 1000001; i++)
            {
                doc.Load(@"..\..\大xml.xml");
                XmlNode node = doc.DocumentElement.SelectSingleNode("//例//题干//例结构");
                node.InnerText += i.ToString();
                string xmlData = doc.InnerXml;
                string sqlCmd = String.Format("INSERT INTO [XQueryData2M] ([XmlData]) VALUES ('{0}')", xmlData);
                SqlCommand cmd = conn.CreateCommand();
                cmd.CommandText = sqlCmd;
                int n = cmd.ExecuteNonQuery();
            }
        }
    }
}
