#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
	map<string, string> namemap;
	//增加
	namemap["岳不群"]="华山派掌门人，人称君子剑";
	namemap["张三丰"]="武当掌门人，太极拳创始人";
	namemap["东方不败"]="第一高手，葵花宝典";
	namemap["张三丰"]="武当掌门人，太极拳创始人2";

	//查找
	map<string, string>::iterator iter;
	iter = namemap.find("张三丰");
	if(iter != namemap.end()){
		cout<<iter->second<<endl;
	}
}



