using System;
using System.ComponentModel;
using System.ComponentModel.Design;
using System.Collections;
using System.Drawing;
using System.Linq;
using System.Workflow.ComponentModel.Compiler;
using System.Workflow.ComponentModel.Serialization;
using System.Workflow.ComponentModel;
using System.Workflow.ComponentModel.Design;
using System.Workflow.Runtime;
using System.Workflow.Activities;
using System.Workflow.Activities.Rules;

namespace HelloWF
{
    public sealed partial class Workflow1 : SequentialWorkflowActivity
    {
        static int _times = 0;

        public Workflow1()
        {
            InitializeComponent();
        }

        private void codeActivity1_ExecuteCode(object sender, EventArgs e)
        {
            Console.WriteLine("Hello World!这是操作1");
        }

        private void delayActivity1_InitializeTimeoutDuration(object sender, EventArgs e)
        {
            DelayActivity delay = sender as DelayActivity;
            if (null != delay)
            {
                Console.WriteLine("运行前延时：" + delay.TimeoutDuration);
            }
        }

        private void delayActivity2_InitializeTimeoutDuration(object sender, EventArgs e)
        {
            DelayActivity delay = sender as DelayActivity;
            if (null != delay)
            {
                Console.WriteLine("运行后延时：" + delay.TimeoutDuration);
            }
        }

        private void WhileCondition(object sender, ConditionalEventArgs e)
        {
            e.Result = _times++ < 5;
        }

        private void codeActivity2_ExecuteCode(object sender, EventArgs e)
        {
            Console.WriteLine("这是操作2");
            throw new System.Exception();
        }

        private void codeActivity3_ExecuteCode(object sender, EventArgs e)
        {
            Console.WriteLine("发生异常了。");
        }
    }

}
