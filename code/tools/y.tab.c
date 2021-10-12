/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "qgen.y"

/* 
 * Legal Notice 
 * 
 * This document and associated source code (the "Work") is a part of a 
 * benchmark specification maintained by the TPC. 
 * 
 * The TPC reserves all right, title, and interest to the Work as provided 
 * under U.S. and international laws, including without limitation all patent 
 * and trademark rights therein. 
 * 
 * No Warranty 
 * 
 * 1.1 TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THE INFORMATION 
 *     CONTAINED HEREIN IS PROVIDED "AS IS" AND WITH ALL FAULTS, AND THE 
 *     AUTHORS AND DEVELOPERS OF THE WORK HEREBY DISCLAIM ALL OTHER 
 *     WARRANTIES AND CONDITIONS, EITHER EXPRESS, IMPLIED OR STATUTORY, 
 *     INCLUDING, BUT NOT LIMITED TO, ANY (IF ANY) IMPLIED WARRANTIES, 
 *     DUTIES OR CONDITIONS OF MERCHANTABILITY, OF FITNESS FOR A PARTICULAR 
 *     PURPOSE, OF ACCURACY OR COMPLETENESS OF RESPONSES, OF RESULTS, OF 
 *     WORKMANLIKE EFFORT, OF LACK OF VIRUSES, AND OF LACK OF NEGLIGENCE. 
 *     ALSO, THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT, 
 *     QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR NON-INFRINGEMENT 
 *     WITH REGARD TO THE WORK. 
 * 1.2 IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THE WORK BE LIABLE TO 
 *     ANY OTHER PARTY FOR ANY DAMAGES, INCLUDING BUT NOT LIMITED TO THE 
 *     COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST PROFITS, LOSS 
 *     OF USE, LOSS OF DATA, OR ANY INCIDENTAL, CONSEQUENTIAL, DIRECT, 
 *     INDIRECT, OR SPECIAL DAMAGES WHETHER UNDER CONTRACT, TORT, WARRANTY,
 *     OR OTHERWISE, ARISING IN ANY WAY OUT OF THIS OR ANY OTHER AGREEMENT 
 *     RELATING TO THE WORK, WHETHER OR NOT SUCH AUTHOR OR DEVELOPER HAD 
 *     ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES. 
 * 
 * Contributors:
 * Gradient Systems
 */
#include "config.h"
#include "porting.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#include <io.h>
#pragma warning(disable: 4305)
#endif

#include "StringBuffer.h"
#include "expr.h"
#include "grammar_support.h"
#include "keywords.h"
#include "substitution.h"
#include "error_msg.h"
#include "tables.h"
#include "qgen_params.h"
#include "tdefs.h"
#include "query_handler.h"
#include "list.h"
#include "dist.h"
#include "scaling.h"


#define DEBUG0(l, fmt) 				if (l <= verbose) printf(fmt)
#define DEBUG1(l, fmt, arg)			if (l <= verbose) printf(fmt, arg)
#define DEBUG2(l, fmt, arg, arg2)	if (l <= verbose) printf(fmt, arg, arg2)

extern file_ref_t file_stack[];

int yylex(void);

#ifdef WIN32
int yyparse(void);
#endif

/* GLOBAL VARIABLES */
int verbose = 0,
	j,
	nRetCode;
ds_key_t i;
char tmpstr[128];
segment_t *pSegment;
substitution_t *pSub;

#line 156 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_INT = 258,
    TOK_LITERAL = 259,
    TOK_PATH = 260,
    TOK_DECIMAL = 261,
    TOK_ID = 262,
    TOK_SQL = 263,
    KW_DEFINE = 264,
    KW_RANDOM = 265,
    KW_UNIFORM = 266,
    KW_RANGE = 267,
    KW_DATE = 268,
    KW_INCLUDE = 269,
    KW_TEXT = 270,
    KW_DIST = 271,
    KW_LIST = 272,
    KW_ROWCOUNT = 273,
    KW_BEGIN = 274,
    KW_END = 275,
    KW_SALES = 276,
    KW_RETURNS = 277,
    KW_DISTMEMBER = 278,
    KW_DISTWEIGHT = 279,
    KW_QUERY = 280,
    KW_STREAM = 281,
    KW_TEMPLATE = 282,
    KW_SEED = 283,
    KW_SCALE = 284,
    KW_SCALE_STEP = 285,
    KW_SET = 286,
    KW_ADD = 287,
    KW_NAMES = 288,
    KW_TYPES = 289,
    KW_WEIGHTS = 290,
    KW_INT = 291,
    KW_VARCHAR = 292,
    KW_DECIMAL = 293,
    KW_LIMIT = 294,
    KW_LIMITA = 295,
    KW_LIMITB = 296,
    KW_LIMITC = 297,
    KW_ULIST = 298,
    KW_SLIST = 299,
    KW_SULIST = 300,
    WITH = 301,
    UMINUS = 302,
    TCAST = 303
  };
#endif
/* Tokens.  */
#define TOK_INT 258
#define TOK_LITERAL 259
#define TOK_PATH 260
#define TOK_DECIMAL 261
#define TOK_ID 262
#define TOK_SQL 263
#define KW_DEFINE 264
#define KW_RANDOM 265
#define KW_UNIFORM 266
#define KW_RANGE 267
#define KW_DATE 268
#define KW_INCLUDE 269
#define KW_TEXT 270
#define KW_DIST 271
#define KW_LIST 272
#define KW_ROWCOUNT 273
#define KW_BEGIN 274
#define KW_END 275
#define KW_SALES 276
#define KW_RETURNS 277
#define KW_DISTMEMBER 278
#define KW_DISTWEIGHT 279
#define KW_QUERY 280
#define KW_STREAM 281
#define KW_TEMPLATE 282
#define KW_SEED 283
#define KW_SCALE 284
#define KW_SCALE_STEP 285
#define KW_SET 286
#define KW_ADD 287
#define KW_NAMES 288
#define KW_TYPES 289
#define KW_WEIGHTS 290
#define KW_INT 291
#define KW_VARCHAR 292
#define KW_DECIMAL 293
#define KW_LIMIT 294
#define KW_LIMITA 295
#define KW_LIMITB 296
#define KW_LIMITC 297
#define KW_ULIST 298
#define KW_SLIST 299
#define KW_SULIST 300
#define WITH 301
#define UMINUS 302
#define TCAST 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 87 "qgen.y"

    int		intval;
    char	*strval;
	expr_t	*exprval;
	list_t  *list;
    

#line 312 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  27
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   260

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

#define YYUNDEFTOK  2
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    56,     2,    49,     2,     2,
      61,    62,    50,    47,    64,    48,    68,    51,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    63,    59,
      57,    60,    58,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    65,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    66,     2,    67,     2,     2,     2,     2,
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
      45,    46,    54,    55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   161,   161,   169,   170,   183,   184,   185,   186,   194,
     199,   210,   213,   214,   217,   218,   219,   222,   223,   224,
     227,   228,   229,   232,   233,   236,   237,   240,   243,   244,
     245,   248,   249,   252,   253,   260,   266,   278,   283,   290,
     294,   298,   299,   304,   308,   312,   316,   320,   323,   327,
     331,   335,   348,   365,   369,   373,   377,   381,   385,   391,
     395,   399,   403,   408,   413,   418,   423,   430,   431,   434,
     435,   436,   439,   440,   441,   444,   445,   446,   447,   450,
     455,   462,   475,   483,   484,   490,   491,   498,   506,   514,
     521,   528,   535,   542,   549,   556,   565,   566,   567,   568,
     576
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_INT", "TOK_LITERAL", "TOK_PATH",
  "TOK_DECIMAL", "TOK_ID", "TOK_SQL", "KW_DEFINE", "KW_RANDOM",
  "KW_UNIFORM", "KW_RANGE", "KW_DATE", "KW_INCLUDE", "KW_TEXT", "KW_DIST",
  "KW_LIST", "KW_ROWCOUNT", "KW_BEGIN", "KW_END", "KW_SALES", "KW_RETURNS",
  "KW_DISTMEMBER", "KW_DISTWEIGHT", "KW_QUERY", "KW_STREAM", "KW_TEMPLATE",
  "KW_SEED", "KW_SCALE", "KW_SCALE_STEP", "KW_SET", "KW_ADD", "KW_NAMES",
  "KW_TYPES", "KW_WEIGHTS", "KW_INT", "KW_VARCHAR", "KW_DECIMAL",
  "KW_LIMIT", "KW_LIMITA", "KW_LIMITB", "KW_LIMITC", "KW_ULIST",
  "KW_SLIST", "KW_SULIST", "WITH", "'+'", "'-'", "'%'", "'*'", "'/'",
  "'^'", "'['", "UMINUS", "TCAST", "'#'", "'<'", "'>'", "';'", "'='",
  "'('", "')'", "':'", "','", "']'", "'{'", "'}'", "'.'", "$accept",
  "workload_spec", "statement_list", "statement", "include_statement",
  "dist_statement", "dist_argument_list", "dist_argument", "dist_type",
  "dist_type_list", "dist_name_list", "dist_members_list", "dist_member",
  "dist_value", "dist_value_list", "dist_weight_list", "define_statement",
  "comma_expr_list", "expr", "function_call", "arithmetic_expr",
  "dist_expr_list", "function_name", "dist_function_name", "keyword_expr",
  "keyword_value", "replacement_list", "replacement", "query_statement",
  "query_component_list", "substitution", "opt_substitution_suffix",
  "path", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,    43,    45,    37,
      42,    47,    94,    91,   302,   303,    35,    60,    62,    59,
      61,    40,    41,    58,    44,    93,   123,   125,    46
};
# endif

#define YYPACT_NINF (-166)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      15,  -166,     3,    29,     7,    27,    53,    15,  -166,  -166,
    -166,  -166,  -166,    -3,  -166,     6,    10,    14,    -1,     0,
      20,    30,    31,    38,    42,    45,     5,  -166,  -166,  -166,
    -166,  -166,   164,   110,    85,    54,     8,    63,  -166,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,   130,  -166,  -166,  -166,
    -166,  -166,    79,  -166,    87,  -166,    90,    93,  -166,  -166,
    -166,  -166,  -166,   100,   101,   117,   122,    12,    67,  -166,
    -166,   123,   136,  -166,    80,    11,   -19,  -166,   106,  -166,
    -166,  -166,  -166,   142,   164,   137,   164,   162,   144,   164,
     164,   164,     1,  -166,  -166,  -166,  -166,   145,   164,   164,
     164,   164,  -166,   164,    76,  -166,   155,   156,   159,   153,
    -166,   188,  -166,  -166,  -166,    13,   217,    95,  -166,    61,
      96,  -166,   105,   148,   154,    54,   157,  -166,   -25,   -25,
    -166,  -166,   108,     4,  -166,     4,   127,   163,   165,   220,
      72,  -166,   222,   166,  -166,   137,   224,  -166,   225,   228,
     229,   230,   169,  -166,  -166,   164,  -166,   120,   221,   109,
     176,  -166,  -166,  -166,  -166,   -34,   174,   234,  -166,   177,
     178,   179,   180,   181,  -166,     4,  -166,     4,  -166,    -5,
    -166,  -166,  -166,  -166,   128,  -166,    78,    72,  -166,   171,
    -166,  -166,  -166,  -166,  -166,   221,   237,   186,   109,   184,
     183,   187,  -166,  -166,   149,  -166,  -166,  -166,    98,   189,
     191,   190,  -166,  -166
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    84,     0,     0,     0,     0,     0,     2,     3,     5,
       8,     6,     7,     0,    83,     0,     0,     0,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     4,    86,
      82,    85,     0,     0,     0,    96,     0,     0,    89,    90,
      91,    92,    93,    94,    95,   100,     0,     9,    40,    39,
      68,    72,     0,    67,     0,    69,     0,     0,    73,    74,
      70,    71,    46,     0,     0,     0,     0,     0,     0,    41,
      47,     0,     0,    42,     0,     0,     0,    12,     0,    99,
      97,    98,    87,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    96,    75,    77,    76,    78,     0,     0,     0,
       0,     0,    35,     0,     0,    36,     0,     0,     0,     0,
      13,    11,    25,    88,    10,     0,     0,     0,    79,     0,
       0,    53,     0,     0,     0,    96,     0,    43,    59,    60,
      61,    62,     0,    37,    64,    63,     0,     0,     0,     0,
       0,    26,     0,     0,    50,     0,     0,    51,     0,     0,
       0,     0,     0,    45,    48,     0,    49,     0,     0,    20,
       0,    28,    29,    30,    31,     0,     0,     0,    80,     0,
       0,     0,     0,     0,    44,    38,    66,    65,    23,     0,
      17,    18,    19,    21,     0,    14,     0,     0,    58,     0,
      55,    52,    54,    57,    56,     0,     0,     0,     0,    28,
       0,     0,    32,    81,     0,    24,    15,    22,     0,     0,
       0,    28,    27,    16
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,  -166,   244,  -166,  -166,  -166,   182,    55,  -166,
      59,  -166,   146,  -165,    69,  -166,  -166,  -166,   -83,  -166,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,   111,  -166,  -166,
     246,   -35,   214
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    10,    76,    77,   183,   184,
     179,   111,   112,   164,   165,   201,    11,   132,    68,    69,
      70,   136,    71,    72,    73,    97,   117,   118,    12,    13,
      14,    37,    47
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      78,   115,    35,   119,   125,    29,   122,   123,   124,    45,
      15,    79,    75,   109,    18,   128,   129,   130,   131,    92,
     133,   135,   202,     1,     2,   100,   101,    80,    81,   186,
     187,     3,    19,    20,    21,    22,    17,    93,    94,    95,
      96,    26,    16,   202,   106,   107,   108,    23,    24,    25,
       4,    98,    99,    27,   100,   101,    30,   126,   195,   196,
      98,    99,    46,   100,   101,    38,    32,    36,     4,    36,
      33,     5,   175,    34,   177,   161,   162,   142,   163,    48,
      49,   199,   162,   134,   163,    39,    50,    51,    52,    53,
     152,    54,    55,    56,    57,    40,    41,    58,    59,    60,
      61,   211,   162,    42,   163,    62,    63,    43,    98,    99,
      44,   100,   101,    74,    98,    99,    75,   100,   101,    64,
      65,    66,    36,    48,    49,   146,   102,   176,    82,    67,
      50,    51,    52,    53,    45,    54,    55,    56,    57,   105,
      84,    58,    59,    60,    61,   180,   181,   182,    85,    62,
      63,    86,    98,    99,    87,   100,   101,   144,   147,   145,
     148,    88,    89,    64,    65,    66,   120,    48,    49,   149,
     154,   113,   155,    67,    50,    51,    52,    53,    90,    54,
      55,    56,    57,    91,   103,    58,    59,    60,    61,   156,
     197,   157,   198,    62,    63,    98,    99,   104,   100,   101,
     114,    98,    99,   116,   100,   101,   121,    64,    65,    66,
     127,   210,   150,   196,   140,   137,   138,    67,   151,   139,
     109,   143,   153,   160,   158,   166,   159,   169,   178,   170,
     167,   171,   172,   173,   174,   185,   188,   189,   203,   190,
     191,   192,   193,   194,   205,   206,   -33,   208,   212,   209,
     213,    28,   -34,   207,   204,   200,   168,   141,   110,    31,
      83
};

static const yytype_uint8 yycheck[] =
{
      35,    84,     3,    86,     3,     8,    89,    90,    91,     4,
       7,     3,    31,    32,     7,    98,    99,   100,   101,     7,
     103,   104,   187,     8,     9,    50,    51,    19,    20,    63,
      64,    16,    25,    26,    27,    28,     7,    25,    26,    27,
      28,    14,    39,   208,    33,    34,    35,    40,    41,    42,
      53,    47,    48,     0,    50,    51,    59,    92,    63,    64,
      47,    48,    57,    50,    51,    65,    60,    68,    53,    68,
      60,    56,   155,    59,   157,     3,     4,    64,     6,     3,
       4,     3,     4,     7,     6,    65,    10,    11,    12,    13,
     125,    15,    16,    17,    18,    65,    65,    21,    22,    23,
      24,     3,     4,    65,     6,    29,    30,    65,    47,    48,
      65,    50,    51,     3,    47,    48,    31,    50,    51,    43,
      44,    45,    68,     3,     4,    64,    59,     7,    65,    53,
      10,    11,    12,    13,     4,    15,    16,    17,    18,    59,
      61,    21,    22,    23,    24,    36,    37,    38,    61,    29,
      30,    61,    47,    48,    61,    50,    51,    62,    62,    64,
      64,    61,    61,    43,    44,    45,     4,     3,     4,    64,
      62,    65,    64,    53,    10,    11,    12,    13,    61,    15,
      16,    17,    18,    61,    61,    21,    22,    23,    24,    62,
      62,    64,    64,    29,    30,    47,    48,    61,    50,    51,
      58,    47,    48,    66,    50,    51,    62,    43,    44,    45,
      65,    62,    64,    64,    61,    60,    60,    53,    64,    60,
      32,     4,    65,     3,    61,     3,    61,     3,     7,     4,
      64,     3,     3,     3,    65,    59,    62,     3,    67,    62,
      62,    62,    62,    62,     7,    59,    62,    64,    59,    62,
      59,     7,    62,   198,   195,   186,   145,   111,    76,    13,
      46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,     9,    16,    53,    56,    70,    71,    72,    73,
      74,    85,    97,    98,    99,     7,    39,     7,     7,    25,
      26,    27,    28,    40,    41,    42,    14,     0,    72,     8,
      59,    99,    60,    60,    59,     3,    68,   100,    65,    65,
      65,    65,    65,    65,    65,     4,    57,   101,     3,     4,
      10,    11,    12,    13,    15,    16,    17,    18,    21,    22,
      23,    24,    29,    30,    43,    44,    45,    53,    87,    88,
      89,    91,    92,    93,     3,    31,    75,    76,   100,     3,
      19,    20,    65,   101,    61,    61,    61,    61,    61,    61,
      61,    61,     7,    25,    26,    27,    28,    94,    47,    48,
      50,    51,    59,    61,    61,    59,    33,    34,    35,    32,
      76,    80,    81,    65,    58,    87,    66,    95,    96,    87,
       4,    62,    87,    87,    87,     3,   100,    65,    87,    87,
      87,    87,    86,    87,     7,    87,    90,    60,    60,    60,
      61,    81,    64,     4,    62,    64,    64,    62,    64,    64,
      64,    64,   100,    65,    62,    64,    62,    64,    61,    61,
       3,     3,     4,     6,    82,    83,     3,    64,    96,     3,
       4,     3,     3,     3,    65,    87,     7,    87,     7,    79,
      36,    37,    38,    77,    78,    59,    63,    64,    62,     3,
      62,    62,    62,    62,    62,    63,    64,    62,    64,     3,
      83,    84,    82,    67,    79,     7,    59,    77,    64,    62,
      62,     3,    59,    59
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    71,    71,    72,    72,    72,    72,    73,
      73,    74,    75,    75,    76,    76,    76,    77,    77,    77,
      78,    78,    78,    79,    79,    80,    80,    81,    82,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    89,
      89,    89,    89,    90,    90,    90,    90,    91,    91,    92,
      92,    92,    93,    93,    93,    94,    94,    94,    94,    95,
      95,    96,    97,    98,    98,    98,    98,    99,    99,    99,
      99,    99,    99,    99,    99,    99,   100,   100,   100,   100,
     101
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       5,     5,     1,     2,     5,     7,     9,     1,     1,     1,
       0,     1,     3,     1,     3,     1,     2,     7,     1,     1,
       1,     1,     3,     1,     3,     5,     5,     1,     3,     1,
       1,     1,     1,     3,     5,     4,     1,     1,     4,     4,
       4,     4,     6,     3,     6,     6,     6,     6,     6,     3,
       3,     3,     3,     1,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     2,     1,     1,     2,     2,     4,     5,     3,
       3,     3,     3,     3,     3,     3,     0,     2,     2,     2,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 162 "qgen.y"
                                                {
							AddQuerySegment(pCurrentQuery, "\n");
							AddQuerySubstitution(pCurrentQuery, "_END", 0, 0);
							AddQuerySegment(pCurrentQuery, "\n");
						}
#line 1658 "y.tab.c"
    break;

  case 4:
#line 171 "qgen.y"
                                                {
							if (is_set("DEBUG"))
							{
								if ((yyvsp[0].intval) != KW_DEFINE)
								{
									printf("STATUS: parsed %s statement at line %d\n", 
										((yyvsp[0].intval) == TOK_SQL)?"SQL":KeywordText((yyvsp[0].intval)), pCurrentFile->line_number);
								}
							}
						}
#line 1673 "y.tab.c"
    break;

  case 5:
#line 183 "qgen.y"
                                        {(yyval.intval) = KW_INCLUDE; }
#line 1679 "y.tab.c"
    break;

  case 6:
#line 184 "qgen.y"
                                                {(yyval.intval) = KW_DEFINE; }
#line 1685 "y.tab.c"
    break;

  case 7:
#line 185 "qgen.y"
                                                {(yyval.intval) = TOK_SQL; }
#line 1691 "y.tab.c"
    break;

  case 8:
#line 186 "qgen.y"
                                                {(yyval.intval) = KW_DIST; }
#line 1697 "y.tab.c"
    break;

  case 9:
#line 195 "qgen.y"
                                        {
					if (include_file((yyvsp[0].strval), pCurrentQuery) < 0)
						yyerror("File include failed");
					}
#line 1706 "y.tab.c"
    break;

  case 10:
#line 200 "qgen.y"
                                        {
					yywarn("System include not supported; using relative pathing");
					if (include_file((yyvsp[-1].strval), pCurrentQuery) < 0)
						yyerror("File include failed");
					}
#line 1716 "y.tab.c"
    break;

  case 35:
#line 261 "qgen.y"
                                                {
						defineSubstitution(pCurrentQuery, (yyvsp[-3].strval), (yyvsp[-1].exprval));
						if (is_set("DEBUG"))
							printf("STATUS: DEFINED %s\n", (yyvsp[-3].strval));
						}
#line 1726 "y.tab.c"
    break;

  case 36:
#line 267 "qgen.y"
                                                {
						pSub = findSubstitution(pCurrentQuery, "_LIMIT", 0);
						sprintf(tmpstr, "%d", (yyvsp[-1].intval));
						ResetBuffer(pSub->pAssignment->Value.pBuf);
						AddBuffer(pSub->pAssignment->Value.pBuf, tmpstr);
						if (is_set("DEBUG"))
							printf("STATUS: SET LIMIT\n");
						}
#line 1739 "y.tab.c"
    break;

  case 37:
#line 279 "qgen.y"
                                                {
						(yyval.list) = makeList(L_FL_TAIL, NULL);
						addList((yyval.list), (yyvsp[0].exprval));
						}
#line 1748 "y.tab.c"
    break;

  case 38:
#line 284 "qgen.y"
                                                {
						addList((yyvsp[-2].list), (yyvsp[0].exprval));
						(yyval.list) = (yyvsp[-2].list);
						}
#line 1757 "y.tab.c"
    break;

  case 39:
#line 291 "qgen.y"
                                                {
						(yyval.exprval) = MakeStringConstant((yyvsp[0].strval));
						}
#line 1765 "y.tab.c"
    break;

  case 40:
#line 295 "qgen.y"
                                                {
						(yyval.exprval) = MakeIntConstant((yyvsp[0].intval));
						}
#line 1773 "y.tab.c"
    break;

  case 42:
#line 300 "qgen.y"
                                                {
						(yyval.exprval) = MakeIntConstant((yyvsp[0].intval));
						(yyval.exprval)->nFlags |= EXPR_FL_KEYWORD;
						}
#line 1782 "y.tab.c"
    break;

  case 43:
#line 305 "qgen.y"
                                                {
						(yyval.exprval) = getKeywordValue((yyvsp[-1].intval));
						}
#line 1790 "y.tab.c"
    break;

  case 44:
#line 309 "qgen.y"
                                                {
						(yyval.exprval) = MakeVariableReference((yyvsp[-3].strval), (yyvsp[-2].intval));
						}
#line 1798 "y.tab.c"
    break;

  case 45:
#line 313 "qgen.y"
                                                {
						(yyval.exprval) = MakeVariableReference((yyvsp[-2].strval), (yyvsp[-1].intval));
						}
#line 1806 "y.tab.c"
    break;

  case 46:
#line 317 "qgen.y"
                                                {
						(yyval.exprval) = MakeIntConstant(get_int("SCALE"));
						}
#line 1814 "y.tab.c"
    break;

  case 48:
#line 324 "qgen.y"
                                                {
						(yyval.exprval) = MakeFunctionCall((yyvsp[-3].intval), (yyvsp[-1].list));
						}
#line 1822 "y.tab.c"
    break;

  case 49:
#line 328 "qgen.y"
                                                {
						(yyval.exprval) = MakeFunctionCall((yyvsp[-3].intval), (yyvsp[-1].list));
						}
#line 1830 "y.tab.c"
    break;

  case 50:
#line 332 "qgen.y"
                                                {
						(yyval.exprval) = MakeFunctionCall(KW_TEXT, (yyvsp[-1].list));
						}
#line 1838 "y.tab.c"
    break;

  case 51:
#line 336 "qgen.y"
                                                {
						i = GetTableNumber((yyvsp[-1].strval));
						if (i == -1)
						{
							i = distsize((yyvsp[-1].strval));
							if (i == -1)
								ReportError(QERR_BAD_NAME, (yyvsp[-1].strval), 1);
						}
						else
							i = getIDCount(i);
						(yyval.exprval) = MakeIntConstant(i);
						}
#line 1855 "y.tab.c"
    break;

  case 52:
#line 349 "qgen.y"
                                                {
						/* TODO: Need to convert this to DSS_HUGE */
						i = GetTableNumber((yyvsp[-3].strval));
						if (i == -1)
						{
							i = distsize((yyvsp[-3].strval));
							if (i == -1)
								ReportError(QERR_BAD_NAME, (yyvsp[-3].strval), 1);
						}
						j = GetTableNumber((yyvsp[-1].strval));
						if (i == -1)
							ReportError(QERR_BAD_NAME, (yyvsp[-1].strval), 1);
						i = (int)getIDCount(i);
						j = (int)getIDCount(j);
						(yyval.exprval) = MakeIntConstant((i>j)?j:i);
						}
#line 1876 "y.tab.c"
    break;

  case 53:
#line 366 "qgen.y"
                                                {
						(yyval.exprval) = MakeIntConstant(getScaleSlot(get_int("SCALE")) + 1);
						}
#line 1884 "y.tab.c"
    break;

  case 54:
#line 370 "qgen.y"
                                                {
						(yyval.exprval) = MakeListExpr(KW_ULIST, (yyvsp[-3].exprval), (yyvsp[-1].intval));
						}
#line 1892 "y.tab.c"
    break;

  case 55:
#line 374 "qgen.y"
                                                {
						(yyval.exprval) = MakeListExpr(KW_LIST, (yyvsp[-3].exprval), (yyvsp[-1].intval));
						}
#line 1900 "y.tab.c"
    break;

  case 56:
#line 378 "qgen.y"
                                                {
						(yyval.exprval) = MakeListExpr(KW_SULIST, (yyvsp[-3].exprval), (yyvsp[-1].intval));
						}
#line 1908 "y.tab.c"
    break;

  case 57:
#line 382 "qgen.y"
                                                {
						(yyval.exprval) = MakeListExpr(KW_SLIST, (yyvsp[-3].exprval), (yyvsp[-1].intval));
						}
#line 1916 "y.tab.c"
    break;

  case 58:
#line 386 "qgen.y"
                                                {
						(yyval.exprval) = MakeListExpr(KW_RANGE, (yyvsp[-3].exprval), (yyvsp[-1].intval));
						}
#line 1924 "y.tab.c"
    break;

  case 59:
#line 392 "qgen.y"
                                                {
						(yyval.exprval) = makeArithmeticExpr(OP_ADD, (yyvsp[-2].exprval), (yyvsp[0].exprval));
						}
#line 1932 "y.tab.c"
    break;

  case 60:
#line 396 "qgen.y"
                                                {
						(yyval.exprval) = makeArithmeticExpr(OP_SUBTRACT, (yyvsp[-2].exprval), (yyvsp[0].exprval));
						}
#line 1940 "y.tab.c"
    break;

  case 61:
#line 400 "qgen.y"
                                                {
						(yyval.exprval) = makeArithmeticExpr(OP_MULTIPLY, (yyvsp[-2].exprval), (yyvsp[0].exprval));
						}
#line 1948 "y.tab.c"
    break;

  case 62:
#line 404 "qgen.y"
                                                {
						(yyval.exprval) = makeArithmeticExpr(OP_DIVIDE, (yyvsp[-2].exprval), (yyvsp[0].exprval));
						}
#line 1956 "y.tab.c"
    break;

  case 63:
#line 409 "qgen.y"
                                                {
						(yyval.list) = makeList(L_FL_TAIL, NULL);
						addList((yyval.list), (yyvsp[0].exprval));
						}
#line 1965 "y.tab.c"
    break;

  case 64:
#line 414 "qgen.y"
                                                {
						(yyval.list) = makeList(L_FL_TAIL, NULL);
						addList((yyval.list), MakeStringConstant((yyvsp[0].strval)));
						}
#line 1974 "y.tab.c"
    break;

  case 65:
#line 419 "qgen.y"
                                                {
						addList((yyvsp[-2].list), (yyvsp[0].exprval));
						(yyval.list) = (yyvsp[-2].list);
						}
#line 1983 "y.tab.c"
    break;

  case 66:
#line 424 "qgen.y"
                                                {
						addList((yyvsp[-2].list), MakeStringConstant((yyvsp[0].strval)));
						(yyval.list) = (yyvsp[-2].list);
						}
#line 1992 "y.tab.c"
    break;

  case 67:
#line 430 "qgen.y"
                                        {(yyval.intval) = KW_DATE;}
#line 1998 "y.tab.c"
    break;

  case 68:
#line 431 "qgen.y"
                                                                {(yyval.intval) = KW_RANDOM;}
#line 2004 "y.tab.c"
    break;

  case 69:
#line 434 "qgen.y"
                                        {(yyval.intval) = KW_DIST;}
#line 2010 "y.tab.c"
    break;

  case 70:
#line 435 "qgen.y"
                                                {(yyval.intval) = KW_DISTMEMBER;}
#line 2016 "y.tab.c"
    break;

  case 71:
#line 436 "qgen.y"
                                                {(yyval.intval) = KW_DISTWEIGHT;}
#line 2022 "y.tab.c"
    break;

  case 72:
#line 439 "qgen.y"
                                        {(yyval.intval) = KW_UNIFORM;}
#line 2028 "y.tab.c"
    break;

  case 73:
#line 440 "qgen.y"
                                                                        {(yyval.intval) = KW_SALES;}
#line 2034 "y.tab.c"
    break;

  case 74:
#line 441 "qgen.y"
                                                                        {(yyval.intval) = KW_RETURNS;}
#line 2040 "y.tab.c"
    break;

  case 75:
#line 444 "qgen.y"
                                                                {(yyval.intval) = KW_QUERY;}
#line 2046 "y.tab.c"
    break;

  case 76:
#line 445 "qgen.y"
                                                {(yyval.intval) = KW_TEMPLATE;}
#line 2052 "y.tab.c"
    break;

  case 77:
#line 446 "qgen.y"
                                                {(yyval.intval) = KW_STREAM;}
#line 2058 "y.tab.c"
    break;

  case 78:
#line 447 "qgen.y"
                                                {(yyval.intval) = KW_SEED;}
#line 2064 "y.tab.c"
    break;

  case 79:
#line 451 "qgen.y"
                                                {
						(yyval.list) = makeList(L_FL_TAIL, NULL);
						addList((yyval.list), (yyvsp[0].exprval));
						}
#line 2073 "y.tab.c"
    break;

  case 80:
#line 456 "qgen.y"
                                                {
						addList((yyval.list), (yyvsp[0].exprval));
						(yyval.list) = (yyvsp[-2].list);
						}
#line 2082 "y.tab.c"
    break;

  case 81:
#line 463 "qgen.y"
                                                {
						(yyval.exprval) = MakeReplacement((yyvsp[-3].strval), (yyvsp[-1].intval));
						}
#line 2090 "y.tab.c"
    break;

  case 82:
#line 476 "qgen.y"
                                                        {
							pSegment = getTail(pCurrentQuery->SegmentList);
							pSegment->flags |= QS_EOS;
							}
#line 2099 "y.tab.c"
    break;

  case 84:
#line 485 "qgen.y"
                                                        {
							if ((nRetCode = AddQuerySegment(pCurrentQuery, (yyvsp[0].strval))) != 0)
								yyerror("SQL parse failed");
							}
#line 2108 "y.tab.c"
    break;

  case 86:
#line 492 "qgen.y"
                                                        {
							if ((nRetCode = AddQuerySegment(pCurrentQuery, (yyvsp[0].strval))) != 0)
								yyerror("SQL parse failed");
							}
#line 2117 "y.tab.c"
    break;

  case 87:
#line 499 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, (yyvsp[-2].strval), 0, (yyvsp[-1].intval))) < 0)
								{
								sprintf(tmpstr, "Substitution match failed on %s", (yyvsp[-2].strval));
								yyerror(tmpstr);
								}
						}
#line 2129 "y.tab.c"
    break;

  case 88:
#line 507 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, (yyvsp[-3].strval), (yyvsp[-2].intval), (yyvsp[-1].intval))) < 0)
								{
								sprintf(tmpstr, "Substitution match failed on %s", (yyvsp[-3].strval));
								yyerror(tmpstr);
								}
						}
#line 2141 "y.tab.c"
    break;

  case 89:
#line 515 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_QUERY", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
#line 2152 "y.tab.c"
    break;

  case 90:
#line 522 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_STREAM", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
#line 2163 "y.tab.c"
    break;

  case 91:
#line 529 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_TEMPLATE", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
#line 2174 "y.tab.c"
    break;

  case 92:
#line 536 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_SEED", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
#line 2185 "y.tab.c"
    break;

  case 93:
#line 543 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_LIMITA", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
#line 2196 "y.tab.c"
    break;

  case 94:
#line 550 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_LIMITB", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
#line 2207 "y.tab.c"
    break;

  case 95:
#line 557 "qgen.y"
                                                {
							if ((nRetCode = AddQuerySubstitution(pCurrentQuery, "_LIMITC", 0, 0)) < 0)
								{
								yyerror("Lookup of predefined constant failed");
								}
						}
#line 2218 "y.tab.c"
    break;

  case 96:
#line 565 "qgen.y"
                                                        {(yyval.intval) = 0;}
#line 2224 "y.tab.c"
    break;

  case 97:
#line 566 "qgen.y"
                                                                        {(yyval.intval) = 0;}
#line 2230 "y.tab.c"
    break;

  case 98:
#line 567 "qgen.y"
                                                                                {(yyval.intval) = 1;}
#line 2236 "y.tab.c"
    break;

  case 99:
#line 568 "qgen.y"
                                                                                {(yyval.intval) = (yyvsp[0].intval);}
#line 2242 "y.tab.c"
    break;

  case 100:
#line 576 "qgen.y"
                                { (yyval.strval) = (yyvsp[0].strval); }
#line 2248 "y.tab.c"
    break;


#line 2252 "y.tab.c"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
#line 580 "qgen.y"



