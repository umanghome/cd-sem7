#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

int removeComments ();
int identifyOperators ();
int identifyIdentifiers ();
int identifyKeywords ();

int isKeyword (char*);
int isIdentifier (char*);
int isAlpha (char);
int isDigit (char);

void clearStr (char*);
int isToken (char*);

int main () {
	// Remove comments
	int removedComments = removeComments();
	
	// Identify operators
	printf("Operators:\n");
	int idetifiedOperators = identifyOperators();

	// Identify identifiers
	printf("\nIdentifiers:\n");
	int identifiedIdentifiers = identifyIdentifiers();

	// Identify keywords
	printf("\nKeywords:\n");
	int identifiedKeywords = identifyKeywords();

	return 0;
}

int removeComments () {
	FILE *in, *out;
	in = fopen("input.c", "r");
	if (in == NULL) {
		printf("Failed to read input.c\n");
		return 1;
	}
	
	out = fopen("input.tmp", "w");
	if (out == NULL) {
		printf("Failed to open input.tmp\n");
		return 1;
	}

	char c;

	bool withinString = false;
	while ((c = getc(in)) != EOF) {
		
		if (c == '/' && !withinString) {
			c = getc(in);
			if (c == '/') {
				while (c != '\n') {
					c = getc(in);
				}
				
				fprintf(out, "\n");
				continue;
			} else if (c == '*') {
				back:
					while (c != '*') {
						c = getc(in);
					}
					c = getc(in);
					if (c == '/') {
						continue;
					} else {
						goto back;
					}
			}
		}

		if (c == '"') {
			withinString = withinString ? false : true;
		}

		fprintf(out, "%c", c);

	}

	fprintf(out, "\n");

	fclose(in);
	fclose(out);

	return 0;
}

int identifyOperators () {
	bool prevPlus, prevMinus, prevDiv, prevMul, prevMod, prevEqual;
	bool withinString, withinChar;
	char c;
	FILE *fp;

	fp = fopen("input.tmp", "r");
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
				printf("%c\n", c);
			else if (c == '+' || c == '=')
				printf("%c\n", c);
			else
				printf("\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevMinus) {
			printf("-");
			if (c == '+' || c == '*' || c == '/' || c == '%')
				printf("%c\n", c);
			else if (c == '-' || c == '=')
				printf("%c\n", c);
			else
				printf("\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevEqual) {
			printf("=");
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c\n", c);
			else if (c == '=')
				printf("%c\n", c);
			else
				printf("\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevMul) {
			printf("*");
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c\n", c);
			else if (c == '=')
				printf("%c\n", c);
			else
				printf("\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevDiv) {
			printf("/");
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c\n", c);
			else if (c == '=')
				printf("%c\n", c);
			else
				printf("\n");
			prevPlus = prevMinus = prevDiv = prevMul = prevMod = prevEqual = false;
			continue;
		}
		if (prevMod) {
			printf("%%");
			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
				printf("%c\n", c);
			else if (c == '=')
				printf("%c\n", c);
			else
				printf("\n");
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

	fclose(fp);

	return 0;
}

int identifyIdentifiers () {
	FILE *fp;

	fp = fopen("input.tmp", "r");
	if (fp == NULL) {
		printf("Could not open input file.\n");
		return 1;
	}

	char str[1000];
	char c;
	int nextIsNew = true;
	while ((c = getc(fp)) != EOF) {
		if (nextIsNew) clearStr(str);
	
		int counter = 0;

		bool withinString = false;

		while (true) {
			char prevChar = '\0';
			if (c == '"') {
				while (true) {
					prevChar = c;
					c = getc(fp);
					if (c == '"' && prevChar != '\\') {
						break;
					} else {
						continue;
					}
				}
				break;
			}

			if (!isDigit(c) && !isAlpha(c) && c != '_') {
				break;
			} else {
				str[counter++] = c;
				c = getc(fp);
			}
		}

		if (isIdentifier(str)) {
			printf("%s\n", str);
		}
	}

	fclose(fp);

	return 0;

}

int identifyKeywords () {
	FILE *fp;

	fp = fopen("input.tmp", "r");
	if (fp == NULL) {
		printf("Could not open input file.\n");
		return 1;
	}

	char str[1000];
	char c;
	int nextIsNew = true;
	while ((c = getc(fp)) != EOF) {
		if (nextIsNew) clearStr(str);
	
		int counter = 0;

		bool withinString = false;

		while (true) {
			char prevChar = '\0';
			if (c == '"') {
				while (true) {
					prevChar = c;
					c = getc(fp);
					if (c == '"' && prevChar != '\\') {
						break;
					} else {
						continue;
					}
				}
				break;
			}

			if (!isDigit(c) && !isAlpha(c) && c != '_') {
				break;
			} else {
				str[counter++] = c;
				c = getc(fp);
			}
		}

		if (isKeyword(str)) {
			printf("%s\n", str);
		}
	}

	fclose(fp);

	return 0;

}

void clearStr (char* str) {
	for (int i = 0; i < 1000; i++) str[i] = '\0';
}

int isKeyword (char* str) {
	static char keywords[32][32] = { "auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while" };
	for (int i = 0; i < 32; i++) {
		if (strcmp(str, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int isAlpha (char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
	return 0;
}

int isDigit (char c) {
	if (c >= '0' && c <= '9') return 1;
	return 0;
}

int isIdentifier (char* str) {
	if (isKeyword(str)) return 0;
	int length = strlen(str);
	if (length >= 32) return 0;
	char c = str[0];
	if (!isAlpha(c) && c != '_') return 0;
	for (int i = 1; i < length; i++) {
		c = str[i];
		if (!isAlpha(c) && !isDigit(c) && c != '_') return 0;
	}
	return 1;
}