using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace XmlNS
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                XmlDocument doc = new XmlDocument();
                doc.Load("试题导出的Udml文件.xml");
                XmlNodeList nl = doc.DocumentElement.ChildNodes;
            }
            catch (System.Exception ex)
            {
            	
            }
        }
    }
}
