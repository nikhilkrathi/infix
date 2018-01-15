#include "stack.h"
void push(stack *s, int num) {
	s->a[s->i]= num;
	(s->i)++;
}
/* the caller should check that the stack is not empty before calling pop() 
 */

int empty(stack *s) {
	return s->i == 0;
}
int full(stack *s) {
	return s->i == MAX;
}
/* It is mandatory to call init() on a stack before calling push, pop or any other function on the stack 
 */

