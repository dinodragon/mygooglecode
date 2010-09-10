using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Xml.XPath;

namespace LinqToXmlXpath
{
    //Linq to Xml 使用 XPath
    class Program
    {
        static void Main(string[] args)
        {
            XDocument doc = XDocument.Load(@"XMLFile.xml");
            XElement xe = doc.XPathSelectElement("/ErrorCode");
        }
    }
}
