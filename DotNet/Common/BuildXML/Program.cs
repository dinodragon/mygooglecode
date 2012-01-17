using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Linq;

namespace BuildXML
{
    class Program
    {
        static void Main(string[] args)
        {
            XDocument doc = new XDocument();
            XElement element = new XElement("难度", "aa");
            doc.Add(element);
            Func();
        }

        static void Func()
        {
            XmlDocument xmlDocument = new XmlDocument();
            XmlElement xmlRoot = xmlDocument.CreateElement("Root");
            xmlDocument.AppendChild(xmlRoot);
            XmlElement ele = null;
            ele = xmlDocument.CreateElement("难度");
            ele.InnerText = "高";
            xmlRoot.AppendChild(ele);
        }
    }
}
