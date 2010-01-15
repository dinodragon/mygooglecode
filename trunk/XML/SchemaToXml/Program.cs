using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace SchemaToXml
{
    class Program
    {
        static void Main(string[] args)
        {
            DataSet thisDataSet = new DataSet();
            string filename = "./data/bookschema.xsd";
            thisDataSet.ReadXmlSchema(filename);

            //thisDataSet.WriteXmlSchema("./data/abc.xml");
            thisDataSet.WriteXml("./data/abc.xml");
            //如果用WriteXmlSchema（）就可以生成一个正确的xml框架   
            //如果用WriteXml()，abc.xml文件里的内容为   
            //<?xml   version="1.0"   standalone="yes"?>   
            //<NewDataSet   />  
        }
    }
}
