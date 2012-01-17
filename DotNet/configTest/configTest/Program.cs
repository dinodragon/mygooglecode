using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Xml;

namespace configTest
{
    class Program
    {
        static void Main(string[] args)
        {
            ClientSetting set = ConfigurationManager.GetSection("clientSetting") as ClientSetting;
            object o = ConfigurationManager.GetSection("clientSetting");
            Console.WriteLine(set.Server.Value);
            object o2 = ConfigurationManager.GetSection("connectionStrings");
            object IDTest1 = ConfigurationManager.GetSection("Test1");
            //string str = (string)IDTest1["setting1"] +" "+(string)IDTest1["setting2"];
            //object set2 = ConfigurationManager.GetSection("clientSetting");
        }
    }


    public class ClientSetting : ConfigurationSection
    {
        [ConfigurationProperty("server")]
        public ClientSettingElement Server
        {
            get
            {
                ClientSettingElement value =
                (ClientSettingElement)this["server"];
                return value;
            }
        }

        [ConfigurationProperty("user")]
        public ClientSettingElement User
        {
            get
            {
                ClientSettingElement value =
                (ClientSettingElement)this["user"];
                return value;
            }
        }

        [ConfigurationProperty("workFolderPath")]
        public ClientSettingElement WorkFolderPath
        {
            get
            {
                ClientSettingElement value =
                (ClientSettingElement)this["workFolderPath"];
                return value;
            }

        }

    }
    public class ClientSettingElement : ConfigurationElement
    {
        [ConfigurationProperty("value", IsRequired = true)]
        public string Value
        {
            get { return (string)this["value"]; }
            set { this["value"] = value; }
        }
    }
}
