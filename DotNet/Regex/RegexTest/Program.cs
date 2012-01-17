using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace RegexTest
{
    class Program
    {
        static void Main(string[] args)
        {
            //Regex regex = new Regex(@"^(?<proto>\w+)://[^/]+?(?<port>\d+)?/", RegexOptions.Compiled);
            string url = "ftp://172.19.41.114:2100/";
            Regex regex = new Regex(@"^\w+://(?<server>[^:]+):(?<port>\d+)", RegexOptions.Compiled);
            string server = regex.Match(url).Result("${server}");
            string port = regex.Match(url).Result("${port}");
            if (regex.IsMatch(url))
            {
                string result = regex.Match(url).Result("${server}:${port}");
                Console.WriteLine(result);
            }
            else
            {
                Console.WriteLine("没有匹配成功！");
            }
        }
    }
}
