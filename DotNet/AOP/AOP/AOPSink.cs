using System;
using System.Collections;
using System.Runtime.Remoting.Contexts;
using System.Runtime.Remoting.Messaging;
using System.Runtime.Remoting.Activation;

namespace Wayfarer.AOP
{
	public delegate void BeforeAOPHandle(IMethodCallMessage callMsg);
	public delegate void AfterAOPHandle(IMethodReturnMessage replyMsg);

	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	public abstract class AOPSink : IMessageSink
	{
		private SortedList m_BeforeHandles;
		private SortedList m_AfterHandles;
		private IMessageSink m_NextSink;

		public AOPSink(IMessageSink nextSink)
		{
			m_NextSink = nextSink;
			m_BeforeHandles = new SortedList();
			m_AfterHandles = new SortedList();
			AddAllBeforeAOPHandles();
			AddAllAfterAOPHandles();
		}

		protected virtual void AddBeforeAOPHandle(string methodName, BeforeAOPHandle beforeHandle)
		{
			lock (this.m_BeforeHandles)
			{
				if (!m_BeforeHandles.Contains(methodName))
				{
					m_BeforeHandles.Add(methodName, beforeHandle);
				}
			}
		}
		protected virtual void AddAfterAOPHandle(string methodName, AfterAOPHandle afterHandle)
		{
			lock (this.m_AfterHandles)
			{
				if (!m_AfterHandles.Contains(methodName))
				{
					m_AfterHandles.Add(methodName, afterHandle);
				}
			}
		}

		protected abstract void AddAllBeforeAOPHandles();
		protected abstract void AddAllAfterAOPHandles();

		protected BeforeAOPHandle FindBeforeAOPHandle(string methodName)
		{
			BeforeAOPHandle beforeHandle;
			lock (this.m_BeforeHandles)
			{
				beforeHandle = (BeforeAOPHandle)m_BeforeHandles[methodName];
			}
			return beforeHandle;
		}
		protected AfterAOPHandle FindAfterAOPHandle(string methodName)
		{
			AfterAOPHandle afterHandle;
			lock (this.m_AfterHandles)
			{
				afterHandle = (AfterAOPHandle)m_AfterHandles[methodName];
			}
			return afterHandle;
		}

		public IMessageSink NextSink
		{
			get { return m_NextSink; }
		}

		public IMessage SyncProcessMessage(IMessage msg)
		{
			IMethodCallMessage call = msg as IMethodCallMessage;
			string methodName = call.MethodName.ToUpper();
			BeforeAOPHandle beforeHandle = FindBeforeAOPHandle(methodName);
			if (beforeHandle != null)
			{
				beforeHandle(call);
			}            
			IMessage retMsg = m_NextSink.SyncProcessMessage(msg);
			IMethodReturnMessage reply = retMsg as IMethodReturnMessage;
			AfterAOPHandle afterHandle = FindAfterAOPHandle(methodName);
			if (afterHandle != null)
			{
				afterHandle(reply);
			}
			return retMsg;
		}

		public IMessageCtrl AsyncProcessMessage(IMessage msg, IMessageSink replySink)
		{
			return null;
		}
	}
}
