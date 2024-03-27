%{
#include <stdio.h>
#include <string.h>
%}

%%
"int"       { printf("INT "); }
"float"     { printf("FLOAT "); }
"char"      { printf("CHAR "); }
"if"        { printf("IF "); }
"else"      { printf("ELSE "); }
"while"     { printf("WHILE "); }
"for"       { printf("FOR "); }
"return"    { printf("RETURN "); }
[a-zA-Z]+   { printf("%s ", yytext); }
.           ;
%%

int main() {
    yylex();
    return 0;
}
