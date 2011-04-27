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
            XmlDocument doc = new XmlDocument();
            doc.Load(@"..\..\data.xml");
            XmlNodeList nodeList;
            nodeList = doc.SelectNodes(@"/root/item");
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
