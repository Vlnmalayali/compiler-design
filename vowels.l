%{
int vowel_count = 0;
int consonant_count = 0;
%}

%%
[a-zA-Z]    {
                if (strchr("aeiouAEIOU", yytext[0]) != NULL)
                    vowel_count++;
                else
                    consonant_count++;
            }
.           ;
%%

int main() {
    yylex();
    printf("Number of vowels: %d\n", vowel_count);
    printf("Number of consonants: %d\n", consonant_count);
    return 0;
}
