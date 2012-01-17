using System;
using System.Collections.Generic;
using System.Text;

using System.Security.Cryptography;

namespace MD5
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine(md5(new byte[]{}));
        }

        public static string md5(string str)
        {
            MD5CryptoServiceProvider m = new MD5CryptoServiceProvider();
            byte[] s = m.ComputeHash(UnicodeEncoding.UTF8.GetBytes(str));
            string md5String = "";
            for (int i = 0; i < s.Length; i++)
            {
                md5String = md5String + s[i].ToString("X");
            }
            return md5String;
        }

        public static string md5(byte[] bytes)
        {
            if (bytes == null)
            {
                bytes = new byte[] { };
            }
            System.Security.Cryptography.MD5 md5Hasher = System.Security.Cryptography.MD5.Create();
            byte[] s = md5Hasher.ComputeHash(bytes);
            string md5String = "";
            for (int i = 0; i < s.Length; i++)
            {
                md5String = md5String + s[i].ToString("X");
            }
            return md5String;

        }
    }

}
