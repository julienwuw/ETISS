#
#	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich
#
#	The above copyright notice and this permission notice shall be included in
#	all copies or substantial portions of the Software.
#
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#	THE SOFTWARE.
#
#	Author: Marc Greim <marc.greim@mytum.de>
#
#	Date: July 29, 2014
#
#	Version: 0.1
#
#

	.global _cust_print
_cust_print:
	l.sw -4(r1),r4
	l.sw -8(r1),r3
	l.addi r4,r3,0x0
_cust_print_loop:
	l.lbz r3,0(r4)
	l.sfeqi r3,0
	l.bf _cust_print_exit
	l.nop
	l.movhi r13,0x8000
	l.sw 0(r13),r3
#	l.nop 0x04
	l.j _cust_print_loop
	l.addi r4,r4,1
_cust_print_exit:
	l.lwz r3,-8(r1)
	l.lwz r4,-4(r1)
	l.jr r9
	l.nop
	
	.global _cust_print_char
_cust_print_char:
	l.movhi r13,0x8000
	l.sw 0(r13),r3
#	l.nop 0x04
	l.jr r9
	l.nop
	
	.global _cust_time_us
_cust_time_us:
	l.jr r9
	l.nop



