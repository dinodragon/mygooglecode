#include "reverse.h"



bool isLetter(char ch) //�ж��ַ��Ƿ�Ϊ��ĸ
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

//���ַ�����ת�������ʱ���ԭ��˳��
void reverse(const char * source,char * des)
{
	int sourceSize = strlen(source);
	//ԭ��Ӻ�ǰѰ�ҵ�һ������
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
			while(isLetter(*(++pwordEnd))); //�ҵ�һ�����ʵĽ����ַ�
			pword = pwordEnd; //��һѭ���Ӹõ���֮��ʼ����
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


//��һ�������еĵ��ʷ�ת
//�罫123  1234   12345
//תΪ321  4321   54321
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

