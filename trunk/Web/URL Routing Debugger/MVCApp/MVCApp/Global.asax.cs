using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace MVCApp
{
    // Note: For instructions on enabling IIS6 or IIS7 classic mode, 
    // visit http://go.microsoft.com/?LinkId=9394801

    public class MvcApplication : System.Web.HttpApplication
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            //这里建立了一条规则
            routes.MapRoute(
                "Default",                                              // Route name
                "{controller}/{action}/{id}",                           // URL with parameters
                new { controller = "Home", action = "Index", id = "" }  // Parameter defaults下面还可以加一条约束条件
            );



            //Dictionary<string, object> defaultDict = new Dictionary<string, object>();
            //defaultDict["action"] = "Index";
            //defaultDict["id"] = 0;
            //RouteValueDictionary defaulatRouteVale = new RouteValueDictionary(defaultDict);

            //RouteValueDictionary constr = new RouteValueDictionary();
            //constr["controller"] = @"^\w+";
            //constr["id"] = @"\d+";

            //Route route = new Route(
            //    "{controller}/{action}/{id}",defaulatRouteVale,constr,new MvcRouteHandler());

        }

        protected void Application_Start()
        {
            RegisterRoutes(RouteTable.Routes);
            RouteDebug.RouteDebugger.RewriteRoutesForTesting(RouteTable.Routes);
        }
    }
}