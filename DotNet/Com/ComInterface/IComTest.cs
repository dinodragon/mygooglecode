using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ComInterface
{
    [ComVisible(true)]
    [Guid("7EBD4911-446D-4ef8-A3EA-A684A3BCB85F")]
    public interface IComTest
    {
        [DispId(1)]
        string GetTime();
    }
}
