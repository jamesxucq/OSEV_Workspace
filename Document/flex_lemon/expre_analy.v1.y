
//
%token_prefix TK_

//
%token_type {leaf_node}
%default_type {leaf_node}

//
%extra_argument {pastat *state}

//
%syntax_error {
  UNUSED_PARAMETER(yymajor);  /* Silence some compiler warnings */
  if( TOKEN.stri[0] ){
    strcpy(state.erro_msg, "syntax error near.\n");
  }else{
    strcpy(state.erro_msg, "incomplete input.\n");
  }
}
%stack_overflow {
  strcpy(state.erro_msg, "parser stack overflow.\n");
}

//
%name expre_parse

//
%include {
#include "valtok.h"
#include "synta_tree.h"
#include "gramm_analy.h"

} // end %include

//
%token OR AND NOT BETWEEN IN NE EQ.
%token GT LE LT GE.
%token LP RP.
%token PLUS MINUS.

//
%left OR.
%left AND.
%right NOT.
%left BETWEEN IN NE EQ.
%left GT LE LT GE.
%left LP RP.
%left PLUS MINUS.
%left STAR SLASH REM.

//
%token_class id  ID|INDEXED.
%token_class ids  ID|STRING.

//// Expression Processing

%type expr {oper_node *}
%destructor expr {OPER_NODE_DELE($$);}
%type term {oper_node *}
%destructor term {OPER_NODE_DELE($$);}

//
expr_line ::= expr.
expr(A) ::= term(A).
expr(A) ::= LP expr(X) RP. {A = X;}
expr(A) ::= id(X).          {A=tokenExpr(pParse,TK_ID,X);}
// expr(A) ::= JOIN_KW(X).     {A=tokenExpr(pParse,TK_ID,X);}
expr(A) ::= nm(X) DOT nm(Y). {
  Expr *temp1 = sqlite3ExprAlloc(pParse->db, TK_ID, &X, 1);
  Expr *temp2 = sqlite3ExprAlloc(pParse->db, TK_ID, &Y, 1);
  if( IN_RENAME_OBJECT ){
    sqlite3RenameTokenMap(pParse, (void*)temp2, &Y);
    sqlite3RenameTokenMap(pParse, (void*)temp1, &X);
  }
  A = sqlite3PExpr(pParse, TK_DOT, temp1, temp2);
}
expr(A) ::= nm(X) DOT nm(Y) DOT nm(Z). {
  Expr *temp1 = sqlite3ExprAlloc(pParse->db, TK_ID, &X, 1);
  Expr *temp2 = sqlite3ExprAlloc(pParse->db, TK_ID, &Y, 1);
  Expr *temp3 = sqlite3ExprAlloc(pParse->db, TK_ID, &Z, 1);
  Expr *temp4 = sqlite3PExpr(pParse, TK_DOT, temp2, temp3);
  if( IN_RENAME_OBJECT ){
    sqlite3RenameTokenMap(pParse, (void*)temp3, &Z);
    sqlite3RenameTokenMap(pParse, (void*)temp2, &Y);
  }
  A = sqlite3PExpr(pParse, TK_DOT, temp1, temp4);
}

//
term(A) ::= NULL|FLOAT|BLOB(X).     {A = new_oper_leaf(@X, X);}
term(A) ::= STRING(X).          {A = new_oper_leaf(@X, X);}
term(A) ::= INTEGER(X).     {A = new_oper_leaf(TK_INTEGER, &X); }

//
expr(A) ::= VARIABLE(X).     {
  if( !(X.z[0]=='#' && sqlite3Isdigit(X.z[1])) ){
    u32 n = X.n;
    A = tokenExpr(pParse, TK_VARIABLE, X);
    sqlite3ExprAssignVarNumber(pParse, A, n);
  }else{
    /* When doing a nested parse, one can include terms in an expression
    ** that look like this:   #1 #2 ...  These terms refer to registers
    ** in the virtual machine.  #N is the N-th register. */
    Token t = X;
    assert( t.n>=2 );
    if( pParse->nested==0 ){
      sqlite3ErrorMsg(pParse, "near \"%T\": syntax error", &t);
      A = 0;
    }else{
      A = sqlite3PExpr(pParse, TK_REGISTER, 0, 0);
      if( A ) sqlite3GetInt32(&t.z[1], &A->iTable);
    }
  }
}

expr(A) ::= expr(A) COLLATE ids(C). {
  A = sqlite3ExprAddCollateToken(pParse, A, &C, 1);
}

expr(A) ::= id(X) LP distinct(D) exprlist(Y) RP. {
  A = sqlite3ExprFunction(pParse, Y, &X, D);
}
expr(A) ::= id(X) LP STAR RP. {
  A = sqlite3ExprFunction(pParse, 0, &X, 0);
}

expr(A) ::= LP nexprlist(X) COMMA expr(Y) RP. {
  ExprList *pList = sqlite3ExprListAppend(pParse, X, Y);
  A = sqlite3PExpr(pParse, TK_VECTOR, 0, 0);
  if( A ){
    A->x.pList = pList;
  }else{
    sqlite3ExprListDelete(pParse->db, pList);
  }
}

expr(A) ::= LP nexprlist(X) COMMA expr(Y) RP. {
  ExprList *pList = sqlite3ExprListAppend(pParse, X, Y);
  A = sqlite3PExpr(pParse, TK_VECTOR, 0, 0);
  if( A ){
    A->x.pList = pList;
  }else{
    sqlite3ExprListDelete(pParse->db, pList);
  }
}

//
expr(A) ::= expr(A) AND(OP) expr(Y).    {A = new_oper_node(state, @OP, A, Y);}
expr(A) ::= expr(A) OR(OP) expr(Y).     {A = new_oper_node(state, @OP, A, Y);}
expr(A) ::= expr(A) LT|GT|GE|LE(OP) expr(Y).        {A = new_oper_node(state, @OP, A, Y);}
expr(A) ::= expr(A) EQ|NE(OP) expr(Y).      {A = new_oper_node(state, @OP, A, Y);}
// expr(A) ::= expr(A) LSHIFT|RSHIFT(OP) expr(Y).      {A = new_oper_node(state, @OP, A, Y);}
expr(A) ::= expr(A) PLUS|MINUS(OP) expr(Y).     {A=sqlite3PExpr(pParse,@OP,A,Y);}
expr(A) ::= expr(A) STAR|SLASH|REM(OP) expr(Y). {A=sqlite3PExpr(pParse,@OP,A,Y);}
expr(A) ::= NOT(B) expr(X).     {A = new_oper_node(state, @B, X, 0);/*A-overwrites-B*/}
expr(A) ::= PLUS|MINUS(B) expr(X). [BITNOT] {
  A = sqlite3PExpr(pParse, @B==TK_PLUS ? TK_UPLUS : TK_UMINUS, X, 0);
  /*A-overwrites-B*/
}

//
%type between_op {int}
between_op(A) ::= BETWEEN.     {A = 0;}
between_op(A) ::= NOT BETWEEN.      {A = 1;}
expr(A) ::= expr(A) between_op(N) expr(X) AND expr(Y). [BETWEEN] {
  oper_list *olist = new_oper_list(0, X);
  olist = new_oper_list(olist, Y);
  A = new_oper_node(state, TK_BETWEEN, A, 0);
  if( A ) A->list_next = olist;
  else oper_list_dele(olist); 
  if( N ) A = new_oper_node(state, TK_NOT, A, 0);
}

//
%type in_op {int}
in_op(A) ::= IN.      {A = 0;}
in_op(A) ::= NOT IN.  {A = 1;}
expr(A) ::= expr(A) in_op(N) LP exprlist(Y) RP. [IN] {
    if( Y == 0 ){
        OPER_NODE_DELE(state, A);
        A = new_oper_leaf(TK_INTEGER, 0x00);
    }else{
        A = new_oper_node(state, TK_IN, A, 0);
        if( A ){
          A->list_next = Y;
        }else{
          oper_list_dele(state, Y);
        }
        if( N ) A = new_oper_node(state, TK_NOT, A, 0);
    }
}

//
%type exprlist {oper_list *}
%destructor exprlist {oper_list_dele(state, $$);}
%type nexprlist {oper_list *}
%destructor nexprlist {oper_list_dele(state, $$);}

exprlist(A) ::= nexprlist(A).
exprlist(A) ::= .    {A = 0;}
nexprlist(A) ::= nexprlist(A) COMMA expr(Y).    {A = new_oper_list(A, Y);}
nexprlist(A) ::= expr(Y).    {A = new_oper_list(0, Y); /*A-overwrites-Y*/}

//
%type nm {leaf_node}
nm(A) ::= id(A).
nm(A) ::= STRING(A).