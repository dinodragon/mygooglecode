using System;
using System.Collections;
using System.Linq;
using System.Workflow.ComponentModel;
using System.Diagnostics;


namespace HelloWF
{
	public class DebugActivity: Activity
	{
        public string Message { get; set; }

		public DebugActivity()
		{
			
		}

        protected override ActivityExecutionStatus Execute(ActivityExecutionContext executionContext)
        {
            if (Debugger.IsAttached)
            {
                Console.WriteLine(Message);
            }
            return base.Execute(executionContext);
        }
	}
}
