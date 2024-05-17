#include<stdio.h>
int a[100],b[100],i,j,len,k,count=0;
int gp[]={1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,};
int main(){
	void div();
	printf("\nEnter the length of Data Frame:");
	scanf("%d",&len);
	printf("\nEnter the message :");
	for(i=0;i<len;i++)
	scanf("%d",&a[i]);
	for(i=0;i<16;i++)
	a[len++]=0;
	for(i=0;i<len;i++)
	b[i]=a[i];
	k=len-16;
	div();
	for(i=0;i<len;i++)
	b[i]=b[i]^a[i];
	printf("\nData to be transmitted: ");
	for(i=0;i<len;i++)
	printf("%2d",b[i]);
	printf("\n\nEnter the Received Data: ");
	for(i=0;i<len;i++)
	scanf("%d",&a[i]);
	div();
	for(i=0;i<len;i++)
	if(a[i]!=0)
	{
		printf("\nERROR in Received Data");
		goto END;
	}
		printf("\nData Received is ERROR FREE");
		END: printf("\nRemember is : ");
		for(i=(len-16);i<len;i++)
		printf("%d",a[i]);
		printf("\n");
}
void div()
{
	for(i=0;i<k;i++)
	{
		if(a[i]==gp[0])
		{
			for(j=i;j<17+i;j++)
			a[j]=a[j]^gp[count++];
		}
		count=0;
	}
}