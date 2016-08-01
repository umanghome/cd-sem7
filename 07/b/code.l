%%
"<"[^>]*> { printf("%s", yytext); }
. {}
%%

int yywrap () {
	return 1;
}

int main () {
	yyin = fopen("input.txt", "r");
	yylex();
	return 0;
}