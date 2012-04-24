﻿
#include <stdio.h> 
#include <string.h> 
//#include <io.h>
#include <fstream>
#include <sys/stat.h> 
#include <fcntl.h> 
#include "Huffmancode.h"

int a;
std::ofstream g_writeFileHandle;
std::ifstream readFileHandle; 

bool Write(unsigned char *s,int len)
{ 
    //	_write(writeFileHandle,s,len);
    g_writeFileHandle.write((char *)s,len);
	return true; 
} 

bool OpenFile(char* source,char* target)
{
    //	int w_flag=_O_WRONLY | _O_CREAT | _O_EXCL | _O_BINARY; 
    //	int r_flag=_O_RDONLY | _O_BINARY; 
    
    //	readFileHandle=_open(source,r_flag,_S_IREAD | _S_IWRITE); 
    //	writeFileHandle=_open(target,w_flag,_S_IREAD | _S_IWRITE);
    readFileHandle.open(source,std::ios::in|std::ios::binary);
    g_writeFileHandle.open(target,std::ios::out|std::ios::binary);
	if(!readFileHandle.is_open())
    { 
        readFileHandle.close(); 
        printf("\n打开文件：'%s'失败!\n",target);
        return false; 
	}
    else if(!g_writeFileHandle.is_open())
    {
        g_writeFileHandle.close();
        printf("\n打开文件：'%s'失败!",source); 
        return false; 
	}else
    { 
		return true; 
	} 
} 

void PrintUsage(){ 
	printf("\n以动态哈夫曼算法压缩或解压缩文件。\n\n"); 
	printf("\thfm -?\t\t\t\t显示帮助信息\n"); 
	printf("\thfm -e -i source -o target\t压缩文件\n"); 
	printf("\thfm -d -i source -o target\t解压缩文件\n\n"); 
} 

int main(int argc,char *args[]){ 
	int mode,i,j,K=0; 
	char src[4096]; 
	char target[4096]; 
	unsigned char buffer[BUFFER_SIZE]; 
	Huffman *h; 
    
	mode=0; 
	for(i=1;i<argc;i++){ 
		if(args[i][0]=='-' || args[i][0]=='/'){ 
			switch(args[i][1]){ 
                case '?': 
                    mode=0;//帮助 
                    break; 
                case 'e': 
                case 'E': 
                    mode=1;//压缩 
                    break; 
                case 'd': 
                case 'D': 
                    mode=2;//解压缩 
                    break; 
                case 'o': 
                case 'O': 
                    if(i+1>=argc){ 
                        mode=0; 
                    }else{//输出文件 
                        j=0; 
                        while(args[i+1][j]!='\0' && j<4096){ 
                            target[j++]=args[i+1][j]; 
                        } 
                        if(j==4096){ 
                            mode=0; 
                        }else{ 
                            target[j]='\0'; 
                            K |= 1; 
                        } 
                    } 
                    break; 
                case 'i': 
                case 'I': 
                    if(i+1>=argc){ 
                        mode=0; 
                    }else{//输入文件 
                        j=0; 
                        while(args[i+1][j]!='\0' && j<4096){ 
                            src[j++]=args[i+1][j]; 
                        } 
                        if(j==4096){ 
                            mode=0; 
                        }else{ 
                            src[j]='\0'; 
                            K |=2; 
                        } 
                    } 
                    break; 
			} 
		} 
	} 
    
	if(K!=3)mode=0; 
    
	switch(mode){ 
        case 0: 
            PrintUsage(); 
            return 0; 
        case 1://压缩 
            if(!OpenFile(src,target))
                return 1; 
            
            h=new Huffman(&Write,true); 
            i=BUFFER_SIZE; 
            while(i==BUFFER_SIZE){ 
                i=(int)readFileHandle.read((char *)buffer,BUFFER_SIZE).gcount();
                //_read(readFileHandle,buffer,BUFFER_SIZE); 
                h->Encode(buffer,i);
            } 
            delete h;
            readFileHandle.close();
            g_writeFileHandle.close();
            printf("压缩完毕!"); 
            break;
            
        case 2://解压缩 
            if(!OpenFile(src,target))
                return 1; 
            h=new Huffman(&Write,false); 
            i=BUFFER_SIZE; 
            while(i==BUFFER_SIZE){ 
                i=(int)readFileHandle.read((char *)buffer,BUFFER_SIZE).gcount(); 
                h->Decode(buffer,i); 
            } 
            delete h; 
            readFileHandle.close();
            g_writeFileHandle.close();
            printf("解压缩完毕!"); 
            break; 
	} 
    
} 