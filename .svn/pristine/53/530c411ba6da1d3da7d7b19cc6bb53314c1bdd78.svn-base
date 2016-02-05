
#include "print.h"

void test_mul(){
	
	int m1;
	int m2;
	
	m1 = 3;
	m2 = 5;
	
	if (m1 * m2 != 15){
		_cust_print("failed test_mul [15]: "); _cust_print_int(m1 * m2); _cust_print("\n");
		return;
	}
	
	m1 = -3;
	m2 = 5;
	
	if (m1 * m2 != -15){
		_cust_print("failed test_mul [-15]: "); _cust_print_int(m1 * m2); _cust_print("\n");
		return;
	}
	
	m1 = 3567;
	m2 = 56454;
	
	if (m1 * m2 != 201371418){
		_cust_print("failed test_mul [201371418]: "); _cust_print_int(m1 * m2); _cust_print("\n");
		return;
	}
	
	m1 = 3567;
	m2 = -56454;
	
	if (m1 * m2 != -201371418){
		_cust_print("failed test_mul [-201371418]: ");  _cust_print_int(m1 * m2); _cust_print("\n");
		return;
	}
	
	m1 = 3567;
	m2 = 56454;
	
	if (m1 * 56454 != 201371418){
		_cust_print("failed test_mul [201371418i]: "); _cust_print_int(m1 * 56454); _cust_print("\n");
		return;
	}
	
	m1 = 3567;
	m2 = -56454;
	
	if (m1 * -56454 != -201371418){
		_cust_print("failed test_mul [-201371418i]: ");  _cust_print_int(m1 * -56454); _cust_print("\n");
		return;
	}

}

void test_div(){
	
	int m1;
	int m2;
	
	m1 = 9;
	m2 = 3;
	
	if (m1 / m2 != 3){
		_cust_print("failed test_div [3]: "); _cust_print_int(m1 / m2); _cust_print("\n");
		return;
	}
	
	m1 = 9;
	m2 = -3;
	
	if (m1 / m2 != -3){
		_cust_print("failed test_div [-3]: "); _cust_print_int(m1 / m2); _cust_print("\n");
		return;
	}
	
	m1 = 201371418;
	m2 = 56454;
	
	if (m1 / m2 != 3567){
		_cust_print("failed test_div [3567]: "); _cust_print_int(m1 / m2); _cust_print("\n");
		return;
	}
	
	m1 = 201371418;
	m2 = -56454;
	
	if (m1 / m2 != -3567){
		_cust_print("failed test_div [-3567]: ");  _cust_print_int(m1 / m2); _cust_print("\n");
		return;
	}
	
	m1 = 201371418;
	m2 = 56454;
	
	if (m1 / 56454 != 3567){
		_cust_print("failed test_div [3567i]: "); _cust_print_int(m1 / 56454); _cust_print("\n");
		return;
	}
	
	m1 = 201371418;
	m2 = -56454;
	
	if (m1 / -56454 != -3567){
		_cust_print("failed test_div [-3567i]: ");  _cust_print_int(m1 / -56454); _cust_print("\n");
		return;
	}

}

void test_fmul(){
	
	float m1;
	float m2;
	
	m1 = 3.4375;
	m2 = 5.3125;
	
	if (m1 * m2 != 18.26171875){
		_cust_print("failed test_fmul [18.26171875]: ");  _cust_print_float(m1 * m2); _cust_print("\n");
		return;
	}
	
	m1 = -3.4375;
	m2 = 5.3125;
	
	if (m1 * m2 != -18.26171875){
		_cust_print("failed test_fmul [-18.26171875]: "); _cust_print_float(m1 * m2); _cust_print("\n");
		return;
	}
}

void test_fdiv(){
	
	float m1;
	float m2;
	
	m1 = 4.14375;
	m2 = 5.3125;
	
	if (m1 / m2 != 0.78){
		_cust_print("failed test_fdiv [0.78]: ");  _cust_print_float(m1 / m2); _cust_print("\n");
		return;
	}
	
	m1 = -4.14375;
	m2 = 5.345;
	
	if (m1 / m2 != -0.78){
		_cust_print("failed test_fdiv [-0.78]: "); _cust_print_float(m1 / m2); _cust_print("\n");
		return;
	}
}

void test_shift(){
	
	int m1;
	int m2;
	
	m1 = 3;
	m2 = 5;
	
	if (((m1 << m2)>>6) != 1){
		_cust_print("failed test_shift [1]: ");  _cust_print_int(((m1 << m2)>>6)); _cust_print("\n");
		return;
	}
}




void test_all(){

	test_mul();
	test_div();
	test_fmul();
	test_shift();
}
