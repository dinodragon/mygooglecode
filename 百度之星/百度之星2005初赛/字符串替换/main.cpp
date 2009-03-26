//解题思路,使用STL中的MAP容器.

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>

using namespace std;

typedef map<string,string> DICT;

void readdict(DICT &dict);
void replacedic(const DICT &dict);

void main()
{
	DICT dict;
	readdict(dict);
	replacedic(dict);
}

void readdict(DICT &dict)
{
	string dic1,dic2;
	ifstream in("dict.txt");
	while (in>>dic1>>dic2)
	{
		dict[dic1] = dic2;
	}
}

void replacedic(const DICT &dict)
{
	DICT::const_iterator iter;
	string text;
	ifstream ifs("text.txt");
	while (getline(ifs,text))
	{
		istringstream instream(text);
		string temp;
		while (instream>>temp)
		{
			iter = dict.find(temp);
			if (iter != dict.end())
			{
				cout<<iter->second<<" ";
			}
			else
			{
				cout<<temp<<" ";
			}
		}
		cout<<endl;
	}	
}