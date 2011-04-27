using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Mvc.Ajax;

namespace MVCApp.Controllers
{
    [HandleError]
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            ViewData["Title"] = "Home Page";
            ViewData["Message"] = "Welcome to ASP.NET MVC!";
            ViewData["MyName"] = "Yangfei!";

            return View();
        }

        public ActionResult About()
        {
            ViewData["Title"] = "About Page";
            ViewData["Message"] = "这是关于我的信息";
            return View();
        }
    }
}
