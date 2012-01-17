using System;

namespace Wayfarer.AOPSample
{
	/// <summary>
	/// Summary description for Calculator.
	/// </summary>
	[MonitorAOP]
	[LogAOP]
	public class Calculator:ContextBoundObject
	{
		public int Add(int x,int y)
		{
			return x + y;
		}

		public int Substract(int x,int y)
		{
			return x - y;
		}

        public int Multiply(int x, int y)
        {
            return x * y;
        }
	}
}
