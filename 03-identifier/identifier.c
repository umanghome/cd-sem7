#include <stdio.h>
#include <string.h>

int isKeyword (char*);
int isIdentifier (char*);
int isAlpha (char);
int isDigit (char);

int main () {
	char* str;
	printf("Enter identifier to check: ");
	gets(str);
	if (!isIdentifier(str)) {
		printf("%s is not an identifier!\n", str);
		return 1;
	} else {
		printf("%s is an identifier!\n", str);
	}
	return 0;
}

int isKeyword (char* str) {
	static char keywords[32][32] = { "auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while" };
	for (int i = 0; i < 14; i++) {
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