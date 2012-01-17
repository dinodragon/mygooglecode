using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.ServiceProcess;
using System.Text;

using ePub.Server.Mail.Core;

namespace ePub.Server.Mail.Host
{
    public partial class EpubMailService : ServiceBase
    {
        public EpubMailService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            try
            {
                ServerProcess.Start();
            }
            catch (System.Exception e)
            {
                Log.Write(e.ToString());
            }
            
        }

        public void Start()
        {
            OnStart(null);
        }

        public void Stop()
        {
            OnStop();
        }

        protected override void OnStop()
        {
            try
            {
                ServerProcess.Stop();
            }
            catch (System.Exception e)
            {
                Log.Write(e.ToString());
            }
            
        }
    }
}
