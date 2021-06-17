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

���ߣ�ManateeLazyCat
���ӣ�https://www.jianshu.com/p/bad193f67a09
��Դ������
��������Ȩ���������У��κ���ʽ��ת�ض�����ϵ���߻����Ȩ��ע��������