#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
	map<string, string> namemap;
	//����
	namemap["����Ⱥ"]="��ɽ�������ˣ��˳ƾ��ӽ�";
	namemap["������"]="�䵱�����ˣ�̫��ȭ��ʼ��";
	namemap["��������"]="��һ���֣���������";
	namemap["������"]="�䵱�����ˣ�̫��ȭ��ʼ��2";

	//����
	map<string, string>::iterator iter;
	iter = namemap.find("������");
	if(iter != namemap.end()){
		cout<<iter->second<<endl;
	}
}



