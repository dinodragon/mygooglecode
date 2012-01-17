using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Linq;
using System.Xml.XPath;

namespace XmlModify
{
    class Program
    {
        static void Main(string[] args)
        {
            Fun1();
            Fun2();
        }

        static void Fun1()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(@"Data.xml");
            XmlNodeList nodes = doc.SelectNodes("/Root/Document");
            foreach (XmlNode item in nodes)
            {
                XmlElement ele = item as XmlElement;
                ele.SetAttribute("ContentGuid", "aaaa");
            }
        }

        static void Fun2()
        {
            XElement doc = XElement.Load(@"Data.xml");
            IEnumerable<XElement> nodes = doc.XPathSelectElements("Document");
            foreach (XElement item in nodes)
            {
                item.SetAttributeValue("ContentGuid", "aaaa");
            }
        }
    }
}
