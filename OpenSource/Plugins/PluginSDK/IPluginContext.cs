using System;

namespace Royo.Plugins
{
	/// <summary>
	/// A public interface used to pass context to plugins
	/// </summary>
	public interface IPluginContext
	{
		string CurrentDocumentText{get;set;}
	}
}
