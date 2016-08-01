%{
	#include <stdio.h>
	int counter = 1;
	FILE *out;
%}

%%
[^\n]* { fprintf(out, "%d. %s\n", counter, yytext); printf("%d. %s", counter++, yytext); }
%%

int yywrap () {
	return 1;
}

int main () {
	yyin = fopen("input.txt", "r");
	out = fopen("output.txt", "w");
	yylex();
	return 0;
}