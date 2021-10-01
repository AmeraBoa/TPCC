#ifndef _TRANSLATE
#define _TRANSLATE

#include "abstract-tree.h"
#include "symbol-table.h"
#include <stdio.h>

void generateASM_Instruction(Node *node);
void setOutput(FILE *file);

#endif