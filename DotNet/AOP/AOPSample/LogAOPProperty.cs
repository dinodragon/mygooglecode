using System;
using Wayfarer.AOP;
using System.Runtime.Remoting.Messaging;

namespace Wayfarer.AOPSample
{
	/// <summary>
	/// Summary description for LogProperty.
	/// </summary>
	public class LogAOPProperty:AOPProperty
	{
		public LogAOPProperty()
		{
			//
			// TODO: Add constructor logic here
			//
		}

		protected override IMessageSink CreateSink(IMessageSink nextSink)
		{
			return new LogAOPSink(nextSink);
		}

		protected override string GetName()
		{
			return "LogAOP";
		}
	}
}
