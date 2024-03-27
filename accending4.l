%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

[1-9][0-9]{3}   {
                    int num = atoi(yytext);
                    int first_digit = num / 1000 % 10;
                    int second_digit = num / 100 % 10;
                    int third_digit = num / 10 % 10;
                    int fourth_digit = num % 10;

                    if (first_digit < second_digit && second_digit < third_digit && third_digit < fourth_digit) {
                        printf("Ascending order number: %s\n", yytext);
                    }
                }

[\t\n\f\r ]     ; // Ignore whitespace characters
.               ;   // Ignore other characters

%%

int main() {
    printf("Enter text: ");
    yylex();
    return 0;
}
