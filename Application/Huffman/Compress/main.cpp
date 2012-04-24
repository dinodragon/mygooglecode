
#include <stdio.h> 
#include <string.h> 
#include <fstream>
#include <sys/stat.h> 
#include <fcntl.h>
#include <vector>
#include <sstream>
#include "Huffmancode.h"

std::ofstream targetFile;
std::ifstream sourceFile; 

bool Write(unsigned char *s,int len)
{ 
    targetFile.write((char *)s,len);
	return true; 
} 

bool OpenFile(char* source,char* target)
{
    sourceFile.open(source,std::ios::in|std::ios::binary);
    targetFile.open(target,std::ios::out|std::ios::binary);
	if(!sourceFile.is_open())
    { 
        sourceFile.close(); 
        printf("\n打开文件：'%s'失败!\n" ,target);
        return false; 
	}
    else if(!targetFile.is_open())
    {
        targetFile.close();
        printf("\n打开文件：'%s'失败!\n" ,source); 
        return false; 
	}else
    { 
		return true; 
	} 
}
//0 帮助 1 压缩 2 解压缩
int CommandLineParser(int argc,char *args[],std::vector<std::string> &inFiles,std::string &outFile)
{
	std::vector<std::string> commands;
	for (int i = 1;i < argc;++i)
	{
		commands.push_back(std::string(args[i]));
	}
	int iCmdSize = commands.size();
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
		for (int i = 0;i < iCmdSize - 1;++i)
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
typedef struct _FileStruct
{
	char * fileName;
	int fileSize;
}FileStruct;

typedef struct _FilesStruct
{
	int contentOffset;//表示文件内容偏移量
	FileStruct *filesList;
};


int main(int argc,char *args[])
{
	int i,j,K=0; 
	char src[4096]; 
	char target[4096]; 
	unsigned char buffer[BUFFER_SIZE]; 
	Huffman *h; 
	std::vector<std::string> inFiles;
	std::string outFile;
	int mode = CommandLineParser(argc,args,inFiles,outFile);
	targetFile.open(outFile.c_str(),std::ios::out|std::ios::binary);
	std::stringstream filelist;
	for (int i = 0;i < inFiles.size(); ++i)
	{
		filelist << ";" << inFiles[i].c_str();
		filelist << "," << inFiles[i].length();
	}
	targetFile << filelist.str().length();
	targetFile << filelist.str();
	targetFile.close();
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
