using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

public partial class UpdatePanelTest : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btnSubmit_Click(object sender, EventArgs e)
    {
        ScriptManager.RegisterClientScriptBlock(Page, this.GetType(), "alert", " alert('你只更新了UpdatePanel2');", true);
    }
    protected void btnUpdate_Click(object sender, EventArgs e)
    {
        ScriptManager.RegisterClientScriptBlock(Page, this.GetType(), "alert", " alert('你更新了UpdatePanel1、UpdatePanel2、UpdatePanel3');", true);
    }
    protected void btnAll_Click(object sender, EventArgs e)
    {
        ScriptManager.RegisterClientScriptBlock(Page, this.GetType(), "alert", " alert('你更新了整个页面');", true);
    }
}
