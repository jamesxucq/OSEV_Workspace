%{
#define YYSTYPE double
#include<stdio.h>
#include<math.h>
int yylex();
void yyerror(char *s);
%}

%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL
%token OP CP
%token POW SQRT

%%
calclist:
| calclist exp EOL { printf("= %f\n>>> ", $2); }
| calclist EOL { printf(">>> "); } /* blank line or a comment */
;

exp: factor { $$ = $1; }
| exp ADD factor { $$ = $1 + $3; }
| exp SUB factor { $$ = $1 - $3; }
;

factor: another_factor { $$ =$1; }
| factor MUL another_factor { $$ = $1 * $3; }
| factor DIV another_factor { $$ = $1 / $3; }
;

another_factor: term { $$ = $1; }
| SUB another_factor { $$ = -$2; }
| another_factor POW another_factor { $$ = pow($1,$3); }
;

term: NUMBER { $$ = $1; }
| ABS exp ABS { $$ = fabs($2); }
| OP exp CP { $$ = $2; }
| SQRT OP exp CP { $$ = sqrt($3); }
;
%%

int main(int argc, char **argv) {
    printf(">>> ");
    yyparse();
}

void yyerror(char *s) {
    fprintf(stderr,"error : %s\n",s);
}

作者：ManateeLazyCat
链接：https://www.jianshu.com/p/bad193f67a09
來源：简书
简书著作权归作者所有，任何形式的转载都请联系作者获得授权并注明出处。