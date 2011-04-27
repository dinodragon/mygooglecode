using System;
using System.Runtime.Remoting.Activation;
using System.Runtime.Remoting.Contexts;
using System.Runtime.Remoting.Messaging;

namespace Wayfarer.AOP
{
	/// <summary>
	/// Summary description for AOPProperty.
	/// </summary>
	public abstract class AOPProperty : IContextProperty, IContributeObjectSink
	{
		protected abstract IMessageSink CreateSink(IMessageSink nextSink);

		protected virtual string GetName()
		{
			return "AOP";
		}

		protected virtual void FreezeImpl(Context newContext)
		{
			return;
		}

		protected virtual bool CheckNewContext(Context newCtx)
		{
			return true;
		}

		#region IContributeObjectSink Members

		public IMessageSink GetObjectSink(MarshalByRefObject obj, IMessageSink nextSink)
		{
			return CreateSink(nextSink);
		}

		#endregion

		#region IContextProperty Members

		public void Freeze(Context newContext)
		{
			FreezeImpl(newContext);
		}

		public bool IsNewContextOK(Context newCtx)
		{
			return CheckNewContext(newCtx);
		}

		public string Name
		{
			get { return GetName(); }
		}

		#endregion
	}
}
