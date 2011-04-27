using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DynamicUI
{
    class ListItem
    {
        public string Value;
        public string Key;

        public ListItem(string Key, string Name)
        {
            this.Value = Name;
            this.Key = Key;
        }

        public override string ToString()
        {
            return Value;
        }
    }
}
