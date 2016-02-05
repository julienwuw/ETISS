
#include "print.h"



#include <or1k-support.h>

extern void or1k_interrupt_handler(void);


typedef void (*irqhandler)(void);

irqhandler global_irqhandler[32];

void interrupt_handler(void) {
	unsigned mask = or1k_mfspr((9<<11)|0);
	or1k_mtspr((9<<11),0);
	unsigned irq = or1k_mfspr(9<<11|2) & mask;
	or1k_mtspr((9<<11) |2,0);
	for (int i = 0;i<32;i++){
		if (irq & (1<<i)){
			if (global_irqhandler[i]){
				(*global_irqhandler[i])();
			}
		}
	}

	or1k_mtspr((9<<5),mask);
}

void irq2(void){
	_cust_print("\n\n\nCALLED irq2\n\n\n");
	return;
}

void timer_isr() {
	_cust_print("<timer interrupt>");
	or1k_mtspr(17, or1k_mfspr(17) | 2 );
	or1k_mtspr((10<<11)+1, 0);
	or1k_mtspr((10<<11), 0xa0<<24 | 40000);
	return;
}

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

	for (int i = 3+30000;i>=3;i-=2){
		ret = ret - power(x,i)/((float)i);
	}

	return ret + x;

}

float pi(){
	return 16*atan_(1.0/5.0)-4*atan_(1.0/239.0);
}

int main(int arcg,char * argv[]){ 

	
	int i = or1k_mfspr(17);

	char * newline = "\n";
	//_cust_print_int((int)newline);

	*(volatile char*)0x80000000 = 'm';
	*(volatile char*)0x80000000 = 'a';
	*(volatile char*)0x80000000 = 'i';
	*(volatile char*)0x80000000 = 'n';
	*(volatile char*)0x80000000 = ' ';
	*(volatile char*)0x80000000 = 'c';
	*(volatile char*)0x80000000 = 'a';
	*(volatile char*)0x80000000 = 'l';
	*(volatile char*)0x80000000 = 'l';
	*(volatile char*)0x80000000 = 'e';
	*(volatile char*)0x80000000 = 'd';
	*(volatile char*)0x80000000 = '\n';


	for (int i = 0;i<32;i++)
		global_irqhandler[i] = 0;

	global_irqhandler[2] = irq2;
	or1k_exception_handler_add (0x8, &interrupt_handler);
	or1k_interrupt_enable(2);
	/*__asm__(
		".byte 0x7C,0x00,0x00,0x00"
	);*/

	// Timer interrupt
	int or1k_timer_period = 40000;
	or1k_exception_handler_add(0x5, &timer_isr); 			// Install handler for Timer interrupt
	or1k_mtspr(10<<11, 0x00<<24 | or1k_timer_period);		// Set Timer Mode Register
	or1k_mtspr(17, or1k_mfspr(17) | 2 );				// Set Special Purpose Register: Enable Timer interrupt
	or1k_mtspr((10<<11) + 1, 0);                             	// reset counter register (qemu bug: automatic counter reset does not work)




	for (int i = 1;i<10000; i = i * 2){
		_cust_print_int(i);
		_cust_print(newline);
	}





	//or1k_exception_handler_add (0x8, &or1k_interrupt_handler);
	//or1k_interrupt_handler_add(11, &irq2);
	//or1k_interrupt_enable(10);

	/*

	float x = 0;



	for (int j = 0;j<(1<<16);j++){
		for (int i = 0;i<(100);i++){
			x += 0.1;
		}
		*((int*)0x0000A000) = (int) x;
	}

	*((int*)0x10000000) = 0;
	*/


	float p = 2 * F(1);

	_cust_print("pi 1: ");
	_cust_print_float(p);
	_cust_print("\n");

	
	_cust_print("pi 2: ");
	_cust_print_float(pi());
	_cust_print("\n");
	

	//if (pi > 0.0)
		//_cust_print("\n\n3-pi > 0\n\n\n");



	//float c = 0;
	//for (int i = 0;i < 10000000;i++){
	//	c+=0.1;
	//}


	//return (int)c;
	return 0;
}
