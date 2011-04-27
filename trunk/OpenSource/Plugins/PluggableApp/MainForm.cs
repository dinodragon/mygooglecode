using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Configuration;
using Royo.Plugins;

namespace Royo.PluggableApp
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class MainForm: System.Windows.Forms.Form
	{
		private System.Windows.Forms.TextBox txtText;
		private System.Windows.Forms.MainMenu mainMenu;
		private System.Windows.Forms.MenuItem menuItem1;
		private System.Windows.Forms.MenuItem menuItem2;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		private System.Windows.Forms.MenuItem PluginMenu;

		//The collection of currently active plugins
		private PluginCollection m_plugins = null;

		public MainForm()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.txtText = new System.Windows.Forms.TextBox();
			this.mainMenu = new System.Windows.Forms.MainMenu();
			this.menuItem1 = new System.Windows.Forms.MenuItem();
			this.menuItem2 = new System.Windows.Forms.MenuItem();
			this.PluginMenu = new System.Windows.Forms.MenuItem();
			this.SuspendLayout();
			// 
			// txtText
			// 
			this.txtText.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left) 
				| System.Windows.Forms.AnchorStyles.Right)));
			this.txtText.Location = new System.Drawing.Point(8, 16);
			this.txtText.Multiline = true;
			this.txtText.Name = "txtText";
			this.txtText.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.txtText.Size = new System.Drawing.Size(328, 208);
			this.txtText.TabIndex = 0;
			this.txtText.Text = @"]This is a test bla@mail.com and nother test at bla@mail.com 
and nother test at bla@mail.com and nother test at bla@m
and nother t and nother test at bla@mail.com and nother test at bla@mail.com
and nother test at bla@mail.com and nother test at bla@mail.com 
";
			// 
			// mainMenu
			// 
			this.mainMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					 this.menuItem1,
																					 this.PluginMenu});
			// 
			// menuItem1
			// 
			this.menuItem1.Index = 0;
			this.menuItem1.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] {
																					  this.menuItem2});
			this.menuItem1.Text = "&File";
			// 
			// menuItem2
			// 
			this.menuItem2.Index = 0;
			this.menuItem2.Text = "E&xit";
			this.menuItem2.Click += new System.EventHandler(this.menuItem2_Click);
			// 
			// PluginMenu
			// 
			this.PluginMenu.Index = 1;
			this.PluginMenu.Text = "&Plugins";
			// 
			// MainForm
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(344, 233);
			this.Controls.Add(this.txtText);
			this.Menu = this.mainMenu;
			this.Name = "MainForm";
			this.Text = "My Editor";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{

			Application.Run(new MainForm());
		}
	
		protected override void OnLoad(EventArgs e)
		{
			
			base.OnLoad (e);
			LoadPlugins();
		}

		
		
		private void LoadPlugins()
		{
			//Retrieve a plugin collection using our custom Configuration section handler
			m_plugins = 	 (PluginCollection )ConfigurationSettings.GetConfig("plugins");
			FillPluginMenu();
		}


		/// <summary>
		/// Create dynamic menu items according to each of the plugins we have loaded
		/// each menu item is connected to the same event handler delegate
		/// whcih then activates that plugin by the text of the menu item
		/// </summary>
		private void FillPluginMenu()
		{
			PluginMenu.MenuItems.Clear();
			//Create the delegate right from the start
			//no need to create one for each menu item seperatly
			EventHandler handler = new EventHandler(OnPluginClick);

			foreach(IPlugin plugin in m_plugins)
			{
				//We add a small ampersand at the start of the name
				//so we can get shortcut key strokes for it
				MenuItem item = new MenuItem("&" + plugin.Name,handler);
				PluginMenu.MenuItems.Add(item);
			}
		}

		/// <summary>
		/// Retrirve the name of the menu item
		/// and execute the needed plugin
		/// </summary>
		/// <param name="sender">MenuItem that was clicked</param>
		/// <param name="args">Default MenuItem EventArgs</param>
		private void OnPluginClick(object sender,EventArgs args)
		{
			MenuItem item = (MenuItem)sender;
			string plugName = item.Text.Replace("&","");
			ExecutePlugin(plugName);
		}

		//Execute a plugin by name
		private void ExecutePlugin(string pluginName)
		{
			//create a context object to pass to the plugin
			//this context holds the current editor text
			//and the plugin might change the text as part of its work
			//we will then show the tranformed text
			EditorContext context = new EditorContext(txtText.Text);

			foreach(IPlugin plugin in m_plugins)
			{
				if(plugin.Name==pluginName)
				{
					plugin.PerformAction(context);
					txtText.Text= context.CurrentDocumentText;
					return;
				}
			}
		}

		private void menuItem2_Click(object sender, System.EventArgs e)
		{
			Close();
		}

		private void MainForm_Load(object sender, System.EventArgs e)
		{
		
		}
	}
}
