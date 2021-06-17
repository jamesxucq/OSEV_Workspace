
//
//
%token_prefix TK_

//
%token_type {leaf_node *}
%default_type {oper_node *}

//
// %extra_context {Parse *state}
%extra_argument {pastat *state}

//
%syntax_error {
  // UNUSED_PARAMETER(yymajor);  /* Silence some compiler warnings */
  strcpy(state->erro_msg, "syntax error near.\n");
}
%stack_overflow {
  strcpy(state->erro_msg, "parser stack overflow.\n");
}

%parse_accept {
  state->accept = PARSE_SUCCESS;
  strcpy(state->erro_msg, "parsing complete!\n");
}

%parse_failure {
  state->accept = PARSE_FAULT;
  strcpy(state->erro_msg, "Giving up.  Parser is hopelessly lost...\n");
}

//
%name ExpreParse

//
%include {
#include "valtok.h"
#include "synta_tree.h"
#include "gramm_analy.h"

//
#define YYNOERRORRECOVERY 1

} // end %include

//
%token OR AND NOT IS MATCH LIKE_KW BETWEEN IN NE EQ.
%token GT LE LT GE ESCAPE.
%token LP RP.
%token PLUS MINUS.

//
%fallback ID LIKE_KW MATCH CTIME_KW.

//
%left OR.
%left AND.
%right NOT.
%left IS MATCH LIKE_KW BETWEEN IN ISNULL NOTNULL NE EQ.
%left GT LE LT GE.
%right ESCAPE.
%left BITAND BITOR LSHIFT RSHIFT.
%left PLUS MINUS.
%left STAR SLASH REM.
%left CONCAT.
%left COLLATE.
%right BITNOT.
%nonassoc ON.

//
%token_class ids  ID|STRING.

/////////////////////////// Expression Processing /////////////////////////////
//

%type expr {oper_node *}
// %destructor expr {OPER_NODE_DELE($$);}
%type term {leaf_node *}
// %destructor term {LEAF_NODE_DELE($$);}

//
expres ::= expr.
expr(A) ::= term(X). {A = new_oper_leaf(TERM_TOKE, X);}
expr(A) ::= LP expr(X) RP. {A = X;}
//
term(A) ::= NULL|FLOAT(X). {A = new_leaf_vato(X);}
term(A) ::= BLOB(X). {A = new_leaf_vato(X);}
term(A) ::= STRING(X). {A = new_leaf_vato(X);}
term(A) ::= INTEGER(X). {A = new_leaf_vato(X);}
term(A) ::= VARIABLE(X). {A = new_leaf_vato(X);}
term(A) ::= ID(X). {A = new_leaf_vato(X);}
term(A) ::= JOIN_KW(X). {A = new_leaf_vato(X);}

//
expr(A) ::= expr(A) COLLATE ids(C). {A = expr_add_collate(state, TK_COLLATE, C, NULL);}
expr(A) ::= ID(X) LP distinct(D) exprlist(Y) RP. { /* A = expr_function(state, TK_DISTINCT, X, D); */}
expr(A) ::= ID(X) LP STAR RP. {/* A = expr_function(state, TK_STAR, X, X); */}

//
term(A) ::= CTIME_KW(OP). {A = new_leaf_vato(OP);}

//
expr(A) ::= LP nexprlist(X) COMMA expr(Y) RP. {
/*
  oper_list *plist = new_oper_list(state, X, Y);
  A = oper_node(state, TK_VECTOR, 0, 0);
  if(A){
    A->list_next = plist;
  }else{
    oper_list_dele(state, pList);
  }
*/
}

//
expr(A) ::= expr(X) AND(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) OR(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) LT|GT|GE|LE(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) EQ|NE(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) BITAND|BITOR|LSHIFT|RSHIFT(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) PLUS|MINUS(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) STAR|SLASH|REM(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}
expr(A) ::= expr(X) CONCAT(OP) expr(Y). {A = new_oper_node(state, @OP, X, Y);}

//
%type likeop {leaf_node *}
likeop(A) ::= LIKE_KW|MATCH(X). {A = X;}
likeop(A) ::= NOT LIKE_KW|MATCH(X). {A = X;}
expr(A) ::= expr(A) likeop(OP) expr(Y).  [LIKE_KW] {
/*
  oper_list *plist;
  pList = new_oper_list(state,0, Y);
  pList = new_oper_list(state,pList, A);
*/
  A = expr_function(state, @OP, OP, OP);
}
expr(A) ::= expr(A) likeop(OP) expr(Y) ESCAPE expr(E).  [LIKE_KW] {
/*
  oper_list *plist;
  plist = new_oper_list(state,0, Y);
  plist = new_oper_list(state,plist, A);
  plist = new_oper_list(state,plist, E);
*/
  A = expr_function(state, @OP, OP, OP);
}

expr(A) ::= expr(A) ISNULL|NOTNULL(E). {A = new_oper_node(state,@E,A,0);}
expr(A) ::= expr(A) NOT NULL. {A = new_oper_node(state,TK_NOTNULL,A,0);}

// 
expr(A) ::= expr(A) IS expr(Y). {
  A = new_oper_node(state,TK_IS,A,Y);
  binary_unary_null(state, Y, A, TK_ISNULL);
}
expr(A) ::= expr(A) IS NOT expr(Y). {
  A = new_oper_node(state,TK_IS,A,Y);
  binary_unary_null(state, Y, A, TK_NOTNULL);
}

//
expr(A) ::= NOT(B) expr(X). {A = new_oper_node(state, @B, X, 0);}
expr(A) ::= BITNOT(B) expr(X). {A = new_oper_node(state, @B, X, 0);}
expr(A) ::= PLUS|MINUS(B) expr(X). [BITNOT] {A = new_oper_node(state, @B==TK_PLUS ? TK_PLUS : TK_MINUS, X, 0);}

//
%type between_op {int}
between_op(A) ::= BETWEEN. {A = 0;}
between_op(A) ::= NOT BETWEEN. {A = 1;}
expr(A) ::= expr(A) between_op(N) expr(X) AND expr(Y). [BETWEEN] {
/*
  oper_list *olist = new_oper_list(0, X);
  olist = new_oper_list(olist, Y);
  A = new_oper_node(state, TK_BETWEEN, A, 0);
  if( A ) A->list_next = olist;
  else oper_list_dele(olist); 
  if( N ) A = new_oper_node(state, TK_NOT, A, 0);
*/
}

//
%type in_op {int}
in_op(A) ::= IN. {A = 0;}
in_op(A) ::= NOT IN. {A = 1;}
expr(A) ::= expr(A) in_op(N) LP exprlist(Y) RP. [IN] {
    if (Y == 0) {
        OPER_NODE_DELE(A);
        A = new_oper_leaf(TK_INTEGER, 0x00);
    } else {
        A = new_oper_node(state, TK_IN, A, 0);
        if (A) {
          A->list_next = Y;
        } else {
          // oper_list_dele(state, Y);
        }
        if (N) A = new_oper_node(state, TK_NOT, A, 0);
    }
}

//
%type exprlist {oper_list *}
// %destructor exprlist {oper_list_dele(state, $$);}
%type nexprlist {oper_list *}
// %destructor nexprlist {oper_list_dele(state, $$);}

exprlist(A) ::= nexprlist(A).
exprlist(A) ::= . {A = 0;}
nexprlist(A) ::= nexprlist(A) COMMA expr(Y).
    {/* A = new_oper_list(state,A,Y); */}
nexprlist(A) ::= expr(Y).
    {/* A = new_oper_list(state,0,Y); */}

//
%type distinct {int}
// distinct(A) ::= DISTINCT. {A = SF_Distinct;}
// distinct(A) ::= ALL. {A = SF_All;}
distinct(A) ::= . {A = 0;}