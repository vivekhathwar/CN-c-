/*To detect error in transmission using checksum on a string of bits */
#include<stdio.h>
int carry=0;
int data[5][16];
int su[16]={0};
int ws=0;
void sum(int row)//funtion to find sum of two rows of 16 bits
{
  int i,j;
  for(i=15;i>-1;i--){
  if(carry==0){
        if(su[i]==0&&data[row][i]==1)
            su[i]=1;
        else if(su[i]==1&&data[row][i]==1)
            {
							carry=1;su[i]=0;
						}
  }
  else if(carry==1){
        if(su[i]==1&&data[row][i]==0)
            su[i]=0;
        else if(su[i]==0&&data[row][i]==0){
            carry=0;su[i]=1;
        }
    }
  }
    if(carry==1){
        carry=0;
        ws++;
    }
}

void split(char a[])//function to strip a single string of bits into strings of 16 bits each
{
    int i=0,j,k;
    while(a[i]!='\0'){
        j=i/16;
        k=i%16;
        data[j][k]=a[i++]-'0';
    }
		i++;
    while(i<80){
        data[j][k]=0;
        j=i/16;k=(i++)%16;
    }
}

void binary(int b[16])//converting the overall checksum carry into binary for wrapsum
{
    int i=15;
    while(ws!=0){
        b[i--]=ws%2;
        ws=ws/2;
    }
}

void checksum(char a[])//to find checksum
{
    int i=0,b[16]={0};
    split(a);
    while(i<5)
        sum(i++);
    binary(b);
    for(i=15;i>-1;i--){
    if(carry==0){
        if(su[i]==0&&b[i]==1)
            su[i]=1;
        else if(su[i]==1&&b[i]==1)
            {
							carry=1;
							su[i]=0;
						}
        continue;
    }
    else if(carry==1){
        if(su[i]==1&&b[i]==0)
            su[i]=0;
        else if(su[i]==0&&b[i]==0){
            carry=0;su[i]=1;
        }
    }
	}
		for(i=0;i<16;i++){
			if(su[i]==1) su[i]=0;
			else su[i]=1;
		}
}

void main()
{
    int i,j;
    char a[80];
		printf("Enter the data\n");
		gets(a);
    checksum(a);
		printf("Enter the received data\n");
		gets(a);
		i=0;
		while(a[i]!='\0') i++;
		while(i%16!=0) i++;
		for(j=0;j<16;j++){
			a[i++]=su[j]+'0';
		}
		a[i]='\0';
		puts(a);
		checksum(a);
		j=0;
		for(i=0;i<16;i++) if(su[i]==1) {
			printf("The transaction is a failure!\n");
			j=1;
			break;
		}
		if(j==0) printf("Success!");
}
