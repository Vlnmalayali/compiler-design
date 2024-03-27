%{
#include <stdio.h>
#include <string.h>

int identifier_count = 0;
int keyword_count = 0;
int digit_count = 0;

%}

%%
"int"       { keyword_count++; }
"float"     { keyword_count++; }
"char"      { keyword_count++; }
"if"        { keyword_count++; }
"else"      { keyword_count++; }
"while"     { keyword_count++; }
"for"       { keyword_count++; }
"return"    { keyword_count++; }

[a-zA-Z_][a-zA-Z0-9_]*   { identifier_count++; }
[0-9]+                    { digit_count++; }
.                         ;

%%

int main() {
    yylex();
    printf("Number of identifiers: %d\n", identifier_count);
    printf("Number of keywords: %d\n", keyword_count);
    printf("Number of digits: %d\n", digit_count);
    return 0;
}
