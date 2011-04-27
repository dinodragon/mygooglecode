using System;
using Wayfarer.AOP;
using System.Runtime.Remoting.Messaging;

namespace Wayfarer.AOPSample
{
	/// <summary>
	/// Summary description for MonitorAOPProperty.
	/// </summary>
	public class MonitorAOPProperty:AOPProperty
	{
		public MonitorAOPProperty()
		{
			//
			// TODO: Add constructor logic here
			//
		}

		protected override IMessageSink CreateSink(IMessageSink nextSink)
		{
			return new MonitorAOPSink(nextSink);
		}

		protected override string GetName()
		{
			return "MonitorAOP";
		}
	}
}
