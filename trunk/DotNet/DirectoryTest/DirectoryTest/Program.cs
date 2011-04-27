using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace DirectoryTest
{
    class Program
    {
        static StreamWriter _sw = new StreamWriter(@"d:\log.txt", true);
        static string lastFilePath = "";
        static string lastTifPath = "";
        static void Main(string[] args)
        {
            ListFiles(new DirectoryInfo(@"\\test_server\机工社样张"));
        }

        public static void ListFiles(FileSystemInfo info)
        {
            if (!info.Exists) return;

            DirectoryInfo dir = info as DirectoryInfo;
            //如果不是目录
            if (dir == null) return;

            FileSystemInfo[] files = dir.GetFileSystemInfos();
            //遍历这个目录
            for (int i = 0; i < files.Length; i++)
            {
                FileInfo file = files[i] as FileInfo;
                //是文件
                if (file != null)
                {
                    if (file.Extension == ".pro" || file.Extension == ".fbd")
                    {
                        //this.list1.Items.Add(file);

                        _sw.Write(file.FullName + "\t");
                        _sw.WriteLine(GetRelationPictureDir(file.DirectoryName));
                        Console.Write(file.FullName + ",");
                        Console.WriteLine(GetRelationPictureDir(file.DirectoryName));
                        _sw.Flush();
                    }
                }
                //对于子目录，进行递归调用
                else
                {
                    ListFiles(files[i]);
                }
            }
        }

        public static string  GetRelationPictureDir(string path)
        {
            if (path == lastFilePath)
            {
                return lastTifPath;
            }
            lastFilePath = path;
            DirectoryInfo dir = new DirectoryInfo(path);
            //先找子目录
            FileSystemInfo[] files = dir.GetFileSystemInfos();
            foreach (FileSystemInfo item in files)
            {
                DirectoryInfo dirInfo = item as DirectoryInfo;
                if (dirInfo != null && isDirectoryContainTIF(dirInfo.FullName))
                {
                    lastTifPath = dirInfo.FullName;
                    return lastTifPath;
                }
                //子目录向下搜索一次
                else if (dirInfo != null && dirInfo.FullName != dir.FullName)
                {
                    FileSystemInfo[] subfiles = dirInfo.GetFileSystemInfos();
                    foreach (FileSystemInfo item2 in subfiles)
                    {
                        DirectoryInfo subDirInfo = item2 as DirectoryInfo;
                        if (subDirInfo != null && isDirectoryContainTIF(item2.FullName))
                        {
                            lastTifPath = item2.FullName;
                            return lastTifPath;
                        }
                    }
                }
            }

            //再找上级目录
            DirectoryInfo parentDir = dir.Parent;
            files = parentDir.GetFileSystemInfos();
            foreach (FileSystemInfo item in files)
            {
                DirectoryInfo dirInfo = item as DirectoryInfo;
                if (dirInfo != null && dirInfo.FullName!=dir.FullName &&
                    isDirectoryContainTIF(dirInfo.FullName))
                {
                    lastTifPath = dirInfo.FullName;
                    return lastTifPath;
                }
                else if (dirInfo != null && dirInfo.FullName!=dir.FullName )
                {
                    FileSystemInfo[] subfiles = dirInfo.GetFileSystemInfos();
                    foreach (FileSystemInfo item2 in subfiles)
                    {
                        DirectoryInfo subDirInfo = item2 as DirectoryInfo;
                        if (subDirInfo != null && isDirectoryContainTIF(item2.FullName))
                        {
                            lastTifPath = item2.FullName;
                            return lastTifPath;
                        }
                        else if (subDirInfo != null)
                        {
                            FileSystemInfo[] subsubfiles = subDirInfo.GetFileSystemInfos();
                            foreach (FileSystemInfo item3 in subsubfiles)
                            {
                                DirectoryInfo subsubDirInfo = item3 as DirectoryInfo;
                                if (subsubDirInfo != null && isDirectoryContainTIF(item3.FullName))
                                {
                                    lastTifPath = item3.FullName;
                                    return lastTifPath;
                                }
                            }
                        }
                    }
                }
            }
            lastTifPath = "没有找到";
            return "没有找到";
        }

        public static bool isDirectoryContainTIF(string path)
        {
            FileSystemInfo[] files = (new DirectoryInfo(path)).GetFileSystemInfos();
            foreach (FileSystemInfo item in files)
            {
                if (item.Extension.ToLower() == ".tif")
                {
                    return true;
                }
            }
            return false;
        }
    }
}
