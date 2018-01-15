#include <stdio.h>
#include <stdlib.h>
#include "token.h"
/* getnext() will return the type of next "token" (OPERAND or OPERATOR)
 * from "arr" and store the token in "number" or "op" depending on 
 * whether it was operand or operator.
 * getnext() returns pointers to malloced() memory. The caller should free it.
 */  
enum states { SPC, DIG, OPR, STOP, ERR };
token *getnext(char *arr) {
	static int currstate = SPC;
	int nextstate;
	static int i = 0, reset = 0;
	int num;
	if(reset == 1) {
		token *t = (token *)malloc(sizeof(token));
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': 
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')':
				nextstate = OPR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERR;
				break;
		}
		switch(currstate) {
			case SPC:
				if(nextstate == DIG)
						num = arr[i] - '0';			
				break;
			case DIG:
				if(nextstate == DIG)
					num = num * 10 + arr[i] - '0';
				else  {
					t->type = OPERAND;
					t->number = num;
					currstate = nextstate;
					return t;
				}
				break;
			case OPR:
				t->type = OPERATOR;
				t->op = arr[i - 1];	
				currstate = nextstate;
				return t;
				break;
			case STOP:
				t->type = END;
				currstate = nextstate;
				reset = 1;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				reset = 1;
				return t;
				break;
		}
		currstate = nextstate;
		i++;
	}
}


