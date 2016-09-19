#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define true 1
#define false 0

bool isTerminal (char c, char* terminals, int count) {
	for (int i = 0; i < count; i++) {
		if (c == terminals[i]) return true;
	}
	return false;
}

bool isNonTerminal (char c, char* non_terminals, int count) {
	for (int i = 0; i < count; i++) {
		if (c == non_terminals[i]) return true;
	}
	return false;
}

int findIndex (char c, char* arr, int count) {
	for (int i = 0; i < count; i++) {
		if (c == arr[i]) return i;
	}
	return -1;
}

int parse (char*** rules, char* non_terminals, char* terminals, int* counters, int number_nt, int number_t, char* input, char left_prod, int rule_index, int counter) {
	int length = strlen(input);
	if (counter >= length) return -1;
	int prod_index = findIndex(left_prod, non_terminals, number_nt);

	int i, j;

	int rule_length = strlen(rules[prod_index][rule_index]);

	for (i = counter, j = 0; j < rule_length; j++) {
		i = counter;
		char c = rules[prod_index][rule_index][j];
		if (isTerminal(c, terminals, number_t)) {
			if (input[i] == c) {
				counter++;
				continue;
			} else {
				// CAN'T PROCESS!
				return -1;
			}
		} else {
			// spawn for the non-terminal
			char nt = c;
			int index_nt = findIndex(nt, non_terminals, number_nt);
			int times = counters[index_nt];
			int f = -1;
			for (int x = 0; x < times; x++) {
				f = parse(rules, non_terminals, terminals, counters, number_nt, number_t, input, c, x, counter);
				if (f >= 0) {
					counter = f;
				}
			}
		}
	}
	return counter;
}

int main () {
	int i, j;

	printf("Number of non-terminals: ");
	int number_nt;
	scanf("%d", &number_nt);

	printf("Number of terminals (excluding e [epsilon]): ");
	int number_t;
	scanf("%d", &number_t);

	printf("Enter %d non-terminals separated by a new line (each should be a single char):\n", number_nt);
	char* non_terminals = (char*) malloc(sizeof(char) * (number_nt + 2));
	for (i = 0; i < number_nt; i++) {
		getchar();
		non_terminals[i] = getchar();
	}
	non_terminals[i] = '\0';

	printf("Enter %d terminals separated by a new line (each should be a single char):\n", number_t);	
	char* terminals = (char*) malloc(sizeof(char) * (number_t + 2));
	for (i = 0; i < number_t; i++) {
		getchar();
		terminals[i] = getchar();
	}
	terminals[i++] = 'e';
	terminals[i] = '\0';

	number_t++;

	int* counters = (int*) malloc(sizeof(int) * (number_nt + 2));

	char*** rules = (char***) malloc(sizeof(char**) * (number_nt + 2));

	for (i = 0; i < number_nt; i++) {
		printf("How many rules do you have for %c? ", non_terminals[i]);
		scanf("%d", &counters[i]);

		rules[i] = (char**) malloc(sizeof(char*) * 20);

		printf("Enter the %d rule(s) separated by a new line:\n", counters[i]);
		for (j = 0; j < counters[i]; j++) {
			rules[i][j] = (char*) malloc(sizeof(char) * 20);
			scanf("%s", rules[i][j]);
		}
	}

	printf("\nRules are:\n");
	for (i = 0; i < number_nt; i++) {
		int count = counters[i];
		for (j = 0; j < count; j++) {
			printf("%c => %s\n", non_terminals[i], rules[i][j]);
		}
	}

	fflush(stdin);
	fflush(stdout);

	char start;
	printf("Start symbol: ");
	getchar();
	start = getchar();

	char *input = (char*) malloc(sizeof(char) * 20);
	printf("Input string: ");
	scanf("%s", input);

	printf("Input string is %s\n", input);

	int startIndex = findIndex(start, non_terminals, number_nt);

	int flag = -1;
	int counter = 0;

	for (i = 0; i < counters[startIndex]; i++) {
		flag = parse(rules, non_terminals, terminals, counters, number_nt, number_t, input, start, i, counter);
		if (flag >= 0) break;
	}

	if (flag >= 0) {
		printf("Parsed successfully!\n");
	} else {
		printf("Parsed unsuccessfully!\n");
	}

	return 0;
}