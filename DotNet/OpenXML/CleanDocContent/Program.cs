using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DocumentFormat.OpenXml.Packaging;
using System.IO;
using MSWord = Microsoft.Office.Interop.Word;
using DocumentFormat.OpenXml.Wordprocessing;

namespace CleanDocContent
{
    class Program
    {
        static void Main(string[] args)
        {
            string target = @"d:\template.docx";
            cleanDocContent(target);
            UpdateFields(target);
        }

        public static void cleanDocContent(string templateDocument)
        {
            using (WordprocessingDocument document = WordprocessingDocument.Open(templateDocument, true))
            {
                document.MainDocumentPart.Document.Body.RemoveAllChildren<DocumentFormat.OpenXml.Wordprocessing.Paragraph>();
                document.MainDocumentPart.Document.Body.RemoveAllChildren<DocumentFormat.OpenXml.Wordprocessing.Table>();
                //document.MainDocumentPart.Document.Body.RemoveAllChildren();
                document.MainDocumentPart.Document.Save();
            }
        }

        static void UpdateFields(string target)
        {
            MSWord._Application application = new MSWord.ApplicationClass();

            object missing = Type.Missing;
            object fileName = Path.Combine(System.Environment.CurrentDirectory, target);
            object visible = false;

            MSWord._Document wordDocument = application.Documents.Open(ref fileName,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref visible,
                            ref missing,
                            ref missing,
                            ref missing,
                            ref missing);

            MSWord.Fields fields = wordDocument.Fields;
            fields.Update();

            object saveChanges = MSWord.WdSaveOptions.wdSaveChanges;
            //让他强制保存一次以更新文档内容，将afaltchunk更新到文档内容中。
            wordDocument.Saved = false;
            wordDocument.Close(ref saveChanges, ref missing, ref missing);

            object saveWithOutChanges = MSWord.WdSaveOptions.wdDoNotSaveChanges;
            application.Quit(ref saveWithOutChanges, ref missing, ref missing);
        }
    }
}
