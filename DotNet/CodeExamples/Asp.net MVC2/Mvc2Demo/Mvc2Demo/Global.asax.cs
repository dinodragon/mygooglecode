using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using System.Reflection;

namespace Mvc2Demo
{
    // 注意: 有关启用 IIS6 或 IIS7 经典模式的说明，
    // 请访问 http://go.microsoft.com/?LinkId=9394801

    public class MvcApplication : System.Web.HttpApplication
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                "Default", // 路由名称
                "{controller}/{action}/{id}", // 带有参数的 URL
                new { controller = "Home", action = "Index", id = UrlParameter.Optional } // 参数默认值
            );

        }

        protected void Application_Start()
        {
            AreaRegistration.RegisterAllAreas();
            string aa = AppDomain.CurrentDomain.BaseDirectory;
            AppDomain.CurrentDomain.ClearPrivatePath();
            AppDomain.CurrentDomain.AppendPrivatePath(Server.MapPath("WebApp\\bin"));
            AppDomainSetup au = new AppDomainSetup();
            aa = AppDomain.CurrentDomain.RelativeSearchPath;
            
            Assembly a = Assembly.LoadFrom(Server.MapPath("WebApp/Bin/WebApp.dll"));
            AppDomain.CurrentDomain.Load(a.FullName);
            RegisterRoutes(RouteTable.Routes);
        }
    }
}