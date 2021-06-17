%{
#include <stdio.h>
#include "lemon_t.h"

int
yywrap(void)
{
    return 1;
}
%}

%%
"+"             return TK_PLUS;
"-"             return TK_MINUS;
"*"             return TK_TIMES;
"/"             return TK_DIVIDE;
// "\n"            return TK_CR;
([1-9][0-9]*)|0 {
    yylval.double_value = temp;
    return INTEGER;
}
[ \t] ;
. {
    fprintf(stderr, "lexical error.\n");
    exit(1);
}
%%