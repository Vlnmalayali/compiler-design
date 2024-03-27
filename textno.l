%{
int word_count = 0;
%}

%%
[a-zA-Z]+   { word_count++; }
.           ;
%%

int main() {
    yylex();
    printf("Total number of words: %d\n", word_count);
    return 0;
}
