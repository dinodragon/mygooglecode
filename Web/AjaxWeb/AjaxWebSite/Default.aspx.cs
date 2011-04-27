using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class _Default : System.Web.UI.Page 
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void Button_Click(object sender, EventArgs e)
    {
        Label1.Text = DateTime.Now.Ticks.ToString();
        Label2.Text = DateTime.Now.Ticks.ToString();
    }
}
