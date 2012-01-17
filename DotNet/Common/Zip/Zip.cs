using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace Zip
{
    public class Zip
    {
        public static int Add(string zipFilePath, string filePath, string password)
        {
            if (String.IsNullOrEmpty(zipFilePath) || String.IsNullOrEmpty(filePath))
            {
                return -1;
            }
            string cmdString = String.Empty;
            if (String.IsNullOrEmpty(password))
            {
                cmdString = String.Format("a -tzip -r \"{0}\" \"{1}\" -y", zipFilePath, filePath);
            }
            else
            {
                cmdString = String.Format("a -tzip -r \"{0}\" \"{1}\"  -p{2} -y", zipFilePath, filePath,password);
            }
            try
            {
                ProcessStartInfo ps = new ProcessStartInfo("7z.exe", cmdString);
                ps.UseShellExecute = false;
                ps.CreateNoWindow = true;
                //ps.RedirectStandardOutput = true;
                //ps.RedirectStandardError = true;
                Process p = Process.Start(ps);
                p.WaitForExit();
                //string output = p.StandardOutput.ReadToEnd();
                //string aa = p.StandardError.ReadToEnd();
                //int nReturn = p.ExitCode;
            }
            catch (System.Exception ex)
            {
                Debug.Print(ex.ToString());
            }
            return System.IO.File.Exists(zipFilePath) ? 0 : -1;
        }

        static public int Extract(string zipFilePath, string outPath, string extractFileName, string password)
        {
            string cmdString = String.Empty;
            if (String.IsNullOrEmpty(extractFileName) && String.IsNullOrEmpty(password))
            {
                cmdString = String.Format("X \"{0}\" -o\"{1}\" -y", zipFilePath, outPath);
            }
            else if (String.IsNullOrEmpty(extractFileName) && !String.IsNullOrEmpty(password))
            {
                cmdString = String.Format("X \"{0}\" -o\"{1}\" -p{2} -y", zipFilePath, outPath, password);
            }
            else if (!String.IsNullOrEmpty(extractFileName) && String.IsNullOrEmpty(password))
            {
                cmdString = String.Format("e \"{0}\" \"{1}\" -o\"{2}\" -y", zipFilePath, extractFileName,outPath);
            }
            else if (!String.IsNullOrEmpty(extractFileName) && !String.IsNullOrEmpty(password))
            {
                cmdString = String.Format("e \"{0}\" \"{1}\" -o\"{2}\" -p{3} -y", zipFilePath,extractFileName, outPath,password);
            }
            else
            {
                return -1;
            }

            try
            {
                ProcessStartInfo ps = new ProcessStartInfo("7z.exe", cmdString);
                ps.UseShellExecute = false;
                ps.CreateNoWindow = true;
                Process p = Process.Start(ps);
                p.WaitForExit();
            }
            catch (System.Exception ex)
            {
                Debug.Print(ex.ToString());
                return -1;
            }
            return 0;
        }

        static public int Erase(string zipFilePath, string filePath, string password)
        {
            if (String.IsNullOrEmpty(zipFilePath) || String.IsNullOrEmpty(filePath))
            {
                return -1;
            }
            string cmdString = String.Empty;
            if (String.IsNullOrEmpty(password))
            {
                cmdString = String.Format("d -r \"{0}\" \"{1}\" -y", zipFilePath, filePath);
            }
            else
            {
                cmdString = String.Format("d -r \"{0}\" \"{1}\"  -p{2} -y", zipFilePath, filePath, password);
            }
            try
            {
                ProcessStartInfo ps = new ProcessStartInfo("7z.exe", cmdString);
                ps.UseShellExecute = false;
                ps.CreateNoWindow = true;
                Process p = Process.Start(ps);
                p.WaitForExit();
            }
            catch (System.Exception ex)
            {
                Debug.Print(ex.ToString());
                return -1;
            }
            return 0;
        }
    }
}
