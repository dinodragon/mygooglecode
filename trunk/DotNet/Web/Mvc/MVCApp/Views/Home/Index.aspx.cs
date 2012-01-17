using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace MVCApp.Views.Home
{
    public class Hp
    {
        public Hp(string Title,string Url)
        {
            this.Title = Title;
            this.Url = Url;
        }
        public string Title { get; set; }
        public string Url { get; set; }
    }

    public partial class Index : ViewPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                List<Hp> ds = new List<Hp>();
                ds.Add(new Hp("新浪","http://www.sina.com"));
                ds.Add(new Hp("百度", "http://www.baidu.com"));
                Repeater1.DataSource = ds;
                Repeater1.DataBind();
            }
        }
    }
}
