
#include "graphics.h"

void numberprint(int n,int x,int y)    
{
	char* p;
	int count=0;
	int number=n;
	int i;
	while(number!=0)
	{
		count++;
		number/=10;
	}
	for(i=0;i<count;i++)
	{
		p=_vp+(y*_width+(x-i))*(_color_bits/8);
		*p=(char)(n%10+48);
		*(p+1)=YELLOW;
		n/=10;
	}
}
