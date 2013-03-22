#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

int main(int argc,char **argv)
{
	int n = 0;
	scanf("%d",&n);
	std::string str;
	getline(std::cin,str);
	for(int i = 0;i < n;++i)
	{
		printf("String #%d\n",i+1);
		getline(std::cin,str);
		int len = str.length();
		for(int index = 0;index < len; ++index)
		{
			char ch = 'A' + (str[index] - 'A' + 1) % 26;
			printf("%c",ch);
		}
		printf("\n\n");
	}
}

