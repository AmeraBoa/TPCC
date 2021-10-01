/*
The symbol table module implement the necessary operations to check for
semantic errors. 

Function parameters and struct fields are implemented with a linked list of type Parameter and 
StructField respectively. As such, they required to be added to the ST_Entry structure externally, 
using addParameter and addStructField (note: addFunction and addStruct return the required structure).
*/

#include "symbol-table.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* -------------------------- private prototypes ---------------------------- */

static int _hash(const char *name, size_t size);
static void _clearST_Entry();
static ST_Entry *_createST_Entry(const char *name, tpc_kind kind, tpc_type type);
static void _addST_EntryToHead(SymbolTable *st, ST_Entry *new_entry);
static void _printST_Entry(ST_Entry entry);
static void _clearParameters(Parameter *parameters);
static void _clearStructFields(StructField *struct_fields);

/* -------------------------- hash function ---------------------------- */

int _hash(const char *name, size_t size)
{
    unsigned int h = 0, k = 513;
    for (int i = 0; i < strlen(name); i++)
    {
        h += name[i] * pow(k, i);
    }
    return h % size;
}

/* -------------------------- API implementation -------------------------- */

SymbolTable *createSymbolTable(const char *name)
{
    SymbolTable *st = malloc(sizeof(SymbolTable));
    if (!st)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    st->name = strdup(name);
    st->size = ST_SIZE;
    st->htable = malloc(ST_SIZE * sizeof(ST_Entry));
    st->total_offset = 0;
    for (size_t i = 0; i < ST_SIZE; i++)
    {
        st->htable[i] = NULL;
    }
    return st;
}

void clearSymbolTable(SymbolTable *st)
{
    for (size_t i = 0; i < st->size; i++)
    {
        _clearST_Entry(st->htable[i]);
    }
    free(st->name);
    free(st->htable);
    free(st);
}

void _clearST_Entry(ST_Entry *entry)
{
    ST_Entry *tmp;
    while (entry != NULL)
    {
        tmp = entry;
        entry = entry->next;
        freeType(tmp->type);
        if (tmp->kind == STRUCT_TYPE)
        {
            _clearStructFields(tmp->u.struct_fields);
        }
        else if (tmp->kind == FUNCTION)
        {
            _clearParameters(tmp->u.parameters);
        }
        free(tmp);
    }
}

ST_Entry *_createST_Entry(const char *name, tpc_kind kind, tpc_type type)
{
    ST_Entry *entry = malloc(sizeof(ST_Entry));
    if (!entry)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(entry->name, name);
    entry->kind = kind;
    entry->type = type;
    entry->next = NULL;
    return entry;
}

void _addST_EntryToHead(SymbolTable *st, ST_Entry *new_entry)
{
    ST_Entry *entry = st->htable[_hash(new_entry->name, st->size)];
    new_entry->next = entry;
    st->htable[_hash(new_entry->name, st->size)] = new_entry;
}

void addVar(SymbolTable *st, const char *name, tpc_kind kind, tpc_type type)
{
    ST_Entry *new_entry = _createST_Entry(name, kind, type);
    st->total_offset += getSizeOfType(type);
    new_entry->offset = st->total_offset;
    _addST_EntryToHead(st, new_entry);
}

ST_Entry *addFunction(SymbolTable *st, const char *name, tpc_type type)
{
    ST_Entry *entry = _createST_Entry(name, FUNCTION, type);
    entry->u.parameters = NULL;
    _addST_EntryToHead(st, entry);
    entry->offset = 0;
    return entry;
}

ST_Entry *addStruct(SymbolTable *st, const char *name)
{
    char formated_name[MAXNAME];
    sprintf(formated_name, ".%s", name);
    ST_Entry *entry = _createST_Entry(formated_name, STRUCT_TYPE, (tpc_type) {_STRUCT, NULL});
    entry->u.struct_fields = NULL;
    _addST_EntryToHead(st, entry);
    return entry;
}

/* Add the specified struct var name and all of his fields. */
void addStructVar(SymbolTable *global, SymbolTable *st, const char *name, const char *struct_name) {
    ST_Entry tmp;
    char buf[MAXNAME];
    size_t size = 0;
    
    sprintf(buf, ".%s", struct_name);
    if(!getVar(*global, buf, &tmp)) {
        perror("readVar in addStructVar");
        exit(EXIT_FAILURE);
    }
    for (StructField *sf = tmp.u.struct_fields; sf != NULL; sf = sf->next)
    {
        sprintf(buf, "%s.%s", name, sf->name);
        addVar(st, buf, PRIMITIVE, sf->type);
        size += getSizeOfType(sf->type);
    }

    ST_Entry *entry = _createST_Entry(name, STRUCT_VAR, TPC_STRUCT(struct_name));
    entry->offset = st->total_offset;
    _addST_EntryToHead(st, entry);
}

/* 
Get a variable 'name' from symbol table 'st'. 

Return 1 if the search was successful.
*/
int getVar(SymbolTable st, const char *name, ST_Entry *dest)
{
    for (ST_Entry *entry = st.htable[_hash(name, st.size)]; entry != NULL; entry = entry->next)
    {
        if (!strcmp(entry->name, name))
        {
            *dest = *entry;
            return 1;
        }
    }
    return 0;
}

int getStruct(SymbolTable *global, const char *name, ST_Entry *dest) {
    char struct_name[MAXNAME];
    sprintf(struct_name, ".%s", name);
    return getVar(*global, struct_name, dest);
}

int getStructField(SymbolTable *st, const char *field, const char *structure, ST_Entry *dest) {
    char struct_name[MAXNAME];
    sprintf(struct_name, "%s.%s", structure, field);
    return getVar(*st, struct_name, dest);
}

/* Offset: */

size_t getOffsetOfStruct(const char *struct_name, SymbolTable *global) {
    ST_Entry tmp;
    getStruct(global, struct_name, &tmp);
    return tmp.offset;
}

size_t getOffsetOfFunction(const char *function_name, SymbolTable* global) {
    ST_Entry tmp;
    getVar(*global, function_name, &tmp);
    return tmp.offset;
}

/* -------------------------- Sub-Entry implementation -------------------------- */

Parameter *_createParameter(tpc_type type)
{
    Parameter *p = malloc(sizeof(Parameter));
    if (!p)
    {
        perror("malloc _createParameter");
        exit(EXIT_FAILURE);
    }
    p->type = type;
    p->next = NULL;
    return p;
}

void _clearParameters(Parameter *p)
{
    Parameter *tmp;
    while (p != NULL)
    {
        tmp = p;
        p = p->next;
        freeType(tmp->type);
        free(tmp);
    }
}

void addParameter(ST_Entry *entry, tpc_type type, SymbolTable *global)
{
    Parameter *new_p = _createParameter(type);
    Parameter *p = entry->u.parameters;
    if (!p)
    {
        entry->u.parameters = new_p;
    }
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = new_p;
    }
    if(isPrimitive(type)) {
        entry->offset += getSizeOfType(type);
    } else {
        entry->offset += getOffsetOfStruct(type.struct_ident, global);
    }
}

StructField *_createStructField(const char *name, tpc_type type)
{
    StructField *sf = malloc(sizeof(StructField));
    if (!sf)
    {
        perror("malloc _createStructField");
        exit(EXIT_FAILURE);
    }
    strcpy(sf->name, name);
    sf->type = type;
    sf->next = NULL;
    return sf;
}

void _clearStructFields(StructField *sf)
{
    StructField *tmp;
    while (sf != NULL)
    {
        tmp = sf;
        sf = sf->next;
        freeType(tmp->type);
        free(tmp);
    }
}

void addStructField(ST_Entry *entry, const char *name, tpc_type type)
{
    StructField *new_sf = _createStructField(name, type);
    StructField *sf = entry->u.struct_fields;
    if (!sf)
    {
        entry->u.struct_fields = new_sf;
    }
    else
    {
        while (sf->next != NULL)
        {
            sf = sf->next;
        }
        sf->next = new_sf;
    }
    entry->offset += getSizeOfType(type);
}

int getOffsetFromFieldInStruct(SymbolTable *global, const char *struct_name, const char *field) {
    ST_Entry tmp;
    size_t size = 0;
    char buf[MAXNAME];
    sprintf(buf, ".%s", struct_name);
    getVar(*global, buf, &tmp);
    for (StructField *sf = tmp.u.struct_fields; sf != NULL; sf = sf->next)
    {
        if(!strcmp(field, sf->name)) {
            return size;
        }
        size += getSizeOfType(sf->type);
    }
    perror("error in getOffsetFromFieldInStruct:");
    exit(EXIT_FAILURE);
}

/* -------------------------- Debug -------------------------- */

void printSymbolTable(SymbolTable st)
{
    printf("-------------- %s --------------\n", st.name);
    for (size_t i = 0; i < st.size; i++)
    {
        for (ST_Entry *entry = st.htable[i]; entry != NULL; entry = entry->next)
        {
            _printST_Entry(*entry);
        }
    }
}

static void _printST_Entry(ST_Entry entry)
{
    printf("%s: ", entry.name);
    switch (entry.kind)
    {
    case PRIMITIVE:
    case STRUCT_VAR:
        printf("%s\n", getStringFromType(entry.type));
        break;
    case STRUCT_TYPE:
        printf("struct\n");
        for (StructField *sf = entry.u.struct_fields; sf != NULL; sf = sf->next)
        {
            printf("  - %s: %s\n", sf->name, getStringFromType(sf->type));
        }
        break;
    case FUNCTION:
        for (Parameter *p = entry.u.parameters; p != NULL; p = p->next)
        {
            printf("%s -> ", getStringFromType(p->type));
        }
        printf("%s\n", getStringFromType(entry.type));
        break;
    default:
        break;
    }
}
