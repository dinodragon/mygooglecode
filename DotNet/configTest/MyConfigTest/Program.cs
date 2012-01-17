using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Configuration;

namespace MyConfigTest
{
    class Program
    {
        static void Main(string[] args)
        {
            //配置信息是只读的
            LogConfig config = (LogConfig)ConfigurationManager.GetSection("ePubLog");
            Console.WriteLine("Config.FileName:" + config.fileName);
            Console.WriteLine("Config.header:" + config.header.value);
            Console.WriteLine("Config.footer:" + config.footer.value);

            //修改配置
            Console.WriteLine("After Modify*******************************************");
            Configuration configInstance = ConfigurationManager.OpenExeConfiguration(ConfigurationUserLevel.None);
            LogConfig config2 = configInstance.GetSection("ePubLog") as LogConfig;
            config2.footer.value = "修改之后的新值";
            configInstance.Save();
            Console.WriteLine("Config.FileName:" + config2.fileName);
            Console.WriteLine("Config.header:" + config2.header.value);
            Console.WriteLine("Config.footer:" + config2.footer.value);
        }
    }
}
