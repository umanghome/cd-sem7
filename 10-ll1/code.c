#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool int
#define true 1
#define false 0
#define STACK_SIZE 50
#define MAX_TRIES 100

void strrev (char* str) {
	int length = strlen(str);

	for (int i = 0; i < (length / 2); i++) {
		char tmp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tmp;
	}
}

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

bool containsEpsilonInProduction (int nt_index, char* non_terminals, int* counters, char*** rules) {
	char c = non_terminals[nt_index];
	int count = counters[nt_index];

	for (int i = 0; i < count; i++) {
		if (strcmp(rules[nt_index][i], "e") == 0) return true;
	}
	return false;
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

	int* first_counters = (int*) malloc(sizeof(int) * (number_nt + 2));

	char** first = (char**) malloc(sizeof(char) * (number_nt + 2));

	fflush(stdin);
	fflush(stdout);

	// printf("%s\n", rules[0][0]);
	char *tmp = (char*) malloc(sizeof(char) * 20);
	strcpy(tmp, rules[0][0]);
	// printf("%s\n", tmp);
	strcpy(rules[0][0], tmp);

	// printf("%s\n", rules[0][0]);

	for (i = number_nt - 1; i >= 0; i--) {
		int count = counters[i];

		// printf("\nCalculating FIRST(%C)..\n", non_terminals[i]);

		first[i] = (char*) malloc(sizeof(char) * 10);
		first_counters[i] = 0;

		// printf("There are %d rule(s)!\n", count);

		// printf("-- %s --\n", rules[0][0]);

		fflush(stdin);
		fflush(stdout);

		for (j = 0; j < count; j++) {
			// printf("For the %d-th rule..\n", j);
			// printf("%s\n", rules[i][j]);
			char c = rules[i][j][0];
			// printf("c: %c\n", c);
			if (isTerminal(c, terminals, number_t)) {
				// printf("Got a T\n");
				first[i][first_counters[i]++] = c;
			} else if (isNonTerminal(c, non_terminals, number_nt)) {
				// printf("Got a NT\n");
				int index = findIndex(c, non_terminals, number_nt);
				int length = strlen(first[index]);
				for (int k = 0; k < length; k++) {
					first[i][first_counters[i]++] = first[index][k];
				}
			}
		}

		// printf("%c: %s\n", non_terminals[i], first[i]);
	}

	printf("\n");
	for (i = 0; i < number_nt; i++) {
		printf("FIRST(%c): ", non_terminals[i]);
		int length = strlen(first[i]);
		for (j = 0; j < length; j++) {
			printf("%c ", first[i][j]);
		}
		printf("\n");
	}

	fflush(stdin);
	fflush(stdout);

	int* follow_counters = (int*) malloc(sizeof(int) * (number_nt + 2));
	char** follow = (char**) malloc(sizeof(char) * (number_nt + 2));

	fflush(stdin);
	fflush(stdout);

	follow_counters[0] = 1;

	for (i = 0; i < number_nt; i++) {
		follow[i] = (char*) malloc(sizeof(char) * 20);
		for (j = 0; j < 20; j++) {
			follow[i][j] = '\0';
		}
	}

	follow[0][0] = '$';
	for (i = 1; i < 20; i++) {
		follow[0][i] = '\0';
	}

	for (i = 0; i < number_nt; i++) {
		follow[i] = (char*) malloc(sizeof(char) * 20);

		if (i == 0) {
			follow[0][0] = '$';
		}

		// printf("Calculating FOLLOW(%c)..", non_terminals[i]);

		for (j = 0; j < number_nt; j++) {
			if (i == j) continue;

			int count = counters[j];

			for (int k = 0; k < count; k++) {
				// printf("Checking rule #%d of %c..\n", k, non_terminals[j]);
				int length = strlen(rules[j][k]);
				int index = findIndex(non_terminals[i], rules[j][k], length);
				if (index >= 0) {
					// printf("Found in rule %s\n", rules[j][k]);
					if (index < (length - 1)) {
						char c = rules[j][k][index + 1];

						test:
						if (isTerminal(c, terminals, number_t)) {
							// printf("Is a T!\n");
							follow[i][follow_counters[i]++] = c;
						} else if (isNonTerminal(c, non_terminals, number_nt)) {
							// printf("Is a NT!\n");
							fflush(stdin);
							fflush(stdout);
							int first_index = findIndex(c, non_terminals, number_nt);
							int tmp_index = first_index;
							int first_length = strlen(first[first_index]);
							// printf("Will start copying..\n");
							for (int l = 0; l < first_length; l++) {
								char _c = first[first_index][l];
								// printf("%c\n", _c);
								if (_c == 'e' || findIndex(_c, follow[i], strlen(follow[i])) >= 0) continue;
								follow[i][follow_counters[i]++] = _c;
							}

							// If the non-terminal has e in its production rules, ..
							if (containsEpsilonInProduction(first_index, non_terminals, counters, rules)) {
								// printf("Contains epsilon!\n");
								// printf("%d\n", index);
								if ((index + 1) < length - 1) {
									// printf("Not last!\n");
									index++;
									c = rules[j][k][index + 1];
									goto test;
								} else { // was the last
									// printf("last..\n");
									goto test2;
								}
							}
						}

					} else { // If this is the last symbol
						test2:;

						// Everything in follow of non_terminals[j] is in follow of non_terminals[i]
						int flength = strlen(follow[j]);
						if (flength > 0) {
							for (int l = 0; l < flength; l++) {
								int x = findIndex(follow[j][l], follow[i], strlen(follow[i]));
								if (x == -1) {
									follow[i][follow_counters[i]++] = follow[j][l];
								}
							}
						}
					}
				}
				// printf("\n%c: %s\n", non_terminals[i], follow[i]);
			}
		}
	}

	printf("\n");
	for (i = 0; i < number_nt; i++) {
		printf("FOLLOW(%c): ", non_terminals[i]);
		int length = strlen(follow[i]);
		for (j = 0; j < length; j++) {
			printf("%c ", follow[i][j]);
		}
		printf("\n");
	}

	terminals[number_t++] = '$';

	fflush(stdin);
	fflush(stdout);

	char*** table = (char***) malloc(sizeof(char**) * (number_nt + 2));

	fflush(stdin);
	fflush(stdout);

	for (i = 0; i < number_nt; i++) {
		table[i] = (char**) malloc(sizeof(char*) * (number_t + 2));
		for (j = 0; j < number_t; j++) {
			table[i][j] = (char*) malloc(sizeof(char) * 20);
		}
	}

	for (i = 0; i < number_nt; i++) {
		int length = strlen(first[i]);
		for (j = 0; j < length; j++) {
			char c = first[i][j];
			if (c == 'e') {
				int follow_length = strlen(follow[i]);
				for (int k = 0; k < follow_length; k++) {
					char _c = follow[i][k];
					int _index = findIndex(_c, terminals, number_t);
					strcpy(table[i][_index], "e");
				}
			} else {
				int t_index = findIndex(c, terminals, number_t);
				char rule_index = 0;
				for (int k = 0; k < counters[i]; k++) {
					if (rules[i][k][0] == c) {
						rule_index = k;
					}
				}
				strcpy(table[i][t_index], rules[i][rule_index]);
			}
		}
	}

	printf("\n\n\t");
	for (i = 0; i < number_t; i++) {
		printf("%c\t", terminals[i]);
	}
	printf("\n--+---------------------------------------------------------------\n");

	for (i = 0; i < number_nt; i++) {
		printf("%c |\t", non_terminals[i]);
		for (j = 0; j < number_t; j++) {
			printf("%s\t", table[i][j]);
		}
		printf("\n");
	}

	printf("Start symbol: ");
	getchar();
	char start = getchar();

	printf("Start symbol is: %c\n", start);

	char* input = (char*) malloc(sizeof(char) * 30);

	printf("Input: ");
	scanf("%s", input);
	strcat(input, "$");
	printf("Input string is: %s\n", input);

	char* stack = (char*) malloc(sizeof(char) * (STACK_SIZE + 5));
	for (i = 0; i < STACK_SIZE; i++) {
		stack[i] = '\0';
	}

	int stack_top = -1;
	stack[++stack_top] = '$';
	stack[++stack_top] = 'A';

	int ip = 0;

	bool parsed = false;

	printf("\nstack\t\tinput\t\taction\n\n");
	printf("%s\t\t%s\n", stack, input);

	int tries = 0;
	while (tries < MAX_TRIES) {
		if (parsed) break;

		printf("%s\t\t", stack);
		for (i = ip; i < strlen(input); i++) {
			printf("%c", input[i]);
		}
		printf("\t\t");

		int ip_index = findIndex(input[ip], terminals, number_t);

		char* rule = (char*) malloc(sizeof(char) * 20);
		for (i = 0; i < 20; i++) {
			rule[i] = '\0';
		}

		if (isNonTerminal(stack[stack_top], non_terminals, number_nt)) {
			char top = stack[stack_top];
			
			int top_index = findIndex(top, non_terminals, number_nt);
			
			printf("%c -> %s\n", stack[stack_top], table[top_index][ip_index]);

			if (strcmp(table[top_index][ip_index], "e") != 0) {

				strcpy(rule, table[top_index][ip_index]);
				strrev(rule);

				stack[stack_top--] = '\0';
				for (i = 0; i < strlen(rule); i++) {
					stack[++stack_top] = rule[i];
				}
			} else {
				stack[stack_top--] = '\0';
			}

		} else {
			if (stack[stack_top] == input[ip]) {

				printf("matched %c\n", stack[stack_top]);

				if (stack[stack_top] == '$') {
					parsed = true;
				}

				stack[stack_top--] = '\0';
				ip++;
			}
		}

		tries++;
	}

	printf("\n");

	if (parsed) {
		printf("Parsing successful!\n");
	} else {
		printf("Parsing unsuccessful!\n");
	}

	return 0;
}