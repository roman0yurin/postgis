/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1685 of yacc.c  */
#line 108 "lwin_wkt_parse.y"

	int integervalue;
	double doublevalue;
	char *stringvalue;
	LWGEOM *geometryvalue;
	POINT coordinatevalue;
	POINTARRAY *ptarrayvalue;



/* Line 1685 of yacc.c  */
#line 90 "C:/db/ext_lib/postgis/liblwgeom/lwin_wkt_parse.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE wkt_yylval;

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

extern YYLTYPE wkt_yylloc;

