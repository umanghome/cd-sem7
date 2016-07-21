#include <stdio.h>

#define bool int
#define true 1
#define false 0

int main () {
	bool prevPlus, prevMinus, prevDiv, prevMul, prevMod, prevEqual;
	bool withinString, withinChar;
	char c;
	FILE *fp;

	fp = fopen("input.c", "r");
	if (fp == NULL) {
		printf("Could not open input file.\n");
		return 1;
	}

	prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
	withinString = withinChar = false;

	while ((c = getc(fp)) != EOF) {
		if (!withinString && c == '\'') {
			withinChar = !withinChar;
			continue;
		}
		if (!withinChar && c == '"') {
			withinString = !withinString;
			continue;
		}
		if (withinString || withinChar) continue;
		if (prevPlus) {
			printf("+");
			if (c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c is not a valid operator.\n", c);
			else if (c == '+' || c == '=')
				printf("%c is a valid operator.\n", c);
			else
				printf(" is a valid operator.\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevMinus) {
			printf("-");
			if (c == '+' || c == '*' || c == '/' || c == '%')
				printf("%c is not a valid operator.\n", c);
			else if (c == '-' || c == '=')
				printf("%c is a valid operator.\n", c);
			else
				printf(" is a valid operator.\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevEqual) {
			printf("=");
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c is not a valid operator.\n", c);
			else if (c == '=')
				printf("%c is a valid operator.\n", c);
			else
				printf(" is a valid operator.\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevMul) {
			printf("*");
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c is not a valid operator.\n", c);
			else if (c == '=')
				printf("%c is a valid operator.\n", c);
			else
				printf(" is a valid operator.\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevDiv) {
			printf("/");
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c is not a valid operator.\n", c);
			else if (c == '=')
				printf("%c is a valid operator.\n", c);
			else
				printf(" is a valid operator.\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevMod) {
			printf("%%");
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c is not a valid operator.\n", c);
			else if (c == '=')
				printf("%c is a valid operator.\n", c);
			else
				printf(" is a valid operator.\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}

		prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
		switch (c) {
			case '+': prevPlus = true; break;
			case '-': prevMinus = true; break;
			case '/': prevDiv = true; break;
			case '*': prevMul = true; break;
			case '=': prevEqual = true; break;
			case '%': prevMod = true; break;
			default: break;
		}

	}

	return 0;
}