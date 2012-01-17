using System;
using System.Runtime.Remoting.Messaging;
using Wayfarer.AOP;

namespace Wayfarer.AOPSample
{
	/// <summary>
	/// Summary description for LogAOPSink.
	/// </summary>
	public class LogAOPSink:AOPSink
	{
		public LogAOPSink(IMessageSink nextSink):base(nextSink)
		{
			
		}

		protected override void AddAllBeforeAOPHandles()
		{
            AddBeforeAOPHandle("ADD",new BeforeAOPHandle(Before_Log));
			AddBeforeAOPHandle("SUBSTRACT",new BeforeAOPHandle(Before_Log));
		}

		protected override void AddAllAfterAOPHandles()
		{
			AddAfterAOPHandle("ADD",new AfterAOPHandle(After_Log));
			AddAfterAOPHandle("SUBSTRACT",new AfterAOPHandle(After_Log));
		}

		private void Before_Log(IMethodCallMessage callMsg)
		{			
			if (callMsg == null)
			{
				return;
			}
			Console.WriteLine("Before {0}",callMsg.MethodName);
			Console.WriteLine("{0}({1},{2})",callMsg.MethodName,callMsg.GetArg(0),callMsg.GetArg(1));
		}

		private void After_Log(IMethodReturnMessage replyMsg)
		{			
			if (replyMsg == null)
			{
				return;
			}			
			Console.WriteLine("Result is {0}",replyMsg.ReturnValue);
			Console.WriteLine("After {0}",replyMsg.MethodName);
		}

	}
}
