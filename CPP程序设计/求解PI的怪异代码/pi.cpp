/***************************************
    ���PI�Ĺ�����룬
	����ʽ�����piֵ��С����ǰ��800λ
	ĳ��Obfuscated C Contest����ѡ¼
				 http://yangfei.vicp.cc

#include <iostream>

long a=10000, b, c=2800, d, e, f[2801], g; 
void main(){
	for(;b-c;)f[b++]=a/5; 
	for(;d=0,g=c*2;c-=14,printf("%.4d",e+d/a),e=d%a) 
	for(b=c;d+=f[b]*a,f[b]=d%--g,d/=g--,--b;d*=b);
} 

****************************************/
#include <iostream>

long a=10000, b, c=2800, d, e, f[2801], g; 
void main(){
	while(b-c)
	{
		f[b++] = 2000;
	}
	d = 0;
	while(g = c*2)
	{
		b = c;
		d += f[b]*a;
		f[b]=d%--g;
		d/=g--;
		while(--b)
		{
			d *= b;
			d += f[b]*a;
			f[b] = d%--g;
			d /= g--;
		}
		c -= 14;
		printf("%.4d",e+d/a);
		e = d%a;
		d = 0;
	}

	
} 
