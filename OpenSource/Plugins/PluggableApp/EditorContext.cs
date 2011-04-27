using System;
using Royo.Plugins;

namespace Royo.PluggableApp
{
	/// <summary>
	/// This class implements the IPluginContext interface
	/// to provide a context which represents the current running
	/// editor's text to plugins
	/// </summary>
	public class EditorContext:IPluginContext
	{
		private string m_CurrentText="";
		public EditorContext(string CurrentEditorText)
		{
			m_CurrentText = CurrentEditorText;
		}
		#region IPluginContext Members

		public string CurrentDocumentText
		{
			get
			{
				return m_CurrentText;
			}
			set
			{
				m_CurrentText = value;
			}
		}

		#endregion
	}
}
