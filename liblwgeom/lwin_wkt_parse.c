/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         wkt_yyparse
#define yylex           wkt_yylex
#define yyerror         wkt_yyerror
#define yylval          wkt_yylval
#define yychar          wkt_yychar
#define yydebug         wkt_yydebug
#define yynerrs         wkt_yynerrs
#define yylloc          wkt_yylloc

/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "lwin_wkt_parse.y"


/* WKT Parser */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lwin_wkt.h"
#include "lwin_wkt_parse.h"
#include "lwgeom_log.h"


/* Prototypes to quiet the compiler */
int wkt_yyparse(void);
void wkt_yyerror(const char *str);
int wkt_yylex(void);


/* Declare the global parser variable */
LWGEOM_PARSER_RESULT global_parser_result;

/* Turn on/off verbose parsing (turn off for production) */
int wkt_yydebug = 0;

/* 
* Error handler called by the bison parser. Mostly we will be 
* catching our own errors and filling out the message and errlocation
* from WKT_ERROR in the grammar, but we keep this one 
* around just in case.
*/
void wkt_yyerror(const char *str)
{
	/* If we haven't already set a message and location, let's set one now. */
	if ( ! global_parser_result.message ) 
	{
		global_parser_result.message = parser_error_messages[PARSER_ERROR_OTHER];
		global_parser_result.errcode = PARSER_ERROR_OTHER;
		global_parser_result.errlocation = wkt_yylloc.last_column;
	}
	LWDEBUGF(4,"%s", str);
}

/**
* Parse a WKT geometry string into an LWGEOM structure. Note that this
* process uses globals and is not re-entrant, so don't call it within itself
* (eg, from within other functions in lwin_wkt.c) or from a threaded program.
* Note that parser_result.wkinput picks up a reference to wktstr.
*/
int lwgeom_parse_wkt(LWGEOM_PARSER_RESULT *parser_result, char *wktstr, int parser_check_flags)
{
	int parse_rv = 0;

	/* Clean up our global parser result. */
	lwgeom_parser_result_init(&global_parser_result);
	/* Work-around possible bug in GNU Bison 3.0.2 resulting in wkt_yylloc
	 * members not being initialized on yyparse() as documented here:
	 * https://www.gnu.org/software/bison/manual/html_node/Location-Type.html
	 * See discussion here:
	 * http://lists.osgeo.org/pipermail/postgis-devel/2014-September/024506.html
	 */
	wkt_yylloc.last_column = wkt_yylloc.last_line = \
	wkt_yylloc.first_column = wkt_yylloc.first_line = 1;

	/* Set the input text string, and parse checks. */
	global_parser_result.wkinput = wktstr;
	global_parser_result.parser_check_flags = parser_check_flags;
		
	wkt_lexer_init(wktstr); /* Lexer ready */
	parse_rv = wkt_yyparse(); /* Run the parse */
	LWDEBUGF(4,"wkt_yyparse returned %d", parse_rv);
	wkt_lexer_close(); /* Clean up lexer */
	
	/* A non-zero parser return is an error. */
	if ( parse_rv != 0 ) 
	{
		if( ! global_parser_result.errcode )
		{
			global_parser_result.errcode = PARSER_ERROR_OTHER;
			global_parser_result.message = parser_error_messages[PARSER_ERROR_OTHER];
			global_parser_result.errlocation = wkt_yylloc.last_column;
		}

		LWDEBUGF(5, "error returned by wkt_yyparse() @ %d: [%d] '%s'", 
		            global_parser_result.errlocation, 
		            global_parser_result.errcode, 
		            global_parser_result.message);
		
		/* Copy the global values into the return pointer */
		*parser_result = global_parser_result;
                wkt_yylex_destroy();
		return LW_FAILURE;
	}
	
	/* Copy the global value into the return pointer */
	*parser_result = global_parser_result;
        wkt_yylex_destroy();
	return LW_SUCCESS;
}

#define WKT_ERROR() { if ( global_parser_result.errcode != 0 ) { YYERROR; } }




/* Line 189 of yacc.c  */
#line 184 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     POINT_TOK = 258,
     LINESTRING_TOK = 259,
     POLYGON_TOK = 260,
     MPOINT_TOK = 261,
     MLINESTRING_TOK = 262,
     MPOLYGON_TOK = 263,
     MSURFACE_TOK = 264,
     MCURVE_TOK = 265,
     CURVEPOLYGON_TOK = 266,
     COMPOUNDCURVE_TOK = 267,
     CIRCULARSTRING_TOK = 268,
     COLLECTION_TOK = 269,
     RBRACKET_TOK = 270,
     LBRACKET_TOK = 271,
     COMMA_TOK = 272,
     EMPTY_TOK = 273,
     SEMICOLON_TOK = 274,
     TRIANGLE_TOK = 275,
     TIN_TOK = 276,
     POLYHEDRALSURFACE_TOK = 277,
     REF3D_TOK = 278,
     REF_ID_TOK = 279,
     REF_BOX_TOK = 280,
     DOUBLE_TOK = 281,
     DIMENSIONALITY_TOK = 282,
     SRID_TOK = 283
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 108 "lwin_wkt_parse.y"

	int integervalue;
	double doublevalue;
	char *stringvalue;
	LWGEOM *geometryvalue;
	POINT coordinatevalue;
	POINTARRAY *ptarrayvalue;



/* Line 214 of yacc.c  */
#line 259 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
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


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 284 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  84
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   313

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  140
/* YYNRULES -- Number of states.  */
#define YYNSTATES  283

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     9,    11,    13,    15,    17,    19,
      21,    23,    25,    27,    29,    31,    33,    35,    37,    39,
      41,    46,    52,    56,    59,    63,    65,    70,    76,    80,
      83,    87,    91,    95,    97,    99,   101,   106,   112,   116,
     119,   124,   130,   141,   146,   152,   156,   159,   164,   170,
     174,   177,   181,   183,   187,   189,   194,   200,   204,   207,
     211,   213,   217,   222,   228,   232,   235,   239,   241,   243,
     245,   247,   249,   253,   255,   259,   261,   265,   269,   274,
     280,   284,   287,   291,   295,   299,   301,   303,   305,   310,
     316,   320,   323,   327,   331,   335,   339,   341,   343,   345,
     347,   352,   358,   362,   365,   369,   371,   376,   382,   386,
     389,   394,   400,   404,   407,   411,   413,   417,   419,   426,
     434,   438,   441,   447,   452,   458,   462,   465,   469,   471,
     473,   477,   479,   484,   490,   494,   497,   501,   503,   506,
     510
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      30,     0,    -1,    31,    -1,    28,    19,    31,    -1,    68,
      -1,    60,    -1,    59,    -1,    53,    -1,    43,    -1,    46,
      -1,    65,    -1,    57,    -1,    40,    -1,    34,    -1,    55,
      -1,    36,    -1,    39,    -1,    63,    -1,    32,    -1,    37,
      -1,    14,    16,    33,    15,    -1,    14,    27,    16,    33,
      15,    -1,    14,    27,    18,    -1,    14,    18,    -1,    33,
      17,    31,    -1,    31,    -1,     9,    16,    35,    15,    -1,
       9,    27,    16,    35,    15,    -1,     9,    27,    18,    -1,
       9,    18,    -1,    35,    17,    43,    -1,    35,    17,    46,
      -1,    35,    17,    44,    -1,    43,    -1,    46,    -1,    44,
      -1,    21,    16,    62,    15,    -1,    21,    27,    16,    62,
      15,    -1,    21,    27,    18,    -1,    21,    18,    -1,    23,
      16,    38,    15,    -1,    23,    27,    16,    38,    15,    -1,
      24,    26,    25,    26,    26,    26,    17,    26,    26,    26,
      -1,    22,    16,    42,    15,    -1,    22,    27,    16,    42,
      15,    -1,    22,    27,    18,    -1,    22,    18,    -1,     8,
      16,    41,    15,    -1,     8,    27,    16,    41,    15,    -1,
       8,    27,    18,    -1,     8,    18,    -1,    41,    17,    44,
      -1,    44,    -1,    42,    17,    45,    -1,    45,    -1,     5,
      16,    50,    15,    -1,     5,    27,    16,    50,    15,    -1,
       5,    27,    18,    -1,     5,    18,    -1,    16,    50,    15,
      -1,    18,    -1,    16,    49,    15,    -1,    11,    16,    47,
      15,    -1,    11,    27,    16,    47,    15,    -1,    11,    27,
      18,    -1,    11,    18,    -1,    47,    17,    48,    -1,    48,
      -1,    61,    -1,    60,    -1,    53,    -1,    59,    -1,    49,
      17,    51,    -1,    51,    -1,    50,    17,    52,    -1,    52,
      -1,    16,    69,    15,    -1,    16,    69,    15,    -1,    12,
      16,    54,    15,    -1,    12,    27,    16,    54,    15,    -1,
      12,    27,    18,    -1,    12,    18,    -1,    54,    17,    59,
      -1,    54,    17,    60,    -1,    54,    17,    61,    -1,    59,
      -1,    60,    -1,    61,    -1,    10,    16,    56,    15,    -1,
      10,    27,    16,    56,    15,    -1,    10,    27,    18,    -1,
      10,    18,    -1,    56,    17,    59,    -1,    56,    17,    53,
      -1,    56,    17,    60,    -1,    56,    17,    61,    -1,    59,
      -1,    53,    -1,    60,    -1,    61,    -1,     7,    16,    58,
      15,    -1,     7,    27,    16,    58,    15,    -1,     7,    27,
      18,    -1,     7,    18,    -1,    58,    17,    61,    -1,    61,
      -1,    13,    16,    69,    15,    -1,    13,    27,    16,    69,
      15,    -1,    13,    27,    18,    -1,    13,    18,    -1,     4,
      16,    69,    15,    -1,     4,    27,    16,    69,    15,    -1,
       4,    27,    18,    -1,     4,    18,    -1,    16,    69,    15,
      -1,    18,    -1,    62,    17,    64,    -1,    64,    -1,    20,
      16,    16,    69,    15,    15,    -1,    20,    27,    16,    16,
      69,    15,    15,    -1,    20,    27,    18,    -1,    20,    18,
      -1,    16,    16,    69,    15,    15,    -1,     6,    16,    66,
      15,    -1,     6,    27,    16,    66,    15,    -1,     6,    27,
      18,    -1,     6,    18,    -1,    66,    17,    67,    -1,    67,
      -1,    70,    -1,    16,    70,    15,    -1,    18,    -1,     3,
      16,    69,    15,    -1,     3,    27,    16,    69,    15,    -1,
       3,    27,    18,    -1,     3,    18,    -1,    69,    17,    70,
      -1,    70,    -1,    26,    26,    -1,    26,    26,    26,    -1,
      26,    26,    26,    26,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   217,   217,   219,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     241,   243,   245,   247,   251,   253,   257,   259,   261,   263,
     267,   269,   271,   273,   275,   277,   281,   283,   285,   287,
     290,   292,   296,   302,   304,   306,   308,   312,   314,   316,
     318,   322,   324,   328,   330,   334,   336,   338,   340,   344,
     346,   350,   353,   355,   357,   359,   363,   365,   369,   370,
     371,   372,   375,   377,   381,   383,   387,   390,   393,   395,
     397,   399,   403,   405,   407,   409,   411,   413,   417,   419,
     421,   423,   427,   429,   431,   433,   435,   437,   439,   441,
     445,   447,   449,   451,   455,   457,   461,   463,   465,   467,
     471,   473,   475,   477,   481,   483,   487,   489,   493,   495,
     497,   499,   503,   507,   509,   511,   513,   517,   519,   523,
     525,   527,   531,   533,   535,   537,   541,   543,   547,   549,
     551
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "POINT_TOK", "LINESTRING_TOK",
  "POLYGON_TOK", "MPOINT_TOK", "MLINESTRING_TOK", "MPOLYGON_TOK",
  "MSURFACE_TOK", "MCURVE_TOK", "CURVEPOLYGON_TOK", "COMPOUNDCURVE_TOK",
  "CIRCULARSTRING_TOK", "COLLECTION_TOK", "RBRACKET_TOK", "LBRACKET_TOK",
  "COMMA_TOK", "EMPTY_TOK", "SEMICOLON_TOK", "TRIANGLE_TOK", "TIN_TOK",
  "POLYHEDRALSURFACE_TOK", "REF3D_TOK", "REF_ID_TOK", "REF_BOX_TOK",
  "DOUBLE_TOK", "DIMENSIONALITY_TOK", "SRID_TOK", "$accept", "geometry",
  "geometry_no_srid", "geometrycollection", "geometry_list",
  "multisurface", "surface_list", "tin", "ref3d", "ref3d_content",
  "polyhedralsurface", "multipolygon", "polygon_list", "patch_list",
  "polygon", "polygon_untagged", "patch", "curvepolygon", "curvering_list",
  "curvering", "patchring_list", "ring_list", "patchring", "ring",
  "compoundcurve", "compound_list", "multicurve", "curve_list",
  "multilinestring", "linestring_list", "circularstring", "linestring",
  "linestring_untagged", "triangle_list", "triangle", "triangle_untagged",
  "multipoint", "point_list", "point_untagged", "point", "ptarray",
  "coordinate", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    29,    30,    30,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      32,    32,    32,    32,    33,    33,    34,    34,    34,    34,
      35,    35,    35,    35,    35,    35,    36,    36,    36,    36,
      37,    37,    38,    39,    39,    39,    39,    40,    40,    40,
      40,    41,    41,    42,    42,    43,    43,    43,    43,    44,
      44,    45,    46,    46,    46,    46,    47,    47,    48,    48,
      48,    48,    49,    49,    50,    50,    51,    52,    53,    53,
      53,    53,    54,    54,    54,    54,    54,    54,    55,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    57,    57,    58,    58,    59,    59,    59,    59,
      60,    60,    60,    60,    61,    61,    62,    62,    63,    63,
      63,    63,    64,    65,    65,    65,    65,    66,    66,    67,
      67,    67,    68,    68,    68,    68,    69,    69,    70,    70,
      70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     5,     3,     2,     3,     1,     4,     5,     3,     2,
       3,     3,     3,     1,     1,     1,     4,     5,     3,     2,
       4,     5,    10,     4,     5,     3,     2,     4,     5,     3,
       2,     3,     1,     3,     1,     4,     5,     3,     2,     3,
       1,     3,     4,     5,     3,     2,     3,     1,     1,     1,
       1,     1,     3,     1,     3,     1,     3,     3,     4,     5,
       3,     2,     3,     3,     3,     1,     1,     1,     4,     5,
       3,     2,     3,     3,     3,     3,     1,     1,     1,     1,
       4,     5,     3,     2,     3,     1,     4,     5,     3,     2,
       4,     5,     3,     2,     3,     1,     3,     1,     6,     7,
       3,     2,     5,     4,     5,     3,     2,     3,     1,     1,
       3,     1,     4,     5,     3,     2,     3,     1,     2,     3,
       4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
      18,    13,    15,    19,    16,    12,     8,     9,     7,    14,
      11,     6,     5,    17,    10,     4,     0,   135,     0,     0,
     113,     0,     0,    58,     0,     0,   126,     0,     0,   103,
       0,     0,    50,     0,     0,    29,     0,     0,    91,     0,
       0,    65,     0,     0,    81,     0,     0,   109,     0,     0,
      23,     0,     0,   121,     0,     0,    39,     0,     0,    46,
       0,     0,     0,     0,     1,     0,     0,   137,     0,   134,
       0,     0,   112,     0,     0,    75,     0,    57,     0,   131,
       0,   128,   129,     0,   125,     0,   115,     0,   105,     0,
     102,     0,    60,     0,    52,     0,    49,     0,    33,    35,
      34,     0,    28,    97,     0,    96,    98,    99,     0,    90,
       0,    67,    70,    71,    69,    68,     0,    64,     0,    85,
      86,    87,     0,    80,     0,     0,   108,    25,     0,     0,
      22,     0,     0,   120,     0,     0,   117,     0,    38,     0,
       0,    54,     0,    45,     0,     0,     0,     3,   138,   132,
       0,     0,   110,     0,     0,    55,     0,     0,     0,   123,
       0,     0,     0,   100,     0,     0,     0,    47,     0,     0,
      26,     0,     0,    88,     0,     0,    62,     0,     0,    78,
       0,     0,   106,     0,    20,     0,     0,     0,     0,     0,
      36,     0,     0,     0,     0,    73,    43,     0,     0,     0,
      40,     0,   139,   136,   133,   111,    77,    74,    56,   130,
     127,   124,   114,   104,   101,    59,    51,    48,    30,    32,
      31,    27,    93,    92,    94,    95,    89,    66,    63,    82,
      83,    84,    79,   107,    24,    21,     0,     0,     0,   116,
      37,     0,    61,     0,    53,    44,     0,    41,   140,   118,
       0,     0,    76,    72,     0,   119,   122,     0,     0,     0,
       0,     0,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    18,   147,    20,   148,    21,   117,    22,    23,   165,
      24,    25,   113,   160,    26,   114,   161,    27,   130,   131,
     214,    94,   215,    95,    28,   138,    29,   124,    30,   107,
      31,    32,   135,   155,    33,   156,    34,   100,   101,    35,
      86,    87
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -94
static const yytype_int16 yypact[] =
{
      26,    53,    81,    85,   110,   145,   146,   149,   150,   162,
     163,   166,   167,   170,   180,   183,    -1,    -3,    19,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,     1,   -94,     6,     1,
     -94,     7,    29,   -94,    56,    25,   -94,    57,    88,   -94,
      93,   184,   -94,   188,    84,   -94,   193,    48,   -94,   196,
      48,   -94,   197,    52,   -94,   200,     1,   -94,   201,   111,
     -94,   204,    42,   -94,   205,    43,   -94,   208,    63,   -94,
     209,    66,    77,   111,   -94,    68,    27,   -94,     1,   -94,
     213,     1,   -94,     1,   214,   -94,    29,   -94,     1,   -94,
     217,   -94,   -94,    25,   -94,     1,   -94,   218,   -94,    88,
     -94,    29,   -94,   221,   -94,   184,   -94,   222,   -94,   -94,
     -94,    84,   -94,   -94,   225,   -94,   -94,   -94,    48,   -94,
     226,   -94,   -94,   -94,   -94,   -94,    48,   -94,   229,   -94,
     -94,   -94,    52,   -94,   230,     1,   -94,   -94,   233,   111,
     -94,     1,    82,   -94,    89,   234,   -94,    43,   -94,    94,
     237,   -94,    63,   -94,   101,   115,    66,   -94,   109,   -94,
       1,   238,   -94,   241,   242,   -94,    29,   245,   121,   -94,
      25,   246,   249,   -94,    88,   250,   253,   -94,   184,   254,
     -94,    84,   257,   -94,    48,   258,   -94,    48,   261,   -94,
      52,   262,   -94,   265,   -94,   111,   266,   269,     1,     1,
     -94,    43,   270,     1,   273,   -94,   -94,    63,   274,   116,
     -94,   125,   126,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,   138,   277,   278,   -94,
     -94,   281,   -94,    94,   -94,   -94,   130,   -94,   -94,   -94,
     144,   154,   -94,   -94,   134,   -94,   -94,   148,   174,   161,
     169,   177,   -94
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,     0,   -94,    59,   -94,    71,   -94,   -94,   131,
     -94,   -94,   185,   137,   -40,   -33,    86,   -34,   165,   105,
     -94,   -93,    41,   129,   -52,   164,   -94,   179,   -94,   199,
     -51,   -50,   -46,   152,   -94,    99,   -94,   210,   132,   -94,
     -38,   -41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      19,    90,   108,   177,   102,   123,   125,   126,   132,   133,
     134,   127,   139,   140,   118,    81,    83,   141,   186,    84,
     120,   119,    88,    91,    89,    92,    82,    85,   144,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    98,   169,    99,   170,    93,    13,    14,    15,    16,
     171,    85,     2,   173,    17,   174,     2,   178,   151,   154,
      10,    11,   102,   108,   105,    11,   106,   182,   105,    36,
     106,    37,    96,   103,    97,   104,   123,   125,   126,   159,
      38,   118,   127,   167,   132,   133,   134,   120,   119,     3,
     164,   139,   140,   166,   168,     9,   141,    39,   208,    40,
     111,    42,   112,    43,   105,   209,   106,   203,    41,   109,
     213,   110,    44,   207,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    45,   219,    46,   223,
     220,    13,    14,    15,    16,   222,   229,    47,   233,   102,
     267,   266,   242,   243,   244,   132,   133,   134,   245,   249,
     250,   238,   268,   269,   251,   236,   274,   240,   239,   275,
     277,    48,    51,    49,    52,    54,    57,    55,    58,   276,
     257,   258,    50,    53,   278,   261,    56,    59,    60,    63,
      61,    64,    66,    69,    67,    70,    72,   280,    73,    62,
      65,   279,   192,    68,    71,   281,    75,    74,    76,    78,
     111,    79,   112,   282,   115,   254,   116,    77,   206,   121,
      80,   122,   128,   136,   129,   137,   142,   145,   143,   146,
     149,   152,   150,   153,   157,   162,   158,   163,   172,   175,
     170,   176,   179,   183,   180,   184,   187,   190,   188,   191,
     193,   196,   194,   197,   199,   202,   200,   170,   204,   210,
     205,   211,   216,   224,   217,   170,   225,   226,   170,   170,
     228,   231,   176,   180,   232,   234,   170,   184,   235,   237,
     176,   188,   241,   246,   191,   194,   248,   252,   197,   200,
     253,   255,   170,   205,   256,   260,   170,   211,   262,   265,
     263,   217,   270,   271,   170,   170,   272,   221,   170,   218,
     189,   198,   247,   264,   273,   227,   201,   195,   185,   212,
     259,     0,   230,   181
};

static const yytype_int16 yycheck[] =
{
       0,    39,    48,    96,    45,    57,    57,    57,    60,    60,
      60,    57,    63,    63,    54,    16,    19,    63,   111,     0,
      54,    54,    16,    16,    18,    18,    27,    26,    66,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    16,    15,    18,    17,    16,    20,    21,    22,    23,
      88,    26,     4,    91,    28,    93,     4,    98,    16,    16,
      12,    13,   103,   109,    16,    13,    18,   105,    16,    16,
      18,    18,    16,    16,    18,    18,   128,   128,   128,    16,
      27,   121,   128,    83,   136,   136,   136,   121,   121,     5,
      24,   142,   142,    16,    26,    11,   142,    16,    16,    18,
      16,    16,    18,    18,    16,    16,    18,   145,    27,    16,
      16,    18,    27,   151,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    16,    26,    18,   170,
      15,    20,    21,    22,    23,    26,    15,    27,   184,   180,
      15,    25,   194,   194,   194,   197,   197,   197,   194,   200,
     200,   191,    26,    15,   200,   188,    26,   191,   191,    15,
      26,    16,    16,    18,    18,    16,    16,    18,    18,    15,
     208,   209,    27,    27,    26,   213,    27,    27,    16,    16,
      18,    18,    16,    16,    18,    18,    16,    26,    18,    27,
      27,    17,   121,    27,    27,    26,    16,    27,    18,    16,
      16,    18,    18,    26,    16,   205,    18,    27,   149,    16,
      27,    18,    16,    16,    18,    18,    16,    16,    18,    18,
      16,    16,    18,    18,    16,    16,    18,    18,    15,    15,
      17,    17,    15,    15,    17,    17,    15,    15,    17,    17,
      15,    15,    17,    17,    15,    15,    17,    17,    15,    15,
      17,    17,    15,    15,    17,    17,    15,    15,    17,    17,
      15,    15,    17,    17,    15,    15,    17,    17,    15,    15,
      17,    17,    15,    15,    17,    17,    15,    15,    17,    17,
      15,    15,    17,    17,    15,    15,    17,    17,    15,    15,
      17,    17,    15,    15,    17,    17,    15,   166,    17,   162,
     115,   136,   197,   217,   263,   176,   142,   128,   109,   157,
     211,    -1,   180,   103
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    20,    21,    22,    23,    28,    30,    31,
      32,    34,    36,    37,    39,    40,    43,    46,    53,    55,
      57,    59,    60,    63,    65,    68,    16,    18,    27,    16,
      18,    27,    16,    18,    27,    16,    18,    27,    16,    18,
      27,    16,    18,    27,    16,    18,    27,    16,    18,    27,
      16,    18,    27,    16,    18,    27,    16,    18,    27,    16,
      18,    27,    16,    18,    27,    16,    18,    27,    16,    18,
      27,    16,    27,    19,     0,    26,    69,    70,    16,    18,
      69,    16,    18,    16,    50,    52,    16,    18,    16,    18,
      66,    67,    70,    16,    18,    16,    18,    58,    61,    16,
      18,    16,    18,    41,    44,    16,    18,    35,    43,    44,
      46,    16,    18,    53,    56,    59,    60,    61,    16,    18,
      47,    48,    53,    59,    60,    61,    16,    18,    54,    59,
      60,    61,    16,    18,    69,    16,    18,    31,    33,    16,
      18,    16,    16,    18,    16,    62,    64,    16,    18,    16,
      42,    45,    16,    18,    24,    38,    16,    31,    26,    15,
      17,    69,    15,    69,    69,    15,    17,    50,    70,    15,
      17,    66,    69,    15,    17,    58,    50,    15,    17,    41,
      15,    17,    35,    15,    17,    56,    15,    17,    47,    15,
      17,    54,    15,    69,    15,    17,    33,    69,    16,    16,
      15,    17,    62,    16,    49,    51,    15,    17,    42,    26,
      15,    38,    26,    70,    15,    15,    15,    52,    15,    15,
      67,    15,    15,    61,    15,    15,    44,    15,    43,    44,
      46,    15,    53,    59,    60,    61,    15,    48,    15,    59,
      60,    61,    15,    15,    31,    15,    15,    69,    69,    64,
      15,    69,    15,    17,    45,    15,    25,    15,    26,    15,
      15,    15,    15,    51,    26,    15,    15,    26,    26,    17,
      26,    26,    26
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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
      case 31: /* "geometry_no_srid" */

/* Line 1009 of yacc.c  */
#line 193 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1465 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 32: /* "geometrycollection" */

/* Line 1009 of yacc.c  */
#line 194 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1474 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 34: /* "multisurface" */

/* Line 1009 of yacc.c  */
#line 201 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1483 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 35: /* "surface_list" */

/* Line 1009 of yacc.c  */
#line 180 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1492 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 36: /* "tin" */

/* Line 1009 of yacc.c  */
#line 208 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1501 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 37: /* "ref3d" */

/* Line 1009 of yacc.c  */
#line 212 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1510 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 38: /* "ref3d_content" */

/* Line 1009 of yacc.c  */
#line 211 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1519 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 39: /* "polyhedralsurface" */

/* Line 1009 of yacc.c  */
#line 207 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1528 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 40: /* "multipolygon" */

/* Line 1009 of yacc.c  */
#line 200 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1537 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 41: /* "polygon_list" */

/* Line 1009 of yacc.c  */
#line 181 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1546 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 42: /* "patch_list" */

/* Line 1009 of yacc.c  */
#line 182 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1555 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 43: /* "polygon" */

/* Line 1009 of yacc.c  */
#line 204 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1564 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 44: /* "polygon_untagged" */

/* Line 1009 of yacc.c  */
#line 206 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1573 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 45: /* "patch" */

/* Line 1009 of yacc.c  */
#line 205 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1582 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 46: /* "curvepolygon" */

/* Line 1009 of yacc.c  */
#line 191 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1591 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 47: /* "curvering_list" */

/* Line 1009 of yacc.c  */
#line 178 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1600 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 48: /* "curvering" */

/* Line 1009 of yacc.c  */
#line 192 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1609 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 49: /* "patchring_list" */

/* Line 1009 of yacc.c  */
#line 188 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1618 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 50: /* "ring_list" */

/* Line 1009 of yacc.c  */
#line 187 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1627 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 51: /* "patchring" */

/* Line 1009 of yacc.c  */
#line 177 "lwin_wkt_parse.y"
	{ ptarray_free((yyvaluep->ptarrayvalue)); };

/* Line 1009 of yacc.c  */
#line 1636 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 52: /* "ring" */

/* Line 1009 of yacc.c  */
#line 176 "lwin_wkt_parse.y"
	{ ptarray_free((yyvaluep->ptarrayvalue)); };

/* Line 1009 of yacc.c  */
#line 1645 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 53: /* "compoundcurve" */

/* Line 1009 of yacc.c  */
#line 190 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1654 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 54: /* "compound_list" */

/* Line 1009 of yacc.c  */
#line 186 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1663 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 55: /* "multicurve" */

/* Line 1009 of yacc.c  */
#line 197 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1672 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 56: /* "curve_list" */

/* Line 1009 of yacc.c  */
#line 185 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1681 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 57: /* "multilinestring" */

/* Line 1009 of yacc.c  */
#line 198 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1690 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 58: /* "linestring_list" */

/* Line 1009 of yacc.c  */
#line 184 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1699 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 59: /* "circularstring" */

/* Line 1009 of yacc.c  */
#line 189 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1708 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 60: /* "linestring" */

/* Line 1009 of yacc.c  */
#line 195 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1717 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 61: /* "linestring_untagged" */

/* Line 1009 of yacc.c  */
#line 196 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1726 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 62: /* "triangle_list" */

/* Line 1009 of yacc.c  */
#line 179 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1735 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 63: /* "triangle" */

/* Line 1009 of yacc.c  */
#line 209 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1744 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 64: /* "triangle_untagged" */

/* Line 1009 of yacc.c  */
#line 210 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1753 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 65: /* "multipoint" */

/* Line 1009 of yacc.c  */
#line 199 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1762 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 66: /* "point_list" */

/* Line 1009 of yacc.c  */
#line 183 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1771 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 67: /* "point_untagged" */

/* Line 1009 of yacc.c  */
#line 203 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1780 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 68: /* "point" */

/* Line 1009 of yacc.c  */
#line 202 "lwin_wkt_parse.y"
	{ lwgeom_free((yyvaluep->geometryvalue)); };

/* Line 1009 of yacc.c  */
#line 1789 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;
      case 69: /* "ptarray" */

/* Line 1009 of yacc.c  */
#line 175 "lwin_wkt_parse.y"
	{ ptarray_free((yyvaluep->ptarrayvalue)); };

/* Line 1009 of yacc.c  */
#line 1798 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
	break;

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;
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

/* Line 1464 of yacc.c  */
#line 218 "lwin_wkt_parse.y"
    { wkt_parser_geometry_new((yyvsp[(1) - (1)].geometryvalue), SRID_UNKNOWN); WKT_ERROR(); ;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 220 "lwin_wkt_parse.y"
    { wkt_parser_geometry_new((yyvsp[(3) - (3)].geometryvalue), (yyvsp[(1) - (3)].integervalue)); WKT_ERROR(); ;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 223 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 224 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 225 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 226 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 227 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 228 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 229 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 230 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 231 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 232 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 233 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 234 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 235 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 236 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 237 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 238 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 242 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COLLECTIONTYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 244 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COLLECTIONTYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 246 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COLLECTIONTYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 248 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COLLECTIONTYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 252 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 254 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 258 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTISURFACETYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 260 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTISURFACETYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 262 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTISURFACETYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 264 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTISURFACETYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 268 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 270 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 272 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 274 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 276 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 278 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 282 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(TINTYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 284 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(TINTYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 286 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(TINTYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 288 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(TINTYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 291 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(3) - (4)].geometryvalue);;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 293 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(4) - (5)].geometryvalue);;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 297 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_ref3d_new((yyvsp[(2) - (10)].doublevalue), (yyvsp[(4) - (10)].doublevalue), (yyvsp[(5) - (10)].doublevalue), (yyvsp[(6) - (10)].doublevalue), (yyvsp[(8) - (10)].doublevalue), (yyvsp[(9) - (10)].doublevalue), (yyvsp[(10) - (10)].doublevalue)); WKT_ERROR(); ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 303 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(POLYHEDRALSURFACETYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 305 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(POLYHEDRALSURFACETYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 307 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(POLYHEDRALSURFACETYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 309 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(POLYHEDRALSURFACETYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 313 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOLYGONTYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 315 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOLYGONTYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 317 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOLYGONTYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 319 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOLYGONTYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 323 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 325 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 329 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 331 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 335 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize((yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 337 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize((yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 339 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize(NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 341 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize(NULL, NULL); WKT_ERROR(); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 345 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(2) - (3)].geometryvalue); ;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 347 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize(NULL, NULL); WKT_ERROR(); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 350 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(2) - (3)].geometryvalue); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 354 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_finalize((yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 356 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_finalize((yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 358 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_finalize(NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 360 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_finalize(NULL, NULL); WKT_ERROR(); ;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 364 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_add_ring((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 366 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 369 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 370 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 371 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 372 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = (yyvsp[(1) - (1)].geometryvalue); ;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 376 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_add_ring((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].ptarrayvalue),'Z'); WKT_ERROR(); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 378 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_new((yyvsp[(1) - (1)].ptarrayvalue),'Z'); WKT_ERROR(); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 382 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_add_ring((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].ptarrayvalue),'2'); WKT_ERROR(); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 384 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_polygon_new((yyvsp[(1) - (1)].ptarrayvalue),'2'); WKT_ERROR(); ;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 387 "lwin_wkt_parse.y"
    { (yyval.ptarrayvalue) = (yyvsp[(2) - (3)].ptarrayvalue); ;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 390 "lwin_wkt_parse.y"
    { (yyval.ptarrayvalue) = (yyvsp[(2) - (3)].ptarrayvalue); ;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 394 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COMPOUNDTYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 396 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COMPOUNDTYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 398 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COMPOUNDTYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 400 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COMPOUNDTYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 404 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_compound_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 406 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_compound_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 408 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_compound_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 410 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_compound_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 412 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_compound_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 414 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_compound_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 418 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTICURVETYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 420 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTICURVETYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 422 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTICURVETYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 424 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTICURVETYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 428 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 430 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 432 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 434 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 436 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 438 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 440 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 442 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 446 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTILINETYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 448 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTILINETYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 450 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTILINETYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 452 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTILINETYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 456 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 458 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 462 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_circularstring_new((yyvsp[(3) - (4)].ptarrayvalue), NULL); WKT_ERROR(); ;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 464 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_circularstring_new((yyvsp[(4) - (5)].ptarrayvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 466 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_circularstring_new(NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 468 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_circularstring_new(NULL, NULL); WKT_ERROR(); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 472 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_linestring_new((yyvsp[(3) - (4)].ptarrayvalue), NULL); WKT_ERROR(); ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 474 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_linestring_new((yyvsp[(4) - (5)].ptarrayvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 476 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_linestring_new(NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 478 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_linestring_new(NULL, NULL); WKT_ERROR(); ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 482 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_linestring_new((yyvsp[(2) - (3)].ptarrayvalue), NULL); WKT_ERROR(); ;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 484 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_linestring_new(NULL, NULL); WKT_ERROR(); ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 488 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 490 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 494 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_triangle_new((yyvsp[(4) - (6)].ptarrayvalue), NULL); WKT_ERROR(); ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 496 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_triangle_new((yyvsp[(5) - (7)].ptarrayvalue), (yyvsp[(2) - (7)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 498 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_triangle_new(NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 500 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_triangle_new(NULL, NULL); WKT_ERROR(); ;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 504 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_triangle_new((yyvsp[(3) - (5)].ptarrayvalue), NULL); WKT_ERROR(); ;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 508 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOINTTYPE, (yyvsp[(3) - (4)].geometryvalue), NULL); WKT_ERROR(); ;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 510 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOINTTYPE, (yyvsp[(4) - (5)].geometryvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 512 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOINTTYPE, NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 514 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOINTTYPE, NULL, NULL); WKT_ERROR(); ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 518 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[(1) - (3)].geometryvalue),(yyvsp[(3) - (3)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 520 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[(1) - (1)].geometryvalue)); WKT_ERROR(); ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 524 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_point_new(wkt_parser_ptarray_new((yyvsp[(1) - (1)].coordinatevalue)),NULL); WKT_ERROR(); ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 526 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_point_new(wkt_parser_ptarray_new((yyvsp[(2) - (3)].coordinatevalue)),NULL); WKT_ERROR(); ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 528 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_point_new(NULL, NULL); WKT_ERROR(); ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 532 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_point_new((yyvsp[(3) - (4)].ptarrayvalue), NULL); WKT_ERROR(); ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 534 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_point_new((yyvsp[(4) - (5)].ptarrayvalue), (yyvsp[(2) - (5)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 536 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_point_new(NULL, (yyvsp[(2) - (3)].stringvalue)); WKT_ERROR(); ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 538 "lwin_wkt_parse.y"
    { (yyval.geometryvalue) = wkt_parser_point_new(NULL,NULL); WKT_ERROR(); ;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 542 "lwin_wkt_parse.y"
    { (yyval.ptarrayvalue) = wkt_parser_ptarray_add_coord((yyvsp[(1) - (3)].ptarrayvalue), (yyvsp[(3) - (3)].coordinatevalue)); WKT_ERROR(); ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 544 "lwin_wkt_parse.y"
    { (yyval.ptarrayvalue) = wkt_parser_ptarray_new((yyvsp[(1) - (1)].coordinatevalue)); WKT_ERROR(); ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 548 "lwin_wkt_parse.y"
    { (yyval.coordinatevalue) = wkt_parser_coord_2((yyvsp[(1) - (2)].doublevalue), (yyvsp[(2) - (2)].doublevalue)); WKT_ERROR(); ;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 550 "lwin_wkt_parse.y"
    { (yyval.coordinatevalue) = wkt_parser_coord_3((yyvsp[(1) - (3)].doublevalue), (yyvsp[(2) - (3)].doublevalue), (yyvsp[(3) - (3)].doublevalue)); WKT_ERROR(); ;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 552 "lwin_wkt_parse.y"
    { (yyval.coordinatevalue) = wkt_parser_coord_4((yyvsp[(1) - (4)].doublevalue), (yyvsp[(2) - (4)].doublevalue), (yyvsp[(3) - (4)].doublevalue), (yyvsp[(4) - (4)].doublevalue)); WKT_ERROR(); ;}
    break;



/* Line 1464 of yacc.c  */
#line 3103 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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

  yyerror_range[0] = yylsp[1-yylen];
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
      if (yyn != YYPACT_NINF)
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

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
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



/* Line 1684 of yacc.c  */
#line 554 "lwin_wkt_parse.y"



