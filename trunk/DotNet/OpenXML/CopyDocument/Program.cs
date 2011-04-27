using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DocumentFormat.OpenXml.Packaging;
using System.IO;

namespace CopyDocument
{
    class Program
    {
        static void Main(string[] args)
        {
            string target = @".\..\..\..\target.docx";
            string source = @".\..\..\..\source.docx";
            CopyThemeContent(source,target);
        }

        public static void CopyThemeContent(string fromDocument1, string toDocument2)
        {
            using (WordprocessingDocument wordDoc1 = WordprocessingDocument.Open(fromDocument1, false))
            using (WordprocessingDocument wordDoc2 = WordprocessingDocument.Open(toDocument2, true))
            {
                ThemePart themePart1 = wordDoc1.MainDocumentPart.ThemePart;
                ThemePart themePart2 = wordDoc2.MainDocumentPart.ThemePart;

                using (StreamReader streamReader = new StreamReader(themePart1.GetStream()))
                using (StreamWriter streamWriter = new StreamWriter(themePart2.GetStream(FileMode.Create)))
                {
                    streamWriter.Write(streamReader.ReadToEnd());
                }
            }
        }
    }
}
