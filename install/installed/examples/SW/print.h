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
	
	@brief provides print and cpu time functions

	@detail 
		
		
		

*/
/**
	@brief uses custom ETISS:OR32 instructions to print the given string (0 terminated!) to stdout of the simulator
*/
extern void _cust_print(char*);
/**
	@brief uses custom ETISS:OR32 instructions to print a single character to stdout of the simulator
*/
extern void _cust_print_char(int);
/**
	@brief uses custom ETISS:OR32 instructions to print a float to stdout of the simulator
*/
extern void _cust_print_float(float);
/**
	@brief uses custom ETISS:OR32 instructions to print an integer to stdout of the simulator
*/
extern void _cust_print_int(int x);
/**
	@brief uses custom ETISS:OR32 instruction to return the current cpu time in microseconds (NOT REALTIME)
*/
extern unsigned _cust_time_us();

