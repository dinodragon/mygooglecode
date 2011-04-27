using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ComInterface
{
    [ComVisible(true)]
    [Guid("FA8416DF-0F62-4ed5-99AD-0086E31BE566")]
    [ProgId("ComTest.ComServer")]
    public class ComTest:IComTest
    {
        public string GetTime()
        {
            return DateTime.Now.ToString();
        }
    }
}
