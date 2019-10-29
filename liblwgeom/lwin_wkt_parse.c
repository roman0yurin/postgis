/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         wkt_yyparse
#define yylex           wkt_yylex
#define yyerror         wkt_yyerror
#define yydebug         wkt_yydebug
#define yynerrs         wkt_yynerrs

#define yylval          wkt_yylval
#define yychar          wkt_yychar
#define yylloc          wkt_yylloc

/* Copy the first part of user declarations.  */
#line 1 "lwin_wkt_parse.y" /* yacc.c:339  */


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
void wkt_yyerror(__attribute__((__unused__)) const char *str)
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
	if ( parse_rv || global_parser_result.errcode )
	{
		if( ! global_parser_result.errcode )
		{
			global_parser_result.errcode = PARSER_ERROR_OTHER;
			global_parser_result.message = parser_error_messages[PARSER_ERROR_OTHER];
			global_parser_result.errlocation = wkt_yylloc.last_column;
		}
		else if (global_parser_result.geom)
		{
			lwgeom_free(global_parser_result.geom);
			global_parser_result.geom = NULL;
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



#line 183 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "lwin_wkt_parse.h".  */
#ifndef YY_WKT_YY_HOME_SERGHY_PROJECTS_TRUNK_SGAZ_DB_V2_EXT_LIB_POSTGIS_LIBLWGEOM_LWIN_WKT_PARSE_H_INCLUDED
# define YY_WKT_YY_HOME_SERGHY_PROJECTS_TRUNK_SGAZ_DB_V2_EXT_LIB_POSTGIS_LIBLWGEOM_LWIN_WKT_PARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int wkt_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    MULTIMESH_TOK = 281,
    DOUBLE_TOK = 282,
    DIMENSIONALITY_TOK = 283,
    SRID_TOK = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 112 "lwin_wkt_parse.y" /* yacc.c:355  */

	int integervalue;
	double doublevalue;
	char *stringvalue;
	LWGEOM *geometryvalue;
	POINT coordinatevalue;
	POINTARRAY *ptarrayvalue;

#line 262 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE wkt_yylval;
extern YYLTYPE wkt_yylloc;
int wkt_yyparse (void);

#endif /* !YY_WKT_YY_HOME_SERGHY_PROJECTS_TRUNK_SGAZ_DB_V2_EXT_LIB_POSTGIS_LIBLWGEOM_LWIN_WKT_PARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 293 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   330

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  301

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   284

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   228,   228,   230,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   253,   255,   257,   259,   263,   265,   269,   271,   273,
     275,   279,   281,   283,   285,   287,   289,   293,   295,   297,
     299,   302,   304,   308,   310,   312,   314,   317,   323,   325,
     327,   329,   333,   335,   337,   339,   343,   345,   349,   351,
     355,   357,   361,   363,   365,   367,   371,   373,   377,   379,
     383,   386,   388,   390,   392,   396,   398,   402,   403,   404,
     405,   408,   410,   414,   416,   420,   423,   426,   428,   430,
     432,   436,   438,   440,   442,   444,   446,   450,   452,   454,
     456,   460,   462,   464,   466,   468,   470,   472,   474,   478,
     480,   482,   484,   488,   490,   494,   496,   498,   500,   504,
     506,   508,   510,   514,   516,   520,   522,   526,   528,   530,
     532,   536,   540,   542,   544,   546,   550,   552,   556,   558,
     560,   564,   566,   568,   570,   574,   576,   580,   582,   584
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
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
  "MULTIMESH_TOK", "DOUBLE_TOK", "DIMENSIONALITY_TOK", "SRID_TOK",
  "$accept", "geometry", "geometry_no_srid", "geometrycollection",
  "geometry_list", "multisurface", "surface_list", "tin", "ref3d",
  "multimesh", "ref3d_content", "polyhedralsurface", "multipolygon",
  "polygon_list", "tin_list", "patch_list", "polygon", "polygon_untagged",
  "tin_untagged", "patch", "curvepolygon", "curvering_list", "curvering",
  "patchring_list", "ring_list", "patchring", "ring", "compoundcurve",
  "compound_list", "multicurve", "curve_list", "multilinestring",
  "linestring_list", "circularstring", "linestring", "linestring_untagged",
  "triangle_list", "triangle", "triangle_untagged", "multipoint",
  "point_list", "point_untagged", "point", "ptarray", "coordinate", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
};
# endif

#define YYPACT_NINF -122

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-122)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     114,    21,    27,    32,    36,    41,    47,    78,    84,    85,
     113,   146,   153,   154,   181,   194,    -3,   195,    42,    16,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,    -4,  -122,
      28,    -4,  -122,    56,    31,  -122,    64,     4,  -122,    89,
      93,  -122,   126,   157,  -122,   199,    24,  -122,   202,    14,
    -122,   203,    14,  -122,   208,    20,  -122,   209,    -4,  -122,
     212,   182,  -122,   213,    46,  -122,   216,    51,  -122,   217,
      52,  -122,   220,    53,    55,   221,  -122,   224,   182,  -122,
      49,   115,  -122,    -4,  -122,   183,    -4,  -122,    -4,   226,
    -122,    31,  -122,    -4,  -122,   229,  -122,  -122,     4,  -122,
      -4,  -122,   230,  -122,    93,  -122,    31,  -122,   233,  -122,
     157,  -122,   234,  -122,  -122,  -122,    24,  -122,  -122,   237,
    -122,  -122,  -122,    14,  -122,   238,  -122,  -122,  -122,  -122,
    -122,    14,  -122,   241,  -122,  -122,  -122,    20,  -122,   242,
      -4,  -122,  -122,   245,   182,  -122,    -4,    65,  -122,    77,
     246,  -122,    51,  -122,    82,   249,  -122,    52,  -122,    81,
      99,    53,    51,  -122,   250,  -122,   221,  -122,  -122,    88,
    -122,    -4,   253,  -122,   254,   257,  -122,    31,   258,   118,
    -122,     4,   261,   262,  -122,    93,   265,   266,  -122,   157,
     269,  -122,    24,   270,  -122,    14,   273,  -122,    14,   274,
    -122,    20,   277,  -122,   278,  -122,   182,   281,   282,    -4,
      -4,  -122,    51,   285,    -4,   286,  -122,  -122,    52,   289,
      79,  -122,   123,   290,  -122,   221,   293,   112,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,   130,   294,   297,  -122,  -122,   298,  -122,    82,  -122,
    -122,   121,  -122,  -122,  -122,  -122,  -122,  -122,   137,   144,
    -122,  -122,   139,  -122,  -122,   140,   159,   150,   156,   174,
    -122
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,    18,    13,    15,    19,    20,    16,    12,     8,     9,
       7,    14,    11,     6,     5,    17,    10,     4,     0,   144,
       0,     0,   122,     0,     0,    65,     0,     0,   135,     0,
       0,   112,     0,     0,    55,     0,     0,    30,     0,     0,
     100,     0,     0,    74,     0,     0,    90,     0,     0,   118,
       0,     0,    24,     0,     0,   130,     0,     0,    40,     0,
       0,    51,     0,     0,     0,     0,    46,     0,     0,     1,
       0,     0,   146,     0,   143,     0,     0,   121,     0,     0,
      84,     0,    64,     0,   140,     0,   137,   138,     0,   134,
       0,   124,     0,   114,     0,   111,     0,    67,     0,    57,
       0,    54,     0,    34,    36,    35,     0,    29,   106,     0,
     105,   107,   108,     0,    99,     0,    76,    79,    80,    78,
      77,     0,    73,     0,    94,    95,    96,     0,    89,     0,
       0,   117,    26,     0,     0,    23,     0,     0,   129,     0,
       0,   126,     0,    39,     0,     0,    61,     0,    50,     0,
       0,     0,     0,    69,     0,    59,     0,    45,     3,   147,
     141,     0,     0,   119,     0,     0,    62,     0,     0,     0,
     132,     0,     0,     0,   109,     0,     0,     0,    52,     0,
       0,    27,     0,     0,    97,     0,     0,    71,     0,     0,
      87,     0,     0,   115,     0,    21,     0,     0,     0,     0,
       0,    37,     0,     0,     0,     0,    82,    48,     0,     0,
       0,    41,     0,     0,    43,     0,     0,   148,   145,   142,
     120,    86,    83,    63,   139,   136,   133,   123,   113,   110,
      66,    56,    53,    31,    33,    32,    28,   102,   101,   103,
     104,    98,    75,    72,    91,    92,    93,    88,   116,    25,
      22,     0,     0,     0,   125,    38,     0,    70,     0,    60,
      49,     0,    42,    68,    58,    44,   149,   127,     0,     0,
      85,    81,     0,   128,   131,     0,     0,     0,     0,     0,
      47
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -122,  -122,     0,  -122,    60,  -122,    80,  -122,  -122,  -122,
     145,  -122,  -122,    87,   141,   151,   -42,   -53,    86,    91,
     -37,   179,   116,  -122,   -95,    44,   136,   -54,   178,  -122,
     193,  -122,   214,   -55,   -50,   -48,  -121,  -122,   105,  -122,
     222,   138,  -122,   -40,   -13
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,   152,    21,   153,    22,   122,    23,    24,    25,
     170,    26,    27,   118,   174,   165,    28,   119,   175,   166,
      29,   135,   136,   225,    99,   226,   100,    30,   143,    31,
     129,    32,   112,    33,    34,   140,   160,    35,   161,    36,
     105,   106,    37,    91,    92
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      20,    95,   113,   124,   130,   128,   188,   138,   137,   131,
     144,   132,   139,    83,   123,   145,    89,   146,     2,   125,
     103,   197,   104,    90,     2,    84,    10,    11,   149,     3,
     110,    90,   111,    11,   107,     9,   110,    38,   111,    39,
     116,   223,   117,    41,    93,    42,    94,    98,    44,    40,
      45,   233,    47,   182,    48,    43,   184,    50,   185,    51,
      46,    88,   156,    53,    49,    54,   113,   159,   164,    52,
     193,   171,    96,   124,    97,    55,   179,   169,   130,   128,
     101,   219,   102,   131,   123,   132,   138,   137,   178,   125,
     189,   139,   144,   220,    56,   107,    57,   145,   224,   146,
      59,    62,    60,    63,   281,   108,    58,   109,   230,   110,
     214,   111,    61,    64,   231,   237,   218,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    65,
     180,    66,   181,   244,    13,    14,    15,    16,   282,   286,
      17,    67,   114,    18,   115,   287,   251,   248,   292,   254,
     258,   257,   293,   138,   137,   259,   264,   260,   139,   294,
     253,   265,    68,   266,    69,   255,   295,   296,   238,    71,
      74,    72,    75,   116,    70,   117,   297,   298,   107,   272,
     273,    73,    76,   299,   276,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    77,   183,    78,
     181,   300,    13,    14,    15,    16,   203,   200,    17,    79,
      80,    85,    81,    86,   217,   120,   269,   121,   126,   133,
     127,   134,    82,    87,   141,   147,   142,   148,   150,   154,
     151,   155,   157,   162,   158,   163,   167,   172,   168,   173,
     176,   186,   177,   187,   190,   194,   191,   195,   198,   201,
     199,   202,   204,   207,   205,   208,   210,   213,   211,   181,
     215,   221,   216,   222,   227,   234,   228,   235,   239,   240,
     181,   181,   241,   243,   181,   187,   246,   247,   191,   181,
     249,   250,   195,   187,   252,   256,   199,   202,   261,   263,
     205,   208,   267,   268,   211,   181,   270,   271,   216,   181,
     275,   277,   222,   278,   280,   283,   228,   222,   285,   288,
     235,   181,   289,   290,   181,   181,   232,   236,   229,   279,
     209,   284,   291,   242,   262,   212,   206,   274,   196,   245,
     192
};

static const yytype_uint16 yycheck[] =
{
       0,    41,    50,    56,    59,    59,   101,    62,    62,    59,
      65,    59,    62,    16,    56,    65,     0,    65,     4,    56,
      16,   116,    18,    27,     4,    28,    12,    13,    68,     5,
      16,    27,    18,    13,    47,    11,    16,    16,    18,    18,
      16,   162,    18,    16,    16,    18,    18,    16,    16,    28,
      18,   172,    16,    93,    18,    28,    96,    16,    98,    18,
      28,    19,    16,    16,    28,    18,   114,    16,    16,    28,
     110,    16,    16,   126,    18,    28,    27,    24,   133,   133,
      16,    16,    18,   133,   126,   133,   141,   141,    88,   126,
     103,   141,   147,    16,    16,   108,    18,   147,    16,   147,
      16,    16,    18,    18,    25,    16,    28,    18,    27,    16,
     150,    18,    28,    28,    15,    27,   156,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    16,
      15,    18,    17,    15,    20,    21,    22,    23,    15,    27,
      26,    28,    16,    29,    18,    15,   199,   195,    27,   202,
     205,   205,    15,   208,   208,   205,   211,   205,   208,    15,
     202,   211,    16,   211,    18,   202,    27,    27,   181,    16,
      16,    18,    18,    16,    28,    18,    17,    27,   191,   219,
     220,    28,    28,    27,   224,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    16,    15,    18,
      17,    27,    20,    21,    22,    23,   126,   120,    26,    28,
      16,    16,    18,    18,   154,    16,   216,    18,    16,    16,
      18,    18,    28,    28,    16,    16,    18,    18,    16,    16,
      18,    18,    16,    16,    18,    18,    16,    16,    18,    18,
      16,    15,    18,    17,    15,    15,    17,    17,    15,    15,
      17,    17,    15,    15,    17,    17,    15,    15,    17,    17,
      15,    15,    17,    17,    15,    15,    17,    17,    15,    15,
      17,    17,    15,    15,    17,    17,    15,    15,    17,    17,
      15,    15,    17,    17,    15,    15,    17,    17,    15,    15,
      17,    17,    15,    15,    17,    17,    15,    15,    17,    17,
      15,    15,    17,    17,    15,    15,    17,    17,    15,    15,
      17,    17,    15,    15,    17,    17,   171,   176,   167,   228,
     141,   235,   278,   187,   208,   147,   133,   222,   114,   191,
     108
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    20,    21,    22,    23,    26,    29,    31,
      32,    33,    35,    37,    38,    39,    41,    42,    46,    50,
      57,    59,    61,    63,    64,    67,    69,    72,    16,    18,
      28,    16,    18,    28,    16,    18,    28,    16,    18,    28,
      16,    18,    28,    16,    18,    28,    16,    18,    28,    16,
      18,    28,    16,    18,    28,    16,    18,    28,    16,    18,
      28,    16,    18,    28,    16,    18,    28,    16,    18,    28,
      16,    18,    28,    16,    28,    16,    18,    28,    19,     0,
      27,    73,    74,    16,    18,    73,    16,    18,    16,    54,
      56,    16,    18,    16,    18,    70,    71,    74,    16,    18,
      16,    18,    62,    65,    16,    18,    16,    18,    43,    47,
      16,    18,    36,    46,    47,    50,    16,    18,    57,    60,
      63,    64,    65,    16,    18,    51,    52,    57,    63,    64,
      65,    16,    18,    58,    63,    64,    65,    16,    18,    73,
      16,    18,    32,    34,    16,    18,    16,    16,    18,    16,
      66,    68,    16,    18,    16,    45,    49,    16,    18,    24,
      40,    16,    16,    18,    44,    48,    16,    18,    32,    27,
      15,    17,    73,    15,    73,    73,    15,    17,    54,    74,
      15,    17,    70,    73,    15,    17,    62,    54,    15,    17,
      43,    15,    17,    36,    15,    17,    60,    15,    17,    51,
      15,    17,    58,    15,    73,    15,    17,    34,    73,    16,
      16,    15,    17,    66,    16,    53,    55,    15,    17,    45,
      27,    15,    40,    66,    15,    17,    44,    27,    74,    15,
      15,    15,    56,    15,    15,    71,    15,    15,    65,    15,
      15,    47,    15,    46,    47,    50,    15,    57,    63,    64,
      65,    15,    52,    15,    63,    64,    65,    15,    15,    32,
      15,    15,    73,    73,    68,    15,    73,    15,    17,    49,
      15,    25,    15,    15,    48,    15,    27,    15,    15,    15,
      15,    55,    27,    15,    15,    27,    27,    17,    27,    27,
      27
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    31,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    33,    33,    33,    33,    34,    34,    35,    35,    35,
      35,    36,    36,    36,    36,    36,    36,    37,    37,    37,
      37,    38,    38,    39,    39,    39,    39,    40,    41,    41,
      41,    41,    42,    42,    42,    42,    43,    43,    44,    44,
      45,    45,    46,    46,    46,    46,    47,    47,    48,    48,
      49,    50,    50,    50,    50,    51,    51,    52,    52,    52,
      52,    53,    53,    54,    54,    55,    56,    57,    57,    57,
      57,    58,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    60,    60,    60,    60,    60,    60,    60,    60,    61,
      61,    61,    61,    62,    62,    63,    63,    63,    63,    64,
      64,    64,    64,    65,    65,    66,    66,    67,    67,    67,
      67,    68,    69,    69,    69,    69,    70,    70,    71,    71,
      71,    72,    72,    72,    72,    73,    73,    74,    74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     5,     3,     2,     3,     1,     4,     5,     3,
       2,     3,     3,     3,     1,     1,     1,     4,     5,     3,
       2,     4,     5,     4,     5,     3,     2,    10,     4,     5,
       3,     2,     4,     5,     3,     2,     3,     1,     3,     1,
       3,     1,     4,     5,     3,     2,     3,     1,     3,     1,
       3,     4,     5,     3,     2,     3,     1,     1,     1,     1,
       1,     3,     1,     3,     1,     3,     3,     4,     5,     3,
       2,     3,     3,     3,     1,     1,     1,     4,     5,     3,
       2,     3,     3,     3,     3,     1,     1,     1,     1,     4,
       5,     3,     2,     3,     1,     4,     5,     3,     2,     4,
       5,     3,     2,     3,     1,     3,     1,     6,     7,     3,
       2,     5,     4,     5,     3,     2,     3,     1,     1,     3,
       1,     4,     5,     3,     2,     3,     1,     2,     3,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
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
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 32: /* geometry_no_srid  */
#line 201 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1402 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 33: /* geometrycollection  */
#line 202 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1408 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 35: /* multisurface  */
#line 209 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1414 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 36: /* surface_list  */
#line 188 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1420 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 37: /* tin  */
#line 217 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1426 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 38: /* ref3d  */
#line 221 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1432 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 39: /* multimesh  */
#line 222 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1438 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 40: /* ref3d_content  */
#line 220 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1444 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 41: /* polyhedralsurface  */
#line 216 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1450 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 42: /* multipolygon  */
#line 208 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1456 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 43: /* polygon_list  */
#line 189 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1462 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 44: /* tin_list  */
#line 223 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1468 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 45: /* patch_list  */
#line 190 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1474 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 46: /* polygon  */
#line 212 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1480 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 47: /* polygon_untagged  */
#line 214 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1486 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 48: /* tin_untagged  */
#line 215 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1492 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 49: /* patch  */
#line 213 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1498 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 50: /* curvepolygon  */
#line 199 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1504 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 51: /* curvering_list  */
#line 186 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1510 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 52: /* curvering  */
#line 200 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1516 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 53: /* patchring_list  */
#line 196 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1522 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 54: /* ring_list  */
#line 195 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1528 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 55: /* patchring  */
#line 185 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { ptarray_free(((*yyvaluep).ptarrayvalue)); }
#line 1534 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 56: /* ring  */
#line 184 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { ptarray_free(((*yyvaluep).ptarrayvalue)); }
#line 1540 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 57: /* compoundcurve  */
#line 198 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1546 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 58: /* compound_list  */
#line 194 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1552 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 59: /* multicurve  */
#line 205 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1558 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 60: /* curve_list  */
#line 193 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1564 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 61: /* multilinestring  */
#line 206 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1570 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 62: /* linestring_list  */
#line 192 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1576 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 63: /* circularstring  */
#line 197 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1582 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 64: /* linestring  */
#line 203 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1588 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 65: /* linestring_untagged  */
#line 204 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1594 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 66: /* triangle_list  */
#line 187 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1600 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 67: /* triangle  */
#line 218 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1606 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 68: /* triangle_untagged  */
#line 219 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1612 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 69: /* multipoint  */
#line 207 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1618 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 70: /* point_list  */
#line 191 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1624 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 71: /* point_untagged  */
#line 211 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1630 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 72: /* point  */
#line 210 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { lwgeom_free(((*yyvaluep).geometryvalue)); }
#line 1636 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;

    case 73: /* ptarray  */
#line 183 "lwin_wkt_parse.y" /* yacc.c:1257  */
      { ptarray_free(((*yyvaluep).ptarrayvalue)); }
#line 1642 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
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

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 229 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { wkt_parser_geometry_new((yyvsp[0].geometryvalue), SRID_UNKNOWN); WKT_ERROR(); }
#line 1930 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 3:
#line 231 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { wkt_parser_geometry_new((yyvsp[0].geometryvalue), (yyvsp[-2].integervalue)); WKT_ERROR(); }
#line 1936 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 4:
#line 234 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1942 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 5:
#line 235 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1948 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 6:
#line 236 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1954 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 7:
#line 237 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1960 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 8:
#line 238 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1966 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 9:
#line 239 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1972 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 10:
#line 240 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1978 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 11:
#line 241 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1984 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 12:
#line 242 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1990 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 13:
#line 243 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 1996 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 14:
#line 244 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2002 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 15:
#line 245 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2008 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 16:
#line 246 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2014 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 17:
#line 247 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2020 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 18:
#line 248 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2026 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 19:
#line 249 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2032 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 20:
#line 250 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2038 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 21:
#line 254 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COLLECTIONTYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2044 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 22:
#line 256 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COLLECTIONTYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2050 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 23:
#line 258 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COLLECTIONTYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2056 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 24:
#line 260 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COLLECTIONTYPE, NULL, NULL); WKT_ERROR(); }
#line 2062 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 25:
#line 264 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2068 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 26:
#line 266 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2074 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 27:
#line 270 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTISURFACETYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2080 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 28:
#line 272 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTISURFACETYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2086 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 29:
#line 274 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTISURFACETYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2092 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 30:
#line 276 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTISURFACETYPE, NULL, NULL); WKT_ERROR(); }
#line 2098 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 31:
#line 280 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2104 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 32:
#line 282 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2110 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 33:
#line 284 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2116 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 34:
#line 286 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2122 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 35:
#line 288 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2128 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 36:
#line 290 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2134 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 37:
#line 294 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(TINTYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2140 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 38:
#line 296 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(TINTYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2146 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 39:
#line 298 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(TINTYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2152 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 40:
#line 300 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(TINTYPE, NULL, NULL); WKT_ERROR(); }
#line 2158 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 41:
#line 303 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[-1].geometryvalue);}
#line 2164 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 42:
#line 305 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[-1].geometryvalue);}
#line 2170 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 43:
#line 309 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIMESH_TYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2176 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 44:
#line 311 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIMESH_TYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2182 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 45:
#line 313 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIMESH_TYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2188 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 46:
#line 315 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIMESH_TYPE, NULL, NULL); WKT_ERROR(); }
#line 2194 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 47:
#line 318 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_ref3d_new((yyvsp[-8].doublevalue), (yyvsp[-6].doublevalue), (yyvsp[-5].doublevalue), (yyvsp[-4].doublevalue), (yyvsp[-2].doublevalue), (yyvsp[-1].doublevalue), (yyvsp[0].doublevalue)); WKT_ERROR(); }
#line 2200 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 48:
#line 324 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(POLYHEDRALSURFACETYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2206 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 49:
#line 326 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(POLYHEDRALSURFACETYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2212 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 50:
#line 328 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(POLYHEDRALSURFACETYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2218 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 51:
#line 330 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(POLYHEDRALSURFACETYPE, NULL, NULL); WKT_ERROR(); }
#line 2224 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 52:
#line 334 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOLYGONTYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2230 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 53:
#line 336 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOLYGONTYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2236 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 54:
#line 338 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOLYGONTYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2242 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 55:
#line 340 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOLYGONTYPE, NULL, NULL); WKT_ERROR(); }
#line 2248 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 56:
#line 344 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2254 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 57:
#line 346 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2260 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 58:
#line 350 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2266 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 59:
#line 352 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2272 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 60:
#line 356 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2278 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 358 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2284 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 62:
#line 362 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize((yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2290 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 63:
#line 364 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize((yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2296 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 64:
#line 366 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize(NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2302 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 65:
#line 368 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize(NULL, NULL); WKT_ERROR(); }
#line 2308 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 66:
#line 372 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[-1].geometryvalue); }
#line 2314 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 67:
#line 374 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_finalize(NULL, NULL); WKT_ERROR(); }
#line 2320 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 68:
#line 378 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[-1].geometryvalue); }
#line 2326 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 69:
#line 380 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_tin_finalize(NULL, NULL); WKT_ERROR(); }
#line 2332 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 70:
#line 383 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[-1].geometryvalue); }
#line 2338 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 71:
#line 387 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_finalize((yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2344 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 72:
#line 389 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_finalize((yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2350 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 73:
#line 391 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_finalize(NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2356 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 74:
#line 393 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_finalize(NULL, NULL); WKT_ERROR(); }
#line 2362 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 75:
#line 397 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_add_ring((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2368 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 76:
#line 399 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_curvepolygon_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2374 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 77:
#line 402 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2380 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 78:
#line 403 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2386 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 79:
#line 404 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2392 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 80:
#line 405 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = (yyvsp[0].geometryvalue); }
#line 2398 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 81:
#line 409 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_add_ring((yyvsp[-2].geometryvalue),(yyvsp[0].ptarrayvalue),'Z'); WKT_ERROR(); }
#line 2404 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 82:
#line 411 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_new((yyvsp[0].ptarrayvalue),'Z'); WKT_ERROR(); }
#line 2410 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 83:
#line 415 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_add_ring((yyvsp[-2].geometryvalue),(yyvsp[0].ptarrayvalue),'2'); WKT_ERROR(); }
#line 2416 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 84:
#line 417 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_polygon_new((yyvsp[0].ptarrayvalue),'2'); WKT_ERROR(); }
#line 2422 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 85:
#line 420 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.ptarrayvalue) = (yyvsp[-1].ptarrayvalue); }
#line 2428 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 86:
#line 423 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.ptarrayvalue) = (yyvsp[-1].ptarrayvalue); }
#line 2434 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 87:
#line 427 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COMPOUNDTYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2440 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 88:
#line 429 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COMPOUNDTYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2446 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 89:
#line 431 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COMPOUNDTYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2452 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 90:
#line 433 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(COMPOUNDTYPE, NULL, NULL); WKT_ERROR(); }
#line 2458 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 91:
#line 437 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_compound_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2464 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 92:
#line 439 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_compound_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2470 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 93:
#line 441 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_compound_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2476 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 94:
#line 443 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_compound_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2482 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 95:
#line 445 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_compound_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2488 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 96:
#line 447 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_compound_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2494 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 97:
#line 451 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTICURVETYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2500 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 98:
#line 453 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTICURVETYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2506 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 99:
#line 455 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTICURVETYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2512 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 100:
#line 457 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTICURVETYPE, NULL, NULL); WKT_ERROR(); }
#line 2518 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 101:
#line 461 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2524 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 102:
#line 463 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2530 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 103:
#line 465 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2536 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 104:
#line 467 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2542 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 105:
#line 469 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2548 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 106:
#line 471 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2554 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 107:
#line 473 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2560 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 108:
#line 475 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2566 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 109:
#line 479 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTILINETYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2572 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 110:
#line 481 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTILINETYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2578 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 111:
#line 483 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTILINETYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2584 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 112:
#line 485 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTILINETYPE, NULL, NULL); WKT_ERROR(); }
#line 2590 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 113:
#line 489 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2596 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 114:
#line 491 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2602 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 115:
#line 495 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_circularstring_new((yyvsp[-1].ptarrayvalue), NULL); WKT_ERROR(); }
#line 2608 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 116:
#line 497 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_circularstring_new((yyvsp[-1].ptarrayvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2614 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 117:
#line 499 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_circularstring_new(NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2620 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 118:
#line 501 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_circularstring_new(NULL, NULL); WKT_ERROR(); }
#line 2626 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 119:
#line 505 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_linestring_new((yyvsp[-1].ptarrayvalue), NULL); WKT_ERROR(); }
#line 2632 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 120:
#line 507 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_linestring_new((yyvsp[-1].ptarrayvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2638 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 121:
#line 509 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_linestring_new(NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2644 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 122:
#line 511 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_linestring_new(NULL, NULL); WKT_ERROR(); }
#line 2650 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 123:
#line 515 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_linestring_new((yyvsp[-1].ptarrayvalue), NULL); WKT_ERROR(); }
#line 2656 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 124:
#line 517 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_linestring_new(NULL, NULL); WKT_ERROR(); }
#line 2662 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 125:
#line 521 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2668 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 126:
#line 523 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2674 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 127:
#line 527 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_triangle_new((yyvsp[-2].ptarrayvalue), NULL); WKT_ERROR(); }
#line 2680 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 128:
#line 529 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_triangle_new((yyvsp[-2].ptarrayvalue), (yyvsp[-5].stringvalue)); WKT_ERROR(); }
#line 2686 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 129:
#line 531 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_triangle_new(NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2692 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 130:
#line 533 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_triangle_new(NULL, NULL); WKT_ERROR(); }
#line 2698 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 131:
#line 537 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_triangle_new((yyvsp[-2].ptarrayvalue), NULL); WKT_ERROR(); }
#line 2704 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 132:
#line 541 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOINTTYPE, (yyvsp[-1].geometryvalue), NULL); WKT_ERROR(); }
#line 2710 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 133:
#line 543 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOINTTYPE, (yyvsp[-1].geometryvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2716 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 134:
#line 545 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOINTTYPE, NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2722 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 135:
#line 547 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_finalize(MULTIPOINTTYPE, NULL, NULL); WKT_ERROR(); }
#line 2728 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 136:
#line 551 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_add_geom((yyvsp[-2].geometryvalue),(yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2734 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 137:
#line 553 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_collection_new((yyvsp[0].geometryvalue)); WKT_ERROR(); }
#line 2740 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 138:
#line 557 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_point_new(wkt_parser_ptarray_new((yyvsp[0].coordinatevalue)),NULL); WKT_ERROR(); }
#line 2746 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 139:
#line 559 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_point_new(wkt_parser_ptarray_new((yyvsp[-1].coordinatevalue)),NULL); WKT_ERROR(); }
#line 2752 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 140:
#line 561 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_point_new(NULL, NULL); WKT_ERROR(); }
#line 2758 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 141:
#line 565 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_point_new((yyvsp[-1].ptarrayvalue), NULL); WKT_ERROR(); }
#line 2764 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 142:
#line 567 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_point_new((yyvsp[-1].ptarrayvalue), (yyvsp[-3].stringvalue)); WKT_ERROR(); }
#line 2770 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 143:
#line 569 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_point_new(NULL, (yyvsp[-1].stringvalue)); WKT_ERROR(); }
#line 2776 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 144:
#line 571 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.geometryvalue) = wkt_parser_point_new(NULL,NULL); WKT_ERROR(); }
#line 2782 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 145:
#line 575 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.ptarrayvalue) = wkt_parser_ptarray_add_coord((yyvsp[-2].ptarrayvalue), (yyvsp[0].coordinatevalue)); WKT_ERROR(); }
#line 2788 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 146:
#line 577 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.ptarrayvalue) = wkt_parser_ptarray_new((yyvsp[0].coordinatevalue)); WKT_ERROR(); }
#line 2794 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 147:
#line 581 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.coordinatevalue) = wkt_parser_coord_2((yyvsp[-1].doublevalue), (yyvsp[0].doublevalue)); WKT_ERROR(); }
#line 2800 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 148:
#line 583 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.coordinatevalue) = wkt_parser_coord_3((yyvsp[-2].doublevalue), (yyvsp[-1].doublevalue), (yyvsp[0].doublevalue)); WKT_ERROR(); }
#line 2806 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;

  case 149:
#line 585 "lwin_wkt_parse.y" /* yacc.c:1646  */
    { (yyval.coordinatevalue) = wkt_parser_coord_4((yyvsp[-3].doublevalue), (yyvsp[-2].doublevalue), (yyvsp[-1].doublevalue), (yyvsp[0].doublevalue)); WKT_ERROR(); }
#line 2812 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
    break;


#line 2816 "/home/serghy/Projects/trunk_sgaz_db_v2/ext_lib/postgis/liblwgeom/lwin_wkt_parse.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 587 "lwin_wkt_parse.y" /* yacc.c:1906  */


