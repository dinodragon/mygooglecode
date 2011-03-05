#include <iostream>

using namespace std;

void PCM_coder(int data,int pcm[8]);

int main()
{
	int data,pcm[8];
	cout<<"输入信号抽样值：";
	cin>>data;
	PCM_coder(data,pcm);
	cout<<"PCM编码:";
	for(int i=0;i<8;i++)
		cout<<pcm[i];
	cout<<endl;
}

void PCM_coder(int data,int pcm[8])
{
	int i=0;
	unsigned abs=0;
	pcm[0] = data<0?0:1;
	abs = data*(data>0?1:-1);   //取绝对值,为了少包含一个库文件，没有用系统提供的函数；
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