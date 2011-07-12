using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Text;
using System.Xml.Linq;


namespace Mvc3QuickStart.Controllers
{
    public class Person
    {
        string Name;
        int Age;
        string Sex;
    }

    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            ViewBag.Message = "Welcome to ASP.NET MVC!";

            return View();
        }

        public JsonResult JsonAction()
        {
            var person = new
            {
                Name = "张三",
                Age = 22,
                Sex = "男"
            };
            JsonResult jr = Json(person, "text/html", Encoding.UTF8, JsonRequestBehavior.AllowGet);
            return jr;
        }

        public ContentResult ContentAction()
        {
            ContentResult cr = new ContentResult();
            XElement xe = new XElement("Root", new XElement("Name", "Yangfei"));
            cr.Content = xe.ToString();
            return cr;
        }

        public ActionResult About()
        {
            return View();
        }
    }
}
