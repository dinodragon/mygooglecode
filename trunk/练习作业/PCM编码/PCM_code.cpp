#include <iostream>

using namespace std;

void PCM_coder(int data,int pcm[8]);

int main()
{
	int data,pcm[8];
	cout<<"�����źų���ֵ��";
	cin>>data;
	PCM_coder(data,pcm);
	cout<<"PCM����:";
	for(int i=0;i<8;i++)
		cout<<pcm[i];
	cout<<endl;
}

void PCM_coder(int data,int pcm[8])
{
	int i=0;
	unsigned abs=0;
	pcm[0] = data<0?0:1;
	abs = data*(data>0?1:-1);   //ȡ����ֵ,Ϊ���ٰ���һ�����ļ���û����ϵͳ�ṩ�ĺ�����
	for(i=10;i>3;i--)
		if( ((abs>>i) & 1) == 1) break;
	pcm[1] = (i-3)/4%2;
	pcm[2] = (i-3)/2%2;
	pcm[3] = (i-3) % 2;
	i = (i==3)?4:i;
	pcm[4] = ((abs>>(i-1)) & 1);
	pcm[5] = (((abs>>(i-2))&1) ^ !pcm[4]);
	pcm[6] = (((abs>>(i-3))&1) ^ !pcm[4]);
	pcm[7] = (((abs>>(i-4))&1) ^ !pcm[4]);
}