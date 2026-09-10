#include<stdio.h>
#include<string.h>
#include "main.h"
extern int calculate(int , long *, char *);
extern int parser(char *);
char paras[100];
int main()
{
	printf("Enter Number\n");
 	fgets(paras,sizeof(paras),stdin);
 	printf("%s" , paras);
 	int Num_of_paras = parser(paras);
 	calculate(Num_of_paras,num,sign);
/*
	
printf("user=%s\n",USER);
printf("Heelo naren this is makefile project\n");

result = add(2,3);
printf("Addition Result = %d\n",result);
 result = sub(2,3);
printf("subtraction Result = %d\n",result);*/


return 0;
}






