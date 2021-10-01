#ifndef _ST
#define _ST

#include "htable.h"

SymbolTable *createSymbolTable();
void clearSymbolTable();
void addVar(SymbolTable *st, const char *name, tpc_kind kind, tpc_type type);
int getVar(SymbolTable st, const char *name, ST_Entry *dest);
int getStruct(SymbolTable *global, const char *name, ST_Entry *dest);
int getStructField(SymbolTable *st, const char *field, const char *structure, ST_Entry *dest);
size_t getOffsetOfStruct(const char *struct_name, SymbolTable *global);
size_t getOffsetOfFunction(const char *function_name, SymbolTable* global);

ST_Entry *addFunction(SymbolTable *st, const char *name, tpc_type type);
ST_Entry *addStruct(SymbolTable *st, const char *name);
void addParameter(ST_Entry *entry, tpc_type type, SymbolTable *global);
void addStructField(ST_Entry *entry, const char *name, tpc_type type);
int getOffsetFromFieldInStruct(SymbolTable *global, const char *name, const char *field);
void addStructVar(SymbolTable *global, SymbolTable *st, const char *name, const char *struct_name);

void printSymbolTable(SymbolTable st);

#endif