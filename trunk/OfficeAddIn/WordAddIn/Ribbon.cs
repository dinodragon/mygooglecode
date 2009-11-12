using System;
using System.Collections.Generic;
using System.Text;
using Office = Microsoft.Office.Core;
using System.Runtime.InteropServices;

namespace WordAddIn
{
    [ComVisible(true)]
    public class Ribbon : Office.IRibbonExtensibility
    {
        public string GetCustomUI(string RibbonID)
        {
            return Properties.Resources.Ribbon;
        }
    }
}
