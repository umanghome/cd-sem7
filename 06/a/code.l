%{
	#include <stdio.h>
	int words = 1;
	int lines = 1;
	int characters = 0;
%}

%%
[ ] { words++; }
[\n] { lines++; words++; }
. { characters++; }
%%

int yywrap () {
	return 1;
}

int main () {
	yyin = fopen("input.txt", "r");
	yylex();
	printf("Words: %d\n", words);
	printf("Lines: %d\n", lines);
	printf("Characters: %d\n", characters);
	return 0;
}