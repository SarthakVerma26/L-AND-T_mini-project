#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define wordlength 10
#define stop 0

MIDI *pmidi;
time_t t0;
time_t t1,t2;
time_t t3,t4;
int seed=0;
int fail=0;
int frequency;
int letters=0;
int words=0;
double rate=0;

struct     
{
	int x;
	int y;
	int length;
	char *s;
	int  correct;
}wordlib[17];

void init();
void wall();
void midopen();
void game();
void initword();
void fresh();
void stat();
void read(int read);
void draw();
void worddraw(int i);
void wordclear(int i);
char* wordproduce();
int xproduce();
int yconverter(int y);
void information();
void wordprint(char *s,int x,int y);
void numberprint(int n,int x,int y);
void score();
void gameover();
void close();
void esc();

int main(int argc, char *argv[])    
{
	int i;
	init();
	wall();
	midopen();
	game();
	gameover();
	return 0;
}

void init()    
{
	int n=2;
	
	char *s1="Welcome ";
	char *s2="Please select the difficulty of the hitword game...";
	char *s3="1 for Difficult";
	char *s4="2 for Normal";
	char *s5="3 for Easy";
	char *s6="Invalid input!Difficulty will be default.";

	clrscr();
	wordprint(s1,24,8);
	wordprint(s2,18,11);
	wordprint(s3,30,13);
	wordprint(s4,30,14);
	wordprint(s5,30,15);

	gotoxy(32,17);
	scanf("%d",&n);
	switch(n)
		{
		case 1:frequency=500;break;
		case 2:frequency=1000;break;
		case 3:frequency=2000;break;
		default:
			wordprint(s6,18,19);
		    frequency=1000;
		    delay(2000);
		}
	clrscr();
}


void wall()    
{
	int i;
	char *p;
	for(i=5;i<=75;i++){
		p=_vp+(2*_width+i)*2;
		*p='*';
		*(p+1)=15;
        p=_vp+(20*_width+i)*2;
		*p='*';
		*(p+1)=15;
	}
	for(i=3;i<=19;i++){
		p=_vp+(i*_width+5)*2;
		*p='��';
		*(p+1)=15;
        p=_vp+(i*_width+60)*2;
		*p='��';
		*(p+1)=15;
		 p=_vp+(i*_width+75)*2;
		*p='��';
		*(p+1)=15;
	}

}

void midopen()    
{
   initsound();
   pmidi=load_midi("1.mid");
   play_midi(pmidi, 20); 

}

void game()    
{
	int i;
	initword();
	t0=t1=t3=clock();
	t3=clock();
	while(!stop)
	{
		t2=t4=clock();
		fresh();
		stat();
		
		if(fail==1)
			break;
		if (bioskey(1))
			read(bioskey(0));
		draw();
		information();
	}
	if(fail==1)
		gameover();
}

void fresh()    
{
	int i;
	if(difftime(t2,t1)>frequency)
	{
		t1=t2;
		for(i=0;i<17;i++)
			{
			if(yconverter(wordlib[i].y)==0)
				{
				fail=1;
				break;
				}
			if(yconverter(wordlib[i].y)>0)
				wordclear(i);
			wordlib[i].y++;
			}
	}
}

void stat()    
{
	if(difftime(t4,t3)>(frequency))
	{
		t3=t4;
		rate=words/(((double)(t4-t0)/1000)/60);
	}
}


void read(int read)    
{
	int i,j;
	int index=0;
	int length;
	if(read==0x011B)
		{
		fail=1;
		return;
		}
	read%=256;
	for(i=1;i<17;i++)
	{
		if(wordlib[i].y>wordlib[i-1].y)
			index=i;
	}
	if(read==(int)*(wordlib[index].s+wordlib[index].correct))
		{
		wordlib[index].correct++;
		letters++;
		}
	if(wordlib[index].correct==wordlib[index].length)
	{
		words++;
		wordclear(index);
		wordlib[index].y-=34;
		wordlib[index].x=xproduce();
		wordlib[index].correct=0;
		wordlib[index].s=wordproduce();
		wordlib[index].length=strlen(wordlib[index].s);
	}


}


void initword()    
{
	int i;
	for(i=0;i<17;i++)
	{
		wordlib[i].x=xproduce();
		wordlib[i].y=3-2*i;
		wordlib[i].s=wordproduce();
		wordlib[i].length=strlen(wordlib[i].s);
		wordlib[i].correct=0;
	}

}

void draw()    
{
	int i;
	for(i=0;i<17;i++)
		{
			if(yconverter(wordlib[i].y)==-1)
				continue;
			else
				worddraw(i);

		}
}




int xproduce()    
{
    int x;
	do
	{
		srand(time(NULL)+seed);
		seed+=7;
		x=rand()%51;
	}
	while (x<6);
	return x;
}

int yconverter(int y)    
{
	if(y<3)
		y=-1;
	else if(y>18)
		y=0;
	return y;
}

char* wordproduce()    
{
	int i,length,character;
	char *s;
	do
	{
		srand(time(NULL)+seed);
		length=rand()%11;
		seed+=7;
		
	}
	while (length==0||length>10);

	if((s=(char*)malloc(sizeof(char)*(length+1)))==NULL)
		exit(0);

	for(i=0;i<length;i++){
		do
		{
			srand(time(NULL)+seed);
			character=rand()%27;
			seed+=7;
		}
		while (character==0);
		*(s+i)=(char)(character+96);
	}
	*(s+i)=NULL;
	return s;
}

void information()    
{
	int x,y;
	char *s1="Letters:";
	char *s2="Words";
	char *s3="Type rate:";
	char *s4="words/min";
	char *s5="Press Esc to";
	char *s6=" exit.";

	wordprint(s5,62,3);
	wordprint(s6,62,4);
	wordprint(s1,62,6);
	numberprint(letters,70,8);
	wordprint(s2,62,10);
	numberprint(words,70,12);
	wordprint(s3,62,14);
	numberprint((int)rate,70,16);
	wordprint(s4,62,18);

}



void score()
{
	char *s1="Your score:";
}

void gameover(){    
   char *s1="GAME OVER!";
   char *s2="Your score:";
   char *s3="words";
   char *s4="letters";
   char *s5="words per miniute";
   
   free_midi(pmidi);
   closesound();
   clrscr();
   
   wordprint(s1,30,6);
   wordprint(s2,20,8);
   numberprint(words,24,10);
   wordprint(s3,30,10);
   numberprint(letters,24,12);
   wordprint(s4,30,12);
   numberprint(rate,24,14);
   wordprint(s5,30,14);
   getch();
   clrscr();
}
