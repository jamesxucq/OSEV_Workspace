
//
%token_prefix TK_

//
%token_type {Token}
%default_type {Token}

//
%syntax_error {
  UNUSED_PARAMETER(yymajor);  /* Silence some compiler warnings */
  if( TOKEN.z[0] ){
    sqlite3ErrorMsg(pParse, "near \"%T\": syntax error", &TOKEN);
  }else{
    sqlite3ErrorMsg(pParse, "incomplete input");
  }
}
%stack_overflow {
  sqlite3ErrorMsg(pParse, "parser stack overflow");
}

//
%name sqlite3Parser

//
%include {
#include "sqliteInt.h"

} // end %include

//
%token OR AND NOT BETWEEN IN NE EQ.
%token GT LE LT GE.

//
%left OR.
%left AND.
%right NOT.
%left BETWEEN IN NE EQ.
%left GT LE LT GE.
%left LSHIFT RSHIFT.

//
%token_class id  ID|INDEXED.

// Expression Processing

//
%type nm {Token}
nm(A) ::= id(A).
nm(A) ::= STRING(A).

//
%type expr {Expr*}
%destructor expr {sqlite3ExprDelete(pParse->db, $$);}
%type term {Expr*}
%destructor term {sqlite3ExprDelete(pParse->db, $$);}

//
expr(A) ::= term(A).
expr(A) ::= LP expr(X) RP. {A = X;}
expr(A) ::= expr(A) AND(OP) expr(Y).    {A=sqlite3PExpr(pParse,@OP,A,Y);}
expr(A) ::= expr(A) OR(OP) expr(Y).     {A=sqlite3PExpr(pParse,@OP,A,Y);}
expr(A) ::= expr(A) LT|GT|GE|LE(OP) expr(Y).
                                        {A=sqlite3PExpr(pParse,@OP,A,Y);}
expr(A) ::= expr(A) EQ|NE(OP) expr(Y).  {A=sqlite3PExpr(pParse,@OP,A,Y);}
expr(A) ::= expr(A) LSHIFT|RSHIFT(OP) expr(Y).
                                        {A=sqlite3PExpr(pParse,@OP,A,Y);}
expr(A) ::= NOT(B) expr(X).  
              {A = sqlite3PExpr(pParse, @B, X, 0);/*A-overwrites-B*/}

%type between_op {int}
between_op(A) ::= BETWEEN.     {A = 0;}
between_op(A) ::= NOT BETWEEN. {A = 1;}
expr(A) ::= expr(A) between_op(N) expr(X) AND expr(Y). [BETWEEN] {
  ExprList *pList = sqlite3ExprListAppend(pParse,0, X);
  pList = sqlite3ExprListAppend(pParse,pList, Y);
  A = sqlite3PExpr(pParse, TK_BETWEEN, A, 0);
  if( A ){
    A->x.pList = pList;
  }else{
    sqlite3ExprListDelete(pParse->db, pList);
  } 
  if( N ) A = sqlite3PExpr(pParse, TK_NOT, A, 0);
}

//
  %type in_op {int}
  in_op(A) ::= IN.      {A = 0;}
  in_op(A) ::= NOT IN.  {A = 1;}
  expr(A) ::= expr(A) in_op(N) LP exprlist(Y) RP. [IN] {
    if( Y==0 ){
      /* Expressions of the form
      **
      **      expr1 IN ()
      **      expr1 NOT IN ()
      **
      ** simplify to constants 0 (false) and 1 (true), respectively,
      ** regardless of the value of expr1.
      */
      sqlite3ExprDelete(pParse->db, A);
      A = sqlite3ExprAlloc(pParse->db, TK_INTEGER,&sqlite3IntTokens[N],1);
    }else if( Y->nExpr==1 ){
      /* Expressions of the form:
      **
      **      expr1 IN (?1)
      **      expr1 NOT IN (?2)
      **
      ** with exactly one value on the RHS can be simplified to something
      ** like this:
      **
      **      expr1 == ?1
      **      expr1 <> ?2
      **
      ** But, the RHS of the == or <> is marked with the EP_Generic flag
      ** so that it may not contribute to the computation of comparison
      ** affinity or the collating sequence to use for comparison.  Otherwise,
      ** the semantics would be subtly different from IN or NOT IN.
      */
      Expr *pRHS = Y->a[0].pExpr;
      Y->a[0].pExpr = 0;
      sqlite3ExprListDelete(pParse->db, Y);
      /* pRHS cannot be NULL because a malloc error would have been detected
      ** before now and control would have never reached this point */
      if( ALWAYS(pRHS) ){
        pRHS->flags &= ~EP_Collate;
        pRHS->flags |= EP_Generic;
      }
      A = sqlite3PExpr(pParse, N ? TK_NE : TK_EQ, A, pRHS);
    }else{
      A = sqlite3PExpr(pParse, TK_IN, A, 0);
      if( A ){
        A->x.pList = Y;
        sqlite3ExprSetHeightAndFlags(pParse, A);
      }else{
        sqlite3ExprListDelete(pParse->db, Y);
      }
      if( N ) A = sqlite3PExpr(pParse, TK_NOT, A, 0);
    }
  }

//
term(A) ::= NULL|FLOAT|BLOB(X). {A=tokenExpr(pParse,@X,X); /*A-overwrites-X*/}
term(A) ::= STRING(X).          {A=tokenExpr(pParse,@X,X); /*A-overwrites-X*/}
term(A) ::= INTEGER(X). {
  A = sqlite3ExprAlloc(pParse->db, TK_INTEGER, &X, 1);
}