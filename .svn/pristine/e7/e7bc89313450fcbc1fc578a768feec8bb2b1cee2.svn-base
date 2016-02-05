/**

@copyright 
<pre>


	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.


</pre>
@author Marc Greim <marc.greim@mytum.de>

@date July 29, 2014

@version 0.1

*/
/**
	@file
	
	@brief partially implements print.h (other part is in print.S)

	@detail 
		
		
		

*/
#include "print.h"

void _cust_print_float(float x){
	
	if (x < 0){
		_cust_print_char('-');
		x = -x;
	}

	float restoreprec = x;
	unsigned d = 0;
	while (x >= 1.0){
		d++;
		x = x / 10.0;
	}
	
	while (d > 0){
		x = x * 10;
		int i = (int)x;
		if (((float)i)>x)
			i--;
		x = x-(float)i;
		_cust_print_char('0'+i);
		d--;
	}
	
	_cust_print_char('.');
	
	x = restoreprec;
	
	while (x >= 1000000000000.0)
		x = x-1000000000000.0;
	while (x >= 10000000000.0)
		x = x-10000000000.0;
	while (x >= 100000000.0)
		x = x-100000000.0;
	while (x >= 1000000.0)
		x = x-1000000.0;
	while (x >= 10000.0)
		x = x-10000.0;
	while (x >= 100.0)
		x = x-100.0;
	while (x >= 1.0)
		x = x-1.0;
	
	for (int i = 0;i<10;i++){
		x = x * 10;
		int j = (int)x;
		if (((float)j)>x)
			j--;
		x = x-(float)j;
		_cust_print_char('0'+j);
	}


}

void _cust_print_int(int x) {
	_cust_print_char('0');
	_cust_print_char('x');
	for (int i = ((sizeof(int)<<1)-1);i>=0;i--){
		int tmp = i*4;
		tmp = x>>tmp;
		tmp = tmp & 0x0f;
		if (tmp < 10){
			_cust_print_char('0'+tmp);
		} else {
			_cust_print_char('A'+tmp-10);
		}
	}
}

