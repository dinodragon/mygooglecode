using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using DocumentFormat.OpenXml.Packaging;
using System.IO;
using System.Xml;

namespace AcceptAllRevision
{
    class Program
    {
        static void Main(string[] args)
        {
            string target = @".\..\..\..\新算法合成结果.docx";
            WDAcceptRevisions(target, null);
        }

        public static void WDAcceptRevisions(string docName, string authorName)
        {
            // Given a document name and an author name, accept revisions. 
            // Note: To accept all revisions, leave the author name blank.    

            const string wordmlNamespace = "http://schemas.openxmlformats.org/wordprocessingml/2006/main";

            using (WordprocessingDocument wdDoc = WordprocessingDocument.Open(docName, true))
            {
                // Manage namespaces to perform XML XPath queries.
                NameTable nt = new NameTable();
                XmlNamespaceManager nsManager = new XmlNamespaceManager(nt);
                nsManager.AddNamespace("w", wordmlNamespace);

                // Get the document part from the package.
                XmlDocument xdoc = new XmlDocument(nt);
                // Load the XML in the document part into an XmlDocument instance.
                xdoc.Load(wdDoc.MainDocumentPart.GetStream());

                // Handle the formatting changes.
                XmlNodeList nodes = null;
                if (string.IsNullOrEmpty(authorName))
                {
                    nodes = xdoc.SelectNodes("//w:pPrChange", nsManager);
                }
                else
                {
                    nodes = xdoc.SelectNodes(string.Format("//w:pPrChange[@w:author='{0}']", authorName), nsManager);
                }
                foreach (System.Xml.XmlNode node in nodes)
                {
                    node.ParentNode.RemoveChild(node);
                }

                // Handle the deletions.
                if (string.IsNullOrEmpty(authorName))
                {
                    nodes = xdoc.SelectNodes("//w:del", nsManager);
                }
                else
                {
                    nodes = xdoc.SelectNodes(string.Format("//w:del[@w:author='{0}']", authorName), nsManager);
                }

                foreach (System.Xml.XmlNode node in nodes)
                {
                    node.ParentNode.RemoveChild(node);
                }


                // Handle the insertions.
                if (string.IsNullOrEmpty(authorName))
                {
                    nodes = xdoc.SelectNodes("//w:ins", nsManager);
                }
                else
                {
                    nodes = xdoc.SelectNodes(string.Format("//w:ins[@w:author='{0}']", authorName), nsManager);
                }

                foreach (System.Xml.XmlNode node in nodes)
                {
                    // Found new content.
                    // Promote them to the same level as node, and then
                    // delete the node.
                    XmlNodeList childNodes;
                    childNodes = node.SelectNodes(".//w:r", nsManager);
                    foreach (System.Xml.XmlNode childNode in childNodes)
                    {
                        if (childNode == node.FirstChild)
                        {
                            node.ParentNode.InsertAfter(childNode, node);
                        }
                        else
                        {
                            node.ParentNode.InsertAfter(childNode, node.NextSibling);
                        }
                    }
                    node.ParentNode.RemoveChild(node);

                    // Remove the modification ID from the node 
                    // so the consumer can merge it on the next save.
                    node.Attributes.RemoveNamedItem("w:rsidR");
                    node.Attributes.RemoveNamedItem("w:rsidRPr");
                }

                // Save the document XML back to its document part.
                xdoc.Save(wdDoc.MainDocumentPart.GetStream(FileMode.Create));
            }
        }

    }
}
