using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

public partial class Default2 : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void Button_Click1(object sender, EventArgs e)
    {
        Label1.Text = DateTime.Now.Ticks.ToString();
        Label2.Text = DateTime.Now.Ticks.ToString();
    }

    protected void Button_Click2(object sender, EventArgs e)
    {
        Label1.Text = DateTime.Now.Ticks.ToString();
        Label2.Text = DateTime.Now.Ticks.ToString();
    }
}
