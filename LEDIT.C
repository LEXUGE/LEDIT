#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int width[3001]={0};
int height=1;
int dwidth=80;
int dheight=300;
int dstart=1;
int maxlen=24000;
int x=1,y=1;
char a[24002]={};

int check();
void pull(int temp);
void format();
int sum(int x);
void push(int temp);
int conv(int x1,int y1);
void fr();
void fw();
int non(char ch);
int key(char ch);
int ctrkey(char ch);
int cursor(char ch);
void prin(int n);
void init();

int check()
{
  int i=1,t=1,temp=1;
  while(a[i]!='\0')
  {
    if ((a[i]=='\n')) {t++;temp=0;}
    else if (temp==dwidth) {if (t<dheight) {t++;temp=0;}}
    i++;
    temp++;
  }
  if (t>dheight) return 1;
  else return 0;
}

void pull(int temp)
{
  int i=0;
  for (i=temp;i<=sum(height);i++)
  {
    a[i-1]=a[i];
  }
  a[sum(height)]=0;
}

void format()
{
  int i=1,t=1,temp=1;
  height=0;
  while(a[i]!='\0')
  {
    if ((a[i]=='\n')) {width[t]=temp;t++;temp=0;}
    else if (temp==dwidth) {width[t]=dwidth;if (t<dheight) {t++;temp=0;}}
    i++;
    temp++;
  }
  if ((a[i]=='\0')) {width[t]=temp;temp=0;}
  height=t;
}

int sum(int x)
{
  int i=0,sum=0;
  for (i=1;i<=x;i++)
    sum+=width[i];
  return sum;
}

void push(int temp)
{
  int i=0;
  for (i=sum(height);i>=temp;i--)
  {
    a[i+1]=a[i];
  }
}

int conv(int x1,int y1)
{
  return sum(x1-1)+y1;
}

void init()
{
  int i=0;
  x=1;y=1;
  for (i=0;i<=maxlen+1;i++)
    a[i]=0;
  for (i=0;i<=3000;i++)
    width[i]=0;
  dstart=1;
  format();
}

void gotoxy(int x,int y)
{
   printf("%c[%d;%df",0x1B,y,x);
}

void clrscr()
{
  printf("\033c");
}

int getch()
{
    char ch;
    system("stty -echo -icanon");
    ch=getchar();
    system("stty echo icanon");
    return ch;
}

void fr()
{
  FILE *fp;
  int c=0,r=0;
  int i;
  char ch;
  char fpath[100];
  memset(fpath,0,sizeof(fpath));
  clrscr();
  printf("[OPEN] Please input a number to decryption:");
  r=scanf("%d",&c);
  while((ch=getchar())!='\n'&&ch!=EOF);
  ch=0;
  if ((r!=1)) {printf("Error!\n");getch();getch();clrscr();return;}
  r=0;

  printf("[OPEN] Please input the file path:");
  scanf("%s",fpath);
  if ((fp=fopen(fpath,"r"))==NULL)
  {
  printf("Can't open the file!");
  getch();
  getch();
  clrscr();
  return;
  }
  init();
  i=1;
  while ((ch=getc(fp))!=EOF)
  {
    if (i>maxlen) break;
    a[i]=ch+c;
    i++;
  }
  fclose(fp);
  printf("Read the file successful!");
  getch();
  getch();
  clrscr();
  return;
}
void fw()
{
  FILE *fp;
  char fpath[100];
  int i=0;
  int c=0,r=0;
  char ch=0;
  memset(fpath,0,sizeof(fpath));
  clrscr();
  printf("[SAVE] Please input a number to encrypt:");
  r=scanf("%d",&c);
  while((ch=getchar())!='\n'&&ch!=EOF);
  ch=0;
  if ((r!=1)) {printf("Error!\n");getch();getch();clrscr();return;}
  r=0;
  printf("[SAVE] Please input the file path:");
  scanf("%s",fpath);
  if ((fp=fopen(fpath,"w"))==NULL)
  {
  printf("Can't open file!");
  getch();
  getch();
  clrscr();
  exit(0);
  }
  for (i=1;i<=sum(height);i++)
  {
    if (a[i]!=0)
    putc(a[i]-c,fp);
  }
  fclose(fp);
  printf("Write the file successful!");
  getch();
  getch();
  clrscr();
  exit(0);
}
int key(char ch)
{
  char temp=0;
  if (((conv(x,y)>=sum(height))&&(height<=dheight)&&(y<=dwidth)))
  {
    a[conv(x,y)]=ch;
    if (width[x]<dwidth) width[x]++;
    if (y<width[x]) y=y+1;
    else
    if ((y==width[x])&&(x<dheight)) {x++;y=1;}
    if (x>(22+dstart)) dstart++;
    format();
    prin(1);
  }
  else
  {
    if ((height>dheight)||((height==dheight)&&(width[height]-1==dwidth))) ;
    else
    {
    push(conv(x,y));
    temp=a[conv(x,y)];
    a[conv(x,y)]=ch;
    if (check()==1) {pull(conv(x,y));a[conv(x,y)]=temp;}
    else
    {
    a[conv(x,y)]=ch;
    /*if (width[x]<dwidth) width[x]++;
    else
    if ((width[x]==dwidth)&&(x<=dheight)) {height++;x++;width[x]++;x--;}*/
    format();
    if (y<width[x]) y=y+1;
    else if ((y==width[x])&&(x<dheight)) {x++;y=1;}
    if (x>(22+dstart)) dstart++;
    prin(1);
    }
    }
  }
  return 1;
}
int ctrkey(char ch)
{
  int temp=0;
  if (ch==10)
  {
    if ((conv(x,y)>=sum(height))&&(height<dheight))
     {
      a[conv(x,y)]='\n';
      if (x<dheight) {x++;y=1;}
      if (x>(22+dstart)) dstart++;
      format();
      prin(1);
      return 1;
    }
    else
    {
       if (height>=dheight) ;
       else
        {
          push(conv(x,y));
          a[conv(x,y)]='\n';
          if (x<dheight) {x++;y=1;}
          if (x>(22+dstart)) dstart++;
          format();
          prin(1);
          return 1;
        }
    }
  }
  if (ch==127)
  {
  if ((conv(x,y)>=sum(height)))
  {
    if (y>1)
    {
      a[conv(x,y-1)]=0;
      if (y>1) {y=y-1;width[x]--;}
      format();
      prin(1);
      return 1;
    }
    else
    if ((y==1)&&(x>1)) {a[conv(x,y-1)]=0;temp=width[x-1];format();x=x-1;y=temp;if (x<(dstart)) dstart--;prin(1);}
  } 
  else
  {
    if (y>1)
    {
      pull(conv(x,y));
      if (y>1) {y=y-1;width[x]--;}
      format();
      prin(1);
      return 1;
    }
    else
    if ((y==1)&&(x>1)) {pull(conv(x,y));temp=width[x-1];format();x=x-1;y=temp;if (x<(dstart)) dstart--;prin(1);}
  }
  }
  /*if (ch==127)
  {
  a[x][y]=' ';
  prin(1);
  return 1;
  }*/
  if (ch==23)
  {
  fw();
  return 1;
  }
  if (ch==18)
  {
  fr();
  format();
  prin(1);
  return 1;
  }
  return 0;
}
int cursor(char ch)
{
  if (ch==27)
  {
  ch=getch();
  if (ch==91)
  {
  ch=getch();
  if (ch=='A')
  {
  if (x>1) {x=x-1;if (width[x]<y) y=width[x];}
  if (x<(dstart)) dstart--;
  prin(1);
  return 1;
  }
  if (ch=='B')
  {
  if (x<height) {x=x+1;if (width[x]==0) y=width[x]+1; else if (width[x]<y) y=width[x];}
  if (x>(22+dstart)) dstart++;
  prin(1);
  return 1;
  }
  if (ch=='D')
  {
  if (y>1) y=y-1;
  else
  if ((y==1)&&(x>1)) {x=x-1;y=width[x];if (x<(dstart)) dstart--;prin(2);}
  prin(1);
  return 1;
  }
  if (ch=='C')
  {
  if ((y<width[x])&&(y<dwidth)) y=y+1; else
  if ((y==width[x])&&(x<height)) {x=x+1;y=1;if (x>(22+dstart)) dstart++;}
  prin(1);
  return 1;
  }
  }
  }
  if (ch==27)  return 2;
  return 0;
}
void prin(int n)
{
  int i=0,j=0,flag=0;

  if (n==1)
  {
  clrscr();
  for (i=dstart;i<=dstart+22;i++)
  {
    flag=0;
    for (j=1;j<=width[i];j++)
    {
      printf("%c",a[conv(i,j)]);
      if (a[conv(i,j)]=='\n') flag=1;
    }
    if (flag==0)
    printf("\n");
  }
  gotoxy(61,24);
  printf("Powered by LEXUGE");
  }
  gotoxy(5,24);
  printf("X:%d Y:%d ",x,y);
  gotoxy(y,(x-dstart+1));
}
int main()
{
   char ch;
   int n=0,key1=0;
   clrscr();
   init();
   prin(1);
   while (1)
   {
   prin(1);
   ch=getch();
   key1=ch;
   n=cursor(ch);
   if (n==2) {clrscr();return 0;}
   if (n==0)
   n=ctrkey(ch);
   if ((key1>=32)&&(key1<=126))
   n=key(ch);
   }
   return 0;
}
