/*****************************************************
YOU ARE NOT ALLOWED TO MODIFY THE FUNCTION PROTOTYPES
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "stack.h"
#include "queue.h"
#include "main.h"

#include "algorithms.h"



//gcc -Wall -o main main.c && main
int main() {
	char str_Infix[257];
	char str_PostFix[257];
	int n_Result;
	printf("CALCULATOR: \n");

	while (1){
		scanf("%[^\n]%*c", str_Infix);
		if (!strcmp(str_Infix, "QUIT")){
			break;
		}
		
		//CONVERT TO POSTFIX
		infixToPostfix(str_Infix, str_PostFix);
		printf(BLU "%s" RESET, str_PostFix);
		
		//CALCULATE THE VALUE
		n_Result = evaluatePostfix(str_PostFix);
		if (n_Result == -999){	//AVOID RESULTS OF -999 SINCE THIS IS MEANT FOR ERROR PROMPT
			printf(RED "\nDivision error by zero!\n\n" RESET);
		}
		else{
			printf(GRN "\n%d\n\n" RESET, n_Result);
		}
	}
	printf("CLOSED PROGRAM");
}

