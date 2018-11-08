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

void main()
{
  int i,j,ss=0,rs=0;
  char sent[32],receive[32],cc[5];
  printf("Enter the data being sent\n");
  gets(sent);
  while(sent[ss]!='\0') ss++;
  for(i=ss;i<ss+4;i++) sent[i]='0';
  sent[i]='\0';
  printf("CRC is ");
  crc(sent);
  i=ss+4;
  j=4;
  while(j>=0)
    cc[j--]=sent[i--];
  cc[4]='\0';
  puts(cc);
  printf("Enter the data received\n");
  gets(receive);
  while(receive[rs]!='\0') rs++;
  if(ss!=rs)
  {
    printf("Data corrupted(Change in number of bits)\n");
    exit(0);
  }
  i=rs;
  j=0;
  while(cc[j]!='\0')receive[i++]=cc[j++];
  receive[i]='\0';
  crc(receive);
  printf("The remainder is %s, hence\n",receive);
  for(i=0;i<rs+4;i++)
    if(receive[i]!='0'){
      printf("The data is corrupted\n");
      j=-1;
      break;
    }
  if(j!=-1)printf("Data successfully transmitted\n");
}
