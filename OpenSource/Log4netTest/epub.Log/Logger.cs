using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using log4net;

namespace epub.Log
{
    public class Logger
    {
        public static void WriteInfo(string info)
        {
            StackTrace st = new StackTrace();
            ILog log = log4net.LogManager.GetLogger(st.GetFrame(1).GetMethod().DeclaringType);
            log.Info(info);
        }

        public static void WriteException(string info, Exception ex)
        {
            StackTrace st = new StackTrace();
            ILog log = log4net.LogManager.GetLogger(st.GetFrame(1).GetMethod().DeclaringType);
            log.Error(info, ex);
        }

        public static void WriteException(string info, Exception ex, string format, params object[] arg)
        {
            StackTrace st = new StackTrace();
            ILog log = log4net.LogManager.GetLogger(st.GetFrame(1).GetMethod().DeclaringType);
            format = info + "\r\n" + ex.ToString() + "\r\nparameter:\r\n" + format;
            log.ErrorFormat(format, arg);
        }
    }
}
