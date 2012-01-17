using System;
using System.Runtime.Remoting.Activation;
using System.Runtime.Remoting.Contexts;
using Wayfarer.AOP;

namespace Wayfarer.AOPSample
{
	/// <summary>
	/// Summary description for MonitorAOPAttribute.
	/// </summary>
	[AttributeUsage(AttributeTargets.Class)]
	public class MonitorAOPAttribute:AOPAttribute
	{
		protected override AOPProperty GetAOPProperty()
		{
			return new MonitorAOPProperty();
		}
	}
}
