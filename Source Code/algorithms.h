/*****************************************************
YOU ARE NOT ALLOWED TO MODIFY THE FUNCTION PROTOTYPES
*****************************************************/
#include "main.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void infixToPostfix(char *infix, char *postfix) {
	stack *p_Operators = createStack(100);	//STACK FOR OPERATORS
	strcpy(postfix, "");		//RESET POSTFIX

	int i = 0;
	
	//READ THE INFIX CHARS
	while(infix[i] != '\0'){	
		char *str_Copy = malloc(257);	//MUST CREATE A NEW STRING EVERY LOOP OR IT'LL COPY PREVIOUS STRING'S VALUE. IDEALLY SIZE MALLOC (NUMBER OF LARGEST INTEGER DIGITS) COULD BE ENOUGH SINCE NEW STRING EVERY LOOP
		str_Copy[i] = infix[i];
		
		switch (distinguishChar(infix[i])){
			//SPACES
			case 0:
				break;
			//NUMBERS
			case 1:
				str_Copy[i+1] = '\0';
				strcat(postfix, (str_Copy+i));	//DIRECTLY ADD THE CHAR
				if(infix[i+1] == ' '){
					strcat(postfix, " ");		//CONCAT A SPACE WHEN IT'S THE LAST DIGIT
				}
				break;
			//OPERATORS
			case 2:
				//EXTARCT THE OPERATOR
				//SINGLE DIGIT OPERATORS +, -, !, /...
				if (infix[i+1] == ' '){
					str_Copy[i+1] = '\0';
					//printf("SINGLE: %s", str_Copy+i);
				}
				//DOUBLE DIGIT OPERATORS !=, ==, &&, ||...
				else{
					str_Copy[i+1] = infix[i+1];
					str_Copy[i+2] = '\0';
					//printf("DOUBLE: %s", str_Copy+i);
				}


				//HANLE WHAT TO DO WITH THE OPERATOR AND STACK
				//PUSH IF EMPTY
				if (stackEmpty(p_Operators)){
					push(&p_Operators, "(");
					push(&p_Operators, (str_Copy+i));
				}

				//PUSH IF (
				else if (str_Copy[i] == '('){
					push(&p_Operators, (str_Copy+i));
				}
				
				//IF ), KEEP POPPING UNTIL (
				else if (str_Copy[i] == ')'){
					while (top(p_Operators)[0] != '(' ){
						strcat(postfix, pop(&p_Operators));
						strcat(postfix, " ");
					}
					//POP THE ( BUT DON'T STORE IT
					pop(&p_Operators);
					//NO NEED TO ADD ) FROM STR_COPY
				}
				
				//PUSH IF GREATER PRECEDENCE	
				else if(getPrecedence(str_Copy+i) > getPrecedence(top(p_Operators))){
					push(&p_Operators, (str_Copy+i));
				}
				
				//POP LOOP IF <= PRECEDENCE
				else if (getPrecedence(str_Copy+i) <= getPrecedence(top(p_Operators))){
					//POP ALL LOWER/EQUAL PRECEDENCE OR UNTIL ( 
					while (getPrecedence(str_Copy+i) <= getPrecedence(top(p_Operators)) && top(p_Operators)[0] != '('){
						strcat(postfix, pop(&p_Operators));
						strcat(postfix, " ");
					}
					//PUSH NOW THAT IT'S THE GREATEST PRECEDENCE
					push(&p_Operators, str_Copy+i);
				}


				//MOVE THE POINTER TO ADJUST FOR 2 DIGIT OPERATORS
				if (strlen(str_Copy+i) == 2){
					i++;	//AVOID READING THE 2ND DIGIT OF AN 2 DIGIT OPERATOR '=' OF !=, <=, >=...
				}
				break;
			default:
				break;
		}
		//INCREMENT THE POINTER FOR READING THE NEXT CHAR
		i++;
	}
	//STRING PARSING LOOP END

	//DUMP ALL REMAINING OPERATORS
	while (!stackEmpty(p_Operators)){
		strcat(postfix, " ");
		strcat(postfix, pop(&p_Operators));
	}

	cleanUpString(postfix);
}

int evaluatePostfix(char *postfix) {
	return evaluatePostfixWithoutQueue(postfix); //VER NOT USING STACK/QUEUE. IT ADDS MORE STEPS TO STORE OPERANDS AS STRING THEN RECONVERT TO INT. JUST IMMEDIATELY CONVERT AND USE INT ARRAY DIRECTLY
	

	//Other ver attempting to use stack/queue
	/*
	int n_Temp = 0;                          //temp int storage
	char c_Temp;                        
	//char c_TempNext;
	int n_TempResult;
	int n_L, n_R;                            //L & R int for computation
	queue* p_Operators = createQueue(257);   //Creates a queue for operators
	stack* p_Operands = createStack(257);    //Creates a stack for operands
	stack* p_TempResult = createStack(257); //Stack if postfix cannot be solved in one go
	int n_Pointer = 0;                       //starting pointer index

	int i = 0;	//index for postfix

	//loops until postfix is completely solved
	while(postfix[i] != '\0'){

		//keeps looping until the postfix is an operator followed by an operand
		while(!(isDigit(postfix[i]) && !isDigit(postfix[i-2]))){
			
			//if postfix value in i is a digit, add it to the stack
			if (isDigit(postfix[i])){
				n_Temp += postfix[i] - 48;

				//if slot after current digit is a digit, loop to keep adding values.
				while(isDigit(postfix[i+1])){
					i++;
					n_Temp *= 10;
					n_Temp += postfix[i] - 48;
				}

				push(&p_Operands, n_Temp);
			}

			//if postfix value is a space, disregard it
			else if (postfix[i] == ' '){

			}

			//if postfic value in i is an operator, add it to the queue
			else{
				c_Temp = postfix[i];
				
				enqueue(&p_Operators, c_Temp);
			}

		//increments index to move on to the next slot in the postfix array.
		i++;
		}

		//evaluation step
		//loops until all values in the stack and queue are used up
		while(!queueEmpty(p_Operators) && !stackEmpty(p_Operands)){
			n_R = pop(&p_Operands);
			n_L = pop(&p_Operands);

			switch(dequeue(&p_Operators)){
				case '+':
					n_Temp = n_L + n_R;
					break;
				case '-':
					n_Temp = n_L - n_R;
					break;
				case '*':
					n_Temp = n_L * n_R;
					break;
				case '/':
					if (n_R == 0){
						//ERROR FOR DIVIDING BY ZERO
						return -999;
					}
					n_Temp = n_L / n_R;
					break;
				case '&':
					//&&
					n_Temp = n_L && n_R;
					i++;	//AVOID READING 2nd &
					break;
				case '|':
					n_Temp = n_L || n_R;
					i++;	//AVOID READING 2nd |
					break;
				case '=':
					//==
					n_Temp = n_L == n_R;
					i++;	//AVOID READING 2nd =
					break;
				case '!':
					//!=
					if (postfix[i+1] == '='){
						n_Temp = n_L != n_R;
						i++;	//AVOID READING =
					}
					//!
					else{
						n_Temp = !n_R;
						n_Pointer++;	//MOVE THE POINTER BACK TO USE RIGHT'S CONTAINER.
					}
					break;
				case '<':
					//<=
					if(postfix[i+1] == '='){
						n_Temp = n_L <= n_R;
						i++;	//AVOID READING =
					}
					//<
					else{
						n_Temp = n_L < n_R;
					}
					break;
				case '>':
					//>=
					if(postfix[i+1] == '='){
						n_Temp = n_L >= n_R;
						i++;	//AVOID READING =
					}
					//>
					else{
						n_Temp = n_L > n_R;
					}
					break;
				default:
			}
		}
			
			
			push(p_TempResult, n_Temp);		//OVERRIDE THE LEFT'S CONTAINER
		
	}

	return p_Operands[0];	//SINCE ALWAYS OVERRIDING THE LEFT, FINAL VALUE IS AT THE BOTTOM
	*/
}

//supposedly for the operators with 2 slots
/*
				//if operator has more than 1 slot in the post fix
				if(!isDigit(postfix[i+1]) && postfix[i+1] != ' '){
					i++;
					strcpy(c_TempNext, postfix[i]); 
					strcat(c_Temp, c_TempNext);
				}*/