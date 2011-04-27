using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace CallShellCmd
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button_Run_Click(object sender, EventArgs e)
        {
            try
            {

                ProcessStartInfo ps = new ProcessStartInfo(@"F:\workspace\NICAS\exe.elNew\release\ProcessEngineLoader.exe", "\"txt.txt\"");
                ps.UseShellExecute = false;
                ps.CreateNoWindow = true;
                ps.RedirectStandardOutput = true;
                ps.RedirectStandardError = true;
                Process p = Process.Start(ps);
                p.WaitForExit(5000);
                if (!p.HasExited)
                {
                    p.Kill();
                }
                string output = p.StandardOutput.ReadToEnd();
                string aa = p.StandardError.ReadToEnd();
                int nRu = p.ExitCode;
                this.textBox_window.Text = output;   
            }
            catch (System.Exception ex)
            {
                this.textBox_window.Text = ex.ToString();
            }
        }

        private void button_clean_Click(object sender, EventArgs e)
        {
            this.textBox_window.Text = "";
        }
    }
}
