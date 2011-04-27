using System;
using System.Runtime.Remoting.Messaging;
using Wayfarer.AOP;

namespace Wayfarer.AOPSample
{
	/// <summary>
	/// Summary description for PerformanceAOPSink.
	/// </summary>
	public class MonitorAOPSink:AOPSink
	{
		public MonitorAOPSink(IMessageSink nextSink):base(nextSink)
		{
			
		}

		protected override void AddAllBeforeAOPHandles()
		{
			AddBeforeAOPHandle("ADD",new BeforeAOPHandle(Before_Monitor));
			AddBeforeAOPHandle("SUBSTRACT",new BeforeAOPHandle(Before_Monitor));
		}
		protected override void AddAllAfterAOPHandles()
		{
			AddAfterAOPHandle("ADD",new AfterAOPHandle(After_Monitor));
			AddAfterAOPHandle("SUBSTRACT",new AfterAOPHandle(After_Monitor));
		}

		private void Before_Monitor(IMethodCallMessage callMsg)
		{			
			if (callMsg == null)
			{
				return;
			}
			Console.WriteLine("Before {0} at {1}",callMsg.MethodName,DateTime.Now);
		}
		private void After_Monitor(IMethodReturnMessage replyMsg)
		{			
			if (replyMsg == null)
			{
				return;
			}
			Console.WriteLine("After {0} at {1}",replyMsg.MethodName,DateTime.Now);
		}

	}
}
