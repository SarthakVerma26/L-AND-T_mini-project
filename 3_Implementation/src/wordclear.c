#include "graphics.h"

void wordclear(int i)    
{
	int j=0;
	char *p;
	while(*(wordlib[i].s+j)!=NULL)
	{
		p=_vp+(wordlib[i].y*_width+wordlib[i].x+j)*(_color_bits/8);
		*p=NULL;
		*(p+1)=NULL;
		j++;
	}
}
