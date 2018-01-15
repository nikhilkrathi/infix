#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "cstack.h"
#include "stack.h"
#include "token.h"

int readline(char *arr, int len) {
	int i = 0;
	int ch;
	while((ch = getchar()) != '\n' && i < len - 1) {
		arr[i] = ch;
		i++;
	}
	arr[i] = '\0';
	return i;
}
int precedence (char op) {
	if(op == '(' || op == ')')
		return 4;
	if(op == '%')
		return 3;
	if(op == '*' || op == '/')
		return 2;
	if(op == '+' || op == '-')
		return 1;
/*	if(op == '@')	
		return 0;
*/
}

char ctop(cstack *cs) {
	char x = cpop(cs);
	cpush(cs, x);
	return x;
}	

int top(stack *a) {
	int c = pop(a);
	push(a, c);
	return c;
}


int infixeval(char *infix) {
	token *t;
	int x, y, z, p, q, k, i = 1;
	int result,/* reset = 1,*/ score;
	char m, n, w;
	stack a, c;
	cstack b, d;
	init(&a); 
	init(&c);
	cinit(&b);
	cpush(&b,'@');
	cinit(&d);
	cpush(&d,'@');
	while(i) {
		t = getnext(infix);
		if(t->type == OPERAND) { 
			push(&a, t->number);
		}
		else if (t->type == OPERATOR) {
			if(t->op == '(') {
				score = infixeval(infix);
				push(&a, score);
			}
			else if(t->op == ')') {
				break;
			}
			else	
			cpush(&b, t->op);
		}
		
		else if (t->type == ERROR) 
			return INT_MIN; 
		else if(t->type == END) {
			i = 0;
		}

	}
	
	while(!empty(&a)) {
	k = pop(&a);
	push(&c, k);
	}
	
	while(1) {
	w = cpop(&b);
	if(w == '@')
		break;
	cpush(&d, w);
	}
		
	while(1) {
		if(!cempty(&d))
			m = cpop(&d);
		else
			break;
		if(!empty(&c)) {
			n = ctop(&d);
			p = precedence(m);
			q = precedence(n);
			if(p >= q) {
				if(!empty(&c))
					x = pop(&c);
				else 
					break;
				if(!empty(&c))
					y = pop(&c);
				else
					break;
				
				switch(m) {
					case '+':
						result = x + y;
						break;
					case '-':
						result = x - y;
						break;
					case '*':
						result = x * y;
						break;
					case '/':
						result = x / y;
						break;
					case '%':
						result = y % x;
						break;
							
				}
				push(&c, result);
			}
		
			else {
				if(!empty(&c))
					x = pop(&c);
				else 
					break;
				if(!empty(&c))
					y = pop(&c);
				else
					break;
				if(!empty(&c))
					z = pop(&c);
				switch(n) {
					case '+':
						result = y + z;
						break;
					case '-':
						result = y - z;
						break;
					case '*':
						result = y * z;
						break;
					case '/':
						result = y / z;
						break;
					case '%':
						result = y % z;
						break;
				}
				push(&c,result);
				push(&c, x);
				cpop(&d);
				cpush(&d, m);
			}
		}

	}	
	return result;
			
}

int main() {
	char infix[128];
	int x, ans;
	while((x = readline(infix, 128))) {
		ans = infixeval(infix);
		if(ans == INT_MIN) {
			fprintf(stderr, "Error in expression\n");
		}  
/*		else
			fprintf(stdout, "%d\n", ans);
*/	}
	return 0;
}
