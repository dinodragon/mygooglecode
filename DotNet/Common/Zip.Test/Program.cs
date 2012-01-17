using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Zip.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            Zip.Add(@"G:\test.zip", @"G:\TelnetServer\*.*", "a");
            Zip.Extract(@"G:\test.zip", @"G:\ya", "MyDialog.h", "a");
            //Zip.Erase(@"G:\test.zip", @"PeerYou\PeerYouC", "a");
        }
    }
}
