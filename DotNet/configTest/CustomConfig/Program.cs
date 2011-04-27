using System;
using System.Collections;
using System.Text;
using System.Configuration;
using System.Xml;

//MSDN示例


namespace MyConfigSectionHandler
{
    class Program
    {
        static void Main(string[] args)
        {
            //MyConfigSectionHandler.MyHandler config =
            //(MyConfigSectionHandler.MyHandler)System.Configuration.ConfigurationManager.GetSection(
            //"myCustomGroup/myCustomSection");


            MyHandler config = (MyHandler)ConfigurationManager.GetSection("myCustomGroup/myCustomSection");
        }
    }


    public class MyHandler : ConfigurationSection
    {
        public MyHandler()
        {
        }

        public MyHandler(String attribVal)
        {
            MyAttrib1 = attribVal;
        }

        [ConfigurationProperty("myAttrib1", DefaultValue = "Clowns", IsRequired = true)]
        [StringValidator(InvalidCharacters = "~!@#$%^&*()[]{}/;'\"|\\", MinLength = 1, MaxLength = 60)]
        public String MyAttrib1
        {
            get
            {
                return (String)this["myAttrib1"]; 
            }
            set
            {
                this["myAttrib1"] = value; 
            }
        }


        [ConfigurationProperty("myChildSection")]
        public MyChildConfigElement MyChildSection
        {
            get
            {
                return (MyChildConfigElement)this["myChildSection"]; 
            }
            set
            {
                this["myChildSection"] = value; 
            }
        }
    }

    public class MyChildConfigElement : ConfigurationElement
    {
        public MyChildConfigElement()
        {
        }

        public MyChildConfigElement(String a1, String a2)
        {
            MyChildAttribute1 = a1;
            MyChildAttribute2 = a2;
        }

        [ConfigurationProperty("myChildAttrib1", DefaultValue = "Zippy", IsRequired = true)]
        [StringValidator(InvalidCharacters = "~!@#$%^&*()[]{}/;'\"|\\", MinLength = 1, MaxLength = 60)]
        public String MyChildAttribute1
        {
            get
            {
                return (String)this["myChildAttrib1"]; 
            }
            set
            {
                this["myChildAttrib1"] = value; 
            }
        }


        [ConfigurationProperty("myChildAttrib2", DefaultValue = "Michael Zawondy", IsRequired = true)]
        [StringValidator(InvalidCharacters = "~!@#$%^&*()[]{}/;'\"|\\", MinLength = 1, MaxLength = 60)]
        public String MyChildAttribute2
        {
            get
            {
                return (String)this["myChildAttrib2"]; 
            }
            set
            {
                this["myChildAttrib2"] = value; 
            }
        }
    }
}
