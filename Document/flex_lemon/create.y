// All token codes are small integers with #defines that begin with "TK_"
%token_prefix TK_

// The type of the data attached to each token is Token.  This is also the
// default type for non-terminals.
// me:struct Token defined in sqliteInt.h
%token_type {Token}
%default_type {Token}

// The generated parser function takes a 4th argument as follows:
%extra_argument {Parse *pParse}

// This code runs whenever there is a syntax error
//
%syntax_error {
  //UNUSED_PARAMETER(yymajor);  /* Silence some compiler warnings */
  assert( TOKEN.z[0] );  /* The tokenizer always gives us a token */
  //sqlite3ErrorMsg(pParse, "near \"%T\": syntax error", &TOKEN);
  printf("near \"%T\": syntax error", &TOKEN);
}

// The name of the generated procedure that implements the parser
// is as follows:
%name titaParser

// The following text is included near the beginning of the C source
// code file that implements the parser.
//
%include {
#include "Tita.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
} // end %include

cmdx ::= cmd.           { sqlite3FinishCoding(pParse); }

///////////////////// The CREATE TABLE statement ////////////////////////////
//nm(Y)    table name
//dbnm(Z)  database name
cmd ::= create_table create_table_args SEMI.
create_table ::= createkw TABLE ifnotexists(E) nm(Y) dbnm(Z). {
   titaStartTable(pParse,&Y,&Z,E);
}

createkw(A) ::= CREATE(A).  {disableLookaside(pParse);}

//define the data type of ifnotexists that is non terminate symbol is int.
%type ifnotexists {int}
//if hasn't ifnotexists statemnet, set ifnotexists's value is 0.
ifnotexists(A) ::= .              {A = 0;}
ifnotexists(A) ::= IF NOT EXISTS. {A = 1;}

create_table_args ::= LP columnlist RP(E). {
  //sqlite3EndTable(pParse,&X,&E,F,0);
  titaEndTable(pParse,0,&E);
}

// An IDENTIFIER can be a generic identifier, or one of several
// keywords.  Any non-standard keyword can also be an identifier.
//
%token_class id  ID|INDEXED.

// The following directive causes tokens ABORT, AFTER, ASC, etc. to
// fallback to ID if they will not parse as their original value.
// This obviates the need for the "id" nonterminal.
//
%fallback ID
  ABORT ACTION AFTER ANALYZE ASC ATTACH BEFORE BEGIN BY CASCADE CAST COLUMNKW
  CONFLICT DATABASE DEFERRED DESC DETACH EACH END EXCLUSIVE EXPLAIN FAIL FOR
  IGNORE IMMEDIATE INITIALLY INSTEAD LIKE_KW MATCH NO PLAN
  QUERY KEY OF OFFSET PRAGMA RAISE RECURSIVE RELEASE REPLACE RESTRICT ROW
  ROLLBACK SAVEPOINT TEMP TRIGGER VACUUM VIEW VIRTUAL WITH WITHOUT
  .

// The name of a column or table can be any of the following:
//
%type nm {Token}
nm(A) ::= id(A).
nm(A) ::= STRING(A).

//dbnm(A) ::= .  ? can be empty
%type dbnm {Token}
dbnm(A) ::= .          {A.z=0; A.n=0;}
dbnm(A) ::= DOT nm(X). {A = X;}

//typetoken(Y):column type
columnlist ::= columnlist COMMA columnname.
columnlist ::= columnname.
//me:void sqlite3AddColumn(Parse *pParse, Token *pName, Token *pType)
columnname(A) ::= nm(A) typetoken(Y). {titaAddColumn(pParse,&A,&Y);}

// And "ids" is an identifer-or-string.
//
%token_class ids  ID|STRING.

%type typetoken {Token}
typetoken(A) ::= .   {A.n = 0; A.z = 0;}
typetoken(A) ::= typename(A).

%type typename {Token}
typename(A) ::= ids(A).
typename(A) ::= typename(A) ids(Y). {A.n=Y.n+(int)(Y.z-A.z);}
