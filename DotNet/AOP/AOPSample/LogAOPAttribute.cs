using System;
using System.Runtime.Remoting.Activation;
using System.Runtime.Remoting.Contexts;
using Wayfarer.AOP;

namespace Wayfarer.AOPSample
{
	/// <summary>
	/// Summary description for LogAOPAttribute.
	/// </summary>
	[AttributeUsage(AttributeTargets.Class)]
	public class LogAOPAttribute:AOPAttribute
	{
		protected override AOPProperty GetAOPProperty()
		{
			return new LogAOPProperty();
		}
	
	}
}
