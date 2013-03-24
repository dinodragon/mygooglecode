#include <stdio.h>
#include <string.h>

void printch(char ch,int k);

int main(int argc,char ** argv)
{
	int count = 0;
	scanf("%d",&count);
	for(int i = 0;i < count; ++i)
	{
		char str[101];
		scanf("%s",str);
		char lastch = str[0];
		int k = 0;
		for(int j = 0; j < strlen(str);++j)
		{
			if(lastch == str[j])
				 ++k;
			else
			{
				printch(lastch,k);
				k = 1;
			}
			lastch = str[j];
			
		}
		printch(lastch,k);
		printf("\n");
	}
}

void printch(char ch,int k)
{
	if(k == 1) printf("%c",ch);
	else printf("%d%c",k,ch);
}
