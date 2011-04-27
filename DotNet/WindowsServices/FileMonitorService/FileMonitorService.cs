using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.ServiceProcess;
using System.Text;
using System.IO;

namespace FileMonitorService
{
    public partial class FileMonitorService : ServiceBase
    {
        bool servicePaused = false;
        public FileMonitorService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            // TODO: 在此处添加代码以启动服务。
            FileSystemWatcher curWatcher = new FileSystemWatcher();

            curWatcher.BeginInit();
            curWatcher.IncludeSubdirectories = true;
            curWatcher.Path = "c:\\oleview";
            curWatcher.Changed += new FileSystemEventHandler(OnFileChanged);
            curWatcher.Created += new FileSystemEventHandler(OnFileCreated);
            curWatcher.Deleted += new FileSystemEventHandler(OnFileDeleted);
            curWatcher.Renamed += new RenamedEventHandler(OnFileRenamed);
            curWatcher.EnableRaisingEvents = true;
            curWatcher.EndInit();
        }

        public void start()
        {
            OnStart(null);
        }

        public void stop()
        {
            OnStop();
        }

        protected override void OnStop()
        {
            // TODO: 在此处添加代码以执行停止服务所需的关闭操作。
            if (fileChangeCounter.RawValue != 0)
            {
                fileChangeCounter.IncrementBy(-fileChangeCounter.RawValue);
            }
            if (fileDeleteCounter.RawValue != 0)
            {
                fileDeleteCounter.IncrementBy(-fileDeleteCounter.RawValue);
            }
            if (fileRenameCounter.RawValue != 0)
            {
                fileRenameCounter.IncrementBy(-fileRenameCounter.RawValue);
            }
            if (fileCreateCounter.RawValue != 0)
            {
                fileCreateCounter.IncrementBy(-fileCreateCounter.RawValue);
            }

        }
        protected override void OnPause()
        {
            servicePaused = true;
        }

        protected override void OnContinue()
        {
            servicePaused = false;
        }
        private void OnFileChanged(Object source, FileSystemEventArgs e)
        {
            if (servicePaused == false)
            {
                fileChangeCounter.IncrementBy(1);
            }
        }

        private void OnFileRenamed(Object source, RenamedEventArgs e)
        {
            if (servicePaused == false)
            {
                fileRenameCounter.IncrementBy(1);
            }
        }

        private void OnFileCreated(Object source, FileSystemEventArgs e)
        {
            if (servicePaused == false)
            {
                fileCreateCounter.IncrementBy(1);
            }
        }

        private void OnFileDeleted(Object source, FileSystemEventArgs e)
        {
            if (servicePaused == false)
            {
                fileDeleteCounter.IncrementBy(1);
            }
        }
 

    }
}
