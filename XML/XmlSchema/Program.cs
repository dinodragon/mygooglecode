using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Xml.Schema;

namespace XmlSchema
{
    public class ValidationReadingXMLSample
    {
        public static void Main()
        {
            Console.WriteLine("正在用架构文件schema.xsd验证XML文件booksSchema.xml...");
            XmlTextReader myXmlTextReader = new XmlTextReader(@"data\bookxml.xml");
            XmlValidatingReader myXmlValidatingReader = new XmlValidatingReader(myXmlTextReader);

            XmlSchemaCollection myXmlSchemaCollection = new XmlSchemaCollection();
            myXmlSchemaCollection.Add("http://www.cpp521.cn", new XmlTextReader(@"data\bookschema.xsd"));
            myXmlValidatingReader.Schemas.Add(myXmlSchemaCollection);
            myXmlValidatingReader.ValidationType = ValidationType.Schema;
            try
            {
                //设置验证事件处理程序   
                myXmlValidatingReader.ValidationEventHandler += new ValidationEventHandler(ValidationEventHandle);
                //读取XML数据   
                while (myXmlValidatingReader.Read()) { }
                Console.WriteLine("验证已完成。验证{0}", "成功");
            }
            catch (XmlException e)
            {
                Console.WriteLine("Xml异常：" + e.ToString());
            }
            catch (Exception e)
            {
                Console.WriteLine("异常：" + e.ToString());
            }
            if (myXmlValidatingReader != null)
                myXmlValidatingReader.Close();
            Console.ReadKey();
        }

        public static void ValidationEventHandle(object sender, ValidationEventArgs args)
        {
            Console.WriteLine("\t验证错误：" + args.Message);

            if (args.Severity == XmlSeverityType.Warning)
            {
                Console.WriteLine("未找到要强制验证的架构。");
            }
            else
                if (args.Severity == XmlSeverityType.Error)
                {
                    Console.WriteLine("验证实例文档时发生验证错误。");
                }

            if (args.Exception != null)//XSD架构验证错误   
            {
                Console.WriteLine(args.Exception.SourceUri + "," + args.Exception.LinePosition + "," + args.Exception.LineNumber);
            }
        }
    }
}
