using System;
using System.Text.RegularExpressions;
using System.Text;
using Royo.Plugins;

namespace Royo.Plugins.Custom
{
	/// <summary>
	/// This class implements the IPlugin interface
	/// to provide the ability to parse and isolate email addresses found within
	/// the current editor's text
	/// </summary>
	public class EmailPlugin:IPlugin
	{
		public EmailPlugin()
		{
		}
		#region IPlugin Members


		/// <summary>
		/// The single point of entry to our plugin
		/// Acepts an IPluginContext object which holds the current
		/// context of the running editor.
		/// It then parses the text found inside the editor
		/// and changes it to reflect any email addresses that are found.
		/// </summary>
		/// <param name="context"></param>
		public void PerformAction(IPluginContext context)
		{
			context.CurrentDocumentText=ParseEmails(context.CurrentDocumentText);
		}

		/// <summary>
		/// The name of the plugins as it will appear 
		/// under the editor's "Plugins" menu
		/// </summary>
		public string Name
		{
			get
			{
				return "Email Parsing Plugin";
			}
		}

		#endregion

		/// <summary>
		/// Parse the given string for any emails using the Regex Class
		/// and return a string containing only email addresses
		/// </summary>
		private string ParseEmails(string text)
		{
			const string emailPattern=@"\w+@\w+\.\w+((\.\w+)*)?";

			MatchCollection emails = Regex.Matches(text,emailPattern,RegexOptions.IgnoreCase);
			StringBuilder emailString = new StringBuilder();
			foreach(Match email in emails)					
			{
				emailString.Append(email.Value + Environment.NewLine);
			}

			return emailString.ToString();
		}
	}
}
