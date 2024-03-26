%{
#include <stdio.h>
int match_found = 0; // Global variable to track if a match was found
int match_count = 0; // Counter for the number of matches found
%}

%%

222 { 
    printf("Matched: %s\n", yytext); 
    match_found = 1; 
    match_count++; // Increment the counter each time a match is found
}

%%

int main() {
    yylex();
    if (!match_found) {
        printf("String not found.\n");
    } else {
	printf("-----------------------------------------------");
        printf("\nNumber of matches found: %d\n", match_count);
	printf("-----------------------------------------------\n");
    }
    return 0;
}

int yywrap() {
    return 1;
}

