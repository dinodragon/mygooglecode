using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using FileMonitorService;

namespace TestFileMonitorService
{
    /// <summary>
    /// Summary description for UnitTest1
    /// </summary>
    public class UnitTest1
    {
        static void Main()
        {
            try
            {
                FileMonitorService.FileMonitorService service = new FileMonitorService.FileMonitorService();
                service.start();
                Console.WriteLine("Hit return to exit");
                Console.ReadLine();
                service.Stop();
            }
            catch (System.Exception e)
            {
                Console.WriteLine(e.ToString());
                Console.ReadLine();            	
            }
        }
    }
}
