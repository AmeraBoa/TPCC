#ifndef _TREE
#define _TREE

#include "htable.h"

typedef enum
{
    _PROG_,
    _VAR_DECL_LIST_,
    _TYPE_,
    _STRUCT_TYPE_,
    _IDENTIFIER_,
    _PARAMETERS_,
    _DECL_FUNCTS_,
    _DECL_FUNCT_,
    _HEADER_FUNCT_,
    _BODY_,
    _LIST_INSTR_,
    _ASSIGN_,
    _RETURN_,
    _READE_,
    _READC_,
    _PRINT_,
    _IF_,
    _IFELSE_,
    _EXP_,
    _WHILE_,
    _AND_,
    _OR_,
    _NOT_,
    _EQ_,
    _NEQ_,
    _GT_,
    _GTEQ_,
    _LT_,
    _LTEQ_,
    _ADD_,
    _SUB_,
    _DIV_,
    _MULT_,
    _MOD_,
    _NUM_,
    _CHARACTER_,
    _CALL_FUNCT_,
    _ARGUMENTS_,
    _STRUCT_FIELD_,
    _STRUCT_VAR_,
    _MINUS_,
    _EMPTY_
} node_kind;

typedef struct node
{
    node_kind kind;
    union
    {
        int integer;
        char character;
        char identifier[MAXNAME];
    } u;
    struct node *firstChild, *nextSibling;
    SymbolTable *st;
    int lineno;
    int charno;
} Node;

Node *makeNode(node_kind kind);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node *node);
void printTree(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling

#endif