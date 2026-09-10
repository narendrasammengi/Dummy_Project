#include<stdio.h>
#include "add.h"
#include "sub.h"
void calculate(int np , long *data , char *sign)
{

 long temp =0;
 char operator ;
 for(int i=0;i< np;i++)
 {
	 operator = sign[i];
	 switch (operator)
	 {
	 	case 42:
	 		
	 	break;
	 	case 43:
	 		temp = add(data[i] , data[i+1]) ;
	 		data[i+1] = temp;
	 	break;
	 	case 44:
	 	
	 	break;
		case 45:
		temp = sub(data[i] , data[i+1] );
	 		data[i+1] = temp;
	 	break;
		case 46:
	 	break;
		case 47:
	 	break;
	 	}
 }

printf("result = %ld\n",temp);
}
