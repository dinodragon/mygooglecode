using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace DataBind
{
    public partial class Form1 : Form
    {
        DataTable dt = new DataTable("Products");
        List<int> idList = new List<int>();
        List<string> nameList = new List<string>();

        public Form1()
        {
            InitializeComponent();
            dt.Columns.Add(new DataColumn("ID", typeof(int)));
            dt.Columns.Add(new DataColumn("Name", typeof(string)));
            dt.Columns.Add(new DataColumn("Type", typeof(string)));
            dt.Columns.Add(new DataColumn("Creator", typeof(string)));
            dt.Rows.Add(new object[] { 1,"江南景", "图片", "作者1" });
            dt.Rows.Add(new object[] { 2,"报告", "文章", "作者2" });
            dt.Rows.Add(new object[] { 3,"北京", "图片", "作者3" });

            idList.AddRange(new int[] {1,2,3});
            nameList.AddRange(new string[] { "江南景", "报告", "北京" });
        }

        private void FillData_Click(object sender, EventArgs e)
        {
            dataGridView1.DataSource = dt;
            textBox1.DataBindings.Clear();
            textBox1.DataBindings.Add(new Binding("Text", dt, "Name"));
            
            listBox1.DataSource = dt;
            listBox1.DisplayMember = "Name";
            listBox1.ValueMember = "ID";

            comboBox1.DataSource = dt;
            comboBox1.DisplayMember = "Name";
            comboBox1.ValueMember = "ID";

            listBox2.DataSource = idList;            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            dt.WriteXml("data.xml", true);
            ProcessStartInfo ps = new ProcessStartInfo(@"notepad.exe", "data.xml");
            System.Diagnostics.Process.Start(ps);
        }
    }
}
