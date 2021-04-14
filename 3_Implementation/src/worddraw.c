#include "graphics.h"

void worddraw(int i)    
{
	int j=0;
	char *p;
	while(*(wordlib[i].s+j)!=NULL)
	{
		p=_vp+(wordlib[i].y*_width+wordlib[i].x+j)*(_color_bits/8);
		*p=*(wordlib[i].s+j);
		if(j<=wordlib[i].correct-1)
			*(p+1)=GREEN;
		else
			*(p+1)=WHITE;
		j++;
	}
}
