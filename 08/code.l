%{
	#include <stdio.h>
	int counter = 0;
%}

%%
"//"(.*) { printf("%s", yytext); counter++; }
"/*"(.*)(\n?)(.*)"*/" { printf("%s", yytext); counter++; }
. { }
%%

int yywrap () {
	return 1;
}

int main () {
	yyin = fopen("input.txt", "r");
	yylex();
	printf("Number of comments: %d\n", counter);
	return 0;
}