#include "graphics.h"

void wordprint(char* s,int x,int y)   
{ 
	char *p;

	int count=0;
	int i;
	while(*s!=NULL)
	{
		s++;
		count++;
	}
	s-=count;
	for(i=0;i<count;i++){
		p=_vp+(y*_width+x+i)*(_color_bits/8);
		*p=*(s+i);
		*(p+1)=YELLOW;
	}
	
}
