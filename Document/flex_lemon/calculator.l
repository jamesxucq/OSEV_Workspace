%{
#define YYSTYPE double
#include "calculator.tab.h"
#include <stdlib.h>
YYSTYPE yylval;
%}

%%
"+"                             { return ADD; }
"-"                             { return SUB; }
"*"                             { return MUL; }
"/"                             { return DIV; }
"|"                             { return ABS; }
"("                             { return OP; }
")"                             { return CP; }
([0-9]*\.?[0-9]+|[0-9]+\.)      { yylval = atof(yytext); return NUMBER;}
"sqrt"                          { return SQRT; }
"**"                            { return POW; }
\n                              { return EOL; }
[ \t]                           {}
"//".*                          {}
%%

作者：ManateeLazyCat
链接：https://www.jianshu.com/p/bad193f67a09
來源：简书
简书著作权归作者所有，任何形式的转载都请联系作者获得授权并注明出处。