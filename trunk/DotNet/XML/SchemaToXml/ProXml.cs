using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Xml;
using System.Xml.Schema;
using System.Collections;


/**/
/// <summary>
/// ProXML 的摘要说明
/// </summary>
public class ProXml
{
    public ProXml()
    {
        //
        // TODO: 在此处添加构造函数逻辑
        //
    }
    /**/
    /// <summary>
    /// 获得xsd文件路径
    /// </summary>
    public static string GetSchemaPath
    {
        get
        {
            return @"Data\bookschema.xsd";
        }
    }
    /**/
    /// <summary>
    /// 获理节点
    /// </summary>
    /// <returns></returns>
    public static System.Collections.Generic.List<XmlSchemaElement> GetDatas()
    {
        XmlSchemaSet xsSet = new XmlSchemaSet();
        xsSet.Add("http://www.w3.org/2001/XMLSchema", GetSchemaPath);
        xsSet.Compile();
        XmlSchema schema = null;
        foreach (XmlSchema xs in xsSet.Schemas())
        {
            schema = xs;
        }
        System.Collections.Generic.List<XmlSchemaElement> elements = new System.Collections.Generic.List<XmlSchemaElement>();
        foreach (XmlSchemaObject obj in schema.Elements.Values)
        {
            if (obj.GetType() == typeof(XmlSchemaElement))
            {
                elements.Add((XmlSchemaElement)obj);
            }

        }
        return elements;

    }
    /**/
    /// <summary>
    /// 添加元素
    /// </summary>
    /// <param name="sourceXsd"></param>
    /// <param name="titles"></param>
    /// <param name="sourceXml"></param>
    /// <param name="sourceNd"></param>
    /// <param name="values"></param>
    public static void AddElement(XmlSchemaObject sourceXsd, Hashtable titles, XmlDocument sourceXml, XmlNode sourceNd, string[] values)
    {

        if (sourceXsd.GetType() == typeof(XmlSchemaChoice))
        {
            XmlSchemaChoice choice = sourceXsd as XmlSchemaChoice;
            decimal min = choice.MinOccurs;
            foreach (XmlSchemaObject item in choice.Items)
            {
                if (item.GetType() == typeof(XmlSchemaElement))
                {
                    string name = ((XmlSchemaElement)item).Name;
                    if (titles.ContainsKey(name))
                    {
                        XmlElement element = sourceXml.CreateElement(name);
                        // element.InnerText = ((Excel.Range)st.Cells[rowIndex, (int)titles[name]]).Value2.ToString();
                        element.InnerText = values[(int)titles[name]];
                        sourceNd.AppendChild(element);
                    }

                }
                else
                {
                    AddElement(item, titles, sourceXml, sourceNd, values);
                }

            }


        }
        else if (sourceXsd.GetType() == typeof(XmlSchemaElement))
        {
            string name = ((XmlSchemaElement)sourceXsd).Name;
            if (titles.ContainsKey(name))
            {
                XmlElement element = sourceXml.CreateElement(name);
                element.InnerText = values[(int)titles[name]];
                sourceNd.AppendChild(element);
            }

        }
        else if (sourceXsd.GetType() == typeof(XmlSchemaSequence))
        {
            foreach (XmlSchemaObject childItem in ((XmlSchemaSequence)sourceXsd).Items)
            {
                if (childItem.GetType() == typeof(XmlSchemaElement))
                {
                    string name = ((XmlSchemaElement)childItem).Name;
                    if (titles.ContainsKey(name))
                    {
                        XmlElement element = sourceXml.CreateElement(name);
                        element.InnerText = values[(int)titles[name]];
                        sourceNd.AppendChild(element);
                    }
                }
                else
                {
                    AddElement(childItem, titles, sourceXml, sourceNd, values);
                }

            }
        }
        else
        {
            return;
        }
    }
    /**/
    /// <summary>
    /// 获得元素
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    public static System.Collections.Generic.List<XmlSchemaElement> GetDataItem(string name)
    {
        System.Collections.Generic.List<XmlSchemaElement> arr = new System.Collections.Generic.List<XmlSchemaElement>();
        XmlSchemaElement element = GetTableSchema(name);
        if (element == null)
        {
            return null;
        }
        XmlSchemaComplexType complex = element.SchemaType as XmlSchemaComplexType;
        XmlSchemaSequence sequence = complex.ContentTypeParticle as XmlSchemaSequence;

        foreach (XmlSchemaObject obj in sequence.Items)
        {
            if (obj.GetType() == typeof(XmlSchemaElement))
            {
                XmlSchemaElement item = (XmlSchemaElement)obj;
                arr.Add(item);

            }
            else
            {
                GetItem(arr, obj);
            }
        }
        return arr;
    }
    public static void GetItem(System.Collections.Generic.List<XmlSchemaElement> arr, XmlSchemaObject obj)
    {
        if (obj.GetType() == typeof(XmlSchemaElement))
        {
            XmlSchemaElement item = (XmlSchemaElement)obj;
            arr.Add(item);
        }
        else if (obj.GetType() == typeof(XmlSchemaChoice))
        {
            XmlSchemaChoice choice = obj as XmlSchemaChoice;
            foreach (XmlSchemaObject child in choice.Items)
            {
                if (child.GetType() == typeof(XmlSchemaElement))
                {
                    XmlSchemaElement item = child as XmlSchemaElement;
                    arr.Add(item);
                }
                else
                {
                    GetItem(arr, child);
                }
            }
        }
        else if (obj.GetType() == typeof(XmlSchemaSequence))
        {
            XmlSchemaSequence sequence = obj as XmlSchemaSequence;
            foreach (XmlSchemaObject child in sequence.Items)
            {
                if (child.GetType() == typeof(XmlSchemaObject))
                {
                    XmlSchemaElement item = child as XmlSchemaElement;
                    arr.Add(item);
                }
                else
                {
                    GetItem(arr, child);
                }
            }
        }
        else
        {
            return;
        }
    }
    /**/
    /// <summary>
    /// 根据节点名获得节点
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    public static XmlSchemaElement GetTableSchema(string name)
    {
        XmlSchemaSet xsSet = new XmlSchemaSet();
        xsSet.Add("http://www.w3.org/2001/XMLSchema", GetSchemaPath);
        xsSet.Compile();
        XmlSchema schema = null;
        foreach (XmlSchema xs in xsSet.Schemas())
        {
            schema = xs;
        }
        XmlQualifiedName qf = new XmlQualifiedName(name, "http://www.w3.org/2001/XMLSchema");
        if (schema.Elements.Contains(qf))
        {
            return (XmlSchemaElement)schema.Elements[qf];
        }
        return null;

    }
    static void XmlValidation(object sendor, ValidationEventArgs e)
    {
        switch (e.Severity)
        {
            case XmlSeverityType.Error:
                throw e.Exception;

            case XmlSeverityType.Warning:
                throw e.Exception;


        }

    }
    /**/
    /// <summary>
    /// 校验dom对象
    /// </summary>
    /// <param name="doc"></param>
    /// <returns></returns>
    public static string CheckDataXml(XmlDocument doc)
    {
        XmlSchemaSet xsd = new XmlSchemaSet();
        xsd.Add("", GetSchemaPath);
        doc.Schemas = xsd;
        try
        {
            doc.Validate(new ValidationEventHandler(XmlValidation));
        }
        catch (Exception ex)
        {
            return ex.Message;
        }
        return null;
    }
}
