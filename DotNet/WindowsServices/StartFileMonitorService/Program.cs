using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace StartFileMonitorService
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                //SrvMon.SrvMon service = new SrvMon.SrvMon();
                FileMonitorService.FileMonitorService service = new FileMonitorService.FileMonitorService();
                service.start();
                Console.WriteLine("Hit return to exit");
                Console.ReadLine();
                service.stop();
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e.ToString());
                Console.ReadLine();
            }
        }
    }
}
