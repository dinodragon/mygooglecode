using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;

namespace XmlReader
{
    class Program
    {
        static void Main(string[] args)
        {

            Fun2();
        }

        static  void Fun2()
        {
            var xd = new XmlDocument();
            xd.Load(@"..\..\data2.xml");
            var nsmanager = new XmlNamespaceManager(xd.NameTable);
            nsmanager.AddNamespace("dp", "www.founder.com");
            var list = xd.SelectNodes("/dp:attrs/dp:attr", nsmanager);
            if (list == null)
                return;
            foreach (XmlNode item in list)
            {
                string name = item.Attributes["name"].Value;
                string value = item.Attributes["value"].Value;
                Console.WriteLine("name:" + name + "   value:" + value);
            }

        }

        static void Fun()
        {
            var doc = new XmlDocument();
            doc.Load(@"..\..\data.xml");
            XmlNodeList nodeList = doc.SelectNodes(@"/root/item");
            if (nodeList != null)
                foreach (XmlNode item in nodeList)
                {
                    Console.WriteLine(item.Attributes["id"].Value);
                    Console.WriteLine(item.Attributes["editor"].Value);
                    Console.WriteLine(item.Attributes["time"].Value);
                    Console.WriteLine(item.Attributes["des"].Value);
                    Console.WriteLine(item.Attributes["fulldes"].Value);
                }
        }
    }
}
