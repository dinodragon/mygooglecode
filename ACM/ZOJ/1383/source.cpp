#include <stdio.h>

int main(int argc, char **argv)
{
	int n = 0;
	scanf("%d",&n);
	int number = 0;
	for(int i = 0;i < n; ++i)
	{
		scanf("%d",&number);
		int index = 0;
		int first = 1;
		while(number != 0)
		{
			if(number % 2 == 1)
			{
				if(first) 
					printf("%d",index);
				else
					printf(" %d",index);
				first = 0;
			}
			number /= 2;
			++index;
		}
		printf("\n");
	}
}
