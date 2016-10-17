#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CMDS 6
#define TYPE_VAR "v"
#define TYPE_NUM "n"
#define TYPE_ANY "a"

#define bool int
#define true 1
#define false 0

int getCommandCode (char* cmd);
char* command (char *str, FILE *output);
bool isVar (char c);
bool isNum (char c);
bool argTypeCorrect (char arg, char type);

char* COMMANDS[] = {"VAR", "STO", "PRI", "ADD", "SUB", "MUL"};
int ARG_MAP[] = {1, 2, 1, 2, 2, 2};
char* ARG_TYPE[] = {"v", "vn", "a", "va", "va", "va"};

int main (int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: /.compile filename\n");
		return 1;
	}

	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen("out.c", "w");

	fprintf(output, "#include <stdio.h>\n\nint main () {\n");

	char* line = NULL;
	size_t len_line = 0;
	char read;

	// Read input line by line
	while ((read = getline(&line, &len_line, input)) != -1) {
		char* args = command(line, output);
	}

	fprintf(output, "\nreturn 0;\n}");
	fclose(output);
	system("gcc out.c -o run");
	printf("Compiled successfully!\nTo run, execute ./run\n");

	return 0;
}

char* command (char *str, FILE *output) {
	char* cmd = (char*) malloc(sizeof(char) * 4);
	for (int i = 0; i < 3; i++) {
		cmd[i] = str[i];
	}
	cmd[3] = '\0';
	int code = getCommandCode(cmd);
	int arg_len = ARG_MAP[code];

	int spaces = 0;
	for (int i = 3; i < strlen(str); i++) {
		if (str[i] == ' ') spaces++;
	}

	// Error handling
	if (spaces != arg_len) {
		printf("\nFound error on line: %s\n", str);
		printf("There should be %d args, but there are %d.\n", arg_len, spaces);
		exit(2);
	}

	// Check for valid argument types
	for (int i = 0; i < arg_len; i++) {
		if (!argTypeCorrect(str[4 + (i * 2)], ARG_TYPE[code][i])) {
			printf("\nFound error on line: %s\n", str);
			printf("Argument #%d (%c) does not have proper type. Should be %c.\n", (i + 1), str[4 + (i * 2)], ARG_TYPE[code][i]);
			exit(2);
		}
	}

	switch (code) {
		// VAr
		case 0:	
			fprintf(output, "int %c;\n", str[4]);
			break;
		// STO
		case 1:	
			fprintf(output, "%c = %c;\n", str[4], str[6]);
			break;
		// PRI
		case 2:	
			fprintf(output, "printf(\"%%d\\n\", %c);\n", str[4]);
			break;
		// ADD
		case 3:
			fprintf(output, "%c = %c + %c;\n", str[4], str[4], str[6]);
			break;
		// SUB
		case 4:	
			fprintf(output, "%c = %c - %c;\n", str[4], str[4], str[6]);
			break;
		// MUL
		case 5:	
			fprintf(output, "%c = %c * %c;\n", str[4], str[4], str[6]);
			break;
		default: break;
	}

	return NULL;
}

int getCommandCode (char* cmd) {
	for (int i = 0; i < NUM_CMDS; i++) {
		if (strcmp(COMMANDS[i], cmd) == 0) {
			return i;
		}
	}
	return -1;
}

bool isVar (char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return true;
	return false;
}

bool isNum (char c) {
	if (c >= '0' && c <= '9') return true;
	return false;
}

bool argTypeCorrect (char arg, char type) {
	if (type == 'v') {
		return isVar(arg);
	} else if (type == 'n') {
		return isNum(arg);
	} else {
		return (isVar(arg) || isNum(arg));
	}
}