/*Using CRC method for error detection on a string of bits of variable length (data-length considered) */
#include<stdio.h>
#include<stdlib.h>
char divisor[6]="10011";//setting a divisor value

void crc(char a[])//function to calculate crc
{
  int count=0,i=0,j;
  while(a[count]!='\0')count++;
  while(i<count-5+1){
    if(a[i]!='1') {
      i++;
      continue;
    }
    else {
      j=0;
      while(divisor[j]!='\0'){
        if(divisor[j]==a[i+j]) a[i+j]='0';
        else a[i+j]='1';
        j++;
      }
      i++;
    }
  }
}

void stringtobit(char a[],char b[])//function to convert the charecters into bits using ascii value
{
  int i,j,k=0;
  for(i=0;a[i]!='\0';i++){
    for(j=7;j>=0;j--){
      b[k+j]=a[i]%2+'0';
      a[i]=a[i]/2;
    }
    k=k+8;
  }
  b[k]='\0';
}

void main()
{
  int i,j,ss=0,rs=0;
  char sent[32],sentb[256],receive[32],receiveb[256],cc[5];
  printf("Enter the data being sent\n");
  gets(sent);
  stringtobit(sent,sentb);
  while(sentb[ss]!='\0') ss++;
  for(i=ss;i<ss+4;i++) sentb[i]='0';
  sentb[i]='\0';
  printf("CRC is ");
  crc(sentb);
  i=ss+4;
  j=4;
  while(j>=0)
    cc[j--]=sentb[i--];
  cc[4]='\0';
  puts(cc);
  printf("Enter the data received\n");
  gets(receive);
  stringtobit(receive,receiveb);
  while(receiveb[rs]!='\0') rs++;
  if(ss!=rs)
  {
    printf("Data corrupted(Change in number of bits)\n");
    exit(0);
  }
  i=rs;
  j=0;
  while(cc[j]!='\0')receiveb[i++]=cc[j++];
  receiveb[i]='\0';
  crc(receiveb);
  i=rs+4;
  j=4;
  while(j>=0)
    cc[j--]=receiveb[i--];
  cc[4]='\0';
  printf("The remainder is %s, hence\n",cc);
  for(i=rs;i<rs+4;i++)
    if(receiveb[i]!='0'){
      printf("The data is corrupted\n");
      j=0;
      break;
    }
  if(j==-1)printf("Data successfully transmitted\n");
}
