%include {
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "lexical.h"
}

//
%include {
#define MAX_TOKE_SIZE 512

    //

    typedef enum {
        ALPHA_TERM,
        TEXT_TERM,
        LOLO_NUMB_TERM,
        DOUB_NUMB_TERM,
    } termin;


    //

    typedef struct leaf_node_t {
        termin term_type;
        long long lolo_valu;
        double doub_valu;
        char stri[MAX_TOKE_SIZE];
    } leaf_node;

    typedef struct leaf_list_t {
        struct leaf_list_t *next;
        leaf_node *opno;
    } leaf_list;
    
    
    //
    typedef struct oper_node_t {
        int node_type;

        union {
            struct oper_node_t *oper_leno;
            leaf_node *leaf_term;
            leaf_list *leaf_item;
        };
        struct oper_node_t *oper_rino;
        void *list_next;
    } oper_node;

    //
    oper_node *new_leaf_node(oper_node *popern, leaf_node *B, int c) {
	printf("in new_leaf_node\n");
    	return NULL;
    }
}


//
%extra_argument {oper_node *onode}

//
%token_prefix TK_
%token_type { leaf_node *}
%default_type {oper_node *}

%left PLUS MINUS.
%left DIVIDE TIMES.

%syntax_error {
  printf("Syntax error!\n");
  exit(1);
}

program ::= expr(A). { printf("Result = %d\n",99999);}

/*
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
*/

expr(A) ::= INTEGER(B). { A = new_leaf_node(onode, B, @B);}

%code {
    int main() {
    oper_node operno;
    leaf_node opno;
      void* pParser = ParseAlloc(malloc);
      Parse(pParser, TK_INTEGER, &opno, &operno);
      Parse(pParser, TK_PLUS, &opno, &operno);
      Parse(pParser, TK_INTEGER, &opno, &operno);
      Parse(pParser, 0, 0, NULL);
      ParseFree(pParser, free);
    }
}