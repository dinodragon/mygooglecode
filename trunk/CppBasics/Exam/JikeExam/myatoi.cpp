#include <stdio.h>

//一个字符串转整形的函数
int myatoi(const char *str)
{
	if(str == NULL)
	{
		return 0;
	}
	int sign = 1;
	if(*str == '-')
		sign = -1;
	if(*str == '-' || *str == '+')
		str++;
		
	int result = 0;
	while(*str != '\0')
	{
		if(*str >= '0' && *str <= '9')
			result = result * 10 + *str - '0';
		else
			break;
		str++;
	}
	return result * sign;
}