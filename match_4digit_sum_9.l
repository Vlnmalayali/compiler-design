%{
#include <stdio.h>
%}

%%

[0-9]{4} {
    int sum = 0;
    for (int i = 0; yytext[i] != '\0'; i++) {
        sum += yytext[i] - '0'; // Convert char to int and add to sum
    }
    if (sum == 9) {
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

