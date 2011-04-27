using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Microsoft.Ccr.Core;

namespace ccrTest
{
    class Program
    {
        static void Main(string[] args)
        {
            int maxiQueueDepth = 10;
            // step1: 创建一个Dispatcher对象
            Dispatcher dispatcher = new Dispatcher(0, "调度器名称");
            // step2: 创建一个与step1创建对象关联的DispatcherQueue对象
            DispatcherQueue depthThrottledQueue = new DispatcherQueue(
                                            "任务队列的名称",
                                            // 关联到该队列的调度器
                                            dispatcher,
                                            // 队列保存数据的策略：保存最近消息策略
                                            TaskExecutionPolicy.Unconstrained,
                                            // 队列的深度
                                            maxiQueueDepth
                                            );
            // step3: 创建一个能够接收整型数据的Port
            Port<int> intPort = new Port<int>();
            // step4: 把Port与处理函数关联，然后再与DispatcherQueue关联
            Arbiter.Activate(depthThrottledQueue,
                            Arbiter.Receive(true,
                                        intPort,
                                        delegate(int i)    // 这里用了一个匿名方法，作为处理函数
                                            {
                                                Thread.Sleep(5000);
                                                Console.WriteLine("[{0}] {1}", DateTime.Now.ToString("o"), i);
                                            }
                                        )
                            );

            // step5: 快速的提交大量的任务
            Console.WriteLine("[{0}] 开始提交大量的任务", DateTime.Now.ToString("o"));
            for (int i = 0; i < maxiQueueDepth * 100000; i++)
            {
                // 把数据Post到intPort内
                intPort.Post(i);
            }
            Console.WriteLine("[{0}] 大量任务提交完毕。", DateTime.Now.ToString("o"));

            Console.WriteLine("Press any key to exit");
            Console.ReadKey();
            dispatcher.Dispose();
        }

    }
}
