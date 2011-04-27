using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.IO;

namespace Serialization
{
    class Program
    {
        static void Main(string[] args)
        {
            Document obj = new Document();
            XmlSerializer ser = new XmlSerializer(obj.GetType());
            StringBuilder sb = new StringBuilder();
            ser.Serialize(XmlWriter.Create(sb), obj);
            Console.WriteLine(XElement.Parse(sb.ToString()).ToString());
        }
    }
}
