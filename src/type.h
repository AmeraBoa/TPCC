/*
TPC type implementation.
*/

#ifndef __TYPE
#define __TYPE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXNAME 64
#define DEFAULT_TYPE_SIZE 8

#define TPC_VOID \
    (tpc_type) { _VOID, NULL }
#define TPC_CHAR \
    (tpc_type) { _CHAR, NULL }
#define TPC_INT \
    (tpc_type) { _INT, NULL }
#define TPC_STRUCT(s) \
    (tpc_type) { _STRUCT, strdup(s) }

typedef enum
{
    PRIMITIVE,
    FUNCTION,
    STRUCT_TYPE,
    STRUCT_VAR
} tpc_kind;

typedef enum
{
    _VOID,
    _INT,
    _CHAR,
    _STRUCT
} simple_type;

typedef struct
{
    simple_type type;
    char *struct_ident;
} tpc_type;

static int inline isPrimitive(tpc_type type)
{
    return type.type != _STRUCT;
}

static inline void freeType(tpc_type type)
{
    free(type.struct_ident);
}

static inline int getSizeOfType(tpc_type t)
{
    return DEFAULT_TYPE_SIZE;
}

static inline tpc_type getTypeFromString(const char *name)
{
    if (!strcmp(name, "int"))
    {
        return TPC_INT;
    }
    else if (!strcmp(name, "char"))
    {
        return TPC_CHAR;
    }
    else if (!strcmp(name, "void"))
    {
        return TPC_VOID;
    }
    else
    {
        return TPC_STRUCT(name);
    }
}

static inline const char *getStringFromType(tpc_type type)
{
    switch (type.type)
    {
    case _VOID:
        return "void";
    case _INT:
        return "int";
    case _CHAR:
        return "char";
    default:
        return type.struct_ident;
    }
}

static int inline isEqual(tpc_type a, tpc_type b)
{
    if (a.type == b.type)
    {
        if (a.type == _STRUCT)
        {
            return !strcmp(a.struct_ident, b.struct_ident);
        }
        return 1;
    }
    return 0;
}

static int inline isCompatible(tpc_type a, tpc_type b)
{
    if (isPrimitive(a) && isPrimitive(b))
    {
        return 1;
    }
    else if (a.type == b.type)
    {
        return !strcmp(a.struct_ident, b.struct_ident);
    }
    return 0;
}

#endif