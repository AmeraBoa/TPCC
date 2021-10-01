/* A Bison parser, made by GNU Bison 3.7.3.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 26 "src/parser.y"

    #include "abstract-tree.h"
    #include "sem-check.h"
    #include "type.h"
    #include "translator.h"

#line 56 "src/parser.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CHARACTER = 258,               /* CHARACTER  */
    NUM = 259,                     /* NUM  */
    IDENT = 260,                   /* IDENT  */
    INT = 261,                     /* INT  */
    CHAR = 262,                    /* CHAR  */
    ADD = 263,                     /* ADD  */
    SUB = 264,                     /* SUB  */
    DIV = 265,                     /* DIV  */
    MUL = 266,                     /* MUL  */
    MOD = 267,                     /* MOD  */
    EQ = 268,                      /* EQ  */
    NEQ = 269,                     /* NEQ  */
    GTEQ = 270,                    /* GTEQ  */
    GT = 271,                      /* GT  */
    LT = 272,                      /* LT  */
    LTEQ = 273,                    /* LTEQ  */
    OR = 274,                      /* OR  */
    AND = 275,                     /* AND  */
    STRUCT = 276,                  /* STRUCT  */
    IF = 277,                      /* IF  */
    WHILE = 278,                   /* WHILE  */
    RETURN = 279,                  /* RETURN  */
    VOID = 280,                    /* VOID  */
    PRINT = 281,                   /* PRINT  */
    READC = 282,                   /* READC  */
    READE = 283,                   /* READE  */
    ELSE = 284                     /* ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "src/parser.y"

    Node* tree;
    char identifier[64];
    int integer;
    char character;

#line 109 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
