#include <stdio.h>



#include "testbench.c"

void _cust_print(char * s){printf("%s",s);}
void _cust_print_float(float f) {printf("%f",f);}
void _cust_print_int(int i) { printf("%d",i);}

float power(float x,int count){
	float ret = 1;
	for (int i = 0;i<count;i++){
		ret = ret * x;
	}
	return ret;
}
float F (int i) {
	if (i > 100)
		return 1;
    	return 1 + i / (2.0 * i + 1) * F(i + 1);
}

float atan_(float x) {
	float ret = 0;
	
	for (int i = 3+3000*4;i>=3;i-=2){
		ret = ret - power(x,i)/((float)i);
	}		

	return ret + x;

}

float pi(){
	return 16*atan_(1.0/5.0)-4*atan_(1.0/239.0);
}


int main (int argc,char**argv){

	float p = 2 * F(1);
	
	printf("pi 1: ");
	printf("%f",p);
	printf("\n");
	
	printf("pi 2: ");
	printf("%f",pi());
	printf("\n");

}
