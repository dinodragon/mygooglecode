using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Messaging;

namespace MessageQueueTest
{
    class Program
    {
        static void SendMessage()
        {
            System.Messaging.MessageQueue queue = new MessageQueue(".\\Private$\\MSMQDemo");
            for (int i = 1; i < 501; i++)
            {
                Message msg = new Message();
                msg.Body = i.ToString();
                queue.Send(msg, "Message");
                Thread.Sleep(100);
            }
        }

        static void ReceiveMessage()
        {
            System.Messaging.MessageQueue queue = new MessageQueue(".\\Private$\\MSMQDemo");
            for (int i = 0; i < 501; i++)
            {
                Message msg = queue.Receive();
                msg.Formatter = new System.Messaging.XmlMessageFormatter(new string[] { "System.String,mscorlib" });
                Thread.Sleep(10);
                Console.WriteLine(msg.Body);
            }
        }
        static void Main(string[] args)
        {
            Thread t1 = new Thread(new ThreadStart(SendMessage));
            Thread t2 = new Thread(new ThreadStart(ReceiveMessage));
            t1.Start();
            t2.Start();
        }
    }
}
