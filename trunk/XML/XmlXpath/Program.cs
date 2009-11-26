using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Xml.XPath;


namespace XmlXpath
{
    class Program
    {
        //根据高位低位的值，使用XPATH来查找所需的值
        static void Main(string[] args)
        {
            int high = 2;
            int low = 3;
            XDocument doc = XDocument.Load(@"..\..\XMLFile.xml");
            XElement element = doc.Root.XPathSelectElement(string.Format(@"/ErrorCode/High[@value='{0}']",high));
            element = element.XPathSelectElement(string.Format(@"Low[@value='{0}']",low));
            Console.WriteLine(element.Attribute("content").Value);
        }
    }
}
