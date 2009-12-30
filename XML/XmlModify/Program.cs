using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace XmlModify
{
    class Program
    {
        static void Main(string[] args)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(@"Data.xml");
            XmlNodeList nodes = doc.SelectNodes("/Root/Document");
            foreach(XmlNode item in nodes)
            {
                XmlElement ele = item as XmlElement;
                ele.SetAttribute("ContentGuid","aaaa");
            }
        }
    }
}
