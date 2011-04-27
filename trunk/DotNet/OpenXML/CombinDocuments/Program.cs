using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using DocumentFormat.OpenXml.Packaging;
using System.Xml;
using System.Xml.Linq;
using DocumentFormat.OpenXml.Wordprocessing;


class Program
{
    static void Main(string[] args)
    {
        string insDoc = @".\..\..\..\source.docx";
        string target = @".\..\..\..\target.docx";
        CombinDoc(target, insDoc);
    }

    private static void CombinDoc1(string target, string source)
    {
        using (WordprocessingDocument myDoc = WordprocessingDocument.Open("Test1.docx", true))
        {
            string altChunkId = "AltChunkId1";
            MainDocumentPart mainPart = myDoc.MainDocumentPart;
            AlternativeFormatImportPart chunk = mainPart.AddAlternativeFormatImportPart(
                AlternativeFormatImportPartType.WordprocessingML, altChunkId);
            using (FileStream fileStream = File.Open("TestInsertedContent.docx", FileMode.Open))
                chunk.FeedData(fileStream);
            AltChunk altChunk = new AltChunk();
            altChunk.Id = altChunkId;
            mainPart.Document
                .Body
                .InsertAfter(altChunk, mainPart.Document.Body.Elements<Paragraph>().Last());
            mainPart.Document.Save();
        }

    }

    private static void CombinDoc(string target, string source)
    {
        XNamespace w =
            "http://schemas.openxmlformats.org/wordprocessingml/2006/main";
        XNamespace r =
            "http://schemas.openxmlformats.org/officeDocument/2006/relationships";


        using (WordprocessingDocument myDoc = WordprocessingDocument.Open(target, true))
        {
            string altChunkId = "AltChunkId1" + Guid.NewGuid();
            MainDocumentPart mainPart = myDoc.MainDocumentPart;
            AlternativeFormatImportPart chunk = mainPart.AddAlternativeFormatImportPart(
              "application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml",
              altChunkId);
            using (FileStream fileStream =
                File.Open(source, FileMode.Open))
                chunk.FeedData(fileStream);
            XElement altChunk = new XElement(w + "altChunk",
                new XAttribute(r + "id", altChunkId)
            );
            XDocument mainDocumentXDoc = GetXDocument(myDoc);

            Paragraph paragraph = myDoc.MainDocumentPart.Document.Descendants<Paragraph>().Last();

            // Add the altChunk element after the last paragraph.
            mainDocumentXDoc.Root.Element(w + "body").Elements(w + "p").Last().AddAfterSelf(altChunk);

            SaveXDocument(myDoc, mainDocumentXDoc);
        }
    }

    private static void SaveXDocument(WordprocessingDocument myDoc,
        XDocument mainDocumentXDoc)
    {
        // Serialize the XDocument back into the part
        using (Stream str = myDoc.MainDocumentPart.GetStream(
            FileMode.Create, FileAccess.Write))
        using (XmlWriter xw = XmlWriter.Create(str))
            mainDocumentXDoc.Save(xw);
    }


    private static XDocument GetXDocument(WordprocessingDocument myDoc)
    {
        // Load the main document part into an XDocument
        XDocument mainDocumentXDoc;
        using (Stream str = myDoc.MainDocumentPart.GetStream())
        using (XmlReader xr = XmlReader.Create(str))
            mainDocumentXDoc = XDocument.Load(xr);
        return mainDocumentXDoc;
    }
}
