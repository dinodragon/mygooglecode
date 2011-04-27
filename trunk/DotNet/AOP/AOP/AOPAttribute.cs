using System;
using System.Runtime.Remoting.Contexts;
using System.Runtime.Remoting.Activation;

namespace Wayfarer.AOP
{
	/// <summary>
	/// Summary description for AOPAttribute.
	/// </summary>
	[AttributeUsage(AttributeTargets.Class)]
	public abstract class AOPAttribute:ContextAttribute
	{
		public AOPAttribute()
			: base("AOP")
		{
		}

		public sealed override void GetPropertiesForNewContext(IConstructionCallMessage ctorMsg)
		{
			ctorMsg.ContextProperties.Add(GetAOPProperty());
		}

		protected abstract AOPProperty GetAOPProperty();		
	}
}
