/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
#include <assert.h>
/************ Begin %include sections from the grammar ************************/
#line 37 "expre_analy.y"

#include "valtok.h"
#include "synta_tree.h"
#include "gramm_analy.h"

//
#define YYNOERRORRECOVERY 1

#line 38 "expre_analy.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ExpreParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ExpreParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ExpreParseARG_SDECL     A static variable declaration for the %extra_argument
**    ExpreParseARG_PDECL     A parameter declaration for the %extra_argument
**    ExpreParseARG_PARAM     Code to pass %extra_argument as a subroutine parameter
**    ExpreParseARG_STORE     Code to store %extra_argument into yypParser
**    ExpreParseARG_FETCH     Code to extract %extra_argument from yypParser
**    ExpreParseCTX_*         As ExpreParseARG_ except for %extra_context
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYNTOKEN           Number of terminal symbols
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
**    YY_MIN_REDUCE      Minimum value for reduce actions
**    YY_MAX_REDUCE      Maximum value for reduce actions
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 52
#define YYACTIONTYPE unsigned char
#define ExpreParseTOKENTYPE leaf_node *
typedef union {
  int yyinit;
  ExpreParseTOKENTYPE yy0;
  int yy20;
  oper_list * yy72;
  oper_node * yy78;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ExpreParseARG_SDECL pastat *state;
#define ExpreParseARG_PDECL ,pastat *state
#define ExpreParseARG_PARAM ,state
#define ExpreParseARG_FETCH pastat *state=yypParser->state;
#define ExpreParseARG_STORE yypParser->state=state;
#define ExpreParseCTX_SDECL
#define ExpreParseCTX_PDECL
#define ExpreParseCTX_PARAM
#define ExpreParseCTX_FETCH
#define ExpreParseCTX_STORE
#define YYFALLBACK 1
#define YYNSTATE             55
#define YYNRULE              45
#define YYNTOKEN             43
#define YY_MAX_SHIFT         54
#define YY_MIN_SHIFTREDUCE   77
#define YY_MAX_SHIFTREDUCE   121
#define YY_ERROR_ACTION      122
#define YY_ACCEPT_ACTION     123
#define YY_NO_ACTION         124
#define YY_MIN_REDUCE        125
#define YY_MAX_REDUCE        169
/************* End control #defines *******************************************/
#define YY_NLOOKAHEAD ((int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])))

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X.
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (360)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */     2,   43,   44,   46,   34,   99,   99,  110,  113,   41,
 /*    10 */    41,   42,   42,   42,   42,    4,  125,   90,   39,   39,
 /*    20 */    48,   88,  103,  103,   40,   40,   40,   40,   38,   38,
 /*    30 */    38,   37,   47,   43,   44,   46,   34,   99,   99,  110,
 /*    40 */   113,   41,   41,   42,   42,   42,   42,   37,   47,   78,
 /*    50 */    39,   39,    3,  125,  103,  103,   40,   40,   40,   40,
 /*    60 */    38,   38,   38,   37,   47,  168,   43,   44,   46,   34,
 /*    70 */    99,   99,  110,  113,   41,   41,   42,   42,   42,   42,
 /*    80 */    47,    8,  125,   39,   39,   52,   51,  103,  103,   40,
 /*    90 */    40,   40,   40,   38,   38,   38,   37,   47,   43,   44,
 /*   100 */    46,   34,   99,   99,  110,  113,   41,   41,   42,   42,
 /*   110 */    42,   42,   49,    8,  125,   39,   39,   50,   51,  103,
 /*   120 */   103,   40,   40,   40,   40,   38,   38,   38,   37,   47,
 /*   130 */    43,   32,   46,   34,   99,   99,  110,  113,   41,   41,
 /*   140 */    42,   42,   42,   42,    5,  125,  123,   39,   39,   13,
 /*   150 */   125,  103,  103,   40,   40,   40,   40,   38,   38,   38,
 /*   160 */    37,   47,   44,   46,   34,   99,   99,  110,  113,   41,
 /*   170 */    41,   42,   42,   42,   42,   36,   33,   53,   39,   39,
 /*   180 */     6,  125,  103,  103,   40,   40,   40,   40,   38,   38,
 /*   190 */    38,   37,   47,   46,   34,   99,   99,  110,  113,   41,
 /*   200 */    41,   42,   42,   42,   42,   24,  125,   26,   39,   39,
 /*   210 */    25,  125,  103,  103,   40,   40,   40,   40,   38,   38,
 /*   220 */    38,   37,   47,   87,   42,   42,   42,   42,   35,   11,
 /*   230 */   125,   39,   39,  115,   14,  125,   28,   40,   40,   40,
 /*   240 */    40,   38,   38,   38,   37,   47,    7,  125,    1,   42,
 /*   250 */    42,   42,   42,   15,  125,   45,   39,   39,   16,  125,
 /*   260 */    31,  124,   40,   40,   40,   40,   38,   38,   38,   37,
 /*   270 */    47,   27,  124,   18,  124,   29,   29,   54,   89,   38,
 /*   280 */    38,   38,   37,   47,   18,   86,   29,   29,   54,   89,
 /*   290 */    30,  124,   81,   79,   79,   80,   82,   83,   85,  124,
 /*   300 */    86,   30,  124,   81,   79,   79,   80,   82,   83,   85,
 /*   310 */   124,   39,   39,   12,  125,   23,  125,   40,   40,   40,
 /*   320 */    40,   38,   38,   38,   37,   47,   39,   39,  100,  100,
 /*   330 */   111,  114,   22,  125,   21,  125,   38,   38,   38,   37,
 /*   340 */    47,   20,  125,  124,  124,   17,  125,   19,  125,    9,
 /*   350 */   125,  124,   10,  125,  124,  124,  124,  124,  124,  104,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    46,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*    10 */    10,   11,   12,   13,   14,   43,   44,   17,   18,   19,
 /*    20 */    48,   17,   22,   23,   24,   25,   26,   27,   28,   29,
 /*    30 */    30,   31,   32,    1,    2,    3,    4,    5,    6,    7,
 /*    40 */     8,    9,   10,   11,   12,   13,   14,   31,   32,   17,
 /*    50 */    18,   19,   43,   44,   22,   23,   24,   25,   26,   27,
 /*    60 */    28,   29,   30,   31,   32,    0,    1,    2,    3,    4,
 /*    70 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    80 */    32,   43,   44,   18,   19,   47,   48,   22,   23,   24,
 /*    90 */    25,   26,   27,   28,   29,   30,   31,   32,    1,    2,
 /*   100 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   110 */    13,   14,   28,   43,   44,   18,   19,   47,   48,   22,
 /*   120 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   130 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   10,
 /*   140 */    11,   12,   13,   14,   43,   44,   45,   18,   19,   43,
 /*   150 */    44,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   160 */    31,   32,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   170 */    10,   11,   12,   13,   14,   49,   50,   51,   18,   19,
 /*   180 */    43,   44,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   190 */    30,   31,   32,    3,    4,    5,    6,    7,    8,    9,
 /*   200 */    10,   11,   12,   13,   14,   43,   44,   42,   18,   19,
 /*   210 */    43,   44,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   220 */    30,   31,   32,   17,   11,   12,   13,   14,   15,   43,
 /*   230 */    44,   18,   19,   17,   43,   44,   42,   24,   25,   26,
 /*   240 */    27,   28,   29,   30,   31,   32,   43,   44,   16,   11,
 /*   250 */    12,   13,   14,   43,   44,   16,   18,   19,   43,   44,
 /*   260 */     3,   52,   24,   25,   26,   27,   28,   29,   30,   31,
 /*   270 */    32,    3,   52,   16,   52,   18,   19,   20,   21,   28,
 /*   280 */    29,   30,   31,   32,   16,   20,   18,   19,   20,   21,
 /*   290 */    33,   52,   35,   36,   37,   38,   39,   40,   41,   52,
 /*   300 */    35,   33,   52,   35,   36,   37,   38,   39,   40,   41,
 /*   310 */    52,   18,   19,   43,   44,   43,   44,   24,   25,   26,
 /*   320 */    27,   28,   29,   30,   31,   32,   18,   19,    5,    6,
 /*   330 */     7,    8,   43,   44,   43,   44,   28,   29,   30,   31,
 /*   340 */    32,   43,   44,   52,   52,   43,   44,   43,   44,   43,
 /*   350 */    44,   52,   43,   44,   52,   52,   52,   52,   52,   36,
 /*   360 */    52,   52,   52,   52,   52,   52,   52,   52,   52,   52,
 /*   370 */    52,   52,
};
#define YY_SHIFT_COUNT    (54)
#define YY_SHIFT_MIN      (0)
#define YY_SHIFT_MAX      (323)
static const unsigned short int yy_shift_ofst[] = {
 /*     0 */   257,  257,  257,    0,   32,   65,   97,  129,   97,  160,
 /*    10 */   190,  190,  213,  238,  238,  238,  238,  238,  257,  293,
 /*    20 */   308,  251,   16,   48,  360,  360,  257,  257,  257,  257,
 /*    30 */   257,  257,  257,  257,  268,  257,  257,  257,  257,  257,
 /*    40 */   257,  257,  257,  257,  257,   84,  323,  265,  165,    4,
 /*    50 */   206,  194,  216,  232,  239,
};
#define YY_REDUCE_COUNT (45)
#define YY_REDUCE_MIN   (-46)
#define YY_REDUCE_MAX   (309)
static const short yy_reduce_ofst[] = {
 /*     0 */   101,   38,   70,  126,  126,  126,  126,  126,  126,  126,
 /*    10 */   126,  126,  126,  126,  126,  126,  126,  126,  -28,  126,
 /*    20 */   126,  126,  126,  126,  126,  126,    9,  106,  137,  162,
 /*    30 */   167,  186,  191,  203,  210,  215,  270,  272,  289,  291,
 /*    40 */   298,  302,  304,  306,  309,  -46,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   122,  164,  164,  165,  166,  122,  165,  122,  166,  140,
 /*    10 */   139,  155,  149,  154,  160,  153,  150,  142,  122,  141,
 /*    20 */   143,  144,  145,  146,  157,  156,  122,  122,  122,  122,
 /*    30 */   122,  122,  122,  122,  122,  122,  122,  122,  122,  122,
 /*    40 */   122,  122,  122,  122,  122,  167,  122,  122,  122,  122,
 /*    50 */   122,  169,  122,  122,  132,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*        NOT => nothing */
    0,  /*         IS => nothing */
   20,  /*      MATCH => ID */
   20,  /*    LIKE_KW => ID */
    0,  /*    BETWEEN => nothing */
    0,  /*         IN => nothing */
    0,  /*         NE => nothing */
    0,  /*         EQ => nothing */
    0,  /*         GT => nothing */
    0,  /*         LE => nothing */
    0,  /*         LT => nothing */
    0,  /*         GE => nothing */
    0,  /*     ESCAPE => nothing */
    0,  /*         LP => nothing */
    0,  /*         RP => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*         ID => nothing */
   20,  /*   CTIME_KW => ID */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ExpreParseARG_SDECL                /* A place to hold %extra_argument */
  ExpreParseCTX_SDECL                /* A place to hold %extra_context */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
  yyStackEntry *yystackEnd;            /* Last entry in the stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ExpreParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#if defined(YYCOVERAGE) || !defined(NDEBUG)
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  /*    0 */ "$",
  /*    1 */ "OR",
  /*    2 */ "AND",
  /*    3 */ "NOT",
  /*    4 */ "IS",
  /*    5 */ "MATCH",
  /*    6 */ "LIKE_KW",
  /*    7 */ "BETWEEN",
  /*    8 */ "IN",
  /*    9 */ "NE",
  /*   10 */ "EQ",
  /*   11 */ "GT",
  /*   12 */ "LE",
  /*   13 */ "LT",
  /*   14 */ "GE",
  /*   15 */ "ESCAPE",
  /*   16 */ "LP",
  /*   17 */ "RP",
  /*   18 */ "PLUS",
  /*   19 */ "MINUS",
  /*   20 */ "ID",
  /*   21 */ "CTIME_KW",
  /*   22 */ "ISNULL",
  /*   23 */ "NOTNULL",
  /*   24 */ "BITAND",
  /*   25 */ "BITOR",
  /*   26 */ "LSHIFT",
  /*   27 */ "RSHIFT",
  /*   28 */ "STAR",
  /*   29 */ "SLASH",
  /*   30 */ "REM",
  /*   31 */ "CONCAT",
  /*   32 */ "COLLATE",
  /*   33 */ "BITNOT",
  /*   34 */ "ON",
  /*   35 */ "STRING",
  /*   36 */ "NULL",
  /*   37 */ "FLOAT",
  /*   38 */ "BLOB",
  /*   39 */ "INTEGER",
  /*   40 */ "VARIABLE",
  /*   41 */ "JOIN_KW",
  /*   42 */ "COMMA",
  /*   43 */ "expr",
  /*   44 */ "term",
  /*   45 */ "expres",
  /*   46 */ "distinct",
  /*   47 */ "exprlist",
  /*   48 */ "nexprlist",
  /*   49 */ "likeop",
  /*   50 */ "between_op",
  /*   51 */ "in_op",
};
#endif /* defined(YYCOVERAGE) || !defined(NDEBUG) */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "expr ::= term",
 /*   1 */ "expr ::= LP expr RP",
 /*   2 */ "term ::= NULL|FLOAT",
 /*   3 */ "term ::= BLOB",
 /*   4 */ "term ::= STRING",
 /*   5 */ "term ::= INTEGER",
 /*   6 */ "term ::= VARIABLE",
 /*   7 */ "term ::= ID",
 /*   8 */ "term ::= JOIN_KW",
 /*   9 */ "expr ::= expr COLLATE ID|STRING",
 /*  10 */ "expr ::= ID LP distinct exprlist RP",
 /*  11 */ "expr ::= ID LP STAR RP",
 /*  12 */ "term ::= CTIME_KW",
 /*  13 */ "expr ::= LP nexprlist COMMA expr RP",
 /*  14 */ "expr ::= expr AND expr",
 /*  15 */ "expr ::= expr OR expr",
 /*  16 */ "expr ::= expr LT|GT|GE|LE expr",
 /*  17 */ "expr ::= expr EQ|NE expr",
 /*  18 */ "expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr",
 /*  19 */ "expr ::= expr PLUS|MINUS expr",
 /*  20 */ "expr ::= expr STAR|SLASH|REM expr",
 /*  21 */ "expr ::= expr CONCAT expr",
 /*  22 */ "likeop ::= LIKE_KW|MATCH",
 /*  23 */ "likeop ::= NOT LIKE_KW|MATCH",
 /*  24 */ "expr ::= expr likeop expr",
 /*  25 */ "expr ::= expr likeop expr ESCAPE expr",
 /*  26 */ "expr ::= expr ISNULL|NOTNULL",
 /*  27 */ "expr ::= expr NOT NULL",
 /*  28 */ "expr ::= expr IS expr",
 /*  29 */ "expr ::= expr IS NOT expr",
 /*  30 */ "expr ::= NOT expr",
 /*  31 */ "expr ::= BITNOT expr",
 /*  32 */ "expr ::= PLUS|MINUS expr",
 /*  33 */ "between_op ::= BETWEEN",
 /*  34 */ "between_op ::= NOT BETWEEN",
 /*  35 */ "expr ::= expr between_op expr AND expr",
 /*  36 */ "in_op ::= IN",
 /*  37 */ "in_op ::= NOT IN",
 /*  38 */ "expr ::= expr in_op LP exprlist RP",
 /*  39 */ "exprlist ::=",
 /*  40 */ "nexprlist ::= nexprlist COMMA expr",
 /*  41 */ "nexprlist ::= expr",
 /*  42 */ "distinct ::=",
 /*  43 */ "expres ::= expr",
 /*  44 */ "exprlist ::= nexprlist",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ExpreParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void ExpreParseInit(void *yypRawParser ExpreParseCTX_PDECL){
  yyParser *yypParser = (yyParser*)yypRawParser;
  ExpreParseCTX_STORE
#ifdef YYTRACKMAXSTACKDEPTH
  yypParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  yypParser->yytos = NULL;
  yypParser->yystack = NULL;
  yypParser->yystksz = 0;
  if( yyGrowStack(yypParser) ){
    yypParser->yystack = &yypParser->yystk0;
    yypParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  yypParser->yytos = yypParser->yystack;
  yypParser->yystack[0].stateno = 0;
  yypParser->yystack[0].major = 0;
#if YYSTACKDEPTH>0
  yypParser->yystackEnd = &yypParser->yystack[YYSTACKDEPTH-1];
#endif
}

#ifndef ExpreParse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to ExpreParse and ExpreParseFree.
*/
void *ExpreParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE) ExpreParseCTX_PDECL){
  yyParser *yypParser;
  yypParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( yypParser ){
    ExpreParseCTX_STORE
    ExpreParseInit(yypParser ExpreParseCTX_PARAM);
  }
  return (void*)yypParser;
}
#endif /* ExpreParse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ExpreParseARG_FETCH
  ExpreParseCTX_FETCH
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void ExpreParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef ExpreParse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ExpreParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  ExpreParseFinalize(p);
  (*freeProc)(p);
}
#endif /* ExpreParse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ExpreParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/* This array of booleans keeps track of the parser statement
** coverage.  The element yycoverage[X][Y] is set when the parser
** is in state X and has a lookahead token Y.  In a well-tested
** systems, every element of this matrix should end up being set.
*/
#if defined(YYCOVERAGE)
static unsigned char yycoverage[YYNSTATE][YYNTOKEN];
#endif

/*
** Write into out a description of every state/lookahead combination that
**
**   (1)  has not been used by the parser, and
**   (2)  is not a syntax error.
**
** Return the number of missed state/lookahead combinations.
*/
#if defined(YYCOVERAGE)
int ExpreParseCoverage(FILE *out){
  int stateno, iLookAhead, i;
  int nMissed = 0;
  for(stateno=0; stateno<YYNSTATE; stateno++){
    i = yy_shift_ofst[stateno];
    for(iLookAhead=0; iLookAhead<YYNTOKEN; iLookAhead++){
      if( yy_lookahead[i+iLookAhead]!=iLookAhead ) continue;
      if( yycoverage[stateno][iLookAhead]==0 ) nMissed++;
      if( out ){
        fprintf(out,"State %d lookahead %s %s\n", stateno,
                yyTokenName[iLookAhead],
                yycoverage[stateno][iLookAhead] ? "ok" : "missed");
      }
    }
  }
  return nMissed;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_shift_action(
  YYCODETYPE iLookAhead,    /* The look-ahead token */
  YYACTIONTYPE stateno      /* Current state number */
){
  int i;

  if( stateno>YY_MAX_SHIFT ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
#if defined(YYCOVERAGE)
  yycoverage[stateno][iLookAhead] = 1;
#endif
  do{
    i = yy_shift_ofst[stateno];
    assert( i>=0 );
    /* assert( i+YYNTOKEN<=(int)YY_NLOOKAHEAD ); */
    assert( iLookAhead!=YYNOCODE );
    assert( iLookAhead < YYNTOKEN );
    i += iLookAhead;
    if( i>=YY_NLOOKAHEAD || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          j<(int)(sizeof(yy_lookahead)/sizeof(yy_lookahead[0])) &&
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static YYACTIONTYPE yy_find_reduce_action(
  YYACTIONTYPE stateno,     /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ExpreParseARG_FETCH
   ExpreParseCTX_FETCH
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
#line 19 "expre_analy.y"

  strcpy(state->erro_msg, "parser stack overflow.\n");
#line 889 "expre_analy.c"
/******** End %stack_overflow code ********************************************/
   ExpreParseARG_STORE /* Suppress warning about unused %extra_argument var */
   ExpreParseCTX_STORE
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState, const char *zTag){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%s%s '%s', go to state %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%s%s '%s', pending reduce %d\n",
         yyTracePrompt, zTag, yyTokenName[yypParser->yytos->major],
         yyNewState - YY_MIN_REDUCE);
    }
  }
}
#else
# define yyTraceShift(X,Y,Z)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  YYACTIONTYPE yyNewState,      /* The new state to shift in */
  YYCODETYPE yyMajor,           /* The major token to shift in */
  ExpreParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>yypParser->yystackEnd ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState, "Shift");
}

/* For rule J, yyRuleInfoLhs[J] contains the symbol on the left-hand side
** of that rule */
static const YYCODETYPE yyRuleInfoLhs[] = {
    43,  /* (0) expr ::= term */
    43,  /* (1) expr ::= LP expr RP */
    44,  /* (2) term ::= NULL|FLOAT */
    44,  /* (3) term ::= BLOB */
    44,  /* (4) term ::= STRING */
    44,  /* (5) term ::= INTEGER */
    44,  /* (6) term ::= VARIABLE */
    44,  /* (7) term ::= ID */
    44,  /* (8) term ::= JOIN_KW */
    43,  /* (9) expr ::= expr COLLATE ID|STRING */
    43,  /* (10) expr ::= ID LP distinct exprlist RP */
    43,  /* (11) expr ::= ID LP STAR RP */
    44,  /* (12) term ::= CTIME_KW */
    43,  /* (13) expr ::= LP nexprlist COMMA expr RP */
    43,  /* (14) expr ::= expr AND expr */
    43,  /* (15) expr ::= expr OR expr */
    43,  /* (16) expr ::= expr LT|GT|GE|LE expr */
    43,  /* (17) expr ::= expr EQ|NE expr */
    43,  /* (18) expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr */
    43,  /* (19) expr ::= expr PLUS|MINUS expr */
    43,  /* (20) expr ::= expr STAR|SLASH|REM expr */
    43,  /* (21) expr ::= expr CONCAT expr */
    49,  /* (22) likeop ::= LIKE_KW|MATCH */
    49,  /* (23) likeop ::= NOT LIKE_KW|MATCH */
    43,  /* (24) expr ::= expr likeop expr */
    43,  /* (25) expr ::= expr likeop expr ESCAPE expr */
    43,  /* (26) expr ::= expr ISNULL|NOTNULL */
    43,  /* (27) expr ::= expr NOT NULL */
    43,  /* (28) expr ::= expr IS expr */
    43,  /* (29) expr ::= expr IS NOT expr */
    43,  /* (30) expr ::= NOT expr */
    43,  /* (31) expr ::= BITNOT expr */
    43,  /* (32) expr ::= PLUS|MINUS expr */
    50,  /* (33) between_op ::= BETWEEN */
    50,  /* (34) between_op ::= NOT BETWEEN */
    43,  /* (35) expr ::= expr between_op expr AND expr */
    51,  /* (36) in_op ::= IN */
    51,  /* (37) in_op ::= NOT IN */
    43,  /* (38) expr ::= expr in_op LP exprlist RP */
    47,  /* (39) exprlist ::= */
    48,  /* (40) nexprlist ::= nexprlist COMMA expr */
    48,  /* (41) nexprlist ::= expr */
    46,  /* (42) distinct ::= */
    45,  /* (43) expres ::= expr */
    47,  /* (44) exprlist ::= nexprlist */
};

/* For rule J, yyRuleInfoNRhs[J] contains the negative of the number
** of symbols on the right-hand side of that rule. */
static const signed char yyRuleInfoNRhs[] = {
   -1,  /* (0) expr ::= term */
   -3,  /* (1) expr ::= LP expr RP */
   -1,  /* (2) term ::= NULL|FLOAT */
   -1,  /* (3) term ::= BLOB */
   -1,  /* (4) term ::= STRING */
   -1,  /* (5) term ::= INTEGER */
   -1,  /* (6) term ::= VARIABLE */
   -1,  /* (7) term ::= ID */
   -1,  /* (8) term ::= JOIN_KW */
   -3,  /* (9) expr ::= expr COLLATE ID|STRING */
   -5,  /* (10) expr ::= ID LP distinct exprlist RP */
   -4,  /* (11) expr ::= ID LP STAR RP */
   -1,  /* (12) term ::= CTIME_KW */
   -5,  /* (13) expr ::= LP nexprlist COMMA expr RP */
   -3,  /* (14) expr ::= expr AND expr */
   -3,  /* (15) expr ::= expr OR expr */
   -3,  /* (16) expr ::= expr LT|GT|GE|LE expr */
   -3,  /* (17) expr ::= expr EQ|NE expr */
   -3,  /* (18) expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr */
   -3,  /* (19) expr ::= expr PLUS|MINUS expr */
   -3,  /* (20) expr ::= expr STAR|SLASH|REM expr */
   -3,  /* (21) expr ::= expr CONCAT expr */
   -1,  /* (22) likeop ::= LIKE_KW|MATCH */
   -2,  /* (23) likeop ::= NOT LIKE_KW|MATCH */
   -3,  /* (24) expr ::= expr likeop expr */
   -5,  /* (25) expr ::= expr likeop expr ESCAPE expr */
   -2,  /* (26) expr ::= expr ISNULL|NOTNULL */
   -3,  /* (27) expr ::= expr NOT NULL */
   -3,  /* (28) expr ::= expr IS expr */
   -4,  /* (29) expr ::= expr IS NOT expr */
   -2,  /* (30) expr ::= NOT expr */
   -2,  /* (31) expr ::= BITNOT expr */
   -2,  /* (32) expr ::= PLUS|MINUS expr */
   -1,  /* (33) between_op ::= BETWEEN */
   -2,  /* (34) between_op ::= NOT BETWEEN */
   -5,  /* (35) expr ::= expr between_op expr AND expr */
   -1,  /* (36) in_op ::= IN */
   -2,  /* (37) in_op ::= NOT IN */
   -5,  /* (38) expr ::= expr in_op LP exprlist RP */
    0,  /* (39) exprlist ::= */
   -3,  /* (40) nexprlist ::= nexprlist COMMA expr */
   -1,  /* (41) nexprlist ::= expr */
    0,  /* (42) distinct ::= */
   -1,  /* (43) expres ::= expr */
   -1,  /* (44) exprlist ::= nexprlist */
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
**
** The yyLookahead and yyLookaheadToken parameters provide reduce actions
** access to the lookahead token (if any).  The yyLookahead will be YYNOCODE
** if the lookahead token has already been consumed.  As this procedure is
** only called from one place, optimizing compilers will in-line it, which
** means that the extra parameters have no performance impact.
*/
static YYACTIONTYPE yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno,       /* Number of the rule by which to reduce */
  int yyLookahead,             /* Lookahead token, or YYNOCODE if none */
  ExpreParseTOKENTYPE yyLookaheadToken  /* Value of the lookahead token */
  ExpreParseCTX_PDECL                   /* %extra_context */
){
  int yygoto;                     /* The next state */
  YYACTIONTYPE yyact;             /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ExpreParseARG_FETCH
  (void)yyLookahead;
  (void)yyLookaheadToken;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfoNRhs[yyruleno];
    if( yysize ){
      fprintf(yyTraceFILE, "%sReduce %d [%s], go to state %d.\n",
        yyTracePrompt,
        yyruleno, yyRuleName[yyruleno], yymsp[yysize].stateno);
    }else{
      fprintf(yyTraceFILE, "%sReduce %d [%s].\n",
        yyTracePrompt, yyruleno, yyRuleName[yyruleno]);
    }
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfoNRhs[yyruleno]==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=yypParser->yystackEnd ){
      yyStackOverflow(yypParser);
      /* The call to yyStackOverflow() above pops the stack until it is
      ** empty, causing the main parser loop to exit.  So the return value
      ** is never used and does not matter. */
      return 0;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        /* The call to yyStackOverflow() above pops the stack until it is
        ** empty, causing the main parser loop to exit.  So the return value
        ** is never used and does not matter. */
        return 0;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* expr ::= term */
#line 84 "expre_analy.y"
{yylhsminor.yy78 = new_oper_leaf(TERM_TOKE, yymsp[0].minor.yy0);}
#line 1145 "expre_analy.c"
  yymsp[0].minor.yy78 = yylhsminor.yy78;
        break;
      case 1: /* expr ::= LP expr RP */
#line 85 "expre_analy.y"
{yymsp[-2].minor.yy78 = yymsp[-1].minor.yy78;}
#line 1151 "expre_analy.c"
        break;
      case 2: /* term ::= NULL|FLOAT */
      case 3: /* term ::= BLOB */ yytestcase(yyruleno==3);
      case 4: /* term ::= STRING */ yytestcase(yyruleno==4);
      case 5: /* term ::= INTEGER */ yytestcase(yyruleno==5);
      case 6: /* term ::= VARIABLE */ yytestcase(yyruleno==6);
      case 7: /* term ::= ID */ yytestcase(yyruleno==7);
      case 8: /* term ::= JOIN_KW */ yytestcase(yyruleno==8);
      case 12: /* term ::= CTIME_KW */ yytestcase(yyruleno==12);
#line 87 "expre_analy.y"
{yylhsminor.yy0 = new_leaf_vato(yymsp[0].minor.yy0);}
#line 1163 "expre_analy.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 9: /* expr ::= expr COLLATE ID|STRING */
#line 96 "expre_analy.y"
{yymsp[-2].minor.yy78 = expr_add_collate(state, TK_COLLATE, yymsp[0].minor.yy0, NULL);}
#line 1169 "expre_analy.c"
        break;
      case 10: /* expr ::= ID LP distinct exprlist RP */
#line 97 "expre_analy.y"
{ /* yylhsminor.yy78 = expr_function(state, TK_DISTINCT, yymsp[-4].minor.yy0, yymsp[-2].minor.yy20); */}
#line 1174 "expre_analy.c"
  yymsp[-4].minor.yy78 = yylhsminor.yy78;
        break;
      case 11: /* expr ::= ID LP STAR RP */
#line 98 "expre_analy.y"
{/* yylhsminor.yy78 = expr_function(state, TK_STAR, yymsp[-3].minor.yy0, yymsp[-3].minor.yy0); */}
#line 1180 "expre_analy.c"
  yymsp[-3].minor.yy78 = yylhsminor.yy78;
        break;
      case 13: /* expr ::= LP nexprlist COMMA expr RP */
#line 104 "expre_analy.y"
{
/*
  oper_list *plist = new_oper_list(state, yymsp[-3].minor.yy72, yymsp[-1].minor.yy78);
  yymsp[-4].minor.yy78 = oper_node(state, TK_VECTOR, 0, 0);
  if(yymsp[-4].minor.yy78){
    yymsp[-4].minor.yy78->list_next = plist;
  }else{
    oper_list_dele(state, pList);
  }
*/
}
#line 1196 "expre_analy.c"
        break;
      case 14: /* expr ::= expr AND expr */
      case 15: /* expr ::= expr OR expr */ yytestcase(yyruleno==15);
      case 16: /* expr ::= expr LT|GT|GE|LE expr */ yytestcase(yyruleno==16);
      case 17: /* expr ::= expr EQ|NE expr */ yytestcase(yyruleno==17);
      case 18: /* expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr */ yytestcase(yyruleno==18);
      case 19: /* expr ::= expr PLUS|MINUS expr */ yytestcase(yyruleno==19);
      case 20: /* expr ::= expr STAR|SLASH|REM expr */ yytestcase(yyruleno==20);
      case 21: /* expr ::= expr CONCAT expr */ yytestcase(yyruleno==21);
#line 117 "expre_analy.y"
{yylhsminor.yy78 = new_oper_node(state, yymsp[-1].major, yymsp[-2].minor.yy78, yymsp[0].minor.yy78);}
#line 1208 "expre_analy.c"
  yymsp[-2].minor.yy78 = yylhsminor.yy78;
        break;
      case 22: /* likeop ::= LIKE_KW|MATCH */
#line 128 "expre_analy.y"
{yylhsminor.yy0 = yymsp[0].minor.yy0;}
#line 1214 "expre_analy.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 23: /* likeop ::= NOT LIKE_KW|MATCH */
#line 129 "expre_analy.y"
{yymsp[-1].minor.yy0 = yymsp[0].minor.yy0;}
#line 1220 "expre_analy.c"
        break;
      case 24: /* expr ::= expr likeop expr */
#line 130 "expre_analy.y"
{
/*
  oper_list *plist;
  pList = new_oper_list(state,0, yymsp[0].minor.yy78);
  pList = new_oper_list(state,pList, yymsp[-2].minor.yy78);
*/
  yymsp[-2].minor.yy78 = expr_function(state, yymsp[-1].major, yymsp[-1].minor.yy0, yymsp[-1].minor.yy0);
}
#line 1232 "expre_analy.c"
        break;
      case 25: /* expr ::= expr likeop expr ESCAPE expr */
#line 138 "expre_analy.y"
{
/*
  oper_list *plist;
  plist = new_oper_list(state,0, yymsp[-2].minor.yy78);
  plist = new_oper_list(state,plist, yymsp[-4].minor.yy78);
  plist = new_oper_list(state,plist, yymsp[0].minor.yy78);
*/
  yymsp[-4].minor.yy78 = expr_function(state, yymsp[-3].major, yymsp[-3].minor.yy0, yymsp[-3].minor.yy0);
}
#line 1245 "expre_analy.c"
        break;
      case 26: /* expr ::= expr ISNULL|NOTNULL */
#line 148 "expre_analy.y"
{yymsp[-1].minor.yy78 = new_oper_node(state,yymsp[0].major,yymsp[-1].minor.yy78,0);}
#line 1250 "expre_analy.c"
        break;
      case 27: /* expr ::= expr NOT NULL */
#line 149 "expre_analy.y"
{yymsp[-2].minor.yy78 = new_oper_node(state,TK_NOTNULL,yymsp[-2].minor.yy78,0);}
#line 1255 "expre_analy.c"
        break;
      case 28: /* expr ::= expr IS expr */
#line 152 "expre_analy.y"
{
  yymsp[-2].minor.yy78 = new_oper_node(state,TK_IS,yymsp[-2].minor.yy78,yymsp[0].minor.yy78);
  binary_unary_null(state, yymsp[0].minor.yy78, yymsp[-2].minor.yy78, TK_ISNULL);
}
#line 1263 "expre_analy.c"
        break;
      case 29: /* expr ::= expr IS NOT expr */
#line 156 "expre_analy.y"
{
  yymsp[-3].minor.yy78 = new_oper_node(state,TK_IS,yymsp[-3].minor.yy78,yymsp[0].minor.yy78);
  binary_unary_null(state, yymsp[0].minor.yy78, yymsp[-3].minor.yy78, TK_NOTNULL);
}
#line 1271 "expre_analy.c"
        break;
      case 30: /* expr ::= NOT expr */
      case 31: /* expr ::= BITNOT expr */ yytestcase(yyruleno==31);
#line 162 "expre_analy.y"
{yylhsminor.yy78 = new_oper_node(state, yymsp[-1].major, yymsp[0].minor.yy78, 0);}
#line 1277 "expre_analy.c"
  yymsp[-1].minor.yy78 = yylhsminor.yy78;
        break;
      case 32: /* expr ::= PLUS|MINUS expr */
#line 164 "expre_analy.y"
{yylhsminor.yy78 = new_oper_node(state, yymsp[-1].major==TK_PLUS ? TK_PLUS : TK_MINUS, yymsp[0].minor.yy78, 0);}
#line 1283 "expre_analy.c"
  yymsp[-1].minor.yy78 = yylhsminor.yy78;
        break;
      case 33: /* between_op ::= BETWEEN */
      case 36: /* in_op ::= IN */ yytestcase(yyruleno==36);
#line 168 "expre_analy.y"
{yymsp[0].minor.yy20 = 0;}
#line 1290 "expre_analy.c"
        break;
      case 34: /* between_op ::= NOT BETWEEN */
      case 37: /* in_op ::= NOT IN */ yytestcase(yyruleno==37);
#line 169 "expre_analy.y"
{yymsp[-1].minor.yy20 = 1;}
#line 1296 "expre_analy.c"
        break;
      case 35: /* expr ::= expr between_op expr AND expr */
#line 170 "expre_analy.y"
{
/*
  oper_list *olist = new_oper_list(0, yymsp[-2].minor.yy78);
  olist = new_oper_list(olist, yymsp[0].minor.yy78);
  yymsp[-4].minor.yy78 = new_oper_node(state, TK_BETWEEN, yymsp[-4].minor.yy78, 0);
  if( yymsp[-4].minor.yy78 ) yymsp[-4].minor.yy78->list_next = olist;
  else oper_list_dele(olist); 
  if( yymsp[-3].minor.yy20 ) yymsp[-4].minor.yy78 = new_oper_node(state, TK_NOT, yymsp[-4].minor.yy78, 0);
*/
}
#line 1310 "expre_analy.c"
        break;
      case 38: /* expr ::= expr in_op LP exprlist RP */
#line 185 "expre_analy.y"
{
    if (yymsp[-1].minor.yy72 == 0) {
        OPER_NODE_DELE(yymsp[-4].minor.yy78);
        yymsp[-4].minor.yy78 = new_oper_leaf(TK_INTEGER, 0x00);
    } else {
        yymsp[-4].minor.yy78 = new_oper_node(state, TK_IN, yymsp[-4].minor.yy78, 0);
        if (yymsp[-4].minor.yy78) {
          yymsp[-4].minor.yy78->list_next = yymsp[-1].minor.yy72;
        } else {
          // oper_list_dele(state, yymsp[-1].minor.yy72);
        }
        if (yymsp[-3].minor.yy20) yymsp[-4].minor.yy78 = new_oper_node(state, TK_NOT, yymsp[-4].minor.yy78, 0);
    }
}
#line 1328 "expre_analy.c"
        break;
      case 39: /* exprlist ::= */
#line 207 "expre_analy.y"
{yymsp[1].minor.yy72 = 0;}
#line 1333 "expre_analy.c"
        break;
      case 40: /* nexprlist ::= nexprlist COMMA expr */
#line 209 "expre_analy.y"
{/* yymsp[-2].minor.yy72 = new_oper_list(state,yymsp[-2].minor.yy72,yymsp[0].minor.yy78); */}
#line 1338 "expre_analy.c"
        break;
      case 41: /* nexprlist ::= expr */
#line 211 "expre_analy.y"
{/* yylhsminor.yy72 = new_oper_list(state,0,yymsp[0].minor.yy78); */}
#line 1343 "expre_analy.c"
  yymsp[0].minor.yy72 = yylhsminor.yy72;
        break;
      case 42: /* distinct ::= */
#line 217 "expre_analy.y"
{yymsp[1].minor.yy20 = 0;}
#line 1349 "expre_analy.c"
        break;
      default:
      /* (43) expres ::= expr */ yytestcase(yyruleno==43);
      /* (44) exprlist ::= nexprlist */ yytestcase(yyruleno==44);
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfoLhs)/sizeof(yyRuleInfoLhs[0]) );
  yygoto = yyRuleInfoLhs[yyruleno];
  yysize = yyRuleInfoNRhs[yyruleno];
  yyact = yy_find_reduce_action(yymsp[yysize].stateno,(YYCODETYPE)yygoto);

  /* There are no SHIFTREDUCE actions on nonterminals because the table
  ** generator has simplified them to pure REDUCE actions. */
  assert( !(yyact>YY_MAX_SHIFT && yyact<=YY_MAX_SHIFTREDUCE) );

  /* It is not possible for a REDUCE to be followed by an error */
  assert( yyact!=YY_ERROR_ACTION );

  yymsp += yysize+1;
  yypParser->yytos = yymsp;
  yymsp->stateno = (YYACTIONTYPE)yyact;
  yymsp->major = (YYCODETYPE)yygoto;
  yyTraceShift(yypParser, yyact, "... then shift");
  return yyact;
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ExpreParseARG_FETCH
  ExpreParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
#line 28 "expre_analy.y"

  state->accept = PARSE_FAULT;
  strcpy(state->erro_msg, "Giving up.  Parser is hopelessly lost...\n");
#line 1399 "expre_analy.c"
/************ End %parse_failure code *****************************************/
  ExpreParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ExpreParseCTX_STORE
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ExpreParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ExpreParseARG_FETCH
  ExpreParseCTX_FETCH
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 15 "expre_analy.y"

  // UNUSED_PARAMETER(yymajor);  /* Silence some compiler warnings */
  strcpy(state->erro_msg, "syntax error near.\n");
#line 1422 "expre_analy.c"
/************ End %syntax_error code ******************************************/
  ExpreParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ExpreParseCTX_STORE
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ExpreParseARG_FETCH
  ExpreParseCTX_FETCH
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
#line 23 "expre_analy.y"

  state->accept = PARSE_SUCCESS;
  strcpy(state->erro_msg, "parsing complete!\n");
#line 1452 "expre_analy.c"
/*********** End %parse_accept code *******************************************/
  ExpreParseARG_STORE /* Suppress warning about unused %extra_argument variable */
  ExpreParseCTX_STORE
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ExpreParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void ExpreParse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ExpreParseTOKENTYPE yyminor       /* The value for the token */
  ExpreParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  YYACTIONTYPE yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser = (yyParser*)yyp;  /* The parser */
  ExpreParseCTX_FETCH
  ExpreParseARG_STORE

  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif

  yyact = yypParser->yytos->stateno;
#ifndef NDEBUG
  if( yyTraceFILE ){
    if( yyact < YY_MIN_REDUCE ){
      fprintf(yyTraceFILE,"%sInput '%s' in state %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact);
    }else{
      fprintf(yyTraceFILE,"%sInput '%s' with pending reduce %d\n",
              yyTracePrompt,yyTokenName[yymajor],yyact-YY_MIN_REDUCE);
    }
  }
#endif

  do{
    assert( yyact==yypParser->yytos->stateno );
    yyact = yy_find_shift_action((YYCODETYPE)yymajor,yyact);
    if( yyact >= YY_MIN_REDUCE ){
      yyact = yy_reduce(yypParser,yyact-YY_MIN_REDUCE,yymajor,
                        yyminor ExpreParseCTX_PARAM);
    }else if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,(YYCODETYPE)yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      break;
    }else if( yyact==YY_ACCEPT_ACTION ){
      yypParser->yytos--;
      yy_accept(yypParser);
      return;
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) > YY_MAX_SHIFTREDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
      if( yymajor==YYNOCODE ) break;
      yyact = yypParser->yytos->stateno;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      break;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      break;
#endif
    }
  }while( yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}

/*
** Return the fallback token corresponding to canonical token iToken, or
** 0 if iToken has no fallback.
*/
int ExpreParseFallback(int iToken){
#ifdef YYFALLBACK
  if( iToken<(int)(sizeof(yyFallback)/sizeof(yyFallback[0])) ){
    return yyFallback[iToken];
  }
#else
  (void)iToken;
#endif
  return 0;
}
