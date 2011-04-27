using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DocumentFormat.OpenXml.Packaging;
using System.IO;


namespace ReplaceHeaderAndFooter
{
    class Program
    {
        static void Main(string[] args)
        {
            string target = @".\..\..\..\target.docx";
            string source = @".\..\..\..\source.docx";
            ReplaceHeader(source, target);
        }

        public static void ReplaceHeader(string fromDocument1, string toDocument2)
        {
            //using (WordprocessingDocument wordDoc1 = WordprocessingDocument.Open(fromDocument1, false))
            //using (WordprocessingDocument wordDoc2 = WordprocessingDocument.Open(toDocument2, true))
            //{
            //    StyleDefinitionsPart stylePart1 = wordDoc1.MainDocumentPart.HeaderParts.ToArray;
            //    StyleDefinitionsPart stylePart2 = wordDoc2.MainDocumentPart.StyleDefinitionsPart;

            //    //using (StreamReader streamReader = new StreamReader(stylePart1.GetStream()))
            //    //using (StreamWriter streamWriter = new StreamWriter(stylePart2.GetStream(FileMode.Create)))
            //    //{
            //    //    streamWriter.Write(streamReader.ReadToEnd());
            //    //}
            //}
        }
    }
}
