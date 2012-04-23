#include <stdio.h> 
#include <string.h> 
#include <io.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include "Huffmancode.h" 

int writeFileHandle; 
int readFileHandle; 

bool Write(unsigned char *s,int len)
{ 
	_write(writeFileHandle,s,len); 
	return true; 
} 

bool OpenFile(char* source,char* target)
{
	int w_flag=_O_WRONLY | _O_CREAT | _O_EXCL | _O_BINARY; 
	int r_flag=_O_RDONLY | _O_BINARY; 

	readFileHandle=_open(source,r_flag,_S_IREAD | _S_IWRITE); 
	writeFileHandle=_open(target,w_flag,_S_IREAD | _S_IWRITE); 

	if(readFileHandle==-1 || writeFileHandle==-1){ 
		if(readFileHandle!=-1){ 
			_close(readFileHandle); 
			printf("\n���ļ���'%s'ʧ��!",target); 
		} 
		if(writeFileHandle!=-1){ 
			_close(writeFileHandle); 
			printf("\n���ļ���'%s'ʧ��!",source); 
		} 

		return false; 
	}else{ 
		return true; 
	} 
} 

void PrintUsage(){ 
	printf("\n�Զ�̬�������㷨ѹ�����ѹ���ļ���\n\n"); 
	printf("\thfm -?\t\t\t\t��ʾ������Ϣ\n"); 
	printf("\thfm -e -i source -o target\tѹ���ļ�\n"); 
	printf("\thfm -d -i source -o target\t��ѹ���ļ�\n\n"); 
} 

void main(int argc,char *args[]){ 
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
	mode=0;//���� 
	break; 
case 'e': 
case 'E': 
	mode=1;//ѹ�� 
	break; 
case 'd': 
case 'D': 
	mode=2;//��ѹ�� 
	break; 
case 'o': 
case 'O': 
	if(i+1>=argc){ 
		mode=0; 
	}else{//����ļ� 
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
	}else{//�����ļ� 
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
	return; 
case 1://ѹ�� 
	if(!OpenFile(src,target))
		return; 
	
	h=new Huffman(&Write,true); 
	i=BUFFER_SIZE; 
	while(i==BUFFER_SIZE){ 
		i=_read(readFileHandle,buffer,BUFFER_SIZE); 
		h->Encode(buffer,i); 
	} 
	delete h; 
	_close(readFileHandle); 
	_close(writeFileHandle); 
	printf("ѹ�����!"); 
	break;

case 2://��ѹ�� 
	if(!OpenFile(src,target))return; 
	h=new Huffman(&Write,false); 
	i=BUFFER_SIZE; 
	while(i==BUFFER_SIZE){ 
		i=_read(readFileHandle,buffer,BUFFER_SIZE); 
		h->Decode(buffer,i); 
	} 
	delete h; 
	_close(readFileHandle); 
	_close(writeFileHandle); 
	printf("��ѹ�����!"); 
	break; 
	} 

} 
