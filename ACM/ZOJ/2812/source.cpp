#include <stdio.h>
#include <iostream>

int main()
{
	std::string str;
	while(getline(std::cin,str) && str != "#")
	{
		int sum = 0;
		//std::cout<<str<<std::endl;
		for(int i = 0;i<str.length();++i)
		{
			if(str[i] != ' ')
			{
				sum += (str[i] - 'A' + 1) * (i+1);
			}
			
		}
		std::cout<<sum<<std::endl;
		
	}
	return 0;
}
