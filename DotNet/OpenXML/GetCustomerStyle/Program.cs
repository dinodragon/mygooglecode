using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DocumentFormat.OpenXml.Packaging;
using System.IO;

namespace GetCustomerStyle
{
    class Program
    {
        static void Main(string[] args)
        {
            string doc1 = @"Word\含自定义样式.docx";
            using (WordprocessingDocument wordDoc1 = WordprocessingDocument.Open(doc1, false))
            {
                StyleDefinitionsPart part = wordDoc1.MainDocumentPart.StyleDefinitionsPart;
               
                
                //wordDoc1.MainDocumentPart.DiagramStyleParts;
            }

        }
    }
}
