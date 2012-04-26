//
//  utilities.cpp
//  Huffman
//
//  Created by 飞 杨 on 12-4-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
#include "utilities.h"
#include <iostream>
#include "filelist.h"
#include "Huffmancode.h"

std::ofstream targetFile;
//std::ifstream sourceFile; 

bool Write(const unsigned char *s,const size_t len)
{ 
	targetFile.write((const char *)s,(std::streamsize)len);
	return true; 
}

void PrintUsage(){ 
	printf("\n以动态哈夫曼算法压缩或解压缩文件。\n\n"); 
	printf("\thfm -?\t\t\t\t显示帮助信息\n"); 
	printf("\thfm -e -i source -o target\t压缩文件\n"); 
	printf("\thfm -d -i source -o target\t解压缩文件\n\n"); 
}

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

bool Decompress(const std::string & tarFile)
{
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
    return false;
}