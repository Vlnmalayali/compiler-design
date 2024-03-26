%{
#include <stdio.h>
%}

%%

[0-9]*11 { printf("Matched: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

