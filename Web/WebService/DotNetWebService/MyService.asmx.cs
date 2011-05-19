﻿using System;
using System.Data;
using System.Web;
using System.Collections;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.ComponentModel;

namespace DotNetWebService
{
    /// <summary>
    /// Service1 的摘要说明
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [ToolboxItem(false)]
    public class MyService : System.Web.Services.WebService
    {

        [WebMethod]
        public string HelloWorld()
        {
            return "Hello World";
        }

        [WebMethod]
        public int Add(int x,int y)
        {
            return x+y;
        }

        [WebMethod]
        public UserInfo GetUserInfo(UserInfo u1)
        {
            UserInfo u = new UserInfo();
            u.Name = "test";
            u.Age = 1;
            return u;
        }
    }


    [Serializable]
    public class UserInfo
    {
        private string _name;
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
        public int Age
        {
            get;
            set;
        }
        //Add   other   properties   or   methods   here 
    }
}