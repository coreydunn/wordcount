#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<ctype.h>

typedef struct Wc
{
  size_t lines;
  size_t words;
  size_t bytes;
} Wc;

void printwc(Wc wc,char*fn);
Wc count(FILE*in,char*fn);

int main(int argc,char**argv)
{
  Wc total={0};

  if(argc<2)
	  count(stdin,NULL);
  else
	{
	  for(size_t i=1;i<argc;++i)
		{
		  char*fn=argv[i];
		  FILE*in=fopen(fn,"r");
		  Wc fwc={0};

		  if(!in)
			{
			  fprintf(stderr,"error: failed to open file '%s'\n",fn);
			  exit(1);
			}

		  fwc=count(in,fn);
		  total.lines+=fwc.lines;
		  total.words+=fwc.words;
		  total.bytes+=fwc.bytes;
		  fclose(in);
		}
	  if(argc>2)
		printwc(total,"total");
	}
  
}

void printwc(Wc wc,char*fn)
{
  char l[128],w[128],b[128];
  size_t max=0;
  size_t t=0;

  sprintf(l,"%lu",wc.lines);
  sprintf(w,"%lu",wc.words);
  sprintf(b,"%lu",wc.bytes);
  max=strlen(l);
  if(strlen(w)>max)max=strlen(w);
  if(strlen(b)>max)max=strlen(b);

  //printf("%3lu %3lu %3lu %s\n",wc.lines,wc.words,wc.bytes,fn?fn:"");
  printf("%*s %*s %*s %s\n",
		 max,l,
		 max,w,
		 max,b,
		 fn?fn:"");
}
  
Wc count(FILE*in,char*fn)
{
  Wc wc={0};
  char b=0;
  char b_prev=0;

  while(fread(&b,1,1,in))
	{
	  if(isspace(b) && !isspace(b_prev))
		++wc.words;
	  if(b=='\n')++wc.lines;
	  ++wc.bytes;
	}
  printwc(wc,fn);
  return wc;
}
