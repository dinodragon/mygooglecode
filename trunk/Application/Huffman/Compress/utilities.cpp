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


std::ofstream targetFile;
bool CompressWrite(const unsigned char *s,const size_t len)
{ 
	targetFile.write((const char *)s,(std::streamsize)len);
	return true; 
}

bool Compress(const std::vector<std::string> & inFiles ,const std::string & outFile)
{
	FileList fl;
	for (unsigned i = 0;i < inFiles.size(); ++i)
	{
		fl.AddFile(inFiles[i]);
	}
	std::vector<unsigned char> ls = fl.serialization();
	targetFile.open(outFile.c_str(),std::ios::out|std::ios::binary|std::ios::trunc);
	if (!targetFile.is_open())
	{
		std::cout<<"打开文件:"<<outFile.c_str()<<"失败!"<<std::endl;
		return false;
	}
	CompressWrite((unsigned char *)&ls[0],ls.size());
	//文件压缩
	Huffman * h=new Huffman(&CompressWrite,true);
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

std::vector<FileList::FileStruct> defilelist;
bool DecompressWrite(const unsigned char *s,const size_t len)
{
    static size_t bufStart = 0;
    static int curfileindex = -1;//当前打开的文件
    static int fileindex = 0;//操作文件序列
    bufStart = 0;
    while(bufStart < len)
    {
        static std::ofstream sourceFile;
        if (curfileindex != fileindex) {
            sourceFile.open(defilelist[fileindex].fileName.c_str(),std::ios::out|std::ios::binary|std::ios::trunc);
            curfileindex = fileindex;
        }
        std::streamoff yetlength = sourceFile.tellp();
        int remaininglength = defilelist[curfileindex].fileSize - yetlength;
        if (remaininglength <= len - bufStart) {
            //buffer数据较多，还未用完。            
            sourceFile.write((const char *)(s + bufStart), remaininglength);
            sourceFile.close();
            bufStart += remaininglength;
            ++fileindex;//下次该写下一文件了
        }
        else {
            //这个文件未写完，下次仍需要写这个文件
            sourceFile.write((const char *)(s + bufStart), len - bufStart);
            bufStart = len;
        }
    }
	return true; 
}

bool Decompress(const std::string & tarFile)
{
    std::ifstream tarstream;
    tarstream.open(tarFile.c_str(),std::ios::in | std::ios::binary);
    if (!tarstream.is_open()) {
        std::cout<<"打开文件:"<<tarFile.c_str()<<"失败!"<<std::endl;
        return false;
    }
    size_t offset = 0;
    tarstream.read((char *)&offset,sizeof(offset));
#ifdef DEBUG
    std::cout<<"offset:"<<offset<<std::endl;
#endif
    offset -= sizeof(offset);
    char * listbuffer = new char[offset];
    tarstream.read(listbuffer, offset);
    FileList g_defl;
    g_defl.deserialization(listbuffer,offset);
    delete[] listbuffer;
    defilelist = g_defl.GetList();
    unsigned char * buffer = new unsigned char[BUFFER_SIZE];
    std::auto_ptr<Huffman> h(new Huffman(&DecompressWrite,false));
    std::streamsize readlength=BUFFER_SIZE;
    while (readlength == BUFFER_SIZE) {
        readlength=(int)tarstream.read((char *)buffer,BUFFER_SIZE).gcount(); 
        h->Decode(buffer,readlength);
    }
    delete[] buffer;
    tarstream.close();
    return false;
}
