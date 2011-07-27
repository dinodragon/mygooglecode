#include "reverse.h"



bool isLetter(char ch) //判断字符是否为字母
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

//将字符串反转，但单词保持原有顺序。
void reverse(const char * source,char * des)
{
	int sourceSize = strlen(source);
	//原句从后到前寻找第一个单词
	char * tempWord =(char *)malloc(sourceSize + 1);
	char * ptempWord = tempWord + sourceSize;
	* (ptempWord--) = '\0';

	const char * pword = source;

	while(*pword != '\0')
	{
		if(isLetter(*pword)) 
		{
			const char * pwordStart = pword;
			const char * pwordEnd = pwordStart;
			while(isLetter(*(++pwordEnd))); //找到一个单词的结束字符
			pword = pwordEnd; //下一循环从该单词之后开始分析
			while(pwordStart < pwordEnd)
			{
				*(ptempWord--) = *(--pwordEnd);
			}
		}
		else
		{
			*(ptempWord--) = *pword;
			pword++;
		}
	}
	strcpy(des,ptempWord + 1);
	free(tempWord);
	tempWord = NULL;
}


//将一个句子中的单词反转
//如将123  1234   12345
//转为321  4321   54321
char* strrevw(char* string){ 
    char* s=string; 
    char* e=s; 
    char  ch; 
    char *ws,*we; 
    while(1){ 
        if(*e==' ' || *e=='\0'){ 
            ws=s; 
            we=e-1;             
            while(ws<we){ 
                ch=*ws; 
                *ws++=*we; 
                *we--=ch; 
            } 
            if(*e=='\0') 
                break; 
            s=e; 
            while(*++s==' '); 
        } 
        e++; 
    } 
    return string;     
} 

