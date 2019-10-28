/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         plpgsql_yyparse
#define yylex           plpgsql_yylex
#define yyerror         plpgsql_yyerror
#define yylval          plpgsql_yylval
#define yychar          plpgsql_yychar
#define yydebug         plpgsql_yydebug
#define yynerrs         plpgsql_yynerrs
#define yylloc          plpgsql_yylloc

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "src\\pl\\plpgsql\\src\\pl_gram.y"

/*-------------------------------------------------------------------------
 *
 * pl_gram.y			- Parser for the PL/pgSQL procedural language
 *
 * Portions Copyright (c) 1996-2013, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 *
 * IDENTIFICATION
 *	  src/pl/plpgsql/src/pl_gram.y
 *
 *-------------------------------------------------------------------------
 */

#include "plpgsql.h"

#include "catalog/namespace.h"
#include "catalog/pg_type.h"
#include "parser/parser.h"
#include "parser/parse_type.h"
#include "parser/scanner.h"
#include "parser/scansup.h"
#include "utils/builtins.h"


/* Location tracking support --- simpler than bison's default */
#define YYLLOC_DEFAULT(Current, Rhs, N) \
	do { \
		if (N) \
			(Current) = (Rhs)[1]; \
		else \
			(Current) = (Rhs)[0]; \
	} while (0)

/*
 * Bison doesn't allocate anything that needs to live across parser calls,
 * so we can easily have it use palloc instead of malloc.  This prevents
 * memory leaks if we error out during parsing.  Note this only works with
 * bison >= 2.0.  However, in bison 1.875 the default is to use alloca()
 * if possible, so there's not really much problem anyhow, at least if
 * you're building with gcc.
 */
#define YYMALLOC palloc
#define YYFREE   pfree


typedef struct
{
	int			location;
	int			leaderlen;
} sql_error_callback_arg;

#define parser_errposition(pos)  plpgsql_scanner_errposition(pos)

union YYSTYPE;					/* need forward reference for tok_is_keyword */

static	bool			tok_is_keyword(int token, union YYSTYPE *lval,
									   int kw_token, const char *kw_str);
static	void			word_is_not_variable(PLword *word, int location);
static	void			cword_is_not_variable(PLcword *cword, int location);
static	void			current_token_is_not_variable(int tok);
static	PLpgSQL_expr	*read_sql_construct(int until,
											int until2,
											int until3,
											const char *expected,
											const char *sqlstart,
											bool isexpression,
											bool valid_sql,
											bool trim,
											int *startloc,
											int *endtoken);
static	PLpgSQL_expr	*read_sql_expression(int until,
											 const char *expected);
static	PLpgSQL_expr	*read_sql_expression2(int until, int until2,
											  const char *expected,
											  int *endtoken);
static	PLpgSQL_expr	*read_sql_stmt(const char *sqlstart);
static	PLpgSQL_type	*read_datatype(int tok);
static	PLpgSQL_stmt	*make_execsql_stmt(int firsttoken, int location);
static	PLpgSQL_stmt_fetch *read_fetch_direction(void);
static	void			 complete_direction(PLpgSQL_stmt_fetch *fetch,
											bool *check_FROM);
static	PLpgSQL_stmt	*make_return_stmt(int location);
static	PLpgSQL_stmt	*make_return_next_stmt(int location);
static	PLpgSQL_stmt	*make_return_query_stmt(int location);
static  PLpgSQL_stmt	*make_case(int location, PLpgSQL_expr *t_expr,
								   List *case_when_list, List *else_stmts);
static	char			*NameOfDatum(PLwdatum *wdatum);
static	void			 check_assignable(PLpgSQL_datum *datum, int location);
static	void			 read_into_target(PLpgSQL_rec **rec, PLpgSQL_row **row,
										  bool *strict);
static	PLpgSQL_row		*read_into_scalar_list(char *initial_name,
											   PLpgSQL_datum *initial_datum,
											   int initial_location);
static	PLpgSQL_row		*make_scalar_list1(char *initial_name,
										   PLpgSQL_datum *initial_datum,
										   int lineno, int location);
static	void			 check_sql_expr(const char *stmt, int location,
										int leaderlen);
static	void			 plpgsql_sql_error_callback(void *arg);
static	PLpgSQL_type	*parse_datatype(const char *string, int location);
static	void			 check_labels(const char *start_label,
									  const char *end_label,
									  int end_location);
static	PLpgSQL_expr	*read_cursor_args(PLpgSQL_var *cursor,
										  int until, const char *expected);
static	List			*read_raise_options(void);


/* Line 371 of yacc.c  */
#line 187 "src\\pl\\plpgsql\\src\\pl_gram.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "pl_gram.h".  */
#ifndef YY_PLPGSQL_YY_SRC_PL_PLPGSQL_SRC_PL_GRAM_H_INCLUDED
# define YY_PLPGSQL_YY_SRC_PL_PLPGSQL_SRC_PL_GRAM_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int plpgsql_yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENT = 258,
     FCONST = 259,
     SCONST = 260,
     BCONST = 261,
     XCONST = 262,
     Op = 263,
     ICONST = 264,
     PARAM = 265,
     TYPECAST = 266,
     DOT_DOT = 267,
     COLON_EQUALS = 268,
     T_WORD = 269,
     T_CWORD = 270,
     T_DATUM = 271,
     LESS_LESS = 272,
     GREATER_GREATER = 273,
     K_ABSOLUTE = 274,
     K_ALIAS = 275,
     K_ALL = 276,
     K_ARRAY = 277,
     K_BACKWARD = 278,
     K_BEGIN = 279,
     K_BY = 280,
     K_CASE = 281,
     K_CLOSE = 282,
     K_COLLATE = 283,
     K_COLUMN = 284,
     K_COLUMN_NAME = 285,
     K_CONSTANT = 286,
     K_CONSTRAINT = 287,
     K_CONSTRAINT_NAME = 288,
     K_CONTINUE = 289,
     K_CURRENT = 290,
     K_CURSOR = 291,
     K_DATATYPE = 292,
     K_DEBUG = 293,
     K_DECLARE = 294,
     K_DEFAULT = 295,
     K_DETAIL = 296,
     K_DIAGNOSTICS = 297,
     K_DUMP = 298,
     K_ELSE = 299,
     K_ELSIF = 300,
     K_END = 301,
     K_ERRCODE = 302,
     K_ERROR = 303,
     K_EXCEPTION = 304,
     K_EXECUTE = 305,
     K_EXIT = 306,
     K_FETCH = 307,
     K_FIRST = 308,
     K_FOR = 309,
     K_FOREACH = 310,
     K_FORWARD = 311,
     K_FROM = 312,
     K_GET = 313,
     K_HINT = 314,
     K_IF = 315,
     K_IN = 316,
     K_INFO = 317,
     K_INSERT = 318,
     K_INTO = 319,
     K_IS = 320,
     K_LAST = 321,
     K_LOG = 322,
     K_LOOP = 323,
     K_MESSAGE = 324,
     K_MESSAGE_TEXT = 325,
     K_MOVE = 326,
     K_NEXT = 327,
     K_NO = 328,
     K_NOT = 329,
     K_NOTICE = 330,
     K_NULL = 331,
     K_OPEN = 332,
     K_OPTION = 333,
     K_OR = 334,
     K_PERFORM = 335,
     K_PG_DATATYPE_NAME = 336,
     K_PG_EXCEPTION_CONTEXT = 337,
     K_PG_EXCEPTION_DETAIL = 338,
     K_PG_EXCEPTION_HINT = 339,
     K_PRIOR = 340,
     K_QUERY = 341,
     K_RAISE = 342,
     K_RELATIVE = 343,
     K_RESULT_OID = 344,
     K_RETURN = 345,
     K_RETURNED_SQLSTATE = 346,
     K_REVERSE = 347,
     K_ROWTYPE = 348,
     K_ROW_COUNT = 349,
     K_SCHEMA = 350,
     K_SCHEMA_NAME = 351,
     K_SCROLL = 352,
     K_SLICE = 353,
     K_SQLSTATE = 354,
     K_STACKED = 355,
     K_STRICT = 356,
     K_TABLE = 357,
     K_TABLE_NAME = 358,
     K_THEN = 359,
     K_TO = 360,
     K_TYPE = 361,
     K_USE_COLUMN = 362,
     K_USE_VARIABLE = 363,
     K_USING = 364,
     K_VARIABLE_CONFLICT = 365,
     K_WARNING = 366,
     K_WHEN = 367,
     K_WHILE = 368
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 116 "src\\pl\\plpgsql\\src\\pl_gram.y"

		core_YYSTYPE			core_yystype;
		/* these fields must match core_YYSTYPE: */
		int						ival;
		char					*str;
		const char				*keyword;

		PLword					word;
		PLcword					cword;
		PLwdatum				wdatum;
		bool					boolean;
		Oid						oid;
		struct
		{
			char *name;
			int  lineno;
		}						varname;
		struct
		{
			char *name;
			int  lineno;
			PLpgSQL_datum   *scalar;
			PLpgSQL_rec		*rec;
			PLpgSQL_row		*row;
		}						forvariable;
		struct
		{
			char *label;
			int  n_initvars;
			int  *initvarnos;
		}						declhdr;
		struct
		{
			List *stmts;
			char *end_label;
			int   end_label_location;
		}						loop_body;
		List					*list;
		PLpgSQL_type			*dtype;
		PLpgSQL_datum			*datum;
		PLpgSQL_var				*var;
		PLpgSQL_expr			*expr;
		PLpgSQL_stmt			*stmt;
		PLpgSQL_condition		*condition;
		PLpgSQL_exception		*exception;
		PLpgSQL_exception_block	*exception_block;
		PLpgSQL_nsitem			*nsitem;
		PLpgSQL_diag_item		*diagitem;
		PLpgSQL_stmt_fetch		*fetch;
		PLpgSQL_case_when		*casewhen;


/* Line 387 of yacc.c  */
#line 396 "src\\pl\\plpgsql\\src\\pl_gram.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE plpgsql_yylval;
extern YYLTYPE plpgsql_yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int plpgsql_yyparse (void *YYPARSE_PARAM);
#else
int plpgsql_yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int plpgsql_yyparse (void);
#else
int plpgsql_yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_PLPGSQL_YY_SRC_PL_PLPGSQL_SRC_PL_GRAM_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 437 "src\\pl\\plpgsql\\src\\pl_gram.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   888

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  121
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  212
/* YYNRULES -- Number of states.  */
#define YYNSTATES  289

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   368

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,   114,     2,     2,     2,     2,
     116,   117,     2,     2,   118,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   115,
       2,   119,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   120,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     8,    11,    15,    19,    23,    27,
      28,    30,    37,    39,    42,    46,    48,    51,    53,    55,
      57,    61,    68,    74,    75,    83,    84,    87,    89,    90,
      91,    95,    97,   101,   104,   106,   108,   110,   112,   114,
     116,   118,   119,   121,   122,   123,   126,   129,   132,   133,
     136,   138,   140,   142,   144,   146,   148,   149,   151,   154,
     156,   159,   161,   163,   165,   167,   169,   171,   173,   175,
     177,   179,   181,   183,   185,   187,   189,   191,   193,   195,
     197,   200,   204,   210,   211,   213,   215,   219,   221,   225,
     226,   228,   230,   232,   234,   238,   247,   248,   253,   254,
     257,   265,   266,   269,   271,   275,   276,   279,   283,   288,
     293,   296,   298,   300,   302,   311,   312,   315,   319,   321,
     323,   325,   327,   333,   335,   337,   339,   341,   344,   349,
     354,   355,   359,   362,   364,   366,   368,   369,   370,   374,
     377,   379,   384,   388,   390,   392,   393,   394,   395,   396,
     397,   401,   402,   404,   406,   409,   411,   413,   415,   417,
     419,   421,   423,   425,   427,   429,   431,   433,   435,   437,
     439,   441,   443,   445,   447,   449,   451,   453,   455,   457,
     459,   461,   463,   465,   467,   469,   471,   473,   475,   477,
     479,   481,   483,   485,   487,   489,   491,   493,   495,   497,
     499,   501,   503,   505,   507,   509,   511,   513,   515,   517,
     519,   521,   523
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     122,     0,    -1,   123,   126,   125,    -1,    -1,   123,   124,
      -1,   114,    78,    43,    -1,   114,   110,    48,    -1,   114,
     110,   108,    -1,   114,   110,   107,    -1,    -1,   115,    -1,
     127,    24,   148,   189,    46,   200,    -1,   199,    -1,   199,
     128,    -1,   199,   128,   129,    -1,    39,    -1,   129,   130,
      -1,   130,    -1,   131,    -1,    39,    -1,    17,   202,    18,
      -1,   140,   141,   142,   143,   144,   145,    -1,   140,    20,
      54,   139,   115,    -1,    -1,   140,   133,    36,   132,   135,
     138,   134,    -1,    -1,    73,    97,    -1,    97,    -1,    -1,
      -1,   116,   136,   117,    -1,   137,    -1,   136,   118,   137,
      -1,   140,   142,    -1,    65,    -1,    54,    -1,    14,    -1,
     203,    -1,    15,    -1,    14,    -1,   203,    -1,    -1,    31,
      -1,    -1,    -1,    28,    14,    -1,    28,   203,    -1,    28,
      15,    -1,    -1,    74,    76,    -1,   115,    -1,   146,    -1,
     147,    -1,    40,    -1,   119,    -1,    13,    -1,    -1,   149,
      -1,   149,   150,    -1,   150,    -1,   126,   115,    -1,   152,
      -1,   160,    -1,   163,    -1,   168,    -1,   169,    -1,   170,
      -1,   173,    -1,   175,    -1,   177,    -1,   178,    -1,   180,
      -1,   181,    -1,   151,    -1,   153,    -1,   182,    -1,   183,
      -1,   184,    -1,   186,    -1,   187,    -1,    80,   195,    -1,
     159,   147,   195,    -1,    58,   154,    42,   155,   115,    -1,
      -1,    35,    -1,   100,    -1,   155,   118,   156,    -1,   156,
      -1,   158,   147,   157,    -1,    -1,    16,    -1,    14,    -1,
      15,    -1,    16,    -1,   159,   120,   196,    -1,    60,   197,
     148,   161,   162,    46,    60,   115,    -1,    -1,   161,    45,
     197,   148,    -1,    -1,    44,   148,    -1,    26,   164,   165,
     167,    46,    26,   115,    -1,    -1,   165,   166,    -1,   166,
      -1,   112,   197,   148,    -1,    -1,    44,   148,    -1,   199,
      68,   179,    -1,   199,   113,   198,   179,    -1,   199,    54,
     171,   179,    -1,   172,    61,    -1,    16,    -1,    14,    -1,
      15,    -1,   199,    55,   172,   174,    61,    22,   198,   179,
      -1,    -1,    98,     9,    -1,   176,   200,   201,    -1,    51,
      -1,    34,    -1,    90,    -1,    87,    -1,   148,    46,    68,
     200,   115,    -1,    63,    -1,    14,    -1,    15,    -1,    50,
      -1,    77,   188,    -1,    52,   185,   188,    64,    -1,    71,
     185,   188,   115,    -1,    -1,    27,   188,   115,    -1,    76,
     115,    -1,    16,    -1,    14,    -1,    15,    -1,    -1,    -1,
      49,   190,   191,    -1,   191,   192,    -1,   192,    -1,   112,
     193,   104,   148,    -1,   193,    79,   194,    -1,   194,    -1,
     202,    -1,    -1,    -1,    -1,    -1,    -1,    17,   202,    18,
      -1,    -1,   202,    -1,   115,    -1,   112,   195,    -1,    14,
      -1,   203,    -1,    16,    -1,    19,    -1,    20,    -1,    22,
      -1,    23,    -1,    29,    -1,    30,    -1,    31,    -1,    32,
      -1,    33,    -1,    35,    -1,    36,    -1,    37,    -1,    38,
      -1,    41,    -1,    43,    -1,    47,    -1,    48,    -1,    53,
      -1,    56,    -1,    59,    -1,    62,    -1,    65,    -1,    66,
      -1,    67,    -1,    69,    -1,    70,    -1,    72,    -1,    73,
      -1,    75,    -1,    78,    -1,    81,    -1,    82,    -1,    83,
      -1,    84,    -1,    85,    -1,    86,    -1,    88,    -1,    89,
      -1,    91,    -1,    92,    -1,    94,    -1,    93,    -1,    95,
      -1,    96,    -1,    97,    -1,    98,    -1,    99,    -1,   100,
      -1,   102,    -1,   103,    -1,   106,    -1,   107,    -1,   108,
      -1,   110,    -1,   111,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   342,   342,   348,   349,   352,   356,   360,   364,   370,
     371,   374,   396,   404,   411,   420,   432,   433,   436,   437,
     441,   454,   509,   515,   514,   567,   570,   574,   581,   587,
     590,   619,   623,   629,   637,   638,   640,   655,   670,   698,
     711,   727,   728,   733,   744,   745,   750,   755,   762,   763,
     767,   769,   775,   776,   779,   780,   784,   785,   789,   796,
     805,   807,   809,   811,   813,   815,   817,   819,   821,   823,
     825,   827,   829,   831,   833,   835,   837,   839,   841,   843,
     847,   860,   874,   934,   937,   941,   947,   951,   957,   970,
    1014,  1026,  1031,  1039,  1044,  1061,  1078,  1081,  1095,  1098,
    1104,  1111,  1125,  1129,  1135,  1147,  1150,  1165,  1182,  1200,
    1234,  1496,  1528,  1543,  1550,  1593,  1596,  1602,  1617,  1621,
    1627,  1653,  1795,  1813,  1817,  1827,  1839,  1903,  1980,  2012,
    2025,  2030,  2043,  2050,  2066,  2071,  2079,  2081,  2080,  2120,
    2124,  2130,  2143,  2152,  2158,  2195,  2199,  2203,  2207,  2211,
    2215,  2223,  2226,  2234,  2236,  2243,  2247,  2251,  2260,  2261,
    2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,  2270,  2271,
    2272,  2273,  2274,  2275,  2276,  2277,  2278,  2279,  2280,  2281,
    2282,  2283,  2284,  2285,  2286,  2287,  2288,  2289,  2290,  2291,
    2292,  2293,  2294,  2295,  2296,  2297,  2298,  2299,  2300,  2301,
    2302,  2303,  2304,  2305,  2306,  2307,  2308,  2309,  2310,  2311,
    2312,  2313,  2314
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "FCONST", "SCONST", "BCONST",
  "XCONST", "Op", "ICONST", "PARAM", "TYPECAST", "DOT_DOT", "COLON_EQUALS",
  "T_WORD", "T_CWORD", "T_DATUM", "LESS_LESS", "GREATER_GREATER",
  "K_ABSOLUTE", "K_ALIAS", "K_ALL", "K_ARRAY", "K_BACKWARD", "K_BEGIN",
  "K_BY", "K_CASE", "K_CLOSE", "K_COLLATE", "K_COLUMN", "K_COLUMN_NAME",
  "K_CONSTANT", "K_CONSTRAINT", "K_CONSTRAINT_NAME", "K_CONTINUE",
  "K_CURRENT", "K_CURSOR", "K_DATATYPE", "K_DEBUG", "K_DECLARE",
  "K_DEFAULT", "K_DETAIL", "K_DIAGNOSTICS", "K_DUMP", "K_ELSE", "K_ELSIF",
  "K_END", "K_ERRCODE", "K_ERROR", "K_EXCEPTION", "K_EXECUTE", "K_EXIT",
  "K_FETCH", "K_FIRST", "K_FOR", "K_FOREACH", "K_FORWARD", "K_FROM",
  "K_GET", "K_HINT", "K_IF", "K_IN", "K_INFO", "K_INSERT", "K_INTO",
  "K_IS", "K_LAST", "K_LOG", "K_LOOP", "K_MESSAGE", "K_MESSAGE_TEXT",
  "K_MOVE", "K_NEXT", "K_NO", "K_NOT", "K_NOTICE", "K_NULL", "K_OPEN",
  "K_OPTION", "K_OR", "K_PERFORM", "K_PG_DATATYPE_NAME",
  "K_PG_EXCEPTION_CONTEXT", "K_PG_EXCEPTION_DETAIL", "K_PG_EXCEPTION_HINT",
  "K_PRIOR", "K_QUERY", "K_RAISE", "K_RELATIVE", "K_RESULT_OID",
  "K_RETURN", "K_RETURNED_SQLSTATE", "K_REVERSE", "K_ROWTYPE",
  "K_ROW_COUNT", "K_SCHEMA", "K_SCHEMA_NAME", "K_SCROLL", "K_SLICE",
  "K_SQLSTATE", "K_STACKED", "K_STRICT", "K_TABLE", "K_TABLE_NAME",
  "K_THEN", "K_TO", "K_TYPE", "K_USE_COLUMN", "K_USE_VARIABLE", "K_USING",
  "K_VARIABLE_CONFLICT", "K_WARNING", "K_WHEN", "K_WHILE", "'#'", "';'",
  "'('", "')'", "','", "'='", "'['", "$accept", "pl_function",
  "comp_options", "comp_option", "opt_semi", "pl_block", "decl_sect",
  "decl_start", "decl_stmts", "decl_stmt", "decl_statement", "$@1",
  "opt_scrollable", "decl_cursor_query", "decl_cursor_args",
  "decl_cursor_arglist", "decl_cursor_arg", "decl_is_for",
  "decl_aliasitem", "decl_varname", "decl_const", "decl_datatype",
  "decl_collate", "decl_notnull", "decl_defval", "decl_defkey",
  "assign_operator", "proc_sect", "proc_stmts", "proc_stmt",
  "stmt_perform", "stmt_assign", "stmt_getdiag", "getdiag_area_opt",
  "getdiag_list", "getdiag_list_item", "getdiag_item", "getdiag_target",
  "assign_var", "stmt_if", "stmt_elsifs", "stmt_else", "stmt_case",
  "opt_expr_until_when", "case_when_list", "case_when", "opt_case_else",
  "stmt_loop", "stmt_while", "stmt_for", "for_control", "for_variable",
  "stmt_foreach_a", "foreach_slice", "stmt_exit", "exit_type",
  "stmt_return", "stmt_raise", "loop_body", "stmt_execsql",
  "stmt_dynexecute", "stmt_open", "stmt_fetch", "stmt_move",
  "opt_fetch_direction", "stmt_close", "stmt_null", "cursor_variable",
  "exception_sect", "@2", "proc_exceptions", "proc_exception",
  "proc_conditions", "proc_condition", "expr_until_semi",
  "expr_until_rightbracket", "expr_until_then", "expr_until_loop",
  "opt_block_label", "opt_label", "opt_exitcond", "any_identifier",
  "unreserved_keyword", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,    35,    59,    40,    41,    44,    61,
      91
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   121,   122,   123,   123,   124,   124,   124,   124,   125,
     125,   126,   127,   127,   127,   128,   129,   129,   130,   130,
     130,   131,   131,   132,   131,   133,   133,   133,   134,   135,
     135,   136,   136,   137,   138,   138,   139,   139,   139,   140,
     140,   141,   141,   142,   143,   143,   143,   143,   144,   144,
     145,   145,   146,   146,   147,   147,   148,   148,   149,   149,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     151,   152,   153,   154,   154,   154,   155,   155,   156,   157,
     158,   158,   158,   159,   159,   160,   161,   161,   162,   162,
     163,   164,   165,   165,   166,   167,   167,   168,   169,   170,
     171,   172,   172,   172,   173,   174,   174,   175,   176,   176,
     177,   178,   179,   180,   180,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   188,   188,   189,   190,   189,   191,
     191,   192,   193,   193,   194,   195,   196,   197,   198,   199,
     199,   200,   200,   201,   201,   202,   202,   202,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     2,     3,     3,     3,     3,     0,
       1,     6,     1,     2,     3,     1,     2,     1,     1,     1,
       3,     6,     5,     0,     7,     0,     2,     1,     0,     0,
       3,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     0,     0,     2,     2,     2,     0,     2,
       1,     1,     1,     1,     1,     1,     0,     1,     2,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     5,     0,     1,     1,     3,     1,     3,     0,
       1,     1,     1,     1,     3,     8,     0,     4,     0,     2,
       7,     0,     2,     1,     3,     0,     2,     3,     4,     4,
       2,     1,     1,     1,     8,     0,     2,     3,     1,     1,
       1,     1,     5,     1,     1,     1,     1,     2,     4,     4,
       0,     3,     2,     1,     1,     1,     0,     0,     3,     2,
       1,     4,     3,     1,     1,     0,     0,     0,     0,     0,
       3,     0,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,   149,     1,     0,     0,     4,     9,     0,    12,
     155,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   199,   198,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,     0,   156,     0,
       0,    10,     2,   149,    15,    13,   150,     5,     6,     8,
       7,   124,   125,    93,   101,     0,   119,   126,   118,   130,
      83,   147,   123,   130,     0,     0,   145,   121,   120,     0,
     136,   149,    59,    73,    61,    74,     0,    62,    63,    64,
      65,    66,    67,    68,   151,    69,    70,    71,    72,    75,
      76,    77,    78,    79,    12,    39,     0,    19,    14,    17,
      18,    41,    40,     0,   134,   135,   133,     0,     0,    84,
      85,     0,   149,     0,   132,   127,    80,    60,   137,     0,
      58,    55,    54,   146,   145,     0,   152,     0,     0,   149,
     148,     0,    16,     0,    42,     0,    27,     0,    43,   147,
     105,   103,   131,     0,     0,    96,     0,     0,   151,    94,
      81,   145,   153,   117,   112,   113,   111,   149,     0,   115,
       0,   107,   149,    20,     0,    26,    23,    44,   149,   149,
     102,     0,   128,    91,    92,    90,     0,    87,     0,    98,
     129,     0,   138,   140,    11,   154,   109,   110,     0,     0,
       0,   108,    36,    38,     0,    37,    29,     0,    48,   104,
     106,     0,    82,     0,    89,   149,   147,     0,     0,   143,
     144,   139,   116,     0,   151,    22,     0,     0,    45,    47,
      46,     0,     0,     0,    86,    88,    99,   149,     0,     0,
     149,   148,     0,     0,    31,    43,    35,    34,    28,    49,
      53,    50,    21,    51,    52,   100,    97,     0,   142,   141,
     149,   122,    30,     0,    33,    24,    95,   114,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    72,    99,     8,    75,   128,   129,
     130,   226,   167,   285,   247,   263,   264,   268,   224,   131,
     168,   197,   228,   252,   272,   273,   154,   190,   101,   102,
     103,   104,   105,   141,   206,   207,   255,   208,   106,   107,
     209,   237,   108,   133,   170,   171,   201,   109,   110,   111,
     187,   188,   112,   219,   113,   114,   115,   116,   191,   117,
     118,   119,   120,   121,   138,   122,   123,   137,   149,   177,
     212,   213,   238,   239,   146,   179,   142,   192,   124,   155,
     183,   156,    68
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -226
static const yytype_int16 yypact[] =
{
    -226,    26,   -13,  -226,   342,   -44,  -226,   -75,    33,    21,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,    45,  -226,    40,
     -34,  -226,  -226,   746,  -226,   244,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,    53,  -226,  -226,  -226,  -226,
     -16,  -226,  -226,  -226,   -30,    53,  -226,  -226,  -226,   -28,
      41,     1,  -226,  -226,  -226,  -226,   -10,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,   342,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,   -31,  -226,   342,  -226,   244,  -226,
    -226,   -11,  -226,   -23,  -226,  -226,  -226,   -17,    53,  -226,
    -226,    57,   731,    53,  -226,  -226,  -226,  -226,  -226,    56,
    -226,  -226,  -226,  -226,  -226,   -76,  -226,    78,    78,   798,
    -226,    90,  -226,    60,  -226,    20,  -226,    82,  -226,  -226,
     -33,  -226,  -226,    55,    81,  -226,     6,    12,   342,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,   798,    64,    28,
      83,  -226,   798,  -226,   440,  -226,  -226,   102,    89,   798,
    -226,    85,  -226,  -226,  -226,  -226,   -77,  -226,    -7,    -2,
    -226,   342,    12,  -226,  -226,  -226,  -226,  -226,   123,    73,
      68,  -226,  -226,  -226,    22,  -226,    27,   538,    70,  -226,
    -226,   112,  -226,    81,  -226,   798,  -226,    96,   -49,  -226,
    -226,  -226,  -226,   124,   342,  -226,   633,   -21,  -226,  -226,
    -226,    69,    -8,    35,  -226,  -226,  -226,   731,    88,   342,
     166,  -226,    36,   -69,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,    39,  -226,  -226,
     798,  -226,  -226,   633,  -226,  -226,  -226,  -226,  -226
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,  -226,  -226,  -226,   153,  -226,  -226,  -226,    29,
    -226,  -226,  -226,  -226,  -226,  -226,  -127,  -226,  -226,  -225,
    -226,  -107,  -226,  -226,  -226,  -226,  -177,   -71,  -226,    58,
    -226,  -226,  -226,  -226,  -226,   -72,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,    -3,  -226,  -226,  -226,  -226,
    -226,     4,  -226,  -226,  -226,  -226,  -226,  -226,  -180,  -226,
    -226,  -226,  -226,  -226,    75,  -226,  -226,   -73,  -226,  -226,
    -226,   -42,  -226,   -96,  -125,  -226,  -156,   -90,   171,  -168,
    -226,    -4,   -74
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -58
static const yytype_int16 yytable[] =
{
      67,   132,   100,   151,     4,   151,   151,   216,    74,   163,
     214,   199,   221,   198,    78,    81,    82,    83,     4,   139,
     164,   265,   145,   157,   158,   -25,     3,    84,    85,   180,
     259,   234,   270,   266,    69,    86,   181,   159,   232,   182,
      71,   233,   235,   236,   267,   -57,   -57,   -57,   282,   283,
     -57,    87,    88,    89,   132,   260,   215,    73,   265,    90,
      74,    91,   165,    76,    92,   173,    70,   134,   135,   136,
     176,   175,    93,    79,    80,   274,   262,    94,    95,   169,
     257,    96,   160,    77,   140,   144,   166,   147,    97,   169,
     148,    98,   184,   185,   186,   203,   204,   205,   172,   174,
     287,     5,   178,    81,    82,    83,     4,   271,   193,   152,
     153,   152,   152,   -57,   194,    84,    85,   195,   196,   202,
     225,   210,   161,    86,   211,   217,   218,   229,   230,   220,
     227,   231,   242,   -56,   243,   -56,   244,   245,   253,    87,
      88,    89,   258,   246,   251,   269,   261,    90,   277,    91,
     275,   281,    92,   250,   286,     7,   288,   162,   284,   150,
      93,   254,   189,   278,   256,    94,    95,   200,   143,    96,
     241,   280,   132,     9,     0,     0,    97,     0,     0,    98,
      81,    82,    83,     4,     0,     0,   276,     0,     0,   279,
       0,     0,    84,    85,     0,     0,     0,     0,     0,     0,
      86,   -56,     0,     0,     0,     0,     0,   240,     0,   132,
       0,     0,   -56,     0,     0,     0,    87,    88,    89,     0,
       0,     0,     0,     0,    90,     0,    91,     0,     0,    92,
       0,     0,     0,     0,     0,     0,     0,    93,     0,     0,
       0,     0,    94,    95,     0,     0,    96,     0,     0,     0,
       0,     0,     0,    97,     0,   240,    98,     0,   125,     0,
       0,   126,     0,    12,    13,     0,    14,    15,     0,     0,
       0,     0,     0,    16,    17,    18,    19,    20,   -56,    21,
      22,    23,    24,   127,     0,    25,     0,    26,     0,     0,
       0,    27,    28,     0,     0,     0,     0,    29,     0,     0,
      30,     0,     0,    31,     0,     0,    32,     0,     0,    33,
      34,    35,     0,    36,    37,     0,    38,    39,     0,    40,
       0,     0,    41,     0,     0,    42,    43,    44,    45,    46,
      47,     0,    48,    49,     0,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,     0,    60,    61,     0,     0,
      62,    63,    64,     0,    65,    66,    10,     0,    11,     0,
       0,    12,    13,     0,    14,    15,     0,     0,     0,     0,
       0,    16,    17,    18,    19,    20,     0,    21,    22,    23,
      24,     0,     0,    25,     0,    26,     0,     0,     0,    27,
      28,     0,     0,     0,     0,    29,     0,     0,    30,     0,
       0,    31,     0,     0,    32,     0,     0,    33,    34,    35,
       0,    36,    37,     0,    38,    39,     0,    40,     0,     0,
      41,     0,     0,    42,    43,    44,    45,    46,    47,     0,
      48,    49,     0,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,     0,    60,    61,     0,     0,    62,    63,
      64,     0,    65,    66,   222,   223,     0,     0,     0,    12,
      13,     0,    14,    15,     0,     0,     0,     0,     0,    16,
      17,    18,    19,    20,     0,    21,    22,    23,    24,     0,
       0,    25,     0,    26,     0,     0,     0,    27,    28,     0,
       0,     0,     0,    29,     0,     0,    30,     0,     0,    31,
       0,     0,    32,     0,     0,    33,    34,    35,     0,    36,
      37,     0,    38,    39,     0,    40,     0,     0,    41,     0,
       0,    42,    43,    44,    45,    46,    47,     0,    48,    49,
       0,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,     0,    60,    61,     0,     0,    62,    63,    64,     0,
      65,    66,   248,   249,     0,     0,     0,    12,    13,     0,
      14,    15,     0,     0,     0,     0,     0,    16,    17,    18,
      19,    20,     0,    21,    22,    23,    24,     0,     0,    25,
       0,    26,     0,     0,     0,    27,    28,     0,     0,     0,
       0,    29,     0,     0,    30,     0,     0,    31,     0,     0,
      32,     0,     0,    33,    34,    35,     0,    36,    37,     0,
      38,    39,     0,    40,     0,     0,    41,     0,     0,    42,
      43,    44,    45,    46,    47,     0,    48,    49,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     0,
      60,    61,     0,     0,    62,    63,    64,   125,    65,    66,
       0,     0,    12,    13,     0,    14,    15,     0,     0,     0,
       0,     0,    16,    17,    18,    19,    20,     0,    21,    22,
      23,    24,     0,     0,    25,     0,    26,     0,     0,     0,
      27,    28,     0,     0,     0,     0,    29,     0,     0,    30,
       0,     0,    31,     0,     0,    32,     0,     0,    33,    34,
      35,     0,    36,    37,     0,    38,    39,     0,    40,     0,
       0,    41,     0,     0,    42,    43,    44,    45,    46,    47,
       0,    48,    49,     0,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     0,    60,    61,     0,     0,    62,
      63,    64,     0,    65,    66,    81,    82,    83,     4,     0,
       0,     0,     0,     0,     0,     0,     0,    84,    85,     0,
      81,    82,    83,     4,     0,    86,     0,     0,     0,     0,
       0,     0,    84,    85,     0,   -56,   -56,   -56,     0,     0,
      86,    87,    88,    89,     0,     0,     0,     0,     0,    90,
       0,    91,   -56,     0,    92,   -56,    87,    88,    89,     0,
       0,     0,    93,     0,    90,     0,    91,    94,    95,    92,
       0,    96,    81,    82,    83,     4,     0,    93,    97,     0,
       0,    98,    94,    95,    84,    85,    96,     0,     0,     0,
       0,     0,    86,    97,     0,     0,    98,     0,     0,     0,
       0,     0,     0,     0,   -56,     0,     0,     0,    87,    88,
      89,     0,     0,     0,     0,     0,    90,     0,    91,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,    93,
       0,     0,     0,     0,    94,    95,     0,     0,    96,     0,
       0,     0,     0,     0,     0,    97,     0,     0,    98
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-226)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       4,    75,    73,    13,    17,    13,    13,   187,    39,    20,
     178,    44,   192,   169,    48,    14,    15,    16,    17,    35,
      31,   246,    95,    54,    55,    36,     0,    26,    27,   154,
      79,   208,    40,    54,    78,    34,   112,    68,   115,   115,
     115,   118,    44,    45,    65,    44,    45,    46,   117,   118,
      49,    50,    51,    52,   128,   104,   181,    24,   283,    58,
      39,    60,    73,    18,    63,   138,   110,    14,    15,    16,
     143,   142,    71,   107,   108,   252,   244,    76,    77,   112,
     236,    80,   113,    43,   100,   115,    97,   115,    87,   112,
      49,    90,    14,    15,    16,    14,    15,    16,   115,    42,
     280,   114,    46,    14,    15,    16,    17,   115,    18,   119,
     120,   119,   119,   112,    54,    26,    27,    97,    36,    64,
     194,   115,   126,    34,   112,    61,    98,   198,   199,    46,
      28,    46,     9,    44,    61,    46,    68,   115,    26,    50,
      51,    52,    46,   116,    74,    76,    22,    58,    60,    60,
     115,   115,    63,   227,   115,     2,   283,   128,   265,   101,
      71,   233,   158,   259,   235,    76,    77,   170,    93,    80,
     212,   261,   246,     2,    -1,    -1,    87,    -1,    -1,    90,
      14,    15,    16,    17,    -1,    -1,   257,    -1,    -1,   260,
      -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      34,   112,    -1,    -1,    -1,    -1,    -1,   211,    -1,   283,
      -1,    -1,    46,    -1,    -1,    -1,    50,    51,    52,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    60,    -1,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    -1,    76,    77,    -1,    -1,    80,    -1,    -1,    -1,
      -1,    -1,    -1,    87,    -1,   259,    90,    -1,    14,    -1,
      -1,    17,    -1,    19,    20,    -1,    22,    23,    -1,    -1,
      -1,    -1,    -1,    29,    30,    31,    32,    33,   112,    35,
      36,    37,    38,    39,    -1,    41,    -1,    43,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      56,    -1,    -1,    59,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    69,    70,    -1,    72,    73,    -1,    75,
      -1,    -1,    78,    -1,    -1,    81,    82,    83,    84,    85,
      86,    -1,    88,    89,    -1,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    -1,   102,   103,    -1,    -1,
     106,   107,   108,    -1,   110,   111,    14,    -1,    16,    -1,
      -1,    19,    20,    -1,    22,    23,    -1,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    -1,    35,    36,    37,
      38,    -1,    -1,    41,    -1,    43,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    53,    -1,    -1,    56,    -1,
      -1,    59,    -1,    -1,    62,    -1,    -1,    65,    66,    67,
      -1,    69,    70,    -1,    72,    73,    -1,    75,    -1,    -1,
      78,    -1,    -1,    81,    82,    83,    84,    85,    86,    -1,
      88,    89,    -1,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    -1,   102,   103,    -1,    -1,   106,   107,
     108,    -1,   110,   111,    14,    15,    -1,    -1,    -1,    19,
      20,    -1,    22,    23,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    -1,    35,    36,    37,    38,    -1,
      -1,    41,    -1,    43,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    56,    -1,    -1,    59,
      -1,    -1,    62,    -1,    -1,    65,    66,    67,    -1,    69,
      70,    -1,    72,    73,    -1,    75,    -1,    -1,    78,    -1,
      -1,    81,    82,    83,    84,    85,    86,    -1,    88,    89,
      -1,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    -1,   102,   103,    -1,    -1,   106,   107,   108,    -1,
     110,   111,    14,    15,    -1,    -1,    -1,    19,    20,    -1,
      22,    23,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    -1,    35,    36,    37,    38,    -1,    -1,    41,
      -1,    43,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    56,    -1,    -1,    59,    -1,    -1,
      62,    -1,    -1,    65,    66,    67,    -1,    69,    70,    -1,
      72,    73,    -1,    75,    -1,    -1,    78,    -1,    -1,    81,
      82,    83,    84,    85,    86,    -1,    88,    89,    -1,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    -1,
     102,   103,    -1,    -1,   106,   107,   108,    14,   110,   111,
      -1,    -1,    19,    20,    -1,    22,    23,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    -1,    35,    36,
      37,    38,    -1,    -1,    41,    -1,    43,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    53,    -1,    -1,    56,
      -1,    -1,    59,    -1,    -1,    62,    -1,    -1,    65,    66,
      67,    -1,    69,    70,    -1,    72,    73,    -1,    75,    -1,
      -1,    78,    -1,    -1,    81,    82,    83,    84,    85,    86,
      -1,    88,    89,    -1,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,    -1,   102,   103,    -1,    -1,   106,
     107,   108,    -1,   110,   111,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,
      14,    15,    16,    17,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    -1,    44,    45,    46,    -1,    -1,
      34,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    60,    46,    -1,    63,    49,    50,    51,    52,    -1,
      -1,    -1,    71,    -1,    58,    -1,    60,    76,    77,    63,
      -1,    80,    14,    15,    16,    17,    -1,    71,    87,    -1,
      -1,    90,    76,    77,    26,    27,    80,    -1,    -1,    -1,
      -1,    -1,    34,    87,    -1,    -1,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      52,    -1,    -1,    -1,    -1,    -1,    58,    -1,    60,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    87,    -1,    -1,    90
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   122,   123,     0,    17,   114,   124,   126,   127,   199,
      14,    16,    19,    20,    22,    23,    29,    30,    31,    32,
      33,    35,    36,    37,    38,    41,    43,    47,    48,    53,
      56,    59,    62,    65,    66,    67,    69,    70,    72,    73,
      75,    78,    81,    82,    83,    84,    85,    86,    88,    89,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     102,   103,   106,   107,   108,   110,   111,   202,   203,    78,
     110,   115,   125,    24,    39,   128,    18,    43,    48,   107,
     108,    14,    15,    16,    26,    27,    34,    50,    51,    52,
      58,    60,    63,    71,    76,    77,    80,    87,    90,   126,
     148,   149,   150,   151,   152,   153,   159,   160,   163,   168,
     169,   170,   173,   175,   176,   177,   178,   180,   181,   182,
     183,   184,   186,   187,   199,    14,    17,    39,   129,   130,
     131,   140,   203,   164,    14,    15,    16,   188,   185,    35,
     100,   154,   197,   185,   115,   188,   195,   115,    49,   189,
     150,    13,   119,   120,   147,   200,   202,    54,    55,    68,
     113,   202,   130,    20,    31,    73,    97,   133,   141,   112,
     165,   166,   115,   188,    42,   148,   188,   190,    46,   196,
     195,   112,   115,   201,    14,    15,    16,   171,   172,   172,
     148,   179,   198,    18,    54,    97,    36,   142,   197,    44,
     166,   167,    64,    14,    15,    16,   155,   156,   158,   161,
     115,   112,   191,   192,   200,   195,   179,    61,    98,   174,
      46,   179,    14,    15,   139,   203,   132,    28,   143,   148,
     148,    46,   115,   118,   147,    44,    45,   162,   193,   194,
     202,   192,     9,    61,    68,   115,   116,   135,    14,    15,
     203,    74,   144,    26,   156,   157,   148,   197,    46,    79,
     104,    22,   200,   136,   137,   140,    54,    65,   138,    76,
      40,   115,   145,   146,   147,   115,   148,    60,   194,   148,
     198,   115,   117,   118,   142,   134,   115,   179,   137
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 343 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_parse_result = (PLpgSQL_stmt_block *) (yyvsp[(2) - (3)].stmt);
					}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 353 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_DumpExecTree = true;
					}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 357 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_curr_compile->resolve_option = PLPGSQL_RESOLVE_ERROR;
					}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 361 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_curr_compile->resolve_option = PLPGSQL_RESOLVE_VARIABLE;
					}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 365 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_curr_compile->resolve_option = PLPGSQL_RESOLVE_COLUMN;
					}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 375 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_block *new;

						new = palloc0(sizeof(PLpgSQL_stmt_block));

						new->cmd_type	= PLPGSQL_STMT_BLOCK;
						new->lineno		= plpgsql_location_to_lineno((yylsp[(2) - (6)]));
						new->label		= (yyvsp[(1) - (6)].declhdr).label;
						new->n_initvars = (yyvsp[(1) - (6)].declhdr).n_initvars;
						new->initvarnos = (yyvsp[(1) - (6)].declhdr).initvarnos;
						new->body		= (yyvsp[(3) - (6)].list);
						new->exceptions	= (yyvsp[(4) - (6)].exception_block);

						check_labels((yyvsp[(1) - (6)].declhdr).label, (yyvsp[(6) - (6)].str), (yylsp[(6) - (6)]));
						plpgsql_ns_pop();

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 397 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* done with decls, so resume identifier lookup */
						plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[(1) - (1)].str);
						(yyval.declhdr).n_initvars = 0;
						(yyval.declhdr).initvarnos = NULL;
					}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 405 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[(1) - (2)].str);
						(yyval.declhdr).n_initvars = 0;
						(yyval.declhdr).initvarnos = NULL;
					}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 412 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
						(yyval.declhdr).label	  = (yyvsp[(1) - (3)].str);
						/* Remember variables declared in decl_stmts */
						(yyval.declhdr).n_initvars = plpgsql_add_initdatums(&((yyval.declhdr).initvarnos));
					}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 421 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* Forget any variables created before block */
						plpgsql_add_initdatums(NULL);
						/*
						 * Disable scanner lookup of identifiers while
						 * we process the decl_stmts
						 */
						plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_DECLARE;
					}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 438 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* We allow useless extra DECLAREs */
					}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 442 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/*
						 * Throw a helpful error if user tries to put block
						 * label just before BEGIN, instead of before DECLARE.
						 */
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("block label must be placed before DECLARE, not after"),
								 parser_errposition((yylsp[(1) - (3)]))));
					}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 455 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_variable	*var;

						/*
						 * If a collation is supplied, insert it into the
						 * datatype.  We assume decl_datatype always returns
						 * a freshly built struct not shared with other
						 * variables.
						 */
						if (OidIsValid((yyvsp[(4) - (6)].oid)))
						{
							if (!OidIsValid((yyvsp[(3) - (6)].dtype)->collation))
								ereport(ERROR,
										(errcode(ERRCODE_DATATYPE_MISMATCH),
										 errmsg("collations are not supported by type %s",
												format_type_be((yyvsp[(3) - (6)].dtype)->typoid)),
										 parser_errposition((yylsp[(4) - (6)]))));
							(yyvsp[(3) - (6)].dtype)->collation = (yyvsp[(4) - (6)].oid);
						}

						var = plpgsql_build_variable((yyvsp[(1) - (6)].varname).name, (yyvsp[(1) - (6)].varname).lineno,
													 (yyvsp[(3) - (6)].dtype), true);
						if ((yyvsp[(2) - (6)].boolean))
						{
							if (var->dtype == PLPGSQL_DTYPE_VAR)
								((PLpgSQL_var *) var)->isconst = (yyvsp[(2) - (6)].boolean);
							else
								ereport(ERROR,
										(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
										 errmsg("row or record variable cannot be CONSTANT"),
										 parser_errposition((yylsp[(2) - (6)]))));
						}
						if ((yyvsp[(5) - (6)].boolean))
						{
							if (var->dtype == PLPGSQL_DTYPE_VAR)
								((PLpgSQL_var *) var)->notnull = (yyvsp[(5) - (6)].boolean);
							else
								ereport(ERROR,
										(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
										 errmsg("row or record variable cannot be NOT NULL"),
										 parser_errposition((yylsp[(4) - (6)]))));

						}
						if ((yyvsp[(6) - (6)].expr) != NULL)
						{
							if (var->dtype == PLPGSQL_DTYPE_VAR)
								((PLpgSQL_var *) var)->default_val = (yyvsp[(6) - (6)].expr);
							else
								ereport(ERROR,
										(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
										 errmsg("default value for row or record variable is not supported"),
										 parser_errposition((yylsp[(5) - (6)]))));
						}
					}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 510 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_ns_additem((yyvsp[(4) - (5)].nsitem)->itemtype,
										   (yyvsp[(4) - (5)].nsitem)->itemno, (yyvsp[(1) - (5)].varname).name);
					}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 515 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { plpgsql_ns_push((yyvsp[(1) - (3)].varname).name); }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 517 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_var *new;
						PLpgSQL_expr *curname_def;
						char		buf[1024];
						char		*cp1;
						char		*cp2;

						/* pop local namespace for cursor args */
						plpgsql_ns_pop();

						new = (PLpgSQL_var *)
							plpgsql_build_variable((yyvsp[(1) - (7)].varname).name, (yyvsp[(1) - (7)].varname).lineno,
												   plpgsql_build_datatype(REFCURSOROID,
																		  -1,
																		  InvalidOid),
												   true);

						curname_def = palloc0(sizeof(PLpgSQL_expr));

						curname_def->dtype = PLPGSQL_DTYPE_EXPR;
						strcpy(buf, "SELECT ");
						cp1 = new->refname;
						cp2 = buf + strlen(buf);
						/*
						 * Don't trust standard_conforming_strings here;
						 * it might change before we use the string.
						 */
						if (strchr(cp1, '\\') != NULL)
							*cp2++ = ESCAPE_STRING_SYNTAX;
						*cp2++ = '\'';
						while (*cp1)
						{
							if (SQL_STR_DOUBLE(*cp1, true))
								*cp2++ = *cp1;
							*cp2++ = *cp1++;
						}
						strcpy(cp2, "'::pg_catalog.refcursor");
						curname_def->query = pstrdup(buf);
						new->default_val = curname_def;

						new->cursor_explicit_expr = (yyvsp[(7) - (7)].expr);
						if ((yyvsp[(5) - (7)].datum) == NULL)
							new->cursor_explicit_argrow = -1;
						else
							new->cursor_explicit_argrow = (yyvsp[(5) - (7)].datum)->dno;
						new->cursor_options = CURSOR_OPT_FAST_PLAN | (yyvsp[(2) - (7)].ival);
					}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 567 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.ival) = 0;
					}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 571 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.ival) = CURSOR_OPT_NO_SCROLL;
					}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 575 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.ival) = CURSOR_OPT_SCROLL;
					}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 581 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.expr) = read_sql_stmt("");
					}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 587 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.datum) = NULL;
					}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 591 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_row *new;
						int i;
						ListCell *l;

						new = palloc0(sizeof(PLpgSQL_row));
						new->dtype = PLPGSQL_DTYPE_ROW;
						new->lineno = plpgsql_location_to_lineno((yylsp[(1) - (3)]));
						new->rowtupdesc = NULL;
						new->nfields = list_length((yyvsp[(2) - (3)].list));
						new->fieldnames = palloc(new->nfields * sizeof(char *));
						new->varnos = palloc(new->nfields * sizeof(int));

						i = 0;
						foreach (l, (yyvsp[(2) - (3)].list))
						{
							PLpgSQL_variable *arg = (PLpgSQL_variable *) lfirst(l);
							new->fieldnames[i] = arg->refname;
							new->varnos[i] = arg->dno;
							i++;
						}
						list_free((yyvsp[(2) - (3)].list));

						plpgsql_adddatum((PLpgSQL_datum *) new);
						(yyval.datum) = (PLpgSQL_datum *) new;
					}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 620 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = list_make1((yyvsp[(1) - (1)].datum));
					}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 624 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = lappend((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].datum));
					}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 630 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.datum) = (PLpgSQL_datum *)
							plpgsql_build_variable((yyvsp[(1) - (2)].varname).name, (yyvsp[(1) - (2)].varname).lineno,
												   (yyvsp[(2) - (2)].dtype), true);
					}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 641 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_nsitem *nsi;

						nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
												(yyvsp[(1) - (1)].word).ident, NULL, NULL,
												NULL);
						if (nsi == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_UNDEFINED_OBJECT),
									 errmsg("variable \"%s\" does not exist",
											(yyvsp[(1) - (1)].word).ident),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.nsitem) = nsi;
					}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 656 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_nsitem *nsi;

						nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
												(yyvsp[(1) - (1)].keyword), NULL, NULL,
												NULL);
						if (nsi == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_UNDEFINED_OBJECT),
									 errmsg("variable \"%s\" does not exist",
											(yyvsp[(1) - (1)].keyword)),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.nsitem) = nsi;
					}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 671 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_nsitem *nsi;

						if (list_length((yyvsp[(1) - (1)].cword).idents) == 2)
							nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
													strVal(linitial((yyvsp[(1) - (1)].cword).idents)),
													strVal(lsecond((yyvsp[(1) - (1)].cword).idents)),
													NULL,
													NULL);
						else if (list_length((yyvsp[(1) - (1)].cword).idents) == 3)
							nsi = plpgsql_ns_lookup(plpgsql_ns_top(), false,
													strVal(linitial((yyvsp[(1) - (1)].cword).idents)),
													strVal(lsecond((yyvsp[(1) - (1)].cword).idents)),
													strVal(lthird((yyvsp[(1) - (1)].cword).idents)),
													NULL);
						else
							nsi = NULL;
						if (nsi == NULL)
							ereport(ERROR,
									(errcode(ERRCODE_UNDEFINED_OBJECT),
									 errmsg("variable \"%s\" does not exist",
											NameListToString((yyvsp[(1) - (1)].cword).idents)),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.nsitem) = nsi;
					}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 699 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.varname).name = (yyvsp[(1) - (1)].word).ident;
						(yyval.varname).lineno = plpgsql_location_to_lineno((yylsp[(1) - (1)]));
						/*
						 * Check to make sure name isn't already declared
						 * in the current block.
						 */
						if (plpgsql_ns_lookup(plpgsql_ns_top(), true,
											  (yyvsp[(1) - (1)].word).ident, NULL, NULL,
											  NULL) != NULL)
							yyerror("duplicate declaration");
					}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 712 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.varname).name = pstrdup((yyvsp[(1) - (1)].keyword));
						(yyval.varname).lineno = plpgsql_location_to_lineno((yylsp[(1) - (1)]));
						/*
						 * Check to make sure name isn't already declared
						 * in the current block.
						 */
						if (plpgsql_ns_lookup(plpgsql_ns_top(), true,
											  (yyvsp[(1) - (1)].keyword), NULL, NULL,
											  NULL) != NULL)
							yyerror("duplicate declaration");
					}
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 727 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.boolean) = false; }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 729 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.boolean) = true; }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 733 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/*
						 * If there's a lookahead token, read_datatype
						 * should consume it.
						 */
						(yyval.dtype) = read_datatype(yychar);
						yyclearin;
					}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 744 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.oid) = InvalidOid; }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 746 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.oid) = get_collation_oid(list_make1(makeString((yyvsp[(2) - (2)].word).ident)),
											   false);
					}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 751 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.oid) = get_collation_oid(list_make1(makeString(pstrdup((yyvsp[(2) - (2)].keyword)))),
											   false);
					}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 756 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.oid) = get_collation_oid((yyvsp[(2) - (2)].cword).idents, false);
					}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 762 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.boolean) = false; }
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 764 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.boolean) = true; }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 768 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.expr) = NULL; }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 770 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.expr) = read_sql_expression(';', ";");
					}
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 784 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.list) = NIL; }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 786 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.list) = (yyvsp[(1) - (1)].list); }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 790 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
							if ((yyvsp[(2) - (2)].stmt) == NULL)
								(yyval.list) = (yyvsp[(1) - (2)].list);
							else
								(yyval.list) = lappend((yyvsp[(1) - (2)].list), (yyvsp[(2) - (2)].stmt));
						}
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 797 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
							if ((yyvsp[(1) - (1)].stmt) == NULL)
								(yyval.list) = NIL;
							else
								(yyval.list) = list_make1((yyvsp[(1) - (1)].stmt));
						}
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 806 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (2)].stmt); }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 808 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 810 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 812 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 814 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 816 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 818 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 820 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 822 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 824 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 826 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 828 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 830 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 832 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 834 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 836 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 838 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 840 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 842 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 844 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.stmt) = (yyvsp[(1) - (1)].stmt); }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 848 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_perform *new;

						new = palloc0(sizeof(PLpgSQL_stmt_perform));
						new->cmd_type = PLPGSQL_STMT_PERFORM;
						new->lineno   = plpgsql_location_to_lineno((yylsp[(1) - (2)]));
						new->expr  = (yyvsp[(2) - (2)].expr);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 861 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_assign *new;

						new = palloc0(sizeof(PLpgSQL_stmt_assign));
						new->cmd_type = PLPGSQL_STMT_ASSIGN;
						new->lineno   = plpgsql_location_to_lineno((yylsp[(1) - (3)]));
						new->varno = (yyvsp[(1) - (3)].ival);
						new->expr  = (yyvsp[(3) - (3)].expr);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 875 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_getdiag	 *new;
						ListCell		*lc;

						new = palloc0(sizeof(PLpgSQL_stmt_getdiag));
						new->cmd_type = PLPGSQL_STMT_GETDIAG;
						new->lineno   = plpgsql_location_to_lineno((yylsp[(1) - (5)]));
						new->is_stacked = (yyvsp[(2) - (5)].boolean);
						new->diag_items = (yyvsp[(4) - (5)].list);

						/*
						 * Check information items are valid for area option.
						 */
						foreach(lc, new->diag_items)
						{
							PLpgSQL_diag_item *ditem = (PLpgSQL_diag_item *) lfirst(lc);

							switch (ditem->kind)
							{
								/* these fields are disallowed in stacked case */
								case PLPGSQL_GETDIAG_ROW_COUNT:
								case PLPGSQL_GETDIAG_RESULT_OID:
									if (new->is_stacked)
										ereport(ERROR,
												(errcode(ERRCODE_SYNTAX_ERROR),
												 errmsg("diagnostics item %s is not allowed in GET STACKED DIAGNOSTICS",
														plpgsql_getdiag_kindname(ditem->kind)),
												 parser_errposition((yylsp[(1) - (5)]))));
									break;
								/* these fields are disallowed in current case */
								case PLPGSQL_GETDIAG_ERROR_CONTEXT:
								case PLPGSQL_GETDIAG_ERROR_DETAIL:
								case PLPGSQL_GETDIAG_ERROR_HINT:
								case PLPGSQL_GETDIAG_RETURNED_SQLSTATE:
								case PLPGSQL_GETDIAG_COLUMN_NAME:
								case PLPGSQL_GETDIAG_CONSTRAINT_NAME:
								case PLPGSQL_GETDIAG_DATATYPE_NAME:
								case PLPGSQL_GETDIAG_MESSAGE_TEXT:
								case PLPGSQL_GETDIAG_TABLE_NAME:
								case PLPGSQL_GETDIAG_SCHEMA_NAME:
									if (!new->is_stacked)
										ereport(ERROR,
												(errcode(ERRCODE_SYNTAX_ERROR),
												 errmsg("diagnostics item %s is not allowed in GET CURRENT DIAGNOSTICS",
														plpgsql_getdiag_kindname(ditem->kind)),
												 parser_errposition((yylsp[(1) - (5)]))));
									break;
								default:
									elog(ERROR, "unrecognized diagnostic item kind: %d",
										 ditem->kind);
									break;
							}
						}

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 83:
/* Line 1792 of yacc.c  */
#line 934 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.boolean) = false;
					}
    break;

  case 84:
/* Line 1792 of yacc.c  */
#line 938 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.boolean) = false;
					}
    break;

  case 85:
/* Line 1792 of yacc.c  */
#line 942 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.boolean) = true;
					}
    break;

  case 86:
/* Line 1792 of yacc.c  */
#line 948 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = lappend((yyvsp[(1) - (3)].list), (yyvsp[(3) - (3)].diagitem));
					}
    break;

  case 87:
/* Line 1792 of yacc.c  */
#line 952 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = list_make1((yyvsp[(1) - (1)].diagitem));
					}
    break;

  case 88:
/* Line 1792 of yacc.c  */
#line 958 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_diag_item *new;

						new = palloc(sizeof(PLpgSQL_diag_item));
						new->target = (yyvsp[(1) - (3)].ival);
						new->kind = (yyvsp[(3) - (3)].ival);

						(yyval.diagitem) = new;
					}
    break;

  case 89:
/* Line 1792 of yacc.c  */
#line 970 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						int	tok = yylex();

						if (tok_is_keyword(tok, &yylval,
										   K_ROW_COUNT, "row_count"))
							(yyval.ival) = PLPGSQL_GETDIAG_ROW_COUNT;
						else if (tok_is_keyword(tok, &yylval,
												K_RESULT_OID, "result_oid"))
							(yyval.ival) = PLPGSQL_GETDIAG_RESULT_OID;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_DETAIL, "pg_exception_detail"))
							(yyval.ival) = PLPGSQL_GETDIAG_ERROR_DETAIL;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_HINT, "pg_exception_hint"))
							(yyval.ival) = PLPGSQL_GETDIAG_ERROR_HINT;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_EXCEPTION_CONTEXT, "pg_exception_context"))
							(yyval.ival) = PLPGSQL_GETDIAG_ERROR_CONTEXT;
						else if (tok_is_keyword(tok, &yylval,
												K_COLUMN_NAME, "column_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_COLUMN_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_CONSTRAINT_NAME, "constraint_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_CONSTRAINT_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_PG_DATATYPE_NAME, "pg_datatype_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_DATATYPE_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_MESSAGE_TEXT, "message_text"))
							(yyval.ival) = PLPGSQL_GETDIAG_MESSAGE_TEXT;
						else if (tok_is_keyword(tok, &yylval,
												K_TABLE_NAME, "table_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_TABLE_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_SCHEMA_NAME, "schema_name"))
							(yyval.ival) = PLPGSQL_GETDIAG_SCHEMA_NAME;
						else if (tok_is_keyword(tok, &yylval,
												K_RETURNED_SQLSTATE, "returned_sqlstate"))
							(yyval.ival) = PLPGSQL_GETDIAG_RETURNED_SQLSTATE;
						else
							yyerror("unrecognized GET DIAGNOSTICS item");
					}
    break;

  case 90:
/* Line 1792 of yacc.c  */
#line 1015 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						check_assignable((yyvsp[(1) - (1)].wdatum).datum, (yylsp[(1) - (1)]));
						if ((yyvsp[(1) - (1)].wdatum).datum->dtype == PLPGSQL_DTYPE_ROW ||
							(yyvsp[(1) - (1)].wdatum).datum->dtype == PLPGSQL_DTYPE_REC)
							ereport(ERROR,
									(errcode(ERRCODE_SYNTAX_ERROR),
									 errmsg("\"%s\" is not a scalar variable",
											NameOfDatum(&((yyvsp[(1) - (1)].wdatum)))),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.ival) = (yyvsp[(1) - (1)].wdatum).datum->dno;
					}
    break;

  case 91:
/* Line 1792 of yacc.c  */
#line 1027 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* just to give a better message than "syntax error" */
						word_is_not_variable(&((yyvsp[(1) - (1)].word)), (yylsp[(1) - (1)]));
					}
    break;

  case 92:
/* Line 1792 of yacc.c  */
#line 1032 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[(1) - (1)].cword)), (yylsp[(1) - (1)]));
					}
    break;

  case 93:
/* Line 1792 of yacc.c  */
#line 1040 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						check_assignable((yyvsp[(1) - (1)].wdatum).datum, (yylsp[(1) - (1)]));
						(yyval.ival) = (yyvsp[(1) - (1)].wdatum).datum->dno;
					}
    break;

  case 94:
/* Line 1792 of yacc.c  */
#line 1045 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_arrayelem	*new;

						new = palloc0(sizeof(PLpgSQL_arrayelem));
						new->dtype		= PLPGSQL_DTYPE_ARRAYELEM;
						new->subscript	= (yyvsp[(3) - (3)].expr);
						new->arrayparentno = (yyvsp[(1) - (3)].ival);
						/* initialize cached type data to "not valid" */
						new->parenttypoid = InvalidOid;

						plpgsql_adddatum((PLpgSQL_datum *) new);

						(yyval.ival) = new->dno;
					}
    break;

  case 95:
/* Line 1792 of yacc.c  */
#line 1062 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_if *new;

						new = palloc0(sizeof(PLpgSQL_stmt_if));
						new->cmd_type	= PLPGSQL_STMT_IF;
						new->lineno		= plpgsql_location_to_lineno((yylsp[(1) - (8)]));
						new->cond		= (yyvsp[(2) - (8)].expr);
						new->then_body	= (yyvsp[(3) - (8)].list);
						new->elsif_list = (yyvsp[(4) - (8)].list);
						new->else_body  = (yyvsp[(5) - (8)].list);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 96:
/* Line 1792 of yacc.c  */
#line 1078 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = NIL;
					}
    break;

  case 97:
/* Line 1792 of yacc.c  */
#line 1082 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_if_elsif *new;

						new = palloc0(sizeof(PLpgSQL_if_elsif));
						new->lineno = plpgsql_location_to_lineno((yylsp[(2) - (4)]));
						new->cond   = (yyvsp[(3) - (4)].expr);
						new->stmts  = (yyvsp[(4) - (4)].list);

						(yyval.list) = lappend((yyvsp[(1) - (4)].list), new);
					}
    break;

  case 98:
/* Line 1792 of yacc.c  */
#line 1095 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = NIL;
					}
    break;

  case 99:
/* Line 1792 of yacc.c  */
#line 1099 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = (yyvsp[(2) - (2)].list);
					}
    break;

  case 100:
/* Line 1792 of yacc.c  */
#line 1105 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.stmt) = make_case((yylsp[(1) - (7)]), (yyvsp[(2) - (7)].expr), (yyvsp[(3) - (7)].list), (yyvsp[(4) - (7)].list));
					}
    break;

  case 101:
/* Line 1792 of yacc.c  */
#line 1111 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_expr *expr = NULL;
						int	tok = yylex();

						if (tok != K_WHEN)
						{
							plpgsql_push_back_token(tok);
							expr = read_sql_expression(K_WHEN, "WHEN");
						}
						plpgsql_push_back_token(K_WHEN);
						(yyval.expr) = expr;
					}
    break;

  case 102:
/* Line 1792 of yacc.c  */
#line 1126 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = lappend((yyvsp[(1) - (2)].list), (yyvsp[(2) - (2)].casewhen));
					}
    break;

  case 103:
/* Line 1792 of yacc.c  */
#line 1130 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = list_make1((yyvsp[(1) - (1)].casewhen));
					}
    break;

  case 104:
/* Line 1792 of yacc.c  */
#line 1136 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_case_when *new = palloc(sizeof(PLpgSQL_case_when));

						new->lineno	= plpgsql_location_to_lineno((yylsp[(1) - (3)]));
						new->expr	= (yyvsp[(2) - (3)].expr);
						new->stmts	= (yyvsp[(3) - (3)].list);
						(yyval.casewhen) = new;
					}
    break;

  case 105:
/* Line 1792 of yacc.c  */
#line 1147 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.list) = NIL;
					}
    break;

  case 106:
/* Line 1792 of yacc.c  */
#line 1151 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/*
						 * proc_sect could return an empty list, but we
						 * must distinguish that from not having ELSE at all.
						 * Simplest fix is to return a list with one NULL
						 * pointer, which make_case() must take care of.
						 */
						if ((yyvsp[(2) - (2)].list) != NIL)
							(yyval.list) = (yyvsp[(2) - (2)].list);
						else
							(yyval.list) = list_make1(NULL);
					}
    break;

  case 107:
/* Line 1792 of yacc.c  */
#line 1166 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_loop *new;

						new = palloc0(sizeof(PLpgSQL_stmt_loop));
						new->cmd_type = PLPGSQL_STMT_LOOP;
						new->lineno   = plpgsql_location_to_lineno((yylsp[(2) - (3)]));
						new->label	  = (yyvsp[(1) - (3)].str);
						new->body	  = (yyvsp[(3) - (3)].loop_body).stmts;

						check_labels((yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].loop_body).end_label, (yyvsp[(3) - (3)].loop_body).end_label_location);
						plpgsql_ns_pop();

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 108:
/* Line 1792 of yacc.c  */
#line 1183 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_while *new;

						new = palloc0(sizeof(PLpgSQL_stmt_while));
						new->cmd_type = PLPGSQL_STMT_WHILE;
						new->lineno   = plpgsql_location_to_lineno((yylsp[(2) - (4)]));
						new->label	  = (yyvsp[(1) - (4)].str);
						new->cond	  = (yyvsp[(3) - (4)].expr);
						new->body	  = (yyvsp[(4) - (4)].loop_body).stmts;

						check_labels((yyvsp[(1) - (4)].str), (yyvsp[(4) - (4)].loop_body).end_label, (yyvsp[(4) - (4)].loop_body).end_label_location);
						plpgsql_ns_pop();

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 109:
/* Line 1792 of yacc.c  */
#line 1201 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* This runs after we've scanned the loop body */
						if ((yyvsp[(3) - (4)].stmt)->cmd_type == PLPGSQL_STMT_FORI)
						{
							PLpgSQL_stmt_fori		*new;

							new = (PLpgSQL_stmt_fori *) (yyvsp[(3) - (4)].stmt);
							new->lineno   = plpgsql_location_to_lineno((yylsp[(2) - (4)]));
							new->label	  = (yyvsp[(1) - (4)].str);
							new->body	  = (yyvsp[(4) - (4)].loop_body).stmts;
							(yyval.stmt) = (PLpgSQL_stmt *) new;
						}
						else
						{
							PLpgSQL_stmt_forq		*new;

							Assert((yyvsp[(3) - (4)].stmt)->cmd_type == PLPGSQL_STMT_FORS ||
								   (yyvsp[(3) - (4)].stmt)->cmd_type == PLPGSQL_STMT_FORC ||
								   (yyvsp[(3) - (4)].stmt)->cmd_type == PLPGSQL_STMT_DYNFORS);
							/* forq is the common supertype of all three */
							new = (PLpgSQL_stmt_forq *) (yyvsp[(3) - (4)].stmt);
							new->lineno   = plpgsql_location_to_lineno((yylsp[(2) - (4)]));
							new->label	  = (yyvsp[(1) - (4)].str);
							new->body	  = (yyvsp[(4) - (4)].loop_body).stmts;
							(yyval.stmt) = (PLpgSQL_stmt *) new;
						}

						check_labels((yyvsp[(1) - (4)].str), (yyvsp[(4) - (4)].loop_body).end_label, (yyvsp[(4) - (4)].loop_body).end_label_location);
						/* close namespace started in opt_block_label */
						plpgsql_ns_pop();
					}
    break;

  case 110:
/* Line 1792 of yacc.c  */
#line 1235 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						int			tok = yylex();
						int			tokloc = yylloc;

						if (tok == K_EXECUTE)
						{
							/* EXECUTE means it's a dynamic FOR loop */
							PLpgSQL_stmt_dynfors	*new;
							PLpgSQL_expr			*expr;
							int						term;

							expr = read_sql_expression2(K_LOOP, K_USING,
														"LOOP or USING",
														&term);

							new = palloc0(sizeof(PLpgSQL_stmt_dynfors));
							new->cmd_type = PLPGSQL_STMT_DYNFORS;
							if ((yyvsp[(1) - (2)].forvariable).rec)
							{
								new->rec = (yyvsp[(1) - (2)].forvariable).rec;
								check_assignable((PLpgSQL_datum *) new->rec, (yylsp[(1) - (2)]));
							}
							else if ((yyvsp[(1) - (2)].forvariable).row)
							{
								new->row = (yyvsp[(1) - (2)].forvariable).row;
								check_assignable((PLpgSQL_datum *) new->row, (yylsp[(1) - (2)]));
							}
							else if ((yyvsp[(1) - (2)].forvariable).scalar)
							{
								/* convert single scalar to list */
								new->row = make_scalar_list1((yyvsp[(1) - (2)].forvariable).name, (yyvsp[(1) - (2)].forvariable).scalar,
															 (yyvsp[(1) - (2)].forvariable).lineno, (yylsp[(1) - (2)]));
								/* no need for check_assignable */
							}
							else
							{
								ereport(ERROR,
										(errcode(ERRCODE_DATATYPE_MISMATCH),
										 errmsg("loop variable of loop over rows must be a record or row variable or list of scalar variables"),
										 parser_errposition((yylsp[(1) - (2)]))));
							}
							new->query = expr;

							if (term == K_USING)
							{
								do
								{
									expr = read_sql_expression2(',', K_LOOP,
																", or LOOP",
																&term);
									new->params = lappend(new->params, expr);
								} while (term == ',');
							}

							(yyval.stmt) = (PLpgSQL_stmt *) new;
						}
						else if (tok == T_DATUM &&
								 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_VAR &&
								 ((PLpgSQL_var *) yylval.wdatum.datum)->datatype->typoid == REFCURSOROID)
						{
							/* It's FOR var IN cursor */
							PLpgSQL_stmt_forc	*new;
							PLpgSQL_var			*cursor = (PLpgSQL_var *) yylval.wdatum.datum;

							new = (PLpgSQL_stmt_forc *) palloc0(sizeof(PLpgSQL_stmt_forc));
							new->cmd_type = PLPGSQL_STMT_FORC;
							new->curvar = cursor->dno;

							/* Should have had a single variable name */
							if ((yyvsp[(1) - (2)].forvariable).scalar && (yyvsp[(1) - (2)].forvariable).row)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 errmsg("cursor FOR loop must have only one target variable"),
										 parser_errposition((yylsp[(1) - (2)]))));

							/* can't use an unbound cursor this way */
							if (cursor->cursor_explicit_expr == NULL)
								ereport(ERROR,
										(errcode(ERRCODE_SYNTAX_ERROR),
										 errmsg("cursor FOR loop must use a bound cursor variable"),
										 parser_errposition(tokloc)));

							/* collect cursor's parameters if any */
							new->argquery = read_cursor_args(cursor,
															 K_LOOP,
															 "LOOP");

							/* create loop's private RECORD variable */
							new->rec = plpgsql_build_record((yyvsp[(1) - (2)].forvariable).name,
															(yyvsp[(1) - (2)].forvariable).lineno,
															true);

							(yyval.stmt) = (PLpgSQL_stmt *) new;
						}
						else
						{
							PLpgSQL_expr	*expr1;
							int				expr1loc;
							bool			reverse = false;

							/*
							 * We have to distinguish between two
							 * alternatives: FOR var IN a .. b and FOR
							 * var IN query. Unfortunately this is
							 * tricky, since the query in the second
							 * form needn't start with a SELECT
							 * keyword.  We use the ugly hack of
							 * looking for two periods after the first
							 * token. We also check for the REVERSE
							 * keyword, which means it must be an
							 * integer loop.
							 */
							if (tok_is_keyword(tok, &yylval,
											   K_REVERSE, "reverse"))
								reverse = true;
							else
								plpgsql_push_back_token(tok);

							/*
							 * Read tokens until we see either a ".."
							 * or a LOOP. The text we read may not
							 * necessarily be a well-formed SQL
							 * statement, so we need to invoke
							 * read_sql_construct directly.
							 */
							expr1 = read_sql_construct(DOT_DOT,
													   K_LOOP,
													   0,
													   "LOOP",
													   "SELECT ",
													   true,
													   false,
													   true,
													   &expr1loc,
													   &tok);

							if (tok == DOT_DOT)
							{
								/* Saw "..", so it must be an integer loop */
								PLpgSQL_expr		*expr2;
								PLpgSQL_expr		*expr_by;
								PLpgSQL_var			*fvar;
								PLpgSQL_stmt_fori	*new;

								/* Check first expression is well-formed */
								check_sql_expr(expr1->query, expr1loc, 7);

								/* Read and check the second one */
								expr2 = read_sql_expression2(K_LOOP, K_BY,
															 "LOOP",
															 &tok);

								/* Get the BY clause if any */
								if (tok == K_BY)
									expr_by = read_sql_expression(K_LOOP,
																  "LOOP");
								else
									expr_by = NULL;

								/* Should have had a single variable name */
								if ((yyvsp[(1) - (2)].forvariable).scalar && (yyvsp[(1) - (2)].forvariable).row)
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("integer FOR loop must have only one target variable"),
											 parser_errposition((yylsp[(1) - (2)]))));

								/* create loop's private variable */
								fvar = (PLpgSQL_var *)
									plpgsql_build_variable((yyvsp[(1) - (2)].forvariable).name,
														   (yyvsp[(1) - (2)].forvariable).lineno,
														   plpgsql_build_datatype(INT4OID,
																				  -1,
																				  InvalidOid),
														   true);

								new = palloc0(sizeof(PLpgSQL_stmt_fori));
								new->cmd_type = PLPGSQL_STMT_FORI;
								new->var	  = fvar;
								new->reverse  = reverse;
								new->lower	  = expr1;
								new->upper	  = expr2;
								new->step	  = expr_by;

								(yyval.stmt) = (PLpgSQL_stmt *) new;
							}
							else
							{
								/*
								 * No "..", so it must be a query loop. We've
								 * prefixed an extra SELECT to the query text,
								 * so we need to remove that before performing
								 * syntax checking.
								 */
								char				*tmp_query;
								PLpgSQL_stmt_fors	*new;

								if (reverse)
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("cannot specify REVERSE in query FOR loop"),
											 parser_errposition(tokloc)));

								Assert(strncmp(expr1->query, "SELECT ", 7) == 0);
								tmp_query = pstrdup(expr1->query + 7);
								pfree(expr1->query);
								expr1->query = tmp_query;

								check_sql_expr(expr1->query, expr1loc, 0);

								new = palloc0(sizeof(PLpgSQL_stmt_fors));
								new->cmd_type = PLPGSQL_STMT_FORS;
								if ((yyvsp[(1) - (2)].forvariable).rec)
								{
									new->rec = (yyvsp[(1) - (2)].forvariable).rec;
									check_assignable((PLpgSQL_datum *) new->rec, (yylsp[(1) - (2)]));
								}
								else if ((yyvsp[(1) - (2)].forvariable).row)
								{
									new->row = (yyvsp[(1) - (2)].forvariable).row;
									check_assignable((PLpgSQL_datum *) new->row, (yylsp[(1) - (2)]));
								}
								else if ((yyvsp[(1) - (2)].forvariable).scalar)
								{
									/* convert single scalar to list */
									new->row = make_scalar_list1((yyvsp[(1) - (2)].forvariable).name, (yyvsp[(1) - (2)].forvariable).scalar,
																 (yyvsp[(1) - (2)].forvariable).lineno, (yylsp[(1) - (2)]));
									/* no need for check_assignable */
								}
								else
								{
									ereport(ERROR,
											(errcode(ERRCODE_SYNTAX_ERROR),
											 errmsg("loop variable of loop over rows must be a record or row variable or list of scalar variables"),
											 parser_errposition((yylsp[(1) - (2)]))));
								}

								new->query = expr1;
								(yyval.stmt) = (PLpgSQL_stmt *) new;
							}
						}
					}
    break;

  case 111:
/* Line 1792 of yacc.c  */
#line 1497 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.forvariable).name = NameOfDatum(&((yyvsp[(1) - (1)].wdatum)));
						(yyval.forvariable).lineno = plpgsql_location_to_lineno((yylsp[(1) - (1)]));
						if ((yyvsp[(1) - (1)].wdatum).datum->dtype == PLPGSQL_DTYPE_ROW)
						{
							(yyval.forvariable).scalar = NULL;
							(yyval.forvariable).rec = NULL;
							(yyval.forvariable).row = (PLpgSQL_row *) (yyvsp[(1) - (1)].wdatum).datum;
						}
						else if ((yyvsp[(1) - (1)].wdatum).datum->dtype == PLPGSQL_DTYPE_REC)
						{
							(yyval.forvariable).scalar = NULL;
							(yyval.forvariable).rec = (PLpgSQL_rec *) (yyvsp[(1) - (1)].wdatum).datum;
							(yyval.forvariable).row = NULL;
						}
						else
						{
							int			tok;

							(yyval.forvariable).scalar = (yyvsp[(1) - (1)].wdatum).datum;
							(yyval.forvariable).rec = NULL;
							(yyval.forvariable).row = NULL;
							/* check for comma-separated list */
							tok = yylex();
							plpgsql_push_back_token(tok);
							if (tok == ',')
								(yyval.forvariable).row = read_into_scalar_list((yyval.forvariable).name,
															   (yyval.forvariable).scalar,
															   (yylsp[(1) - (1)]));
						}
					}
    break;

  case 112:
/* Line 1792 of yacc.c  */
#line 1529 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						int			tok;

						(yyval.forvariable).name = (yyvsp[(1) - (1)].word).ident;
						(yyval.forvariable).lineno = plpgsql_location_to_lineno((yylsp[(1) - (1)]));
						(yyval.forvariable).scalar = NULL;
						(yyval.forvariable).rec = NULL;
						(yyval.forvariable).row = NULL;
						/* check for comma-separated list */
						tok = yylex();
						plpgsql_push_back_token(tok);
						if (tok == ',')
							word_is_not_variable(&((yyvsp[(1) - (1)].word)), (yylsp[(1) - (1)]));
					}
    break;

  case 113:
/* Line 1792 of yacc.c  */
#line 1544 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[(1) - (1)].cword)), (yylsp[(1) - (1)]));
					}
    break;

  case 114:
/* Line 1792 of yacc.c  */
#line 1551 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_foreach_a *new;

						new = palloc0(sizeof(PLpgSQL_stmt_foreach_a));
						new->cmd_type = PLPGSQL_STMT_FOREACH_A;
						new->lineno = plpgsql_location_to_lineno((yylsp[(2) - (8)]));
						new->label = (yyvsp[(1) - (8)].str);
						new->slice = (yyvsp[(4) - (8)].ival);
						new->expr = (yyvsp[(7) - (8)].expr);
						new->body = (yyvsp[(8) - (8)].loop_body).stmts;

						if ((yyvsp[(3) - (8)].forvariable).rec)
						{
							new->varno = (yyvsp[(3) - (8)].forvariable).rec->dno;
							check_assignable((PLpgSQL_datum *) (yyvsp[(3) - (8)].forvariable).rec, (yylsp[(3) - (8)]));
						}
						else if ((yyvsp[(3) - (8)].forvariable).row)
						{
							new->varno = (yyvsp[(3) - (8)].forvariable).row->dno;
							check_assignable((PLpgSQL_datum *) (yyvsp[(3) - (8)].forvariable).row, (yylsp[(3) - (8)]));
						}
						else if ((yyvsp[(3) - (8)].forvariable).scalar)
						{
							new->varno = (yyvsp[(3) - (8)].forvariable).scalar->dno;
							check_assignable((yyvsp[(3) - (8)].forvariable).scalar, (yylsp[(3) - (8)]));
						}
						else
						{
							ereport(ERROR,
									(errcode(ERRCODE_SYNTAX_ERROR),
									 errmsg("loop variable of FOREACH must be a known variable or list of variables"),
											 parser_errposition((yylsp[(3) - (8)]))));
						}

						check_labels((yyvsp[(1) - (8)].str), (yyvsp[(8) - (8)].loop_body).end_label, (yyvsp[(8) - (8)].loop_body).end_label_location);
						plpgsql_ns_pop();

						(yyval.stmt) = (PLpgSQL_stmt *) new;
					}
    break;

  case 115:
/* Line 1792 of yacc.c  */
#line 1593 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.ival) = 0;
					}
    break;

  case 116:
/* Line 1792 of yacc.c  */
#line 1597 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.ival) = (yyvsp[(2) - (2)].ival);
					}
    break;

  case 117:
/* Line 1792 of yacc.c  */
#line 1603 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_exit *new;

						new = palloc0(sizeof(PLpgSQL_stmt_exit));
						new->cmd_type = PLPGSQL_STMT_EXIT;
						new->is_exit  = (yyvsp[(1) - (3)].boolean);
						new->lineno	  = plpgsql_location_to_lineno((yylsp[(1) - (3)]));
						new->label	  = (yyvsp[(2) - (3)].str);
						new->cond	  = (yyvsp[(3) - (3)].expr);

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 118:
/* Line 1792 of yacc.c  */
#line 1618 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.boolean) = true;
					}
    break;

  case 119:
/* Line 1792 of yacc.c  */
#line 1622 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.boolean) = false;
					}
    break;

  case 120:
/* Line 1792 of yacc.c  */
#line 1628 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						int	tok;

						tok = yylex();
						if (tok == 0)
							yyerror("unexpected end of function definition");

						if (tok_is_keyword(tok, &yylval,
										   K_NEXT, "next"))
						{
							(yyval.stmt) = make_return_next_stmt((yylsp[(1) - (1)]));
						}
						else if (tok_is_keyword(tok, &yylval,
												K_QUERY, "query"))
						{
							(yyval.stmt) = make_return_query_stmt((yylsp[(1) - (1)]));
						}
						else
						{
							plpgsql_push_back_token(tok);
							(yyval.stmt) = make_return_stmt((yylsp[(1) - (1)]));
						}
					}
    break;

  case 121:
/* Line 1792 of yacc.c  */
#line 1654 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_raise		*new;
						int	tok;

						new = palloc(sizeof(PLpgSQL_stmt_raise));

						new->cmd_type	= PLPGSQL_STMT_RAISE;
						new->lineno		= plpgsql_location_to_lineno((yylsp[(1) - (1)]));
						new->elog_level = ERROR;	/* default */
						new->condname	= NULL;
						new->message	= NULL;
						new->params		= NIL;
						new->options	= NIL;

						tok = yylex();
						if (tok == 0)
							yyerror("unexpected end of function definition");

						/*
						 * We could have just RAISE, meaning to re-throw
						 * the current error.
						 */
						if (tok != ';')
						{
							/*
							 * First is an optional elog severity level.
							 */
							if (tok_is_keyword(tok, &yylval,
											   K_EXCEPTION, "exception"))
							{
								new->elog_level = ERROR;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_WARNING, "warning"))
							{
								new->elog_level = WARNING;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_NOTICE, "notice"))
							{
								new->elog_level = NOTICE;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_INFO, "info"))
							{
								new->elog_level = INFO;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_LOG, "log"))
							{
								new->elog_level = LOG;
								tok = yylex();
							}
							else if (tok_is_keyword(tok, &yylval,
													K_DEBUG, "debug"))
							{
								new->elog_level = DEBUG1;
								tok = yylex();
							}
							if (tok == 0)
								yyerror("unexpected end of function definition");

							/*
							 * Next we can have a condition name, or
							 * equivalently SQLSTATE 'xxxxx', or a string
							 * literal that is the old-style message format,
							 * or USING to start the option list immediately.
							 */
							if (tok == SCONST)
							{
								/* old style message and parameters */
								new->message = yylval.str;
								/*
								 * We expect either a semi-colon, which
								 * indicates no parameters, or a comma that
								 * begins the list of parameter expressions,
								 * or USING to begin the options list.
								 */
								tok = yylex();
								if (tok != ',' && tok != ';' && tok != K_USING)
									yyerror("syntax error");

								while (tok == ',')
								{
									PLpgSQL_expr *expr;

									expr = read_sql_construct(',', ';', K_USING,
															  ", or ; or USING",
															  "SELECT ",
															  true, true, true,
															  NULL, &tok);
									new->params = lappend(new->params, expr);
								}
							}
							else if (tok != K_USING)
							{
								/* must be condition name or SQLSTATE */
								if (tok_is_keyword(tok, &yylval,
												   K_SQLSTATE, "sqlstate"))
								{
									/* next token should be a string literal */
									char   *sqlstatestr;

									if (yylex() != SCONST)
										yyerror("syntax error");
									sqlstatestr = yylval.str;

									if (strlen(sqlstatestr) != 5)
										yyerror("invalid SQLSTATE code");
									if (strspn(sqlstatestr, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ") != 5)
										yyerror("invalid SQLSTATE code");
									new->condname = sqlstatestr;
								}
								else
								{
									if (tok == T_WORD)
										new->condname = yylval.word.ident;
									else if (plpgsql_token_is_unreserved_keyword(tok))
										new->condname = pstrdup(yylval.keyword);
									else
										yyerror("syntax error");
									plpgsql_recognize_err_condition(new->condname,
																	false);
								}
								tok = yylex();
								if (tok != ';' && tok != K_USING)
									yyerror("syntax error");
							}

							if (tok == K_USING)
								new->options = read_raise_options();
						}

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 122:
/* Line 1792 of yacc.c  */
#line 1796 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.loop_body).stmts = (yyvsp[(1) - (5)].list);
						(yyval.loop_body).end_label = (yyvsp[(4) - (5)].str);
						(yyval.loop_body).end_label_location = (yylsp[(4) - (5)]);
					}
    break;

  case 123:
/* Line 1792 of yacc.c  */
#line 1814 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.stmt) = make_execsql_stmt(K_INSERT, (yylsp[(1) - (1)]));
					}
    break;

  case 124:
/* Line 1792 of yacc.c  */
#line 1818 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						int			tok;

						tok = yylex();
						plpgsql_push_back_token(tok);
						if (tok == '=' || tok == COLON_EQUALS || tok == '[')
							word_is_not_variable(&((yyvsp[(1) - (1)].word)), (yylsp[(1) - (1)]));
						(yyval.stmt) = make_execsql_stmt(T_WORD, (yylsp[(1) - (1)]));
					}
    break;

  case 125:
/* Line 1792 of yacc.c  */
#line 1828 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						int			tok;

						tok = yylex();
						plpgsql_push_back_token(tok);
						if (tok == '=' || tok == COLON_EQUALS || tok == '[')
							cword_is_not_variable(&((yyvsp[(1) - (1)].cword)), (yylsp[(1) - (1)]));
						(yyval.stmt) = make_execsql_stmt(T_CWORD, (yylsp[(1) - (1)]));
					}
    break;

  case 126:
/* Line 1792 of yacc.c  */
#line 1840 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_dynexecute *new;
						PLpgSQL_expr *expr;
						int endtoken;

						expr = read_sql_construct(K_INTO, K_USING, ';',
												  "INTO or USING or ;",
												  "SELECT ",
												  true, true, true,
												  NULL, &endtoken);

						new = palloc(sizeof(PLpgSQL_stmt_dynexecute));
						new->cmd_type = PLPGSQL_STMT_DYNEXECUTE;
						new->lineno = plpgsql_location_to_lineno((yylsp[(1) - (1)]));
						new->query = expr;
						new->into = false;
						new->strict = false;
						new->rec = NULL;
						new->row = NULL;
						new->params = NIL;

						/*
						 * We loop to allow the INTO and USING clauses to
						 * appear in either order, since people easily get
						 * that wrong.  This coding also prevents "INTO foo"
						 * from getting absorbed into a USING expression,
						 * which is *really* confusing.
						 */
						for (;;)
						{
							if (endtoken == K_INTO)
							{
								if (new->into)			/* multiple INTO */
									yyerror("syntax error");
								new->into = true;
								read_into_target(&new->rec, &new->row, &new->strict);
								endtoken = yylex();
							}
							else if (endtoken == K_USING)
							{
								if (new->params)		/* multiple USING */
									yyerror("syntax error");
								do
								{
									expr = read_sql_construct(',', ';', K_INTO,
															  ", or ; or INTO",
															  "SELECT ",
															  true, true, true,
															  NULL, &endtoken);
									new->params = lappend(new->params, expr);
								} while (endtoken == ',');
							}
							else if (endtoken == ';')
								break;
							else
								yyerror("syntax error");
						}

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 127:
/* Line 1792 of yacc.c  */
#line 1904 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_open *new;
						int				  tok;

						new = palloc0(sizeof(PLpgSQL_stmt_open));
						new->cmd_type = PLPGSQL_STMT_OPEN;
						new->lineno = plpgsql_location_to_lineno((yylsp[(1) - (2)]));
						new->curvar = (yyvsp[(2) - (2)].var)->dno;
						new->cursor_options = CURSOR_OPT_FAST_PLAN;

						if ((yyvsp[(2) - (2)].var)->cursor_explicit_expr == NULL)
						{
							/* be nice if we could use opt_scrollable here */
							tok = yylex();
							if (tok_is_keyword(tok, &yylval,
											   K_NO, "no"))
							{
								tok = yylex();
								if (tok_is_keyword(tok, &yylval,
												   K_SCROLL, "scroll"))
								{
									new->cursor_options |= CURSOR_OPT_NO_SCROLL;
									tok = yylex();
								}
							}
							else if (tok_is_keyword(tok, &yylval,
													K_SCROLL, "scroll"))
							{
								new->cursor_options |= CURSOR_OPT_SCROLL;
								tok = yylex();
							}

							if (tok != K_FOR)
								yyerror("syntax error, expected \"FOR\"");

							tok = yylex();
							if (tok == K_EXECUTE)
							{
								int		endtoken;

								new->dynquery =
									read_sql_expression2(K_USING, ';',
														 "USING or ;",
														 &endtoken);

								/* If we found "USING", collect argument(s) */
								if (endtoken == K_USING)
								{
									PLpgSQL_expr *expr;

									do
									{
										expr = read_sql_expression2(',', ';',
																	", or ;",
																	&endtoken);
										new->params = lappend(new->params,
															  expr);
									} while (endtoken == ',');
								}
							}
							else
							{
								plpgsql_push_back_token(tok);
								new->query = read_sql_stmt("");
							}
						}
						else
						{
							/* predefined cursor query, so read args */
							new->argquery = read_cursor_args((yyvsp[(2) - (2)].var), ';', ";");
						}

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 128:
/* Line 1792 of yacc.c  */
#line 1981 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_fetch *fetch = (yyvsp[(2) - (4)].fetch);
						PLpgSQL_rec	   *rec;
						PLpgSQL_row	   *row;

						/* We have already parsed everything through the INTO keyword */
						read_into_target(&rec, &row, NULL);

						if (yylex() != ';')
							yyerror("syntax error");

						/*
						 * We don't allow multiple rows in PL/pgSQL's FETCH
						 * statement, only in MOVE.
						 */
						if (fetch->returns_multiple_rows)
							ereport(ERROR,
									(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
									 errmsg("FETCH statement cannot return multiple rows"),
									 parser_errposition((yylsp[(1) - (4)]))));

						fetch->lineno = plpgsql_location_to_lineno((yylsp[(1) - (4)]));
						fetch->rec		= rec;
						fetch->row		= row;
						fetch->curvar	= (yyvsp[(3) - (4)].var)->dno;
						fetch->is_move	= false;

						(yyval.stmt) = (PLpgSQL_stmt *)fetch;
					}
    break;

  case 129:
/* Line 1792 of yacc.c  */
#line 2013 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_fetch *fetch = (yyvsp[(2) - (4)].fetch);

						fetch->lineno = plpgsql_location_to_lineno((yylsp[(1) - (4)]));
						fetch->curvar	= (yyvsp[(3) - (4)].var)->dno;
						fetch->is_move	= true;

						(yyval.stmt) = (PLpgSQL_stmt *)fetch;
					}
    break;

  case 130:
/* Line 1792 of yacc.c  */
#line 2025 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.fetch) = read_fetch_direction();
					}
    break;

  case 131:
/* Line 1792 of yacc.c  */
#line 2031 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_stmt_close *new;

						new = palloc(sizeof(PLpgSQL_stmt_close));
						new->cmd_type = PLPGSQL_STMT_CLOSE;
						new->lineno = plpgsql_location_to_lineno((yylsp[(1) - (3)]));
						new->curvar = (yyvsp[(2) - (3)].var)->dno;

						(yyval.stmt) = (PLpgSQL_stmt *)new;
					}
    break;

  case 132:
/* Line 1792 of yacc.c  */
#line 2044 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* We do not bother building a node for NULL */
						(yyval.stmt) = NULL;
					}
    break;

  case 133:
/* Line 1792 of yacc.c  */
#line 2051 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						if ((yyvsp[(1) - (1)].wdatum).datum->dtype != PLPGSQL_DTYPE_VAR)
							ereport(ERROR,
									(errcode(ERRCODE_DATATYPE_MISMATCH),
									 errmsg("cursor variable must be a simple variable"),
									 parser_errposition((yylsp[(1) - (1)]))));

						if (((PLpgSQL_var *) (yyvsp[(1) - (1)].wdatum).datum)->datatype->typoid != REFCURSOROID)
							ereport(ERROR,
									(errcode(ERRCODE_DATATYPE_MISMATCH),
									 errmsg("variable \"%s\" must be of type cursor or refcursor",
											((PLpgSQL_var *) (yyvsp[(1) - (1)].wdatum).datum)->refname),
									 parser_errposition((yylsp[(1) - (1)]))));
						(yyval.var) = (PLpgSQL_var *) (yyvsp[(1) - (1)].wdatum).datum;
					}
    break;

  case 134:
/* Line 1792 of yacc.c  */
#line 2067 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* just to give a better message than "syntax error" */
						word_is_not_variable(&((yyvsp[(1) - (1)].word)), (yylsp[(1) - (1)]));
					}
    break;

  case 135:
/* Line 1792 of yacc.c  */
#line 2072 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/* just to give a better message than "syntax error" */
						cword_is_not_variable(&((yyvsp[(1) - (1)].cword)), (yylsp[(1) - (1)]));
					}
    break;

  case 136:
/* Line 1792 of yacc.c  */
#line 2079 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.exception_block) = NULL; }
    break;

  case 137:
/* Line 1792 of yacc.c  */
#line 2081 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						/*
						 * We use a mid-rule action to add these
						 * special variables to the namespace before
						 * parsing the WHEN clauses themselves.  The
						 * scope of the names extends to the end of the
						 * current block.
						 */
						int			lineno = plpgsql_location_to_lineno((yylsp[(1) - (1)]));
						PLpgSQL_exception_block *new = palloc(sizeof(PLpgSQL_exception_block));
						PLpgSQL_variable *var;

						var = plpgsql_build_variable("sqlstate", lineno,
													 plpgsql_build_datatype(TEXTOID,
																			-1,
																			plpgsql_curr_compile->fn_input_collation),
													 true);
						((PLpgSQL_var *) var)->isconst = true;
						new->sqlstate_varno = var->dno;

						var = plpgsql_build_variable("sqlerrm", lineno,
													 plpgsql_build_datatype(TEXTOID,
																			-1,
																			plpgsql_curr_compile->fn_input_collation),
													 true);
						((PLpgSQL_var *) var)->isconst = true;
						new->sqlerrm_varno = var->dno;

						(yyval.exception_block) = new;
					}
    break;

  case 138:
/* Line 1792 of yacc.c  */
#line 2112 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_exception_block *new = (yyvsp[(2) - (3)].exception_block);
						new->exc_list = (yyvsp[(3) - (3)].list);

						(yyval.exception_block) = new;
					}
    break;

  case 139:
/* Line 1792 of yacc.c  */
#line 2121 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
							(yyval.list) = lappend((yyvsp[(1) - (2)].list), (yyvsp[(2) - (2)].exception));
						}
    break;

  case 140:
/* Line 1792 of yacc.c  */
#line 2125 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
							(yyval.list) = list_make1((yyvsp[(1) - (1)].exception));
						}
    break;

  case 141:
/* Line 1792 of yacc.c  */
#line 2131 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						PLpgSQL_exception *new;

						new = palloc0(sizeof(PLpgSQL_exception));
						new->lineno = plpgsql_location_to_lineno((yylsp[(1) - (4)]));
						new->conditions = (yyvsp[(2) - (4)].condition);
						new->action = (yyvsp[(4) - (4)].list);

						(yyval.exception) = new;
					}
    break;

  case 142:
/* Line 1792 of yacc.c  */
#line 2144 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
							PLpgSQL_condition	*old;

							for (old = (yyvsp[(1) - (3)].condition); old->next != NULL; old = old->next)
								/* skip */ ;
							old->next = (yyvsp[(3) - (3)].condition);
							(yyval.condition) = (yyvsp[(1) - (3)].condition);
						}
    break;

  case 143:
/* Line 1792 of yacc.c  */
#line 2153 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
							(yyval.condition) = (yyvsp[(1) - (1)].condition);
						}
    break;

  case 144:
/* Line 1792 of yacc.c  */
#line 2159 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
							if (strcmp((yyvsp[(1) - (1)].str), "sqlstate") != 0)
							{
								(yyval.condition) = plpgsql_parse_err_condition((yyvsp[(1) - (1)].str));
							}
							else
							{
								PLpgSQL_condition *new;
								char   *sqlstatestr;

								/* next token should be a string literal */
								if (yylex() != SCONST)
									yyerror("syntax error");
								sqlstatestr = yylval.str;

								if (strlen(sqlstatestr) != 5)
									yyerror("invalid SQLSTATE code");
								if (strspn(sqlstatestr, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ") != 5)
									yyerror("invalid SQLSTATE code");

								new = palloc(sizeof(PLpgSQL_condition));
								new->sqlerrstate =
									MAKE_SQLSTATE(sqlstatestr[0],
												  sqlstatestr[1],
												  sqlstatestr[2],
												  sqlstatestr[3],
												  sqlstatestr[4]);
								new->condname = sqlstatestr;
								new->next = NULL;

								(yyval.condition) = new;
							}
						}
    break;

  case 145:
/* Line 1792 of yacc.c  */
#line 2195 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.expr) = read_sql_expression(';', ";"); }
    break;

  case 146:
/* Line 1792 of yacc.c  */
#line 2199 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.expr) = read_sql_expression(']', "]"); }
    break;

  case 147:
/* Line 1792 of yacc.c  */
#line 2203 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.expr) = read_sql_expression(K_THEN, "THEN"); }
    break;

  case 148:
/* Line 1792 of yacc.c  */
#line 2207 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.expr) = read_sql_expression(K_LOOP, "LOOP"); }
    break;

  case 149:
/* Line 1792 of yacc.c  */
#line 2211 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_ns_push(NULL);
						(yyval.str) = NULL;
					}
    break;

  case 150:
/* Line 1792 of yacc.c  */
#line 2216 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						plpgsql_ns_push((yyvsp[(2) - (3)].str));
						(yyval.str) = (yyvsp[(2) - (3)].str);
					}
    break;

  case 151:
/* Line 1792 of yacc.c  */
#line 2223 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.str) = NULL;
					}
    break;

  case 152:
/* Line 1792 of yacc.c  */
#line 2227 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						if (plpgsql_ns_lookup_label(plpgsql_ns_top(), (yyvsp[(1) - (1)].str)) == NULL)
							yyerror("label does not exist");
						(yyval.str) = (yyvsp[(1) - (1)].str);
					}
    break;

  case 153:
/* Line 1792 of yacc.c  */
#line 2235 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.expr) = NULL; }
    break;

  case 154:
/* Line 1792 of yacc.c  */
#line 2237 "src\\pl\\plpgsql\\src\\pl_gram.y"
    { (yyval.expr) = (yyvsp[(2) - (2)].expr); }
    break;

  case 155:
/* Line 1792 of yacc.c  */
#line 2244 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.str) = (yyvsp[(1) - (1)].word).ident;
					}
    break;

  case 156:
/* Line 1792 of yacc.c  */
#line 2248 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						(yyval.str) = pstrdup((yyvsp[(1) - (1)].keyword));
					}
    break;

  case 157:
/* Line 1792 of yacc.c  */
#line 2252 "src\\pl\\plpgsql\\src\\pl_gram.y"
    {
						if ((yyvsp[(1) - (1)].wdatum).ident == NULL) /* composite name not OK */
							yyerror("syntax error");
						(yyval.str) = (yyvsp[(1) - (1)].wdatum).ident;
					}
    break;


/* Line 1792 of yacc.c  */
#line 4490 "src\\pl\\plpgsql\\src\\pl_gram.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 2317 "src\\pl\\plpgsql\\src\\pl_gram.y"


/*
 * Check whether a token represents an "unreserved keyword".
 * We have various places where we want to recognize a keyword in preference
 * to a variable name, but not reserve that keyword in other contexts.
 * Hence, this kluge.
 */
static bool
tok_is_keyword(int token, union YYSTYPE *lval,
			   int kw_token, const char *kw_str)
{
	if (token == kw_token)
	{
		/* Normal case, was recognized by scanner (no conflicting variable) */
		return true;
	}
	else if (token == T_DATUM)
	{
		/*
		 * It's a variable, so recheck the string name.  Note we will not
		 * match composite names (hence an unreserved word followed by "."
		 * will not be recognized).
		 */
		if (!lval->wdatum.quoted && lval->wdatum.ident != NULL &&
			strcmp(lval->wdatum.ident, kw_str) == 0)
			return true;
	}
	return false;				/* not the keyword */
}

/*
 * Convenience routine to complain when we expected T_DATUM and got T_WORD,
 * ie, unrecognized variable.
 */
static void
word_is_not_variable(PLword *word, int location)
{
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("\"%s\" is not a known variable",
					word->ident),
			 parser_errposition(location)));
}

/* Same, for a CWORD */
static void
cword_is_not_variable(PLcword *cword, int location)
{
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("\"%s\" is not a known variable",
					NameListToString(cword->idents)),
			 parser_errposition(location)));
}

/*
 * Convenience routine to complain when we expected T_DATUM and got
 * something else.  "tok" must be the current token, since we also
 * look at yylval and yylloc.
 */
static void
current_token_is_not_variable(int tok)
{
	if (tok == T_WORD)
		word_is_not_variable(&(yylval.word), yylloc);
	else if (tok == T_CWORD)
		cword_is_not_variable(&(yylval.cword), yylloc);
	else
		yyerror("syntax error");
}

/* Convenience routine to read an expression with one possible terminator */
static PLpgSQL_expr *
read_sql_expression(int until, const char *expected)
{
	return read_sql_construct(until, 0, 0, expected,
							  "SELECT ", true, true, true, NULL, NULL);
}

/* Convenience routine to read an expression with two possible terminators */
static PLpgSQL_expr *
read_sql_expression2(int until, int until2, const char *expected,
					 int *endtoken)
{
	return read_sql_construct(until, until2, 0, expected,
							  "SELECT ", true, true, true, NULL, endtoken);
}

/* Convenience routine to read a SQL statement that must end with ';' */
static PLpgSQL_expr *
read_sql_stmt(const char *sqlstart)
{
	return read_sql_construct(';', 0, 0, ";",
							  sqlstart, false, true, true, NULL, NULL);
}

/*
 * Read a SQL construct and build a PLpgSQL_expr for it.
 *
 * until:		token code for expected terminator
 * until2:		token code for alternate terminator (pass 0 if none)
 * until3:		token code for another alternate terminator (pass 0 if none)
 * expected:	text to use in complaining that terminator was not found
 * sqlstart:	text to prefix to the accumulated SQL text
 * isexpression: whether to say we're reading an "expression" or a "statement"
 * valid_sql:   whether to check the syntax of the expr (prefixed with sqlstart)
 * trim:		trim trailing whitespace
 * startloc:	if not NULL, location of first token is stored at *startloc
 * endtoken:	if not NULL, ending token is stored at *endtoken
 *				(this is only interesting if until2 or until3 isn't zero)
 */
static PLpgSQL_expr *
read_sql_construct(int until,
				   int until2,
				   int until3,
				   const char *expected,
				   const char *sqlstart,
				   bool isexpression,
				   bool valid_sql,
				   bool trim,
				   int *startloc,
				   int *endtoken)
{
	int					tok;
	StringInfoData		ds;
	IdentifierLookup	save_IdentifierLookup;
	int					startlocation = -1;
	int					parenlevel = 0;
	PLpgSQL_expr		*expr;

	initStringInfo(&ds);
	appendStringInfoString(&ds, sqlstart);

	/* special lookup mode for identifiers within the SQL text */
	save_IdentifierLookup = plpgsql_IdentifierLookup;
	plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;

	for (;;)
	{
		tok = yylex();
		if (startlocation < 0)			/* remember loc of first token */
			startlocation = yylloc;
		if (tok == until && parenlevel == 0)
			break;
		if (tok == until2 && parenlevel == 0)
			break;
		if (tok == until3 && parenlevel == 0)
			break;
		if (tok == '(' || tok == '[')
			parenlevel++;
		else if (tok == ')' || tok == ']')
		{
			parenlevel--;
			if (parenlevel < 0)
				yyerror("mismatched parentheses");
		}
		/*
		 * End of function definition is an error, and we don't expect to
		 * hit a semicolon either (unless it's the until symbol, in which
		 * case we should have fallen out above).
		 */
		if (tok == 0 || tok == ';')
		{
			if (parenlevel != 0)
				yyerror("mismatched parentheses");
			if (isexpression)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("missing \"%s\" at end of SQL expression",
								expected),
						 parser_errposition(yylloc)));
			else
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("missing \"%s\" at end of SQL statement",
								expected),
						 parser_errposition(yylloc)));
		}
	}

	plpgsql_IdentifierLookup = save_IdentifierLookup;

	if (startloc)
		*startloc = startlocation;
	if (endtoken)
		*endtoken = tok;

	/* give helpful complaint about empty input */
	if (startlocation >= yylloc)
	{
		if (isexpression)
			yyerror("missing expression");
		else
			yyerror("missing SQL statement");
	}

	plpgsql_append_source_text(&ds, startlocation, yylloc);

	/* trim any trailing whitespace, for neatness */
	if (trim)
	{
		while (ds.len > 0 && scanner_isspace(ds.data[ds.len - 1]))
			ds.data[--ds.len] = '\0';
	}

	expr = palloc0(sizeof(PLpgSQL_expr));
	expr->dtype			= PLPGSQL_DTYPE_EXPR;
	expr->query			= pstrdup(ds.data);
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->ns			= plpgsql_ns_top();
	pfree(ds.data);

	if (valid_sql)
		check_sql_expr(expr->query, startlocation, strlen(sqlstart));

	return expr;
}

static PLpgSQL_type *
read_datatype(int tok)
{
	StringInfoData		ds;
	char			   *type_name;
	int					startlocation;
	PLpgSQL_type		*result;
	int					parenlevel = 0;

	/* Should only be called while parsing DECLARE sections */
	Assert(plpgsql_IdentifierLookup == IDENTIFIER_LOOKUP_DECLARE);

	/* Often there will be a lookahead token, but if not, get one */
	if (tok == YYEMPTY)
		tok = yylex();

	startlocation = yylloc;

	/*
	 * If we have a simple or composite identifier, check for %TYPE
	 * and %ROWTYPE constructs.
	 */
	if (tok == T_WORD)
	{
		char   *dtname = yylval.word.ident;

		tok = yylex();
		if (tok == '%')
		{
			tok = yylex();
			if (tok_is_keyword(tok, &yylval,
							   K_TYPE, "type"))
			{
				result = plpgsql_parse_wordtype(dtname);
				if (result)
					return result;
			}
			else if (tok_is_keyword(tok, &yylval,
									K_ROWTYPE, "rowtype"))
			{
				result = plpgsql_parse_wordrowtype(dtname);
				if (result)
					return result;
			}
		}
	}
	else if (plpgsql_token_is_unreserved_keyword(tok))
	{
		char   *dtname = pstrdup(yylval.keyword);

		tok = yylex();
		if (tok == '%')
		{
			tok = yylex();
			if (tok_is_keyword(tok, &yylval,
							   K_TYPE, "type"))
			{
				result = plpgsql_parse_wordtype(dtname);
				if (result)
					return result;
			}
			else if (tok_is_keyword(tok, &yylval,
									K_ROWTYPE, "rowtype"))
			{
				result = plpgsql_parse_wordrowtype(dtname);
				if (result)
					return result;
			}
		}
	}
	else if (tok == T_CWORD)
	{
		List   *dtnames = yylval.cword.idents;

		tok = yylex();
		if (tok == '%')
		{
			tok = yylex();
			if (tok_is_keyword(tok, &yylval,
							   K_TYPE, "type"))
			{
				result = plpgsql_parse_cwordtype(dtnames);
				if (result)
					return result;
			}
			else if (tok_is_keyword(tok, &yylval,
									K_ROWTYPE, "rowtype"))
			{
				result = plpgsql_parse_cwordrowtype(dtnames);
				if (result)
					return result;
			}
		}
	}

	while (tok != ';')
	{
		if (tok == 0)
		{
			if (parenlevel != 0)
				yyerror("mismatched parentheses");
			else
				yyerror("incomplete data type declaration");
		}
		/* Possible followers for datatype in a declaration */
		if (tok == K_COLLATE || tok == K_NOT ||
			tok == '=' || tok == COLON_EQUALS || tok == K_DEFAULT)
			break;
		/* Possible followers for datatype in a cursor_arg list */
		if ((tok == ',' || tok == ')') && parenlevel == 0)
			break;
		if (tok == '(')
			parenlevel++;
		else if (tok == ')')
			parenlevel--;

		tok = yylex();
	}

	/* set up ds to contain complete typename text */
	initStringInfo(&ds);
	plpgsql_append_source_text(&ds, startlocation, yylloc);
	type_name = ds.data;

	if (type_name[0] == '\0')
		yyerror("missing data type declaration");

	result = parse_datatype(type_name, startlocation);

	pfree(ds.data);

	plpgsql_push_back_token(tok);

	return result;
}

static PLpgSQL_stmt *
make_execsql_stmt(int firsttoken, int location)
{
	StringInfoData		ds;
	IdentifierLookup	save_IdentifierLookup;
	PLpgSQL_stmt_execsql *execsql;
	PLpgSQL_expr		*expr;
	PLpgSQL_row			*row = NULL;
	PLpgSQL_rec			*rec = NULL;
	int					tok;
	int					prev_tok;
	bool				have_into = false;
	bool				have_strict = false;
	int					into_start_loc = -1;
	int					into_end_loc = -1;

	initStringInfo(&ds);

	/* special lookup mode for identifiers within the SQL text */
	save_IdentifierLookup = plpgsql_IdentifierLookup;
	plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;

	/*
	 * We have to special-case the sequence INSERT INTO, because we don't want
	 * that to be taken as an INTO-variables clause.  Fortunately, this is the
	 * only valid use of INTO in a pl/pgsql SQL command, and INTO is already a
	 * fully reserved word in the main grammar.  We have to treat it that way
	 * anywhere in the string, not only at the start; consider CREATE RULE
	 * containing an INSERT statement.
	 */
	tok = firsttoken;
	for (;;)
	{
		prev_tok = tok;
		tok = yylex();
		if (have_into && into_end_loc < 0)
			into_end_loc = yylloc;		/* token after the INTO part */
		if (tok == ';')
			break;
		if (tok == 0)
			yyerror("unexpected end of function definition");

		if (tok == K_INTO && prev_tok != K_INSERT)
		{
			if (have_into)
				yyerror("INTO specified more than once");
			have_into = true;
			into_start_loc = yylloc;
			plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_NORMAL;
			read_into_target(&rec, &row, &have_strict);
			plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_EXPR;
		}
	}

	plpgsql_IdentifierLookup = save_IdentifierLookup;

	if (have_into)
	{
		/*
		 * Insert an appropriate number of spaces corresponding to the
		 * INTO text, so that locations within the redacted SQL statement
		 * still line up with those in the original source text.
		 */
		plpgsql_append_source_text(&ds, location, into_start_loc);
		appendStringInfoSpaces(&ds, into_end_loc - into_start_loc);
		plpgsql_append_source_text(&ds, into_end_loc, yylloc);
	}
	else
		plpgsql_append_source_text(&ds, location, yylloc);

	/* trim any trailing whitespace, for neatness */
	while (ds.len > 0 && scanner_isspace(ds.data[ds.len - 1]))
		ds.data[--ds.len] = '\0';

	expr = palloc0(sizeof(PLpgSQL_expr));
	expr->dtype			= PLPGSQL_DTYPE_EXPR;
	expr->query			= pstrdup(ds.data);
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->ns			= plpgsql_ns_top();
	pfree(ds.data);

	check_sql_expr(expr->query, location, 0);

	execsql = palloc(sizeof(PLpgSQL_stmt_execsql));
	execsql->cmd_type = PLPGSQL_STMT_EXECSQL;
	execsql->lineno  = plpgsql_location_to_lineno(location);
	execsql->sqlstmt = expr;
	execsql->into	 = have_into;
	execsql->strict	 = have_strict;
	execsql->rec	 = rec;
	execsql->row	 = row;

	return (PLpgSQL_stmt *) execsql;
}


/*
 * Read FETCH or MOVE direction clause (everything through FROM/IN).
 */
static PLpgSQL_stmt_fetch *
read_fetch_direction(void)
{
	PLpgSQL_stmt_fetch *fetch;
	int			tok;
	bool		check_FROM = true;

	/*
	 * We create the PLpgSQL_stmt_fetch struct here, but only fill in
	 * the fields arising from the optional direction clause
	 */
	fetch = (PLpgSQL_stmt_fetch *) palloc0(sizeof(PLpgSQL_stmt_fetch));
	fetch->cmd_type = PLPGSQL_STMT_FETCH;
	/* set direction defaults: */
	fetch->direction = FETCH_FORWARD;
	fetch->how_many  = 1;
	fetch->expr		 = NULL;
	fetch->returns_multiple_rows = false;

	tok = yylex();
	if (tok == 0)
		yyerror("unexpected end of function definition");

	if (tok_is_keyword(tok, &yylval,
					   K_NEXT, "next"))
	{
		/* use defaults */
	}
	else if (tok_is_keyword(tok, &yylval,
							K_PRIOR, "prior"))
	{
		fetch->direction = FETCH_BACKWARD;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_FIRST, "first"))
	{
		fetch->direction = FETCH_ABSOLUTE;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_LAST, "last"))
	{
		fetch->direction = FETCH_ABSOLUTE;
		fetch->how_many  = -1;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_ABSOLUTE, "absolute"))
	{
		fetch->direction = FETCH_ABSOLUTE;
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		check_FROM = false;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_RELATIVE, "relative"))
	{
		fetch->direction = FETCH_RELATIVE;
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		check_FROM = false;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_ALL, "all"))
	{
		fetch->how_many = FETCH_ALL;
		fetch->returns_multiple_rows = true;
	}
	else if (tok_is_keyword(tok, &yylval,
							K_FORWARD, "forward"))
	{
		complete_direction(fetch, &check_FROM);
	}
	else if (tok_is_keyword(tok, &yylval,
							K_BACKWARD, "backward"))
	{
		fetch->direction = FETCH_BACKWARD;
		complete_direction(fetch, &check_FROM);
	}
	else if (tok == K_FROM || tok == K_IN)
	{
		/* empty direction */
		check_FROM = false;
	}
	else if (tok == T_DATUM)
	{
		/* Assume there's no direction clause and tok is a cursor name */
		plpgsql_push_back_token(tok);
		check_FROM = false;
	}
	else
	{
		/*
		 * Assume it's a count expression with no preceding keyword.
		 * Note: we allow this syntax because core SQL does, but we don't
		 * document it because of the ambiguity with the omitted-direction
		 * case.  For instance, "MOVE n IN c" will fail if n is a variable.
		 * Perhaps this can be improved someday, but it's hardly worth a
		 * lot of work.
		 */
		plpgsql_push_back_token(tok);
		fetch->expr = read_sql_expression2(K_FROM, K_IN,
										   "FROM or IN",
										   NULL);
		fetch->returns_multiple_rows = true;
		check_FROM = false;
	}

	/* check FROM or IN keyword after direction's specification */
	if (check_FROM)
	{
		tok = yylex();
		if (tok != K_FROM && tok != K_IN)
			yyerror("expected FROM or IN");
	}

	return fetch;
}

/*
 * Process remainder of FETCH/MOVE direction after FORWARD or BACKWARD.
 * Allows these cases:
 *   FORWARD expr,  FORWARD ALL,  FORWARD
 *   BACKWARD expr, BACKWARD ALL, BACKWARD
 */
static void
complete_direction(PLpgSQL_stmt_fetch *fetch,  bool *check_FROM)
{
	int			tok;

	tok = yylex();
	if (tok == 0)
		yyerror("unexpected end of function definition");

	if (tok == K_FROM || tok == K_IN)
	{
		*check_FROM = false;
		return;
	}

	if (tok == K_ALL)
	{
		fetch->how_many = FETCH_ALL;
		fetch->returns_multiple_rows = true;
		*check_FROM = true;
		return;
	}

	plpgsql_push_back_token(tok);
	fetch->expr = read_sql_expression2(K_FROM, K_IN,
									   "FROM or IN",
									   NULL);
	fetch->returns_multiple_rows = true;
	*check_FROM = false;
}


static PLpgSQL_stmt *
make_return_stmt(int location)
{
	PLpgSQL_stmt_return *new;

	new = palloc0(sizeof(PLpgSQL_stmt_return));
	new->cmd_type = PLPGSQL_STMT_RETURN;
	new->lineno   = plpgsql_location_to_lineno(location);
	new->expr	  = NULL;
	new->retvarno = -1;

	if (plpgsql_curr_compile->fn_retset)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN cannot have a parameter in function returning set"),
					 errhint("Use RETURN NEXT or RETURN QUERY."),
					 parser_errposition(yylloc)));
	}
	else if (plpgsql_curr_compile->out_param_varno >= 0)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN cannot have a parameter in function with OUT parameters"),
					 parser_errposition(yylloc)));
		new->retvarno = plpgsql_curr_compile->out_param_varno;
	}
	else if (plpgsql_curr_compile->fn_rettype == VOIDOID)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN cannot have a parameter in function returning void"),
					 parser_errposition(yylloc)));
	}
	else if (plpgsql_curr_compile->fn_retistuple)
	{
		/*
		 * We want to special-case simple row or record references for
		 * efficiency.  So peek ahead to see if that's what we have.
		 */
		int		tok = yylex();

		if (tok == T_DATUM && plpgsql_peek() == ';' &&
			(yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_ROW ||
			 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_REC))
		{
			new->retvarno = yylval.wdatum.datum->dno;
			/* eat the semicolon token that we only peeked at above */
			tok = yylex();
			Assert(tok == ';');
		}
		else
		{
			/* Not (just) a row/record name, so treat as expression */
			plpgsql_push_back_token(tok);
			new->expr = read_sql_expression(';', ";");
		}
	}
	else
	{
		/*
		 * Note that a well-formed expression is _required_ here;
		 * anything else is a compile-time error.
		 */
		new->expr = read_sql_expression(';', ";");
	}

	return (PLpgSQL_stmt *) new;
}


static PLpgSQL_stmt *
make_return_next_stmt(int location)
{
	PLpgSQL_stmt_return_next *new;

	if (!plpgsql_curr_compile->fn_retset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("cannot use RETURN NEXT in a non-SETOF function"),
				 parser_errposition(location)));

	new = palloc0(sizeof(PLpgSQL_stmt_return_next));
	new->cmd_type	= PLPGSQL_STMT_RETURN_NEXT;
	new->lineno		= plpgsql_location_to_lineno(location);
	new->expr		= NULL;
	new->retvarno	= -1;

	if (plpgsql_curr_compile->out_param_varno >= 0)
	{
		if (yylex() != ';')
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("RETURN NEXT cannot have a parameter in function with OUT parameters"),
					 parser_errposition(yylloc)));
		new->retvarno = plpgsql_curr_compile->out_param_varno;
	}
	else if (plpgsql_curr_compile->fn_retistuple)
	{
		/*
		 * We want to special-case simple row or record references for
		 * efficiency.  So peek ahead to see if that's what we have.
		 */
		int		tok = yylex();

		if (tok == T_DATUM && plpgsql_peek() == ';' &&
			(yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_ROW ||
			 yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_REC))
		{
			new->retvarno = yylval.wdatum.datum->dno;
			/* eat the semicolon token that we only peeked at above */
			tok = yylex();
			Assert(tok == ';');
		}
		else
		{
			/* Not (just) a row/record name, so treat as expression */
			plpgsql_push_back_token(tok);
			new->expr = read_sql_expression(';', ";");
		}
	}
	else
		new->expr = read_sql_expression(';', ";");

	return (PLpgSQL_stmt *) new;
}


static PLpgSQL_stmt *
make_return_query_stmt(int location)
{
	PLpgSQL_stmt_return_query *new;
	int			tok;

	if (!plpgsql_curr_compile->fn_retset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("cannot use RETURN QUERY in a non-SETOF function"),
				 parser_errposition(location)));

	new = palloc0(sizeof(PLpgSQL_stmt_return_query));
	new->cmd_type = PLPGSQL_STMT_RETURN_QUERY;
	new->lineno = plpgsql_location_to_lineno(location);

	/* check for RETURN QUERY EXECUTE */
	if ((tok = yylex()) != K_EXECUTE)
	{
		/* ordinary static query */
		plpgsql_push_back_token(tok);
		new->query = read_sql_stmt("");
	}
	else
	{
		/* dynamic SQL */
		int		term;

		new->dynquery = read_sql_expression2(';', K_USING, "; or USING",
											 &term);
		if (term == K_USING)
		{
			do
			{
				PLpgSQL_expr *expr;

				expr = read_sql_expression2(',', ';', ", or ;", &term);
				new->params = lappend(new->params, expr);
			} while (term == ',');
		}
	}

	return (PLpgSQL_stmt *) new;
}


/* convenience routine to fetch the name of a T_DATUM */
static char *
NameOfDatum(PLwdatum *wdatum)
{
	if (wdatum->ident)
		return wdatum->ident;
	Assert(wdatum->idents != NIL);
	return NameListToString(wdatum->idents);
}

static void
check_assignable(PLpgSQL_datum *datum, int location)
{
	switch (datum->dtype)
	{
		case PLPGSQL_DTYPE_VAR:
			if (((PLpgSQL_var *) datum)->isconst)
				ereport(ERROR,
						(errcode(ERRCODE_ERROR_IN_ASSIGNMENT),
						 errmsg("\"%s\" is declared CONSTANT",
								((PLpgSQL_var *) datum)->refname),
						 parser_errposition(location)));
			break;
		case PLPGSQL_DTYPE_ROW:
			/* always assignable? */
			break;
		case PLPGSQL_DTYPE_REC:
			/* always assignable?  What about NEW/OLD? */
			break;
		case PLPGSQL_DTYPE_RECFIELD:
			/* always assignable? */
			break;
		case PLPGSQL_DTYPE_ARRAYELEM:
			/* always assignable? */
			break;
		default:
			elog(ERROR, "unrecognized dtype: %d", datum->dtype);
			break;
	}
}

/*
 * Read the argument of an INTO clause.  On entry, we have just read the
 * INTO keyword.
 */
static void
read_into_target(PLpgSQL_rec **rec, PLpgSQL_row **row, bool *strict)
{
	int			tok;

	/* Set default results */
	*rec = NULL;
	*row = NULL;
	if (strict)
		*strict = false;

	tok = yylex();
	if (strict && tok == K_STRICT)
	{
		*strict = true;
		tok = yylex();
	}

	/*
	 * Currently, a row or record variable can be the single INTO target,
	 * but not a member of a multi-target list.  So we throw error if there
	 * is a comma after it, because that probably means the user tried to
	 * write a multi-target list.  If this ever gets generalized, we should
	 * probably refactor read_into_scalar_list so it handles all cases.
	 */
	switch (tok)
	{
		case T_DATUM:
			if (yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_ROW)
			{
				check_assignable(yylval.wdatum.datum, yylloc);
				*row = (PLpgSQL_row *) yylval.wdatum.datum;

				if ((tok = yylex()) == ',')
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("record or row variable cannot be part of multiple-item INTO list"),
							 parser_errposition(yylloc)));
				plpgsql_push_back_token(tok);
			}
			else if (yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_REC)
			{
				check_assignable(yylval.wdatum.datum, yylloc);
				*rec = (PLpgSQL_rec *) yylval.wdatum.datum;

				if ((tok = yylex()) == ',')
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("record or row variable cannot be part of multiple-item INTO list"),
							 parser_errposition(yylloc)));
				plpgsql_push_back_token(tok);
			}
			else
			{
				*row = read_into_scalar_list(NameOfDatum(&(yylval.wdatum)),
											 yylval.wdatum.datum, yylloc);
			}
			break;

		default:
			/* just to give a better message than "syntax error" */
			current_token_is_not_variable(tok);
	}
}

/*
 * Given the first datum and name in the INTO list, continue to read
 * comma-separated scalar variables until we run out. Then construct
 * and return a fake "row" variable that represents the list of
 * scalars.
 */
static PLpgSQL_row *
read_into_scalar_list(char *initial_name,
					  PLpgSQL_datum *initial_datum,
					  int initial_location)
{
	int				 nfields;
	char			*fieldnames[1024];
	int				 varnos[1024];
	PLpgSQL_row		*row;
	int				 tok;

	check_assignable(initial_datum, initial_location);
	fieldnames[0] = initial_name;
	varnos[0]	  = initial_datum->dno;
	nfields		  = 1;

	while ((tok = yylex()) == ',')
	{
		/* Check for array overflow */
		if (nfields >= 1024)
			ereport(ERROR,
					(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
					 errmsg("too many INTO variables specified"),
					 parser_errposition(yylloc)));

		tok = yylex();
		switch (tok)
		{
			case T_DATUM:
				check_assignable(yylval.wdatum.datum, yylloc);
				if (yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_ROW ||
					yylval.wdatum.datum->dtype == PLPGSQL_DTYPE_REC)
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("\"%s\" is not a scalar variable",
									NameOfDatum(&(yylval.wdatum))),
							 parser_errposition(yylloc)));
				fieldnames[nfields] = NameOfDatum(&(yylval.wdatum));
				varnos[nfields++]	= yylval.wdatum.datum->dno;
				break;

			default:
				/* just to give a better message than "syntax error" */
				current_token_is_not_variable(tok);
		}
	}

	/*
	 * We read an extra, non-comma token from yylex(), so push it
	 * back onto the input stream
	 */
	plpgsql_push_back_token(tok);

	row = palloc(sizeof(PLpgSQL_row));
	row->dtype = PLPGSQL_DTYPE_ROW;
	row->refname = pstrdup("*internal*");
	row->lineno = plpgsql_location_to_lineno(initial_location);
	row->rowtupdesc = NULL;
	row->nfields = nfields;
	row->fieldnames = palloc(sizeof(char *) * nfields);
	row->varnos = palloc(sizeof(int) * nfields);
	while (--nfields >= 0)
	{
		row->fieldnames[nfields] = fieldnames[nfields];
		row->varnos[nfields] = varnos[nfields];
	}

	plpgsql_adddatum((PLpgSQL_datum *)row);

	return row;
}

/*
 * Convert a single scalar into a "row" list.  This is exactly
 * like read_into_scalar_list except we never consume any input.
 *
 * Note: lineno could be computed from location, but since callers
 * have it at hand already, we may as well pass it in.
 */
static PLpgSQL_row *
make_scalar_list1(char *initial_name,
				  PLpgSQL_datum *initial_datum,
				  int lineno, int location)
{
	PLpgSQL_row		*row;

	check_assignable(initial_datum, location);

	row = palloc(sizeof(PLpgSQL_row));
	row->dtype = PLPGSQL_DTYPE_ROW;
	row->refname = pstrdup("*internal*");
	row->lineno = lineno;
	row->rowtupdesc = NULL;
	row->nfields = 1;
	row->fieldnames = palloc(sizeof(char *));
	row->varnos = palloc(sizeof(int));
	row->fieldnames[0] = initial_name;
	row->varnos[0] = initial_datum->dno;

	plpgsql_adddatum((PLpgSQL_datum *)row);

	return row;
}

/*
 * When the PL/pgSQL parser expects to see a SQL statement, it is very
 * liberal in what it accepts; for example, we often assume an
 * unrecognized keyword is the beginning of a SQL statement. This
 * avoids the need to duplicate parts of the SQL grammar in the
 * PL/pgSQL grammar, but it means we can accept wildly malformed
 * input. To try and catch some of the more obviously invalid input,
 * we run the strings we expect to be SQL statements through the main
 * SQL parser.
 *
 * We only invoke the raw parser (not the analyzer); this doesn't do
 * any database access and does not check any semantic rules, it just
 * checks for basic syntactic correctness. We do this here, rather
 * than after parsing has finished, because a malformed SQL statement
 * may cause the PL/pgSQL parser to become confused about statement
 * borders. So it is best to bail out as early as we can.
 *
 * It is assumed that "stmt" represents a copy of the function source text
 * beginning at offset "location", with leader text of length "leaderlen"
 * (typically "SELECT ") prefixed to the source text.  We use this assumption
 * to transpose any error cursor position back to the function source text.
 * If no error cursor is provided, we'll just point at "location".
 */
static void
check_sql_expr(const char *stmt, int location, int leaderlen)
{
	sql_error_callback_arg cbarg;
	ErrorContextCallback  syntax_errcontext;
	MemoryContext oldCxt;

	if (!plpgsql_check_syntax)
		return;

	cbarg.location = location;
	cbarg.leaderlen = leaderlen;

	syntax_errcontext.callback = plpgsql_sql_error_callback;
	syntax_errcontext.arg = &cbarg;
	syntax_errcontext.previous = error_context_stack;
	error_context_stack = &syntax_errcontext;

	oldCxt = MemoryContextSwitchTo(compile_tmp_cxt);
	(void) raw_parser(stmt);
	MemoryContextSwitchTo(oldCxt);

	/* Restore former ereport callback */
	error_context_stack = syntax_errcontext.previous;
}

static void
plpgsql_sql_error_callback(void *arg)
{
	sql_error_callback_arg *cbarg = (sql_error_callback_arg *) arg;
	int			errpos;

	/*
	 * First, set up internalerrposition to point to the start of the
	 * statement text within the function text.  Note this converts
	 * location (a byte offset) to a character number.
	 */
	parser_errposition(cbarg->location);

	/*
	 * If the core parser provided an error position, transpose it.
	 * Note we are dealing with 1-based character numbers at this point.
	 */
	errpos = geterrposition();
	if (errpos > cbarg->leaderlen)
	{
		int		myerrpos = getinternalerrposition();

		if (myerrpos > 0)		/* safety check */
			internalerrposition(myerrpos + errpos - cbarg->leaderlen - 1);
	}

	/* In any case, flush errposition --- we want internalerrpos only */
	errposition(0);
}

/*
 * Parse a SQL datatype name and produce a PLpgSQL_type structure.
 *
 * The heavy lifting is done elsewhere.  Here we are only concerned
 * with setting up an errcontext link that will let us give an error
 * cursor pointing into the plpgsql function source, if necessary.
 * This is handled the same as in check_sql_expr(), and we likewise
 * expect that the given string is a copy from the source text.
 */
static PLpgSQL_type *
parse_datatype(const char *string, int location)
{
	Oid			type_id;
	int32		typmod;
	sql_error_callback_arg cbarg;
	ErrorContextCallback  syntax_errcontext;

	cbarg.location = location;
	cbarg.leaderlen = 0;

	syntax_errcontext.callback = plpgsql_sql_error_callback;
	syntax_errcontext.arg = &cbarg;
	syntax_errcontext.previous = error_context_stack;
	error_context_stack = &syntax_errcontext;

	/* Let the main parser try to parse it under standard SQL rules */
	parseTypeString(string, &type_id, &typmod);

	/* Restore former ereport callback */
	error_context_stack = syntax_errcontext.previous;

	/* Okay, build a PLpgSQL_type data structure for it */
	return plpgsql_build_datatype(type_id, typmod,
								  plpgsql_curr_compile->fn_input_collation);
}

/*
 * Check block starting and ending labels match.
 */
static void
check_labels(const char *start_label, const char *end_label, int end_location)
{
	if (end_label)
	{
		if (!start_label)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("end label \"%s\" specified for unlabelled block",
							end_label),
					 parser_errposition(end_location)));

		if (strcmp(start_label, end_label) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("end label \"%s\" differs from block's label \"%s\"",
							end_label, start_label),
					 parser_errposition(end_location)));
	}
}

/*
 * Read the arguments (if any) for a cursor, followed by the until token
 *
 * If cursor has no args, just swallow the until token and return NULL.
 * If it does have args, we expect to see "( arg [, arg ...] )" followed
 * by the until token, where arg may be a plain expression, or a named
 * parameter assignment of the form argname := expr. Consume all that and
 * return a SELECT query that evaluates the expression(s) (without the outer
 * parens).
 */
static PLpgSQL_expr *
read_cursor_args(PLpgSQL_var *cursor, int until, const char *expected)
{
	PLpgSQL_expr *expr;
	PLpgSQL_row *row;
	int			tok;
	int			argc;
	char	  **argv;
	StringInfoData ds;
	char	   *sqlstart = "SELECT ";
	bool		any_named = false;

	tok = yylex();
	if (cursor->cursor_explicit_argrow < 0)
	{
		/* No arguments expected */
		if (tok == '(')
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("cursor \"%s\" has no arguments",
							cursor->refname),
					 parser_errposition(yylloc)));

		if (tok != until)
			yyerror("syntax error");

		return NULL;
	}

	/* Else better provide arguments */
	if (tok != '(')
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("cursor \"%s\" has arguments",
						cursor->refname),
				 parser_errposition(yylloc)));

	/*
	 * Read the arguments, one by one.
	 */
	row = (PLpgSQL_row *) plpgsql_Datums[cursor->cursor_explicit_argrow];
	argv = (char **) palloc0(row->nfields * sizeof(char *));

	for (argc = 0; argc < row->nfields; argc++)
	{
		PLpgSQL_expr *item;
		int		endtoken;
		int		argpos;
		int		tok1,
				tok2;
		int		arglocation;

		/* Check if it's a named parameter: "param := value" */
		plpgsql_peek2(&tok1, &tok2, &arglocation, NULL);
		if (tok1 == IDENT && tok2 == COLON_EQUALS)
		{
			char   *argname;
			IdentifierLookup save_IdentifierLookup;

			/* Read the argument name, ignoring any matching variable */
			save_IdentifierLookup = plpgsql_IdentifierLookup;
			plpgsql_IdentifierLookup = IDENTIFIER_LOOKUP_DECLARE;
			yylex();
			argname = yylval.str;
			plpgsql_IdentifierLookup = save_IdentifierLookup;

			/* Match argument name to cursor arguments */
			for (argpos = 0; argpos < row->nfields; argpos++)
			{
				if (strcmp(row->fieldnames[argpos], argname) == 0)
					break;
			}
			if (argpos == row->nfields)
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("cursor \"%s\" has no argument named \"%s\"",
								cursor->refname, argname),
						 parser_errposition(yylloc)));

			/*
			 * Eat the ":=". We already peeked, so the error should never
			 * happen.
			 */
			tok2 = yylex();
			if (tok2 != COLON_EQUALS)
				yyerror("syntax error");

			any_named = true;
		}
		else
			argpos = argc;

		if (argv[argpos] != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("value for parameter \"%s\" of cursor \"%s\" specified more than once",
							row->fieldnames[argpos], cursor->refname),
					 parser_errposition(arglocation)));

		/*
		 * Read the value expression. To provide the user with meaningful
		 * parse error positions, we check the syntax immediately, instead of
		 * checking the final expression that may have the arguments
		 * reordered. Trailing whitespace must not be trimmed, because
		 * otherwise input of the form (param -- comment\n, param) would be
		 * translated into a form where the second parameter is commented
		 * out.
		 */
		item = read_sql_construct(',', ')', 0,
								  ",\" or \")",
								  sqlstart,
								  true, true,
								  false, /* do not trim */
								  NULL, &endtoken);

		argv[argpos] = item->query + strlen(sqlstart);

		if (endtoken == ')' && !(argc == row->nfields - 1))
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("not enough arguments for cursor \"%s\"",
							cursor->refname),
					 parser_errposition(yylloc)));

		if (endtoken == ',' && (argc == row->nfields - 1))
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("too many arguments for cursor \"%s\"",
							cursor->refname),
					 parser_errposition(yylloc)));
	}

	/* Make positional argument list */
	initStringInfo(&ds);
	appendStringInfoString(&ds, sqlstart);
	for (argc = 0; argc < row->nfields; argc++)
	{
		Assert(argv[argc] != NULL);

		/*
		 * Because named notation allows permutated argument lists, include
		 * the parameter name for meaningful runtime errors.
		 */
		appendStringInfoString(&ds, argv[argc]);
		if (any_named)
			appendStringInfo(&ds, " AS %s",
							 quote_identifier(row->fieldnames[argc]));
		if (argc < row->nfields - 1)
			appendStringInfoString(&ds, ", ");
	}
	appendStringInfoChar(&ds, ';');

	expr = palloc0(sizeof(PLpgSQL_expr));
	expr->dtype			= PLPGSQL_DTYPE_EXPR;
	expr->query			= pstrdup(ds.data);
	expr->plan			= NULL;
	expr->paramnos		= NULL;
	expr->ns            = plpgsql_ns_top();
	pfree(ds.data);

	/* Next we'd better find the until token */
	tok = yylex();
	if (tok != until)
		yyerror("syntax error");

	return expr;
}

/*
 * Parse RAISE ... USING options
 */
static List *
read_raise_options(void)
{
	List	   *result = NIL;

	for (;;)
	{
		PLpgSQL_raise_option *opt;
		int		tok;

		if ((tok = yylex()) == 0)
			yyerror("unexpected end of function definition");

		opt = (PLpgSQL_raise_option *) palloc(sizeof(PLpgSQL_raise_option));

		if (tok_is_keyword(tok, &yylval,
						   K_ERRCODE, "errcode"))
			opt->opt_type = PLPGSQL_RAISEOPTION_ERRCODE;
		else if (tok_is_keyword(tok, &yylval,
								K_MESSAGE, "message"))
			opt->opt_type = PLPGSQL_RAISEOPTION_MESSAGE;
		else if (tok_is_keyword(tok, &yylval,
								K_DETAIL, "detail"))
			opt->opt_type = PLPGSQL_RAISEOPTION_DETAIL;
		else if (tok_is_keyword(tok, &yylval,
								K_HINT, "hint"))
			opt->opt_type = PLPGSQL_RAISEOPTION_HINT;
		else if (tok_is_keyword(tok, &yylval,
								K_COLUMN, "column"))
			opt->opt_type = PLPGSQL_RAISEOPTION_COLUMN;
		else if (tok_is_keyword(tok, &yylval,
								K_CONSTRAINT, "constraint"))
			opt->opt_type = PLPGSQL_RAISEOPTION_CONSTRAINT;
		else if (tok_is_keyword(tok, &yylval,
								K_DATATYPE, "datatype"))
			opt->opt_type = PLPGSQL_RAISEOPTION_DATATYPE;
		else if (tok_is_keyword(tok, &yylval,
								K_TABLE, "table"))
			opt->opt_type = PLPGSQL_RAISEOPTION_TABLE;
		else if (tok_is_keyword(tok, &yylval,
								K_SCHEMA, "schema"))
			opt->opt_type = PLPGSQL_RAISEOPTION_SCHEMA;
		else
			yyerror("unrecognized RAISE statement option");

		tok = yylex();
		if (tok != '=' && tok != COLON_EQUALS)
			yyerror("syntax error, expected \"=\"");

		opt->expr = read_sql_expression2(',', ';', ", or ;", &tok);

		result = lappend(result, opt);

		if (tok == ';')
			break;
	}

	return result;
}

/*
 * Fix up CASE statement
 */
static PLpgSQL_stmt *
make_case(int location, PLpgSQL_expr *t_expr,
		  List *case_when_list, List *else_stmts)
{
	PLpgSQL_stmt_case	*new;

	new = palloc(sizeof(PLpgSQL_stmt_case));
	new->cmd_type = PLPGSQL_STMT_CASE;
	new->lineno = plpgsql_location_to_lineno(location);
	new->t_expr = t_expr;
	new->t_varno = 0;
	new->case_when_list = case_when_list;
	new->have_else = (else_stmts != NIL);
	/* Get rid of list-with-NULL hack */
	if (list_length(else_stmts) == 1 && linitial(else_stmts) == NULL)
		new->else_stmts = NIL;
	else
		new->else_stmts = else_stmts;

	/*
	 * When test expression is present, we create a var for it and then
	 * convert all the WHEN expressions to "VAR IN (original_expression)".
	 * This is a bit klugy, but okay since we haven't yet done more than
	 * read the expressions as text.  (Note that previous parsing won't
	 * have complained if the WHEN ... THEN expression contained multiple
	 * comma-separated values.)
	 */
	if (t_expr)
	{
		char	varname[32];
		PLpgSQL_var *t_var;
		ListCell *l;

		/* use a name unlikely to collide with any user names */
		snprintf(varname, sizeof(varname), "__Case__Variable_%d__",
				 plpgsql_nDatums);

		/*
		 * We don't yet know the result datatype of t_expr.  Build the
		 * variable as if it were INT4; we'll fix this at runtime if needed.
		 */
		t_var = (PLpgSQL_var *)
			plpgsql_build_variable(varname, new->lineno,
								   plpgsql_build_datatype(INT4OID,
														  -1,
														  InvalidOid),
								   true);
		new->t_varno = t_var->dno;

		foreach(l, case_when_list)
		{
			PLpgSQL_case_when *cwt = (PLpgSQL_case_when *) lfirst(l);
			PLpgSQL_expr *expr = cwt->expr;
			StringInfoData	ds;

			/* copy expression query without SELECT keyword (expr->query + 7) */
			Assert(strncmp(expr->query, "SELECT ", 7) == 0);

			/* And do the string hacking */
			initStringInfo(&ds);

			appendStringInfo(&ds, "SELECT \"%s\" IN (%s)",
							 varname, expr->query + 7);

			pfree(expr->query);
			expr->query = pstrdup(ds.data);
			/* Adjust expr's namespace to include the case variable */
			expr->ns = plpgsql_ns_top();

			pfree(ds.data);
		}
	}

	return (PLpgSQL_stmt *) new;
}
