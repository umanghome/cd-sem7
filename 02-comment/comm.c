#include <stdio.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

int main () {
	FILE *in;
	in = fopen("input.c", "r");
	if (in == NULL) {
		printf("Failed to read input.c\n");
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
				printf("\n");
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

		printf("%c", c);

	}

	printf("\n");

	return 0;
}