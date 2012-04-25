
#include <stdio.h> 
#include <string.h> 
#include <iostream>
#include <fstream>
#include <sys/stat.h> 
#include <fcntl.h>
#include <vector>
#include <sstream>
#include "Huffmancode.h"

std::ofstream targetFile;
//std::ifstream sourceFile; 

bool Write(const unsigned char *s,const size_t len)
{ 
	targetFile.write((const char *)s,(std::streamsize)len);
	return true; 
} 

//bool OpenFile(char* source,char* target)
//{
//    sourceFile.open(source,std::ios::in|std::ios::binary);
//    targetFile.open(target,std::ios::out|std::ios::binary);
//	if(!sourceFile.is_open())
//    { 
//        sourceFile.close(); 
//        printf("\n打开文件：'%s'失败!\n" ,target);
//        return false; 
//	}
//    else if(!targetFile.is_open())
//    {
//        targetFile.close();
//        printf("\n打开文件：'%s'失败!\n" ,source); 
//        return false; 
//	}else
//    { 
//		return true; 
//	} 
//}
//0 帮助 1 压缩 2 解压缩
int CommandLineParser(int argc,char *args[],std::vector<std::string> &inFiles,std::string &outFile)
{
	std::vector<std::string> commands;
	for (int i = 1;i < argc;++i)
	{
		commands.push_back(std::string(args[i]));
	}
	size_t iCmdSize = commands.size();
	int mode = 0;
	if (iCmdSize < 1)
	{
		mode = 0;
	}
	if (iCmdSize == 1)
	{
		mode = 2;//解压缩
		outFile = commands[iCmdSize - 1];
	}
	if (iCmdSize > 1)
	{
		mode = 1;//压缩
		for (unsigned i = 0;i < iCmdSize - 1;++i)
		{
			inFiles.push_back(commands[i]);
		}
		outFile = commands[iCmdSize - 1];
	}
	return mode;
}

void PrintUsage(){ 
	printf("\n以动态哈夫曼算法压缩或解压缩文件。\n\n"); 
	printf("\thfm -?\t\t\t\t显示帮助信息\n"); 
	printf("\thfm -e -i source -o target\t压缩文件\n"); 
	printf("\thfm -d -i source -o target\t解压缩文件\n\n"); 
}

class FileList
{
public:
	typedef struct _FileStruct
	{
		std::string fileName;
		long fileSize;
	}FileStruct;

private:
	size_t offset;
	std::vector<FileStruct> filelist;
public:
	std::vector<FileStruct> GetList()
	{
		return filelist;
	}

	void AddFile(std::string fileName)
	{
		FileStruct fs;
		fs.fileName = fileName;
		fs.fileSize = 0;
		std::ifstream targetFile;
		targetFile.open(fileName.c_str(),std::ios::in|std::ios::binary);
		if (targetFile.is_open())
		{
			targetFile.seekg(0, std::ios::end);
			std::streamoff length = targetFile.tellg();
			fs.fileSize = length;
		}
		targetFile.close();
		filelist.push_back(fs);
	}

	std::vector<unsigned char> serialization()
	{
		std::stringstream ssfiles;
		for (unsigned i = 0;i < filelist.size(); ++i)
		{
			ssfiles << ";" << filelist[i].fileName.c_str();
			ssfiles << "," << filelist[i].fileSize;
		}
		offset = ssfiles.str().size() + sizeof(offset);
		std::vector<unsigned char> ss;
		ss.resize(offset);
		memcpy_s((char *)&(ss[0]),sizeof(offset),(const char *)(&offset),sizeof(offset));
		memcpy_s((char *)&(ss[sizeof(offset)]),
			ssfiles.str().size(),
			ssfiles.str().c_str(),
			ssfiles.str().length());
		return ss;
	}
};

bool Compress(const std::vector<std::string> & inFiles ,const std::string & outFile);
int main(int argc,char *args[])
{
	//int i,j,K=0; 
	//char src[4096]; 
	//char target[4096]; 
	//unsigned char buffer[BUFFER_SIZE]; 
	//Huffman * h; 
	std::vector<std::string> inFiles;
	std::string outFile;
	int mode = CommandLineParser(argc,args,inFiles,outFile);
	switch(mode)
	{
	case 1:
			bool r = Compress(inFiles,outFile);
			if (!r)
			{
				return 1;
			}
	}

	//switch(mode){ 
 //       case 0: 
 //           PrintUsage(); 
 //           return 0; 
 //       case 1://压缩 
 //           if(!OpenFile(src,target))
 //               return 1; 
 //           
 //           h=new Huffman(&Write,true); 
 //           i=BUFFER_SIZE; 
 //           while(i==BUFFER_SIZE){ 
 //               i=(int)sourceFile.read((char *)buffer,BUFFER_SIZE).gcount();
 //               h->Encode(buffer,i);
 //           } 
 //           delete h;
 //           sourceFile.close();
 //           targetFile.close();
 //           printf("压缩完毕!"); 
 //           break;
 //           
 //       case 2://解压缩 
 //           if(!OpenFile(src,target))
 //               return 1; 
 //           h=new Huffman(&Write,false); 
 //           i=BUFFER_SIZE; 
 //           while(i==BUFFER_SIZE){ 
 //               i=(int)sourceFile.read((char *)buffer,BUFFER_SIZE).gcount(); 
 //               h->Decode(buffer,i); 
 //           } 
 //           delete h; 
 //           sourceFile.close();
 //           targetFile.close();
 //           printf("解压缩完毕!"); 
 //           break; 
	//} 
  
} 

bool Compress(const std::vector<std::string> & inFiles ,const std::string & outFile)
{
	FileList fl;
	for (unsigned i = 0;i < inFiles.size(); ++i)
	{
		fl.AddFile(inFiles[i]);
	}
	std::vector<unsigned char> ls = fl.serialization();
	targetFile.open(outFile.c_str(),std::ios::out|std::ios::binary);
	if (!targetFile.is_open())
	{
		std::cout<<"打开文件:"<<outFile.c_str()<<"失败!"<<std::endl;
		return false;
	}
	Write((unsigned char *)&ls[0],ls.size());
	//文件压缩
	Huffman * h=new Huffman(&Write,true);
	unsigned char * buffer = new unsigned char[BUFFER_SIZE];
	std::vector<FileList::FileStruct> sourcelist = fl.GetList();
	for (size_t i = 0;i < sourcelist.size();++i)
	{
		std::ifstream sourceFile;
		sourceFile.open(sourcelist[i].fileName.c_str(),std::ios::in|std::ios::binary);
		std::streamsize readlength=BUFFER_SIZE;
		while(readlength==BUFFER_SIZE)
		{
			readlength=(int)sourceFile.read((char *)buffer,BUFFER_SIZE).gcount();
			h->Encode(buffer,readlength);
		}
		sourceFile.close();
	}
	delete[] buffer;
	delete h;
	targetFile.close();
	return true;
}