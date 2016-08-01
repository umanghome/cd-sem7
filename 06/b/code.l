%{
	#include <stdio.h>
	int vowels = 0;
	int consontants = 0;
%}

%%
[aeiouAEIOU] { vowels++; }
[a-zA-Z] { consontants++; }
. {}
%%

int yywrap () {
	return 1;
}

int main () {
	yyin = fopen("input.txt", "r");
	yylex();
	printf("Vowels: %d\n", vowels);
	printf("Consontants: %d\n", consontants);
	return 0;
}