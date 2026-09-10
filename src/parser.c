#include "parser.h"
#include <stdio.h>
#include <string.h>
int parser(char *data)
{
   
long temp=0;
int j=0;
int k=0;
printf("str length = %d",strlen(data));
for(unsigned int i=0;i<strlen(data);i++)
{
       //printf("word[%d]=%d\n",i,paras[i]-0x30);
       if(data[i] >= 48 && data[i] <= 57 )
       	 {  	    
       	    temp = (temp * 10) + (data[i] - 0x30);   
       	 }
       	 else
       	 {
	       	 num[j] = temp;
		 temp=0;
		 printf("num[%d]= %ld\n",j,num[j]);	
		 j++;
       	 }
         
        // printf("temp=%ld",temp);
	if(data[i] >= 42 && data[i] <= 47 )
	       	 {  	    
	       	         
	       	    sign[k] = data[i]  ;
	       	    k++;
	       	 }
}
return j;
}
