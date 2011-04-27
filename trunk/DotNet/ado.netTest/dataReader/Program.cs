using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;

namespace dataReader
{
    class Program
    {
        static void Main(string[] args)
        {
            string conStr = ConfigurationManager.ConnectionStrings["connectionStrings"].ConnectionString;
            SqlConnection conn = new SqlConnection(conStr);
            conn.Open();
            SqlCommand cmd = conn.CreateCommand();
            //cmd.CommandText = "select * from dom_3_doclib";
            cmd.CommandText = "update [cm_doc_contents] set Content = @content where DocumentId = 'AF7AACAC-D88C-4961-B645-F120F32CCB21'";
            //string aa = "234";
            byte[] str = System.IO.File.ReadAllBytes(@"d:\1.docx");
            cmd.Parameters.AddWithValue("@content", str);
            SqlDataReader thisReader = cmd.ExecuteReader();
            while (thisReader.Read())
            {
                int fieldCount = thisReader.FieldCount;
                for (int i = 0; i < fieldCount;i++ )
                    Console.WriteLine(thisReader.GetName(i) +":"+ thisReader[i].ToString());
                Console.WriteLine("\n-------------------------------------");
            }
            thisReader.Close();
            conn.Close();
        }
    }
}
