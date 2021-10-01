I [ \t\r]+
L [a-zA-Z_]
N [0-9]

%{
  #include "parser.tab.h"
  int lineno = 1;
  int charno = 0;
  char prev[64];
%}
%option yylineno noyywrap nounput noinput
%x SHORT_COMMENT LONG_COMMENT
%%
{I}               { charno += yyleng; }
"\n"		          { charno = 0; lineno++; }
"/*"		          { charno += yyleng; BEGIN LONG_COMMENT; }
"//"		          { charno += yyleng; BEGIN SHORT_COMMENT; }

"&&"			        { charno += yyleng; return AND; }
"||"			        { charno += yyleng; return OR; }

"+"               { charno += yyleng; return ADD; }
"-"			          { charno += yyleng; return SUB; }
"*"               { charno += yyleng; return MUL; }
"/"               { charno += yyleng; return DIV; }
"%"			          { charno += yyleng; return MOD; }
"<"               { charno += yyleng; return LT; }
"<="              { charno += yyleng; return LTEQ; }
">"               { charno += yyleng; return GT; }
">="	            { charno += yyleng; return GTEQ; }
"=="              { charno += yyleng; return EQ; }
"!="		          { charno += yyleng; return NEQ; }

"int"			        { charno += yyleng; return INT; }
"char"		        { charno += yyleng; return CHAR; }

"print"			      { charno += yyleng; return PRINT; }
"readc"			      { charno += yyleng; return READC; }
"reade"			      { charno += yyleng; return READE; }
"void"			      { charno += yyleng; return VOID; }
"struct"		      { charno += yyleng; return STRUCT; }
"if"			        { charno += yyleng; return IF; }
"else"			      { charno += yyleng; return ELSE; }
"while"			      { charno += yyleng; return WHILE; }
"return"		      { charno += yyleng; return RETURN; }

{L}({L}|{N})*	    { charno += yyleng; strcpy(prev, yylval.identifier); strcpy(yylval.identifier, yytext); return IDENT; }
{N}+		          { charno += yyleng; yylval.integer = atoi(yytext); return NUM; }
'\\?.'		        { charno += yyleng; yylval.character = yytext[1]; return CHARACTER; }
.			            { charno += yyleng; return yytext[0]; }

<LONG_COMMENT>"*/"		            { BEGIN INITIAL; charno += yyleng; }
<LONG_COMMENT,SHORT_COMMENT>.		  { charno += yyleng; }
<LONG_COMMENT>\n		              { lineno++; charno = 0; }
<SHORT_COMMENT>\n		              { BEGIN INITIAL; lineno++; charno = 0; }
%%
