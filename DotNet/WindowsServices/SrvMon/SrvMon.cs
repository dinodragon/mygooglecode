using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.ServiceProcess;
using System.Text;
using System.IO;
namespace SrvMon
{
    public partial class SrvMon : ServiceBase
    {
        public SrvMon()
        {
            InitializeComponent();
        }

        public void start()
        {
            OnStart(null);
        }

        public void stop()
        {
            OnStop();
        }

        protected override void OnStart(string[] args)
        {
            // TODO: 在此处添加代码以启动服务。
            StreamWriter swr;
            try
            {
                swr = File.AppendText("C:\\srvLog.txt");
            }
            catch
            {
                eventLog1.WriteEntry("文件没有找到！");
                return;
            }
            swr.WriteLine("本次启动时间:" + dateTimePicker1.Value.ToString());
            ServiceController[] services = ServiceController.GetDevices();
            foreach (ServiceController service in services)
            {
                swr.WriteLine("名称:" + service.ServiceName);
                swr.WriteLine("类型:" + service.ServiceType);
                swr.WriteLine("绑定名" + service.DisplayName);
            }
            swr.Close();

        }

        protected override void OnStop()
        {
            // TODO: 在此处添加代码以执行停止服务所需的关闭操作。
            StreamWriter swr;
            try
            {
                swr = File.AppendText("C:\\srvLog.txt");
            }
            catch
            {
                eventLog1.WriteEntry("文件没有找到!");
                return;
            }
            swr.WriteLine(" 本次结束时间：" + dateTimePicker1.Value.ToString());
            swr.Close();

        }
    }
}
