%{
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
%}

%code requires {
    #include "abstract-tree.h"
    #include "sem-check.h"
    #include "type.h"
    #include "translator.h"
}

%union {
    Node* tree;
    char identifier[64];
    int integer;
    char character;
}

%token <tree> CHARACTER
%token <tree> NUM
%token <tree> IDENT

%token <tree> INT CHAR
%token <tree> ADD SUB DIV MUL MOD
%token <tree> EQ NEQ GTEQ GT LT LTEQ
%token <tree> OR AND STRUCT IF WHILE RETURN VOID PRINT READC READE
%precedence <tree> ')'
%precedence <tree> ELSE

%type <tree> S Prog 
%type <tree> TypesVars TypeVar
%type <tree> Type
%type <tree> Declarators 
%type <tree> DeclFields
%type <tree> DeclFuncts DeclFunct HeaderFunct Parameters
%type <tree> ListTypVar StructVar
%type <tree> Body
%type <tree> DeclVars
%type <tree> ListInstr Instr
%type <tree> Exp TB FB M E T F LValue Arguments ListExp StructField

%type <tree> SimpleType
%type <tree> Order Equal
%type <tree> AddSub
%type <tree> DivStar
%%

S:     Prog
        {
            $$ = $1;
            if(opts.tree) {
                printTree($$);
            }
            lookForSemanticError($$);
            generateASM_Instruction($$);
            deleteTree($$);
        }
    ;
Prog:  TypesVars DeclFuncts 
        {
            $$ = makeNode(_PROG_);
            Node* var = makeNode(_VAR_DECL_LIST_);
            addChild(var, $1);
            addChild($$, var);
            Node* fonc = makeNode(_DECL_FUNCTS_);
            addChild(fonc, $2);
            addChild($$, fonc);
        }
    ;
TypesVars:
       TypesVars TypeVar { if($1 == NULL) $$ = $2; else { $$ = $1; addSibling($$, $2); } }
    |  %empty { $$ = NULL; }
    ;
TypeVar:
    STRUCT IDENT '{' { strcpy(buf, yylval.identifier); } DeclFields '}' ';'
        { 
            $$ = makeNode(_STRUCT_TYPE_);
            strcpy($$->u.identifier, buf);
            addChild($$, $5);
        }
    | Type Declarators ';' { $$ = $1; addChild($$, $2); }
    ;

Type:
       SimpleType
    |  StructVar
    ;
StructVar:
      STRUCT IDENT { $$ = makeNode(_STRUCT_VAR_); strcpy($$->u.identifier, struct_arg ? yylval.identifier : prev); }
    ;
SimpleType:
      CHAR  { $$ = makeNode(_TYPE_); strcpy($$->u.identifier, "char"); }
    | INT   { $$ = makeNode(_TYPE_); strcpy($$->u.identifier, "int"); }
    ;
Declarators:
       Declarators ',' IDENT { $$ = $1; Node *node = makeNode(_IDENTIFIER_); strcpy(node->u.identifier, yylval.identifier); addSibling($$, node); }
    |  IDENT { $$ = makeNode(_IDENTIFIER_); strcpy($$->u.identifier, yylval.identifier); }
    ;
DeclFields :
       DeclFields SimpleType Declarators ';' { $$ = $1; addSibling($$, $2); addChild($2, $3); }
    |  SimpleType Declarators ';' { $$ = $1; addChild($$, $2); }
    ;
DeclFuncts:
       DeclFuncts DeclFunct { $$ = $1; Node *node = makeNode(_DECL_FUNCT_); addChild(node, $2); addSibling($$, node); }
    |  DeclFunct { $$ = makeNode(_DECL_FUNCT_); addChild($$, $1); }
    ;
DeclFunct:
       HeaderFunct Body 
        {
            $$ = makeNode(_HEADER_FUNCT_); 
            addChild($$, $1); 
            Node* corps = makeNode(_BODY_); 
            addChild(corps, $2); 
            addSibling($$, corps);
        }
    ;
HeaderFunct:
       Type IDENT { if($1->kind == _STRUCT_VAR_) strcpy($1->u.identifier, prev); struct_arg = 1; strcpy(buf, yylval.identifier); } '(' Parameters ')' 
        {
            struct_arg = 0;
            $$ = $1;
            Node* ident = makeNode(_IDENTIFIER_); 
            strcpy(ident->u.identifier, buf); 
            addSibling($$, ident);
            Node* param = makeNode(_PARAMETERS_);
            addChild(param, $5);
            addSibling($$, param);
        }
    |  VOID IDENT { struct_arg = 1; strcpy(buf, yylval.identifier); } '(' Parameters ')' 
        { 
            struct_arg = 0;
            $$ = makeNode(_TYPE_); 
            strcpy($$->u.identifier, "void"); 
            Node* ident = makeNode(_IDENTIFIER_); 
            strcpy(ident->u.identifier, buf); 
            addSibling($$, ident); 
            Node* param = makeNode(_PARAMETERS_);
            addChild(param, $5);
            addSibling($$, param);
        }
    ;
Parameters:
       VOID { $$ = NULL; }
    |  ListTypVar
    ;
ListTypVar:
       ListTypVar ',' Type IDENT 
        { 
            $$ = $1;
            addSibling($$, $3);
            Node* ident = makeNode(_IDENTIFIER_);
            strcpy(ident->u.identifier, yylval.identifier);
            addChild($3, ident);
        }
    |  Type IDENT 
        { 
            $$ = $1; 
            Node* ident = makeNode(_IDENTIFIER_);
            strcpy(ident->u.identifier, yylval.identifier);
            addChild($$, ident);
        }
    ;
Body: '{' DeclVars ListInstr '}' 
        {
            $$ = makeNode(_VAR_DECL_LIST_);
            addChild($$, $2);
            
            Node* suiteInstr = makeNode(_LIST_INSTR_); 
            addChild(suiteInstr, $3);
            addSibling($$, suiteInstr);
        }
    ;
DeclVars:
        DeclVars Type Declarators ';' 
        { 
            if($1 != NULL) { 
                $$ = $1; 
                addSibling($1, $2);
            } else {
                $$ = $2;
            }
            addChild($2, $3);
            if($2->kind == _STRUCT_VAR_) {
                strcpy($2->u.identifier, prev); 
            }
        }
    |  %empty { $$ = NULL; }
    ;
ListInstr:
       ListInstr Instr 
       { 
           if($1 != NULL) { 
                $$ = $1; 
                addSibling($$, $2);
            } else {
                $$ = $2;
            }
       }
    |  %empty { $$ = NULL; }
    ;
Instr:
       LValue '=' Exp ';' { $$ = makeNode(_ASSIGN_); addChild($$, $1); addChild($$, $3); }
    |  READE '(' LValue ')' ';' { $$ = makeNode(_READE_); addChild($$, $3); }
    |  READC '(' LValue ')' ';' { $$ = makeNode(_READC_); addChild($$, $3); }
    |  PRINT '(' Exp ')' ';' { $$ = makeNode(_PRINT_); addChild($$, $3); }
    |  IF '(' Exp ')' Instr { 
        $$ = makeNode(_IF_); 
        addChild($$, $3); 
        Node *lst_instr = makeNode(_LIST_INSTR_); 
        addChild(lst_instr, $5); 
        addChild($$, lst_instr);
    }
    |  IF '(' Exp ')' Instr ELSE Instr { 
        $$ = makeNode(_IFELSE_); 
        addChild($$, $3);
        
        Node *if_instr = makeNode(_LIST_INSTR_); 
        addChild(if_instr, $5);
        addChild($$, if_instr);

        Node *else_instr = makeNode(_LIST_INSTR_); 
        addChild(else_instr, $7);
        addChild($$, else_instr);
    }
    |  WHILE '(' Exp ')' Instr { 
        $$ = makeNode(_WHILE_); 
        addChild($$, $3); 
        Node *lst_instr = makeNode(_LIST_INSTR_); 
        addChild(lst_instr, $5); 
        addChild($$, lst_instr); 
    }
    |  Exp ';'
    |  RETURN Exp ';' { $$ = makeNode(_RETURN_); addChild($$, $2); }
    |  RETURN ';' { $$ = makeNode(_RETURN_); }
    |  '{' ListInstr '}' { $$ = $2; }
    |  ';' { $$ = makeNode(_EMPTY_); }
    ;
Exp :  Exp OR TB { $$ = makeNode(_OR_); addChild($$, $1); addChild($$, $3); }
    |  TB
    ;
TB  :  TB AND FB { $$ = makeNode(_AND_); addChild($$, $1); addChild($$, $3); }
    |  FB
    ;
FB  :  FB Equal M { $$ = $2; addChild($$, $1); addChild($$, $3); }
    |  M
    ;
M   :  M Order E { $$ = $2; addChild($$, $1); addChild($$, $3); }
    |  E
    ;
E   :  E AddSub T { $$ = $2; addChild($$, $1); addChild($$, $3); }
    |  T
    ;
T   :  T DivStar F { $$ = $2; addChild($$, $1); addChild($$, $3); }
    |  F
    ;
F   :  SUB F { $$ = makeNode(_MINUS_); addChild($$, $2); }
    |  '!' F { $$ = makeNode(_NOT_); addChild($$, $2); }
    |  '(' Exp ')' { $$ = $2; }
    |  NUM { $$ = makeNode(_NUM_); $$->u.integer = yylval.integer; }
    |  CHARACTER { $$ = makeNode(_CHARACTER_); $$->u.character = yylval.character; }
    |  LValue
    |  IDENT { strcpy(func_name, yylval.identifier); } '(' Arguments  ')' 
        { 
            $$ = makeNode(_CALL_FUNCT_);
            
            Node* ident = makeNode(_IDENTIFIER_); 
            strcpy(ident->u.identifier, func_name); 
            addChild($$, ident); 

            Node* args = makeNode(_ARGUMENTS_);
            addChild(args, $4);
            addChild($$, args);
        }
    ;

Equal:
      EQ  { $$ = makeNode(_EQ_); }
    | NEQ { $$ = makeNode(_NEQ_); }
    ;
Order:
      GT { $$ =  makeNode(_GT_); }
    | GTEQ { $$ =  makeNode(_GTEQ_); }
    | LT { $$ =  makeNode(_LT_); }
    | LTEQ { $$ =  makeNode(_LTEQ_); }
    ;
AddSub:
      ADD { $$ = makeNode(_ADD_); }
    | SUB { $$ = makeNode(_SUB_); }
    ;
DivStar:
      MUL { $$ = makeNode(_MULT_); }
    | DIV { $$ = makeNode(_DIV_); }
    | MOD { $$ = makeNode(_MOD_); }
    ;

LValue:
       IDENT { $$ = makeNode(_IDENTIFIER_); strcpy($$->u.identifier, yylval.identifier); }
    |  StructField { $$ = makeNode(_STRUCT_FIELD_); addChild($$, $1); }
    ;
StructField:
        IDENT { strcpy(buf, yylval.identifier); } '.' IDENT 
        { 
            $$ = makeNode(_IDENTIFIER_); 
            strcpy($$->u.identifier, buf); 
            Node* champs = makeNode(_IDENTIFIER_); 
            strcpy(champs->u.identifier, yylval.identifier);  
            addSibling($$, champs); 
        }
    ;
Arguments:
       ListExp
    |  %empty { $$ = NULL; }
    ;
ListExp:
       ListExp ',' Exp { $$ = $1; addSibling($$, $3); }
    |  Exp
    ;

%%

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
