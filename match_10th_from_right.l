%{
#include <stdio.h>
%}

%%

[0-9]+ {
    // Check if the 10th symbol from the right end is 1
    int len = strlen(yytext);
    if (len >= 10 && yytext[len - 10] == '1') {
        printf("Matched: %s\n", yytext);
    }
}

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

