#ifndef _HTABLE
#define _HTABLE

#include "type.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define ST_SIZE 2048

typedef struct parameter
{
    tpc_type type;
    struct parameter *next;
} Parameter;

typedef struct struct_field
{
    char name[MAXNAME];
    tpc_type type;
    struct struct_field *next;
} StructField;

typedef struct st_entry
{
    char name[MAXNAME];
    size_t offset;
    tpc_kind kind;
    tpc_type type;
    union
    {
        Parameter *parameters;
        StructField *struct_fields;
    } u;
    struct st_entry *next;
} ST_Entry;

typedef struct st
{
    /* Name of the corresponding function symbol table. */
    char *name;

    /* Offset to rbp. */
    int total_offset;

    ST_Entry **htable;
    size_t size;
} SymbolTable;

#endif