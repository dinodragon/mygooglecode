using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace WCFServer
{
    [ServiceContract]
    public interface ICalculate
    {
        [OperationContract(IsOneWay = true)]
        void DealOrder(string orderID);
    }

    public class Calculator : ICalculate
    {
        public void DealOrder(string orderID)
        {
           Console.WriteLine(orderID);
        }
    }


    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                ServiceHost serviceHost = new ServiceHost(typeof(Calculator));
                serviceHost.Open();
                // The service can now be accessed.
                Console.WriteLine("The service is ready.");
                Console.WriteLine("Press <ENTER> to terminate service.");
                Console.ReadLine();
                // Close the ServiceHost.
                serviceHost.Close();
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine("Press <ENTER> to terminate service.");
                Console.ReadLine();
            }
        }
    }
}
