#ifndef MAIN_HEADER
#define MAIN_HEADER

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"


//RETURNS THE CHAR TYPE
int distinguishChar(const char c){
	if (c == ' '){
		//Space
		return 0;
	}
	else if (c >= '0' && c <= '9'){
		//Number
		return 1;
	}
	else{
		//Assume operator. and alphabets are ignored 
		return 2;
	}
}

//RETURNS THE PRECEDENCE
int getPrecedence(const char* c){
	switch (c[0]){
		case '(':
		case ')':
			return -1;
		case '!':
			//!=
			if (c[1] == '='){
				return 3;
			}
			//!
			else{
				return 7;
			}
		case '*':
		case '/':
			return 6;
		case '+':
		case '-':
			return 5;
		case '<':
		case '>':
			return 4;
		case '=':
		//case '!':
			return 3;
		case '&':
			return 2;
		case '|':
			return 1;
		default:
			printf("[PRECEDENCE] ERROR. SYMBOL NOT IDENTIFIED");
			return 0;
	}
}

//RETURNS IF NUMERIC DIGIT OR NOT
int isDigit(const char c){
	if(c >= 48 && c <= 58){
		return 1;
	}
	return 0;
}

//CUSTOM SOLUTION SINCE SNODE DOESN'T ALLOW INT
int evaluatePostfixWithoutQueue(char* postfix){
//NOT USING STACK/QUEUE. IT ADDS MORE STEPS TO STORE STRING THEN RECONVERT TO INT. JUST CONVERT AND USE INT ARRAY DIRECTLY
	int n_Temp = 0;			//TEMPORARY INT STORAGE
	int n_L, n_R;			//THE LEFT AND RIGHT INT FOR COMPUTATION
	int a_Operands[257];	//THE OPERANDS CONTAINER. CAN BE SWITCHED FOR QUEUE
	int n_Pointer = -1;		//THE STARTING POINTER INDEX

	int i = 0;	//THE CHAR INDEX


	//READ THE STRING
	while(postfix[i] != '\0'){
		//IF A NUMBER
		if (isDigit(postfix[i])){
			n_Temp += postfix[i] - 48;
			
			//CHECK IF IT'S THE LAST DIGIT THEN STORE
			if(!isDigit(postfix[i+1])){
				n_Pointer++;
				a_Operands[n_Pointer] = n_Temp;
			}
			//ELSE PREPARE TO ADD MORE DIGITS
			else{
				n_Temp *= 10;
			}
		}

		//JUST REFRESH IF SPACE
		else if (postfix[i] == ' '){
			n_Temp = 0;
		}

		//IF AN OPERATOR
		else{
			n_R = a_Operands[n_Pointer];	//SET THE CURRENT AS RIGHT
			n_Pointer--;
			n_L = a_Operands[n_Pointer];	//SET THE PREVIOUS AS LEFT


			switch(postfix[i]){
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
			//printf("(%d)", n_Temp);		//RESULT OF EVERY CALC
			a_Operands[n_Pointer] = n_Temp;		//OVERRIDE THE LEFT'S CONTAINER
		}
		i++;
	}

	return a_Operands[0];	//SINCE ALWAYS OVERRIDING THE LEFT, FINAL VALUE IS AT THE BOTTOM
}

//REFORMATS THE STRING
void cleanUpString(char* postfix){
	int i = 0;
	while (postfix[i] != '\0'){
		//REMOVE PARANTHESIS
		if (postfix[i] == '(' || postfix[i] == ')'){
			strcpy(postfix+i, postfix+i+1);
		}
		//REMOVE DOUBLE SPACES
		if (postfix[i] == ' ' && postfix[i+1] == ' '){
			strcpy(postfix+i, postfix+i+1);
		}
		
		i++;
	}
	
}
#endif