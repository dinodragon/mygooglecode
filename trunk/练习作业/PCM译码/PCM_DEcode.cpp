#include <iostream>
#include <string>

using namespace std;

int PCM_decode(int pcm[8]);

int main()
{
	int pcm[8],error=0,data=0;
	string in;
	cout<<"输入PCM折叠二进码：";
	cin>>in;
	for(int i=0;i<8;i++)
		pcm[i]=in[i]-'0';
	for(int i=0;i<8;i++)
		if( pcm[i]!=1 && pcm[i]!=0 ) error=1;
	if(error==0)
		data=PCM_decode(pcm);
	else
		cout <<"输入有误！";
	cout<<"采样值："<<data<<endl;
}

int PCM_decode(int pcm[8])
{
	int data=0;
	int segment=(pcm[1]<<2) + (pcm[2]<<1) + pcm[3];
	data += 1<<(segment+3);
	data += pcm[4]<<(segment+2);
	data += (pcm[5]^!pcm[4])<<(segment+1);
	data += (pcm[6]^!pcm[4])<<(segment);
	data += (pcm[7]^!pcm[4])<<(segment-1);
	if(segment>1) data += 1<<(segment-2);    //这一句是加上量化间隔的一半，当量化间隔是1时没有加上0.5。如果不需要这个修正的话删掉就可以了。
	return data*(pcm[0]==0?-1:1);
}