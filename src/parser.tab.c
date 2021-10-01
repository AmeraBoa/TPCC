/* A Bison parser, made by GNU Bison 3.7.3.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <getopt.h>
    #include <unistd.h>
    #include <stdlib.h>
    extern int lineno;
    extern int charno;
    char buf[64];
    char func_name[64];

    /* Previous identifier in yylval. Used when retrieving identifier in struct var, 
    as the last yylval identifier value is the name of the variable and not the type. */
    extern char prev[64];
    int struct_arg = 0;
    int yylex();
    void yyerror(const char *);
    
    static struct {
        unsigned char symtab:1, tree:1;
    } opts;

#line 96 "src/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CHARACTER = 3,                  /* CHARACTER  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_IDENT = 5,                      /* IDENT  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_CHAR = 7,                       /* CHAR  */
  YYSYMBOL_ADD = 8,                        /* ADD  */
  YYSYMBOL_SUB = 9,                        /* SUB  */
  YYSYMBOL_DIV = 10,                       /* DIV  */
  YYSYMBOL_MUL = 11,                       /* MUL  */
  YYSYMBOL_MOD = 12,                       /* MOD  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_NEQ = 14,                       /* NEQ  */
  YYSYMBOL_GTEQ = 15,                      /* GTEQ  */
  YYSYMBOL_GT = 16,                        /* GT  */
  YYSYMBOL_LT = 17,                        /* LT  */
  YYSYMBOL_LTEQ = 18,                      /* LTEQ  */
  YYSYMBOL_OR = 19,                        /* OR  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_STRUCT = 21,                    /* STRUCT  */
  YYSYMBOL_IF = 22,                        /* IF  */
  YYSYMBOL_WHILE = 23,                     /* WHILE  */
  YYSYMBOL_RETURN = 24,                    /* RETURN  */
  YYSYMBOL_VOID = 25,                      /* VOID  */
  YYSYMBOL_PRINT = 26,                     /* PRINT  */
  YYSYMBOL_READC = 27,                     /* READC  */
  YYSYMBOL_READE = 28,                     /* READE  */
  YYSYMBOL_29_ = 29,                       /* ')'  */
  YYSYMBOL_ELSE = 30,                      /* ELSE  */
  YYSYMBOL_31_ = 31,                       /* '{'  */
  YYSYMBOL_32_ = 32,                       /* '}'  */
  YYSYMBOL_33_ = 33,                       /* ';'  */
  YYSYMBOL_34_ = 34,                       /* ','  */
  YYSYMBOL_35_ = 35,                       /* '('  */
  YYSYMBOL_36_ = 36,                       /* '='  */
  YYSYMBOL_37_ = 37,                       /* '!'  */
  YYSYMBOL_38_ = 38,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_S = 40,                         /* S  */
  YYSYMBOL_Prog = 41,                      /* Prog  */
  YYSYMBOL_TypesVars = 42,                 /* TypesVars  */
  YYSYMBOL_TypeVar = 43,                   /* TypeVar  */
  YYSYMBOL_44_1 = 44,                      /* $@1  */
  YYSYMBOL_Type = 45,                      /* Type  */
  YYSYMBOL_StructVar = 46,                 /* StructVar  */
  YYSYMBOL_SimpleType = 47,                /* SimpleType  */
  YYSYMBOL_Declarators = 48,               /* Declarators  */
  YYSYMBOL_DeclFields = 49,                /* DeclFields  */
  YYSYMBOL_DeclFuncts = 50,                /* DeclFuncts  */
  YYSYMBOL_DeclFunct = 51,                 /* DeclFunct  */
  YYSYMBOL_HeaderFunct = 52,               /* HeaderFunct  */
  YYSYMBOL_53_2 = 53,                      /* $@2  */
  YYSYMBOL_54_3 = 54,                      /* $@3  */
  YYSYMBOL_Parameters = 55,                /* Parameters  */
  YYSYMBOL_ListTypVar = 56,                /* ListTypVar  */
  YYSYMBOL_Body = 57,                      /* Body  */
  YYSYMBOL_DeclVars = 58,                  /* DeclVars  */
  YYSYMBOL_ListInstr = 59,                 /* ListInstr  */
  YYSYMBOL_Instr = 60,                     /* Instr  */
  YYSYMBOL_Exp = 61,                       /* Exp  */
  YYSYMBOL_TB = 62,                        /* TB  */
  YYSYMBOL_FB = 63,                        /* FB  */
  YYSYMBOL_M = 64,                         /* M  */
  YYSYMBOL_E = 65,                         /* E  */
  YYSYMBOL_T = 66,                         /* T  */
  YYSYMBOL_F = 67,                         /* F  */
  YYSYMBOL_68_4 = 68,                      /* $@4  */
  YYSYMBOL_Equal = 69,                     /* Equal  */
  YYSYMBOL_Order = 70,                     /* Order  */
  YYSYMBOL_AddSub = 71,                    /* AddSub  */
  YYSYMBOL_DivStar = 72,                   /* DivStar  */
  YYSYMBOL_LValue = 73,                    /* LValue  */
  YYSYMBOL_StructField = 74,               /* StructField  */
  YYSYMBOL_75_5 = 75,                      /* $@5  */
  YYSYMBOL_Arguments = 76,                 /* Arguments  */
  YYSYMBOL_ListExp = 77                    /* ListExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,     2,     2,     2,     2,     2,
      35,    29,     2,     2,    34,     2,    38,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    33,
       2,    36,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
      25,    26,    27,    28,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    69,    69,    80,    92,    93,    96,    96,   102,   106,
     107,   110,   113,   114,   117,   118,   121,   122,   125,   126,
     129,   139,   139,   150,   150,   164,   165,   168,   176,   184,
     195,   208,   211,   220,   223,   224,   225,   226,   227,   234,
     246,   253,   254,   255,   256,   257,   259,   260,   262,   263,
     265,   266,   268,   269,   271,   272,   274,   275,   277,   278,
     279,   280,   281,   282,   283,   283,   298,   299,   302,   303,
     304,   305,   308,   309,   312,   313,   314,   318,   319,   322,
     322,   332,   333,   336,   337
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CHARACTER", "NUM",
  "IDENT", "INT", "CHAR", "ADD", "SUB", "DIV", "MUL", "MOD", "EQ", "NEQ",
  "GTEQ", "GT", "LT", "LTEQ", "OR", "AND", "STRUCT", "IF", "WHILE",
  "RETURN", "VOID", "PRINT", "READC", "READE", "')'", "ELSE", "'{'", "'}'",
  "';'", "','", "'('", "'='", "'!'", "'.'", "$accept", "S", "Prog",
  "TypesVars", "TypeVar", "$@1", "Type", "StructVar", "SimpleType",
  "Declarators", "DeclFields", "DeclFuncts", "DeclFunct", "HeaderFunct",
  "$@2", "$@3", "Parameters", "ListTypVar", "Body", "DeclVars",
  "ListInstr", "Instr", "Exp", "TB", "FB", "M", "E", "T", "F", "$@4",
  "Equal", "Order", "AddSub", "DivStar", "LValue", "StructField", "$@5",
  "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    41,
     284,   123,   125,    59,    44,    40,    61,    33,    46
};
#endif

#define YYPACT_NINF (-114)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-80)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -114,     5,  -114,    16,  -114,  -114,  -114,     2,    19,  -114,
      21,  -114,  -114,   119,  -114,   -13,    -3,  -114,    39,    17,
      43,    71,  -114,  -114,  -114,  -114,    47,    65,  -114,    82,
    -114,  -114,    13,   117,   121,   121,  -114,    86,    35,    86,
       3,  -114,   104,    92,    77,   102,  -114,    83,  -114,  -114,
      57,    85,   100,   127,    12,   128,   129,   130,  -114,  -114,
    -114,    85,    85,  -114,    -8,   141,   116,   133,   147,   142,
    -114,   103,  -114,   124,   134,    86,  -114,  -114,    13,  -114,
    -114,   131,   132,  -114,  -114,    85,    85,  -114,    -6,    85,
     163,   163,    75,    27,  -114,    85,  -114,    85,  -114,  -114,
      85,  -114,  -114,  -114,  -114,    85,  -114,  -114,    85,  -114,
    -114,  -114,    85,    85,  -114,  -114,   126,   164,    85,   166,
      52,    54,  -114,    56,   135,   143,   145,  -114,  -114,   141,
     116,   133,   147,   142,  -114,    36,  -114,  -114,   156,   148,
     144,  -114,   110,   110,   146,   149,   150,  -114,  -114,    85,
     151,  -114,  -114,  -114,  -114,   156,   110,  -114
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     2,     0,     1,    13,    12,     0,     0,     4,
       0,    10,     9,     3,    19,     0,    11,    23,    15,     0,
       0,     0,    18,    31,    20,     6,     0,     0,     8,     0,
      11,    21,    33,     0,     0,     0,    14,     0,     0,     0,
       0,    25,     0,     0,    26,     0,    15,     0,    62,    61,
      77,     0,     0,     0,     0,     0,     0,     0,    33,    29,
      45,     0,     0,    32,     0,    47,    49,    51,    53,    55,
      57,    63,    78,     0,     0,     0,    28,    24,     0,    22,
      30,     0,     0,    58,    63,     0,     0,    43,     0,     0,
       0,     0,     0,     0,    59,     0,    41,     0,    66,    67,
       0,    69,    68,    70,    71,     0,    72,    73,     0,    75,
      74,    76,     0,     0,    17,     7,     0,     0,    82,     0,
       0,     0,    42,     0,    77,     0,     0,    44,    60,    46,
      48,    50,    52,    54,    56,     0,    16,    27,    84,     0,
      81,    80,     0,     0,     0,     0,     0,    34,    65,     0,
      38,    40,    37,    36,    35,    83,     0,    39
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -114,  -114,  -114,  -114,  -114,  -114,    -1,  -114,    53,   -33,
    -114,  -114,   167,  -114,  -114,  -114,   152,  -114,  -114,  -114,
     118,  -113,   -53,    89,    88,    90,    81,    80,   -48,  -114,
    -114,  -114,  -114,  -114,   -38,  -114,  -114,  -114,  -114
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     9,    33,    42,    11,    12,    19,
      40,    13,    14,    15,    27,    26,    43,    44,    24,    32,
      38,    63,    64,    65,    66,    67,    68,    69,    70,    81,
     100,   105,   108,   112,    84,    72,    82,   139,   140
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,    88,    10,    83,    47,     4,    73,    16,    93,     5,
       6,    95,    21,    95,    94,    48,    49,    50,    23,     5,
       6,    51,     5,     6,    17,    96,    18,   122,    25,   150,
     151,    37,   120,   121,    20,    74,   123,     7,    48,    49,
      50,     8,   116,   157,    51,    87,    95,    61,    30,    62,
      28,    29,   125,   126,    71,    95,   128,    52,    53,    54,
     135,    55,    56,    57,   134,   138,    58,    59,    60,   147,
      61,    95,    62,    95,   -21,    95,    31,   117,    48,    49,
      50,   142,    34,   143,    51,   144,    39,    36,    48,    49,
      50,    46,   -64,    75,    51,   -79,   155,    52,    53,    54,
      35,    55,    56,    57,    71,    71,    58,   127,    60,    76,
      61,    78,    62,    48,    49,    50,    80,    29,    71,    51,
      61,    77,    62,     5,     6,     5,     6,     5,     6,    98,
      99,    79,    52,    53,    54,    85,    55,    56,    57,   113,
      20,    58,    20,    60,     8,    61,    41,    62,   101,   102,
     103,   104,   109,   110,   111,   106,   107,   114,    29,   136,
      29,    97,    86,    89,    90,    91,   118,   115,   124,   137,
     119,   141,   145,   -79,   146,    95,    92,   148,   149,   152,
      22,   156,   153,   154,   129,   130,   132,    45,   133,     0,
     131
};

static const yytype_int16 yycheck[] =
{
      38,    54,     3,    51,    37,     0,    39,     5,    61,     6,
       7,    19,    13,    19,    62,     3,     4,     5,    31,     6,
       7,     9,     6,     7,     5,    33,     5,    33,    31,   142,
     143,    32,    85,    86,    21,    32,    89,    21,     3,     4,
       5,    25,    75,   156,     9,    33,    19,    35,     5,    37,
      33,    34,    90,    91,    92,    19,    29,    22,    23,    24,
     113,    26,    27,    28,   112,   118,    31,    32,    33,    33,
      35,    19,    37,    19,    35,    19,     5,    78,     3,     4,
       5,    29,    35,    29,     9,    29,    33,     5,     3,     4,
       5,     5,    35,    40,     9,    38,   149,    22,    23,    24,
      35,    26,    27,    28,   142,   143,    31,    32,    33,     5,
      35,    34,    37,     3,     4,     5,    33,    34,   156,     9,
      35,    29,    37,     6,     7,     6,     7,     6,     7,    13,
      14,    29,    22,    23,    24,    35,    26,    27,    28,    36,
      21,    31,    21,    33,    25,    35,    25,    37,    15,    16,
      17,    18,    10,    11,    12,     8,     9,    33,    34,    33,
      34,    20,    35,    35,    35,    35,    35,    33,     5,     5,
      38,     5,    29,    38,    29,    19,    58,    29,    34,    33,
      13,    30,    33,    33,    95,    97,   105,    35,   108,    -1,
     100
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,    41,    42,     0,     6,     7,    21,    25,    43,
      45,    46,    47,    50,    51,    52,     5,     5,     5,    48,
      21,    45,    51,    31,    57,    31,    54,    53,    33,    34,
       5,     5,    58,    44,    35,    35,     5,    45,    59,    47,
      49,    25,    45,    55,    56,    55,     5,    48,     3,     4,
       5,     9,    22,    23,    24,    26,    27,    28,    31,    32,
      33,    35,    37,    60,    61,    62,    63,    64,    65,    66,
      67,    73,    74,    48,    32,    47,     5,    29,    34,    29,
      33,    68,    75,    67,    73,    35,    35,    33,    61,    35,
      35,    35,    59,    61,    67,    19,    33,    20,    13,    14,
      69,    15,    16,    17,    18,    70,     8,     9,    71,    10,
      11,    12,    72,    36,    33,    33,    48,    45,    35,    38,
      61,    61,    33,    61,     5,    73,    73,    32,    29,    62,
      63,    64,    65,    66,    67,    61,    33,     5,    61,    76,
      77,     5,    29,    29,    29,    29,    29,    33,    29,    34,
      60,    60,    33,    33,    33,    61,    30,    60
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    41,    42,    42,    44,    43,    43,    45,
      45,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    53,    52,    54,    52,    55,    55,    56,    56,    57,
      58,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    65,    65,    66,    66,    67,    67,
      67,    67,    67,    67,    68,    67,    69,    69,    70,    70,
      70,    70,    71,    71,    72,    72,    72,    73,    73,    75,
      74,    76,    76,    77,    77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     0,     7,     3,     1,
       1,     2,     1,     1,     3,     1,     4,     3,     2,     1,
       2,     0,     6,     0,     6,     1,     1,     4,     2,     4,
       4,     0,     2,     0,     4,     5,     5,     5,     5,     7,
       5,     2,     3,     2,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     2,     2,
       3,     1,     1,     1,     0,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

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
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* S: Prog  */
#line 70 "src/parser.y"
        {
            (yyval.tree) = (yyvsp[0].tree);
            if(opts.tree) {
                printTree((yyval.tree));
            }
            lookForSemanticError((yyval.tree));
            generateASM_Instruction((yyval.tree));
            deleteTree((yyval.tree));
        }
#line 1277 "src/parser.tab.c"
    break;

  case 3: /* Prog: TypesVars DeclFuncts  */
#line 81 "src/parser.y"
        {
            (yyval.tree) = makeNode(_PROG_);
            Node* var = makeNode(_VAR_DECL_LIST_);
            addChild(var, (yyvsp[-1].tree));
            addChild((yyval.tree), var);
            Node* fonc = makeNode(_DECL_FUNCTS_);
            addChild(fonc, (yyvsp[0].tree));
            addChild((yyval.tree), fonc);
        }
#line 1291 "src/parser.tab.c"
    break;

  case 4: /* TypesVars: TypesVars TypeVar  */
#line 92 "src/parser.y"
                         { if((yyvsp[-1].tree) == NULL) (yyval.tree) = (yyvsp[0].tree); else { (yyval.tree) = (yyvsp[-1].tree); addSibling((yyval.tree), (yyvsp[0].tree)); } }
#line 1297 "src/parser.tab.c"
    break;

  case 5: /* TypesVars: %empty  */
#line 93 "src/parser.y"
              { (yyval.tree) = NULL; }
#line 1303 "src/parser.tab.c"
    break;

  case 6: /* $@1: %empty  */
#line 96 "src/parser.y"
                     { strcpy(buf, yylval.identifier); }
#line 1309 "src/parser.tab.c"
    break;

  case 7: /* TypeVar: STRUCT IDENT '{' $@1 DeclFields '}' ';'  */
#line 97 "src/parser.y"
        { 
            (yyval.tree) = makeNode(_STRUCT_TYPE_);
            strcpy((yyval.tree)->u.identifier, buf);
            addChild((yyval.tree), (yyvsp[-2].tree));
        }
#line 1319 "src/parser.tab.c"
    break;

  case 8: /* TypeVar: Type Declarators ';'  */
#line 102 "src/parser.y"
                           { (yyval.tree) = (yyvsp[-2].tree); addChild((yyval.tree), (yyvsp[-1].tree)); }
#line 1325 "src/parser.tab.c"
    break;

  case 11: /* StructVar: STRUCT IDENT  */
#line 110 "src/parser.y"
                   { (yyval.tree) = makeNode(_STRUCT_VAR_); strcpy((yyval.tree)->u.identifier, struct_arg ? yylval.identifier : prev); }
#line 1331 "src/parser.tab.c"
    break;

  case 12: /* SimpleType: CHAR  */
#line 113 "src/parser.y"
            { (yyval.tree) = makeNode(_TYPE_); strcpy((yyval.tree)->u.identifier, "char"); }
#line 1337 "src/parser.tab.c"
    break;

  case 13: /* SimpleType: INT  */
#line 114 "src/parser.y"
            { (yyval.tree) = makeNode(_TYPE_); strcpy((yyval.tree)->u.identifier, "int"); }
#line 1343 "src/parser.tab.c"
    break;

  case 14: /* Declarators: Declarators ',' IDENT  */
#line 117 "src/parser.y"
                             { (yyval.tree) = (yyvsp[-2].tree); Node *node = makeNode(_IDENTIFIER_); strcpy(node->u.identifier, yylval.identifier); addSibling((yyval.tree), node); }
#line 1349 "src/parser.tab.c"
    break;

  case 15: /* Declarators: IDENT  */
#line 118 "src/parser.y"
             { (yyval.tree) = makeNode(_IDENTIFIER_); strcpy((yyval.tree)->u.identifier, yylval.identifier); }
#line 1355 "src/parser.tab.c"
    break;

  case 16: /* DeclFields: DeclFields SimpleType Declarators ';'  */
#line 121 "src/parser.y"
                                             { (yyval.tree) = (yyvsp[-3].tree); addSibling((yyval.tree), (yyvsp[-2].tree)); addChild((yyvsp[-2].tree), (yyvsp[-1].tree)); }
#line 1361 "src/parser.tab.c"
    break;

  case 17: /* DeclFields: SimpleType Declarators ';'  */
#line 122 "src/parser.y"
                                  { (yyval.tree) = (yyvsp[-2].tree); addChild((yyval.tree), (yyvsp[-1].tree)); }
#line 1367 "src/parser.tab.c"
    break;

  case 18: /* DeclFuncts: DeclFuncts DeclFunct  */
#line 125 "src/parser.y"
                            { (yyval.tree) = (yyvsp[-1].tree); Node *node = makeNode(_DECL_FUNCT_); addChild(node, (yyvsp[0].tree)); addSibling((yyval.tree), node); }
#line 1373 "src/parser.tab.c"
    break;

  case 19: /* DeclFuncts: DeclFunct  */
#line 126 "src/parser.y"
                 { (yyval.tree) = makeNode(_DECL_FUNCT_); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1379 "src/parser.tab.c"
    break;

  case 20: /* DeclFunct: HeaderFunct Body  */
#line 130 "src/parser.y"
        {
            (yyval.tree) = makeNode(_HEADER_FUNCT_); 
            addChild((yyval.tree), (yyvsp[-1].tree)); 
            Node* corps = makeNode(_BODY_); 
            addChild(corps, (yyvsp[0].tree)); 
            addSibling((yyval.tree), corps);
        }
#line 1391 "src/parser.tab.c"
    break;

  case 21: /* $@2: %empty  */
#line 139 "src/parser.y"
                  { if((yyvsp[-1].tree)->kind == _STRUCT_VAR_) strcpy((yyvsp[-1].tree)->u.identifier, prev); struct_arg = 1; strcpy(buf, yylval.identifier); }
#line 1397 "src/parser.tab.c"
    break;

  case 22: /* HeaderFunct: Type IDENT $@2 '(' Parameters ')'  */
#line 140 "src/parser.y"
        {
            struct_arg = 0;
            (yyval.tree) = (yyvsp[-5].tree);
            Node* ident = makeNode(_IDENTIFIER_); 
            strcpy(ident->u.identifier, buf); 
            addSibling((yyval.tree), ident);
            Node* param = makeNode(_PARAMETERS_);
            addChild(param, (yyvsp[-1].tree));
            addSibling((yyval.tree), param);
        }
#line 1412 "src/parser.tab.c"
    break;

  case 23: /* $@3: %empty  */
#line 150 "src/parser.y"
                  { struct_arg = 1; strcpy(buf, yylval.identifier); }
#line 1418 "src/parser.tab.c"
    break;

  case 24: /* HeaderFunct: VOID IDENT $@3 '(' Parameters ')'  */
#line 151 "src/parser.y"
        { 
            struct_arg = 0;
            (yyval.tree) = makeNode(_TYPE_); 
            strcpy((yyval.tree)->u.identifier, "void"); 
            Node* ident = makeNode(_IDENTIFIER_); 
            strcpy(ident->u.identifier, buf); 
            addSibling((yyval.tree), ident); 
            Node* param = makeNode(_PARAMETERS_);
            addChild(param, (yyvsp[-1].tree));
            addSibling((yyval.tree), param);
        }
#line 1434 "src/parser.tab.c"
    break;

  case 25: /* Parameters: VOID  */
#line 164 "src/parser.y"
            { (yyval.tree) = NULL; }
#line 1440 "src/parser.tab.c"
    break;

  case 27: /* ListTypVar: ListTypVar ',' Type IDENT  */
#line 169 "src/parser.y"
        { 
            (yyval.tree) = (yyvsp[-3].tree);
            addSibling((yyval.tree), (yyvsp[-1].tree));
            Node* ident = makeNode(_IDENTIFIER_);
            strcpy(ident->u.identifier, yylval.identifier);
            addChild((yyvsp[-1].tree), ident);
        }
#line 1452 "src/parser.tab.c"
    break;

  case 28: /* ListTypVar: Type IDENT  */
#line 177 "src/parser.y"
        { 
            (yyval.tree) = (yyvsp[-1].tree); 
            Node* ident = makeNode(_IDENTIFIER_);
            strcpy(ident->u.identifier, yylval.identifier);
            addChild((yyval.tree), ident);
        }
#line 1463 "src/parser.tab.c"
    break;

  case 29: /* Body: '{' DeclVars ListInstr '}'  */
#line 185 "src/parser.y"
        {
            (yyval.tree) = makeNode(_VAR_DECL_LIST_);
            addChild((yyval.tree), (yyvsp[-2].tree));
            
            Node* suiteInstr = makeNode(_LIST_INSTR_); 
            addChild(suiteInstr, (yyvsp[-1].tree));
            addSibling((yyval.tree), suiteInstr);
        }
#line 1476 "src/parser.tab.c"
    break;

  case 30: /* DeclVars: DeclVars Type Declarators ';'  */
#line 196 "src/parser.y"
        { 
            if((yyvsp[-3].tree) != NULL) { 
                (yyval.tree) = (yyvsp[-3].tree); 
                addSibling((yyvsp[-3].tree), (yyvsp[-2].tree));
            } else {
                (yyval.tree) = (yyvsp[-2].tree);
            }
            addChild((yyvsp[-2].tree), (yyvsp[-1].tree));
            if((yyvsp[-2].tree)->kind == _STRUCT_VAR_) {
                strcpy((yyvsp[-2].tree)->u.identifier, prev); 
            }
        }
#line 1493 "src/parser.tab.c"
    break;

  case 31: /* DeclVars: %empty  */
#line 208 "src/parser.y"
              { (yyval.tree) = NULL; }
#line 1499 "src/parser.tab.c"
    break;

  case 32: /* ListInstr: ListInstr Instr  */
#line 212 "src/parser.y"
       { 
           if((yyvsp[-1].tree) != NULL) { 
                (yyval.tree) = (yyvsp[-1].tree); 
                addSibling((yyval.tree), (yyvsp[0].tree));
            } else {
                (yyval.tree) = (yyvsp[0].tree);
            }
       }
#line 1512 "src/parser.tab.c"
    break;

  case 33: /* ListInstr: %empty  */
#line 220 "src/parser.y"
              { (yyval.tree) = NULL; }
#line 1518 "src/parser.tab.c"
    break;

  case 34: /* Instr: LValue '=' Exp ';'  */
#line 223 "src/parser.y"
                          { (yyval.tree) = makeNode(_ASSIGN_); addChild((yyval.tree), (yyvsp[-3].tree)); addChild((yyval.tree), (yyvsp[-1].tree)); }
#line 1524 "src/parser.tab.c"
    break;

  case 35: /* Instr: READE '(' LValue ')' ';'  */
#line 224 "src/parser.y"
                                { (yyval.tree) = makeNode(_READE_); addChild((yyval.tree), (yyvsp[-2].tree)); }
#line 1530 "src/parser.tab.c"
    break;

  case 36: /* Instr: READC '(' LValue ')' ';'  */
#line 225 "src/parser.y"
                                { (yyval.tree) = makeNode(_READC_); addChild((yyval.tree), (yyvsp[-2].tree)); }
#line 1536 "src/parser.tab.c"
    break;

  case 37: /* Instr: PRINT '(' Exp ')' ';'  */
#line 226 "src/parser.y"
                             { (yyval.tree) = makeNode(_PRINT_); addChild((yyval.tree), (yyvsp[-2].tree)); }
#line 1542 "src/parser.tab.c"
    break;

  case 38: /* Instr: IF '(' Exp ')' Instr  */
#line 227 "src/parser.y"
                            { 
        (yyval.tree) = makeNode(_IF_); 
        addChild((yyval.tree), (yyvsp[-2].tree)); 
        Node *lst_instr = makeNode(_LIST_INSTR_); 
        addChild(lst_instr, (yyvsp[0].tree)); 
        addChild((yyval.tree), lst_instr);
    }
#line 1554 "src/parser.tab.c"
    break;

  case 39: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 234 "src/parser.y"
                                       { 
        (yyval.tree) = makeNode(_IFELSE_); 
        addChild((yyval.tree), (yyvsp[-4].tree));
        
        Node *if_instr = makeNode(_LIST_INSTR_); 
        addChild(if_instr, (yyvsp[-2].tree));
        addChild((yyval.tree), if_instr);

        Node *else_instr = makeNode(_LIST_INSTR_); 
        addChild(else_instr, (yyvsp[0].tree));
        addChild((yyval.tree), else_instr);
    }
#line 1571 "src/parser.tab.c"
    break;

  case 40: /* Instr: WHILE '(' Exp ')' Instr  */
#line 246 "src/parser.y"
                               { 
        (yyval.tree) = makeNode(_WHILE_); 
        addChild((yyval.tree), (yyvsp[-2].tree)); 
        Node *lst_instr = makeNode(_LIST_INSTR_); 
        addChild(lst_instr, (yyvsp[0].tree)); 
        addChild((yyval.tree), lst_instr); 
    }
#line 1583 "src/parser.tab.c"
    break;

  case 42: /* Instr: RETURN Exp ';'  */
#line 254 "src/parser.y"
                      { (yyval.tree) = makeNode(_RETURN_); addChild((yyval.tree), (yyvsp[-1].tree)); }
#line 1589 "src/parser.tab.c"
    break;

  case 43: /* Instr: RETURN ';'  */
#line 255 "src/parser.y"
                  { (yyval.tree) = makeNode(_RETURN_); }
#line 1595 "src/parser.tab.c"
    break;

  case 44: /* Instr: '{' ListInstr '}'  */
#line 256 "src/parser.y"
                         { (yyval.tree) = (yyvsp[-1].tree); }
#line 1601 "src/parser.tab.c"
    break;

  case 45: /* Instr: ';'  */
#line 257 "src/parser.y"
           { (yyval.tree) = makeNode(_EMPTY_); }
#line 1607 "src/parser.tab.c"
    break;

  case 46: /* Exp: Exp OR TB  */
#line 259 "src/parser.y"
                 { (yyval.tree) = makeNode(_OR_); addChild((yyval.tree), (yyvsp[-2].tree)); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1613 "src/parser.tab.c"
    break;

  case 48: /* TB: TB AND FB  */
#line 262 "src/parser.y"
                 { (yyval.tree) = makeNode(_AND_); addChild((yyval.tree), (yyvsp[-2].tree)); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1619 "src/parser.tab.c"
    break;

  case 50: /* FB: FB Equal M  */
#line 265 "src/parser.y"
                  { (yyval.tree) = (yyvsp[-1].tree); addChild((yyval.tree), (yyvsp[-2].tree)); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1625 "src/parser.tab.c"
    break;

  case 52: /* M: M Order E  */
#line 268 "src/parser.y"
                 { (yyval.tree) = (yyvsp[-1].tree); addChild((yyval.tree), (yyvsp[-2].tree)); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1631 "src/parser.tab.c"
    break;

  case 54: /* E: E AddSub T  */
#line 271 "src/parser.y"
                  { (yyval.tree) = (yyvsp[-1].tree); addChild((yyval.tree), (yyvsp[-2].tree)); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1637 "src/parser.tab.c"
    break;

  case 56: /* T: T DivStar F  */
#line 274 "src/parser.y"
                   { (yyval.tree) = (yyvsp[-1].tree); addChild((yyval.tree), (yyvsp[-2].tree)); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1643 "src/parser.tab.c"
    break;

  case 58: /* F: SUB F  */
#line 277 "src/parser.y"
             { (yyval.tree) = makeNode(_MINUS_); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1649 "src/parser.tab.c"
    break;

  case 59: /* F: '!' F  */
#line 278 "src/parser.y"
             { (yyval.tree) = makeNode(_NOT_); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1655 "src/parser.tab.c"
    break;

  case 60: /* F: '(' Exp ')'  */
#line 279 "src/parser.y"
                   { (yyval.tree) = (yyvsp[-1].tree); }
#line 1661 "src/parser.tab.c"
    break;

  case 61: /* F: NUM  */
#line 280 "src/parser.y"
           { (yyval.tree) = makeNode(_NUM_); (yyval.tree)->u.integer = yylval.integer; }
#line 1667 "src/parser.tab.c"
    break;

  case 62: /* F: CHARACTER  */
#line 281 "src/parser.y"
                 { (yyval.tree) = makeNode(_CHARACTER_); (yyval.tree)->u.character = yylval.character; }
#line 1673 "src/parser.tab.c"
    break;

  case 64: /* $@4: %empty  */
#line 283 "src/parser.y"
             { strcpy(func_name, yylval.identifier); }
#line 1679 "src/parser.tab.c"
    break;

  case 65: /* F: IDENT $@4 '(' Arguments ')'  */
#line 284 "src/parser.y"
        { 
            (yyval.tree) = makeNode(_CALL_FUNCT_);
            
            Node* ident = makeNode(_IDENTIFIER_); 
            strcpy(ident->u.identifier, func_name); 
            addChild((yyval.tree), ident); 

            Node* args = makeNode(_ARGUMENTS_);
            addChild(args, (yyvsp[-1].tree));
            addChild((yyval.tree), args);
        }
#line 1695 "src/parser.tab.c"
    break;

  case 66: /* Equal: EQ  */
#line 298 "src/parser.y"
          { (yyval.tree) = makeNode(_EQ_); }
#line 1701 "src/parser.tab.c"
    break;

  case 67: /* Equal: NEQ  */
#line 299 "src/parser.y"
          { (yyval.tree) = makeNode(_NEQ_); }
#line 1707 "src/parser.tab.c"
    break;

  case 68: /* Order: GT  */
#line 302 "src/parser.y"
         { (yyval.tree) =  makeNode(_GT_); }
#line 1713 "src/parser.tab.c"
    break;

  case 69: /* Order: GTEQ  */
#line 303 "src/parser.y"
           { (yyval.tree) =  makeNode(_GTEQ_); }
#line 1719 "src/parser.tab.c"
    break;

  case 70: /* Order: LT  */
#line 304 "src/parser.y"
         { (yyval.tree) =  makeNode(_LT_); }
#line 1725 "src/parser.tab.c"
    break;

  case 71: /* Order: LTEQ  */
#line 305 "src/parser.y"
           { (yyval.tree) =  makeNode(_LTEQ_); }
#line 1731 "src/parser.tab.c"
    break;

  case 72: /* AddSub: ADD  */
#line 308 "src/parser.y"
          { (yyval.tree) = makeNode(_ADD_); }
#line 1737 "src/parser.tab.c"
    break;

  case 73: /* AddSub: SUB  */
#line 309 "src/parser.y"
          { (yyval.tree) = makeNode(_SUB_); }
#line 1743 "src/parser.tab.c"
    break;

  case 74: /* DivStar: MUL  */
#line 312 "src/parser.y"
          { (yyval.tree) = makeNode(_MULT_); }
#line 1749 "src/parser.tab.c"
    break;

  case 75: /* DivStar: DIV  */
#line 313 "src/parser.y"
          { (yyval.tree) = makeNode(_DIV_); }
#line 1755 "src/parser.tab.c"
    break;

  case 76: /* DivStar: MOD  */
#line 314 "src/parser.y"
          { (yyval.tree) = makeNode(_MOD_); }
#line 1761 "src/parser.tab.c"
    break;

  case 77: /* LValue: IDENT  */
#line 318 "src/parser.y"
             { (yyval.tree) = makeNode(_IDENTIFIER_); strcpy((yyval.tree)->u.identifier, yylval.identifier); }
#line 1767 "src/parser.tab.c"
    break;

  case 78: /* LValue: StructField  */
#line 319 "src/parser.y"
                   { (yyval.tree) = makeNode(_STRUCT_FIELD_); addChild((yyval.tree), (yyvsp[0].tree)); }
#line 1773 "src/parser.tab.c"
    break;

  case 79: /* $@5: %empty  */
#line 322 "src/parser.y"
              { strcpy(buf, yylval.identifier); }
#line 1779 "src/parser.tab.c"
    break;

  case 80: /* StructField: IDENT $@5 '.' IDENT  */
#line 323 "src/parser.y"
        { 
            (yyval.tree) = makeNode(_IDENTIFIER_); 
            strcpy((yyval.tree)->u.identifier, buf); 
            Node* champs = makeNode(_IDENTIFIER_); 
            strcpy(champs->u.identifier, yylval.identifier);  
            addSibling((yyval.tree), champs); 
        }
#line 1791 "src/parser.tab.c"
    break;

  case 82: /* Arguments: %empty  */
#line 333 "src/parser.y"
              { (yyval.tree) = NULL; }
#line 1797 "src/parser.tab.c"
    break;

  case 83: /* ListExp: ListExp ',' Exp  */
#line 336 "src/parser.y"
                       { (yyval.tree) = (yyvsp[-2].tree); addSibling((yyval.tree), (yyvsp[0].tree)); }
#line 1803 "src/parser.tab.c"
    break;


#line 1807 "src/parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 340 "src/parser.y"


void print_help() {
    const char help_msg[] =
    "Usage: ./tpcc [OPTION]... [FILE]\n\
    tpcc - a tpc compiler\n\
    \n\
    Arguments\n\
      -t, --tree        print the abstract tree.\n\
      -s, --symtabs     print the symbol tables.\n\
      -h, --help        display this help and exit.\n";
    printf("%s", help_msg);
    exit(0);
}

void cmd_err() {
    fprintf(stderr, "Usage: ./tpcc [OPTION]... [FILE]\n");
    exit(3);
}

char *get_base_name(char *name) {
    char *s = strrchr(name, '/');
    return s == NULL ? name : s + 1;
}

char *get_valid_filename(char *name) {
    char *buf = malloc(256);
    char *s = strchr(name, '.');
    if(s != NULL) {
        *s = '\0';
    }
    sprintf(buf, "%s.asm", get_base_name(name));
    return buf;
}

int main(int argc, char** argv) {
    int opt, option_index = 0;
    static struct option long_options[] = {
        {"help", no_argument, 0,  'h' },
        {"tree", no_argument, 0, 't' },
        {"symtabs",  no_argument, 0,  's' },
        {0, 0, 0,  0 }
    };

    while ((opt = getopt_long(argc, argv, "hts", long_options, &option_index)) != -1) {
        switch (opt) {
            case 's':
                opts.symtab = 1;
                break;
            case 't':
                opts.tree = 1;
                break;
            case 'h':
                print_help();
            default:
                cmd_err();
        }
    }
    
    if(argc - optind >= 2) {
        fprintf(stderr, "error: too many input files\n");
        exit(EXIT_FAILURE);
    }

    FILE *input, *output;
    int yyret;
    char *output_name;

    output = fopen("_anonymous.asm", "w");
    setOutput(output);
    setDisplayMode(opts.symtab);
    if(optind < argc) {
        input = fopen(argv[optind], "r");
        output_name = get_valid_filename(argv[optind]);
        output = fopen(output_name, "w");
        setOutput(output);
        free(output_name);

        if(!input) {
            fprintf(stderr, "error: this file does not exists\n");
            exit(EXIT_FAILURE);
        }
        stdin = input;
        yyret = yyparse();
        fclose(input);
        fclose(output);
        return yyret;
    }
    yyret = yyparse();
    fclose(output);
    return yyret;
}

void yyerror(const char *s){
	fprintf(stderr, "%s near line %d character %d\n", s, lineno, charno);
}
