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
				printf("\nSingle-line comment: ");
				while (c != '\n') {
					c = getc(in);
					printf("%c", c);
				}
				continue;
			} else if (c == '*') {
				printf("\nMulti-line comment: ");
				back:

					while (c != '*') {
						printf("%c", c);
						c = getc(in);
					}
					c = getc(in);
					if (c == '/') {
						printf("\n");
						continue;
					} else {
						goto back;
					}
			}
		}

		if (c == '"') {
			withinString = withinString ? false : true;
		}

	}

	printf("\n");

	return 0;
}