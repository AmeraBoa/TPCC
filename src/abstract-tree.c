#include "abstract-tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

extern int lineno;
extern int charno;

static const char *StringFromKind[] = {
    "Prog",
    "VarDeclList",
    "Type",
    "Struct",
    "Identifier",
    "Parameters",
    "DeclFuncts",
    "DeclFunct",
    "HeaderFoncts",
    "Body",
    "ListInstr",
    "Assign",
    "Return",
    "ReadE",
    "ReadC",
    "Print",
    "If",
    "IfElse",
    "Exp",
    "While",
    "And",
    "Or",
    "Not",
    "Equal",
    "NotEqual",
    "Greater",
    "GreaterOrEqual",
    "Less",
    "LessOrEqual",
    "Add",
    "Sub",
    "Div",
    "Mult",
    "Mod",
    "Num",
    "Character",
    "CallFunct",
    "Arguments",
    "StructField",
    "StructVar",
    "Minus",
    "Empty"};

/* -------------------------- API implementation ---------------------------- */

Node *makeNode(node_kind kind)
{
    Node *node = malloc(sizeof(Node));
    if (!node)
    {
        printf("Run out of memory\n");
        exit(1);
    }
    node->kind = kind;
    node->firstChild = node->nextSibling = NULL;
    node->lineno = lineno;
    node->charno = charno;
    return node;
}

void addSibling(Node *node, Node *sibling)
{
    Node *curr = node;
    while (curr->nextSibling != NULL)
    {
        curr = curr->nextSibling;
    }
    curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child)
{
    if (parent->firstChild == NULL)
    {
        parent->firstChild = child;
    }
    else
    {
        addSibling(parent->firstChild, child);
    }
}

void deleteTree(Node *node)
{
    if (node->firstChild)
    {
        deleteTree(node->firstChild);
    }
    if (node->nextSibling)
    {
        deleteTree(node->nextSibling);
    }
    free(node);
}

/* -------------------------- Debug -------------------------- */

void printTree(Node *node)
{
    static bool rightmost[128]; /* current node is rightmost sibling */
    static int depth = 0;       /* depth of current node */
    for (int i = 1; i < depth; i++)
    { /* 2502 = vertical line */
        printf(rightmost[i] ? "    " : "\u2502   ");
    }
    if (depth > 0)
    { /* 2514 = up and right; 2500 = horiz; 251c = vertical and right */
        printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
    }
    printf("%s", StringFromKind[node->kind]);
    switch (node->kind)
    {
    case _STRUCT_VAR_:
        printf(": %s", node->u.identifier);
        break;
    case _STRUCT_TYPE_:
        printf(": %s", node->u.identifier);
        break;
    case _IDENTIFIER_:
        printf(": %s", node->u.identifier);
        break;
    case _TYPE_:
        printf(": %s", node->u.identifier);
        break;
    case _NUM_:
        printf(": %d", node->u.integer);
        break;
    case _CHARACTER_:
        printf(": %c", node->u.character);
        break;
    default:
        break;
    }
    printf("\n");
    depth++;
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        rightmost[depth] = (child->nextSibling) ? false : true;
        printTree(child);
    }
    depth--;
}
