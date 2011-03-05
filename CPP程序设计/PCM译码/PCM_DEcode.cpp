#include <iostream>
#include <string>

using namespace std;

int PCM_decode(int pcm[8]);

int main()
{
	int pcm[8],error=0,data=0;
	string in;
	cout<<"����PCM�۵������룺";
	cin>>in;
	for(int i=0;i<8;i++)
		pcm[i]=in[i]-'0';
	for(int i=0;i<8;i++)
		if( pcm[i]!=1 && pcm[i]!=0 ) error=1;
	if(error==0)
		data=PCM_decode(pcm);
	else
		cout <<"��������";
	cout<<"����ֵ��"<<data<<endl;
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
	if(segment>1) data += 1<<(segment-2);    //��һ���Ǽ������������һ�룬�����������1ʱû�м���0.5���������Ҫ��������Ļ�ɾ���Ϳ����ˡ�
	return data*(pcm[0]==0?-1:1);
}