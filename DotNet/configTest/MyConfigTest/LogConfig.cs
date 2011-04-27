using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;

namespace MyConfigTest
{
    public class LogConfig : ConfigurationSection
    {
        [ConfigurationProperty("fileName", DefaultValue = "log.txt", IsRequired = true)]
        [StringValidator(InvalidCharacters = "~!@#$%^&*()[]{}/;'\"|\\", MinLength = 1, MaxLength = 60)]
        public String fileName
        {
            get
            {
                return (String)this["fileName"];
            }
            set
            {
                this["fileName"] = value;
            }
        }

        [ConfigurationProperty("header")]
        public LogConfigElement header
        {
            get
            {
                return ((LogConfigElement)this["header"]);
            }
        }

        [ConfigurationProperty("footer")]
        public LogConfigElement footer
        {
            get
            {
                return (LogConfigElement)this["footer"];
            }
        }
    }

    public class LogConfigElement : ConfigurationElement
    {
        [ConfigurationProperty("value", DefaultValue = "--------", IsRequired = true)]
        [StringValidator(InvalidCharacters = "~!@#$%^&*()[]{}/;'\"|\\", MinLength = 1, MaxLength = 60)]
        public String value
        {
            get
            {
                return (String)this["value"];
            }
            set
            {
                this["value"] = value;
            }
        }
    }
}
