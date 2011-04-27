using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DocumentFormat.OpenXml.Packaging;
using DocumentFormat.OpenXml.Wordprocessing;
using System.IO;
using System.Xml;

namespace DeleteHeaderFooter
{
    class Program
    {
        static void Main(string[] args)
        {
            string target = @"d:\复件 template.docx";
            WDRemoveHeadersFooters(target);
        }

        public static void WDRemoveHeadersFooters(string docName)
        {
            // Given a document name, remove all headers and footers.

            const string wordmlNamespace = "http://schemas.openxmlformats.org/wordprocessingml/2006/main";

            using (WordprocessingDocument wdDoc = WordprocessingDocument.Open(docName, true))
            {
                if (wdDoc.MainDocumentPart.GetPartsCountOfType<HeaderPart>() > 0 ||
                  wdDoc.MainDocumentPart.GetPartsCountOfType<FooterPart>() > 0)
                {
                    wdDoc.MainDocumentPart.DeleteParts(wdDoc.MainDocumentPart.HeaderParts);
                    wdDoc.MainDocumentPart.DeleteParts(wdDoc.MainDocumentPart.FooterParts);

                    // Manage namespaces to perform XPath queries.
                    NameTable nt = new NameTable();
                    XmlNamespaceManager nsManager = new XmlNamespaceManager(nt);
                    nsManager.AddNamespace("w", wordmlNamespace);

                    // Get the document part from the package.
                    // Load the XML in the document part into an XmlDocument instance.
                    XmlDocument xdoc = new XmlDocument(nt);
                    xdoc.Load(wdDoc.MainDocumentPart.GetStream());

                    // Find the node that contains the document layout.
                    XmlNodeList layoutNodes = xdoc.SelectNodes("//w:sectPr", nsManager);
                    foreach (System.Xml.XmlNode layoutNode in layoutNodes)
                    {
                        // Delete existing references to headers.
                        XmlNodeList headerNodes = layoutNode.SelectNodes("./w:headerReference", nsManager);
                        foreach (System.Xml.XmlNode headerNode in headerNodes)
                        {
                            layoutNode.RemoveChild(headerNode);
                        }

                        // Delete existing references to footers.
                        XmlNodeList footerNodes = layoutNode.SelectNodes("./w:footerReference", nsManager);
                        foreach (System.Xml.XmlNode footerNode in footerNodes)
                        {
                            layoutNode.RemoveChild(footerNode);
                        }
                    }

                    // Save the document XML back to its document part.
                    xdoc.Save(wdDoc.MainDocumentPart.GetStream(FileMode.Create));
                }
            }
        }
    }
}
