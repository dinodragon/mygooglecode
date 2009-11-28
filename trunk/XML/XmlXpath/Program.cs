using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using System.Xml.XPath;
using System.Xml;


namespace XmlXpath
{
    class Program
    {
        //根据高位低位的值，使用XPATH来查找所需的值
        static void Main(string[] args)
        {
            int highValue = 2;
            int lowValue = 5;
            //XDocument doc = XDocument.Load(@"XMLFile.xml");
            //XElement element = doc.Root.XPathSelectElement(string.Format(@"/ErrorCode/High[@value='{0}']",high));
            //element = element.XPathSelectElement(string.Format(@"Low[@value='{0}']",low));
            //Console.WriteLine(element.Attribute("content").Value);


            XmlDocument doc = new XmlDocument();
            string des = "";
            doc.Load(@"XMLFile.xml");
            XmlNode high = doc.SelectSingleNode(string.Format("/ErrorCode/High[@value='{0}']", (highValue)));
            XmlNode low = high.SelectSingleNode("Low[@value='" + (lowValue) + "']");
            if (low != null)
            {
                des = low.Attributes["content"].Value;
            }
            else if (high != null)
            {
                des = high.Attributes["content"].Value;
            }
            Console.WriteLine(des);
        }
    }
}
