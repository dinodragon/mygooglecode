using System;

namespace Wayfarer.AOPSample
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Program
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			Calculator cal = new Calculator();
			cal.Add(3,5);
			cal.Substract(3,5);
            cal.Multiply(3, 5);
		}
	}
}
