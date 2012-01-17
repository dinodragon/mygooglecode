using System.ServiceModel;
using ePub.Server.Mail.Service;

using ePub.Server.Mail.Core;

namespace ePub.Server.Mail.Host
{
    class ServerProcess
    {
        static ServiceHost serviceHost = null;
        public static void Start()
        {
            try
            {
                serviceHost = new ServiceHost(typeof(MailService));
                serviceHost.Open();
                Log.Write("ServerProcess.Start()");
            }
            catch (System.Exception e)
            {
                Log.Write(e.ToString());
            }
        }

        public static void Stop()
        {
            try
            {
                serviceHost.Close();
                Log.Write("ServerProcess.Stop()");
            }
            catch (System.Exception e)
            {
                Log.Write(e.ToString());
            }
        }
    }
}