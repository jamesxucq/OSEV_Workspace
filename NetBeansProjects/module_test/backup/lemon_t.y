%include {
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "lemon_t.h"
}

%token_prefix TK_
%token_type { int }
%default_type {int}

%left PLUS MINUS.
%left DIVIDE TIMES.

%syntax_error {
  printf("Syntax error!\n");
  exit(1);
}

program ::= expr(A). { printf("Result = %d\n",A);}

expr(A) ::= expr(B) MINUS  expr(C). {A = B - C;}
expr(A) ::= expr(B) PLUS   expr(C). {A = B + C;}
expr(A) ::= expr(B) TIMES  expr(C). {A = B * C;}
expr(A) ::= expr(B) DIVIDE expr(C). {
  if(C != 0) {
    A = B / C;
  } else {
    printf("Divide by zero!\n");
  }
}

expr(A) ::= INTEGER(B). { A = B;}

%code {
    int main() {
      void* pParser = ParseAlloc(malloc);
      Parse(pParser, TK_INTEGER, 1);
      Parse(pParser, TK_PLUS   , 0);
      Parse(pParser, TK_INTEGER, 2);
      Parse(pParser, 0, 0);
      ParseFree(pParser, free);
    }
}