using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FtpUploadDll;

namespace FtpUploadDllTest
{
    class Program
    {

        static void Main(string[] args)
        {
            FtpUpLoader ftp = new FtpUpLoader();
            ftp.UploadCompleted += new UploadEvent(ftp_UploadEvent);
            ftp.UploadError += new UploadEvent(ftp_UploadEvent);
            ftp.UploadGuage += new UploadEvent(ftp_UploadEvent);
            ftp.Upload(@"ftp://bwang2/test/a1.pdf", @"f:\aa.pdf");
            ftp.Upload(@"ftp://bwang2/test/a2.pdf", @"f:\aa.pdf");
            ftp.Upload(@"ftp://bwang2/test/a3.pdf", @"f:\aa.pdf");
            ftp.Upload(@"ftp://bwang2/test/a4.pdf", @"f:\aa.pdf");
            ftp.Upload(@"ftp://bwang2/test/a5.pdf", @"f:\aa.pdf");
            ftp.Upload(@"ftp://bwang2/test/a6.pdf", @"f:\aa.pdf");
            ftp.Upload(@"ftp://bwang2/test/a7.pdf", @"f:\aa.pdf");
            ftp.Upload(@"ftp://bwang2/test/a8.pdf", @"f:\aa.pdf");
            Console.ReadKey();
        }

        static void ftp_UploadEvent(FtpUploadEvent uploadEvent, object param)
        {
            Console.WriteLine(uploadEvent.ToString());
            Console.WriteLine(param.ToString());
        }
    }
}
