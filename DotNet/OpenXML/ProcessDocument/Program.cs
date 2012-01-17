using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using DocumentFormat.OpenXml;
using DocumentFormat.OpenXml.Packaging;
using DocumentFormat.OpenXml.Wordprocessing;

using MSWord = Microsoft.Office.Interop.Word;
using System.IO;

//文档合并

namespace ProcessDocument
{
    class Program
    {
        static void Main(string[] args)
        {
            string target = @".\..\..\..\target.docx";
            string source = @".\..\..\..\source.docx";

            WordprocessingDocument targetDocument = WordprocessingDocument.Open(target, true);

            using (targetDocument)
            {
                string altChunkId = "AltChunkId1";
                AlternativeFormatImportPart importPart = targetDocument.MainDocumentPart.
                    AddAlternativeFormatImportPart("application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml",
              altChunkId
                    );
                using (StreamReader reader = new StreamReader(source))
                    importPart.FeedData(reader.BaseStream);

                AltChunk altChunk = new AltChunk();
                altChunk.Id = altChunkId;
                targetDocument.MainDocumentPart.Document
                    .Body
                    .InsertAfter(altChunk, targetDocument.MainDocumentPart.Document.Body.Elements<Paragraph>().Last());
                targetDocument.MainDocumentPart.Document.Save();                    
            }

            //UpdateFields(target);
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
