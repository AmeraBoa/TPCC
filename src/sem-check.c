/*
Look over the AST and symbol table searching for semantic errors.
*/

#include "sem-check.h"

#define SEM_ERR 2
#define SYS_ERR 3

/* Value of symtab option from parser.y. */
static int g_print_tab;

void setDisplayMode(int mode)
{
    g_print_tab = mode;
}

/* -------------------------- private prototypes ---------------------------- */

/* Declarations check: */
static void _checkProg(Node *node, SymbolTable *global);
static void _checkVarDeclList(Node *node, SymbolTable *global, SymbolTable *st);
static void _checkStructType(Node *node, SymbolTable *global);
static void _checkStructVar(Node *node, SymbolTable *global, SymbolTable *st);
static void _checkType(Node *node, SymbolTable *st);

/* Functions: */
static void _checkDeclFuncts(Node *node, SymbolTable *global);
static void _checkDeclFunct(Node *node, SymbolTable *global);
static void _checkHeaderFunct(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkBody(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkParameters(Node *node, ST_Entry *function, SymbolTable *global);

/* Instructions: */
static void _checkListInstr(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkAssign(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkIf(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkIfElse(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkWhile(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkCondition(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkReturn(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkReadC(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkReadE(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkPrint(Node *node, SymbolTable *global, SymbolTable *local);

/* Expressions/Type check: */
static tpc_type _getTypeOfExp(Node *node, SymbolTable *global, SymbolTable *local);
static tpc_type _getTypeOfBinaryOp(Node *node, SymbolTable *global, SymbolTable *local);
static tpc_type _getTypeOfLogicalOp(Node *node, SymbolTable *global, SymbolTable *local);
static tpc_type _getTypeOfUnaryOp(Node *node, SymbolTable *global, SymbolTable *local);
static tpc_type _getTypeOfIdentifier(Node *node, SymbolTable *global, SymbolTable *local);
static tpc_type _getTypeOfCallFunct(Node *node, SymbolTable *global, SymbolTable *local);
static void _checkArguments(Node *node, SymbolTable *global, SymbolTable *local, ST_Entry function);
static tpc_type _getTypeOfStructField(Node *node, SymbolTable *global, SymbolTable *local);

/* Error messages: */
static void _checkIfMainExists(Node *node, int lineno, int charno);
static void _checkIfFuncReturnTypeIsVoid(tpc_type func_type, tpc_type return_type, int lineno, int charno);
static void _checkIfTypeCompatible(tpc_type a, tpc_type b, int lineno, int charno);
static void _validNameAddVar(SymbolTable *st, const char *name, tpc_kind kind, tpc_type type, int lineno, int charno);
static ST_Entry *_validNameAddFunction(SymbolTable *st, const char *name, tpc_type type, int lineno, int charno);
static ST_Entry *_validNameAddStruct(SymbolTable *st, const char *name, int lineno, int charno);
static void _validNameAddStructVar(SymbolTable *global, SymbolTable *st, const char *name, const char *struct_name, int lineno, int charno);
static void _checkIfNameExists(SymbolTable *st, const char *name, int lineno, int charno);
static void _checkForImplicitConversion(tpc_type a, tpc_type b, int lineno, int charno);
static void _checkIfNonVoidFuncContainsReturn(Node *node, SymbolTable *global, SymbolTable *local);
static int _checkIfContainsReturn(Node *node);
static void _checkIfExpIsScalar(Node *node, SymbolTable *global, SymbolTable *local);

/* -------------------------- Utility -------------------------- */

static const char *_getSymbolFromBinaryKind(tpc_kind kind)
{
    switch (kind)
    {
    case _ADD_:
        return "+";
    case _SUB_:
        return "-";
    case _MULT_:
        return "*";
    case _DIV_:
        return "/";
    case _EQ_:
        return "==";
    case _GTEQ_:
        return ">=";
    case _GT_:
        return ">";
    case _LTEQ_:
        return "<=";
    case _LT_:
        return "<";
    case _NEQ_:
        return "!=";
    }
}

/* -------------------------- Declaration check -------------------------- */

void lookForSemanticError(Node *node)
{
    node->st = createSymbolTable(".global");
    _checkProg(node, node->st);
    if (g_print_tab)
    {
        printSymbolTable(*(node->st));
    }
    _checkIfMainExists(node, node->lineno, node->charno);
}

void _checkProg(Node *node, SymbolTable *global)
{
    _checkVarDeclList(FIRSTCHILD(node), global, NULL);
    _checkDeclFuncts(SECONDCHILD(node), global);
}

void _checkVarDeclList(Node *node, SymbolTable *global, SymbolTable *st)
{
    SymbolTable *target = st == NULL ? global : st;
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        switch (child->kind)
        {
        case _STRUCT_TYPE_:
            _checkStructType(child, target);
            break;
        case _STRUCT_VAR_:
            _checkStructVar(child, global, target);
            break;
        case _TYPE_:
            _checkType(child, target);
            break;
        }
    }
}

void _checkStructType(Node *node, SymbolTable *global)
{
    ST_Entry *struct_entry = _validNameAddStruct(global, node->u.identifier, node->lineno, node->charno);
    node->st = createSymbolTable();
    for (Node *type = node->firstChild; type != NULL; type = type->nextSibling)
    {
        for (Node *ident = type->firstChild; ident != NULL; ident = ident->nextSibling)
        {
            addStructField(struct_entry, ident->u.identifier, getTypeFromString(type->u.identifier));
            _validNameAddVar(node->st, ident->u.identifier, STRUCT_VAR, getTypeFromString(type->u.identifier),
                             node->lineno, node->charno);
        }
    }
    clearSymbolTable(node->st);
}

void _checkStructVar(Node *node, SymbolTable *global, SymbolTable *st)
{
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        _validNameAddStructVar(global, st, child->u.identifier, node->u.identifier,
                               node->lineno, node->charno);
    }
}

void _checkType(Node *node, SymbolTable *st)
{
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        _validNameAddVar(st, child->u.identifier, PRIMITIVE, getTypeFromString(node->u.identifier),
                         node->lineno, node->charno);
    }
}

void _checkDeclFuncts(Node *node, SymbolTable *global)
{
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        _checkDeclFunct(child, global);
    }
}

void _checkDeclFunct(Node *node, SymbolTable *global)
{
    node->st = createSymbolTable(SECONDCHILD(FIRSTCHILD(node))->u.identifier);
    _checkHeaderFunct(FIRSTCHILD(node), global, node->st);
    _checkBody(SECONDCHILD(node), global, node->st);
    if (g_print_tab)
    {
        printSymbolTable(*(node->st));
    }
}

void _checkHeaderFunct(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *type = FIRSTCHILD(node)->u.identifier;
    char *name = SECONDCHILD(node)->u.identifier;
    ST_Entry *function = _validNameAddFunction(global, name, getTypeFromString(type), node->lineno, node->charno);
    _checkParameters(FIRSTCHILD(THIRDCHILD(node)), function, global);

    /* Add parameters as local variables. */
    _checkVarDeclList(THIRDCHILD(node), global, local);
}

void _checkParameters(Node *node, ST_Entry *function, SymbolTable *global)
{
    for (; node != NULL; node = node->nextSibling)
    {
        addParameter(function, getTypeFromString(node->u.identifier), global);
    }
}

void _checkBody(Node *node, SymbolTable *global, SymbolTable *local)
{
    _checkVarDeclList(FIRSTCHILD(node), global, local);
    _checkListInstr(SECONDCHILD(node), global, local);
    _checkIfNonVoidFuncContainsReturn(node, global, local);
}

/* -------------------------- Type check -------------------------- */

void _checkListInstr(Node *node, SymbolTable *global, SymbolTable *local)
{
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        switch (child->kind)
        {
        case _ASSIGN_:
            _checkAssign(child, global, local);
            break;
        case _IFELSE_:
            _checkIfElse(child, global, local);
            break;
        case _IF_:
            _checkIf(child, global, local);
            break;
        case _WHILE_:
            _checkWhile(child, global, local);
            break;
        case _RETURN_:
            _checkReturn(child, global, local);
            break;
        case _READC_:
            _checkReadC(child, global, local);
            break;
        case _READE_:
            _checkReadE(child, global, local);
            break;
        case _PRINT_:
            _checkPrint(child, global, local);
            break;
        default:
            _getTypeOfExp(child, global, local);
            break;
        }
    }
}

void _checkAssign(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type a, b;
    a = _getTypeOfExp(FIRSTCHILD(node), global, local);
    b = _getTypeOfExp(SECONDCHILD(node), global, local);
    _checkIfTypeCompatible(a, b, node->lineno, node->charno);
    _checkForImplicitConversion(b, a, node->lineno, node->charno);
}

void _checkIf(Node *node, SymbolTable *global, SymbolTable *local)
{
    _checkCondition(FIRSTCHILD(node), global, local);
    _checkListInstr(SECONDCHILD(node), global, local);
}

void _checkIfElse(Node *node, SymbolTable *global, SymbolTable *local)
{
    _checkCondition(FIRSTCHILD(node), global, local);
    _checkListInstr(SECONDCHILD(node), global, local);
    _checkListInstr(THIRDCHILD(node), global, local);
}

void _checkWhile(Node *node, SymbolTable *global, SymbolTable *local)
{
    _checkCondition(FIRSTCHILD(node), global, local);
    _checkListInstr(SECONDCHILD(node), global, local);
}

void _checkCondition(Node *node, SymbolTable *global, SymbolTable *local)
{
    _checkIfExpIsScalar(node, global, local);
}

void _checkReturn(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type return_type = _getTypeOfExp(FIRSTCHILD(node), global, local);
    ST_Entry tmp;
    getVar(*global, local->name, &tmp);
    tpc_type func_type = tmp.type;
    _checkIfFuncReturnTypeIsVoid(func_type, return_type, node->lineno, node->charno);
    _checkIfTypeCompatible(return_type, func_type, node->lineno, node->charno);
    _checkForImplicitConversion(return_type, func_type, node->lineno, node->charno);
}

void _checkReadC(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type type = _getTypeOfExp(FIRSTCHILD(node), global, local);
    _checkIfTypeCompatible(type, TPC_CHAR, node->lineno, node->charno);
    _checkForImplicitConversion(type, TPC_CHAR, node->lineno, node->charno);
}

void _checkReadE(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type type = _getTypeOfExp(FIRSTCHILD(node), global, local);
    _checkIfTypeCompatible(type, TPC_INT, node->lineno, node->charno);
    _checkForImplicitConversion(type, TPC_INT, node->lineno, node->charno);
}

void _checkPrint(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type type = _getTypeOfExp(FIRSTCHILD(node), global, local);
    _checkIfTypeCompatible(type, TPC_INT, node->lineno, node->charno);

    if (type.type == _INT)
    {
        strcpy(node->u.identifier, "int");
    }
    else if (type.type == _CHAR)
    {
        strcpy(node->u.identifier, "char");
    }
}

tpc_type _getTypeOfExp(Node *node, SymbolTable *global, SymbolTable *local)
{
    if (node == NULL)
        return TPC_VOID;
    switch (node->kind)
    {
    case _IDENTIFIER_:
        return _getTypeOfIdentifier(node, global, local);
    case _ADD_:
    case _SUB_:
    case _MULT_:
    case _DIV_:
    case _MOD_:
        return _getTypeOfBinaryOp(node, global, local);
    case _EQ_:
    case _NEQ_:
    case _GT_:
    case _GTEQ_:
    case _LT_:
    case _LTEQ_:
        return _getTypeOfBinaryOp(node, global, local);
    case _NOT_:
    case _MINUS_:
        return _getTypeOfUnaryOp(node, global, local);
    case _AND_:
    case _OR_:
        return _getTypeOfLogicalOp(node, global, local);
    case _NUM_:
        return TPC_INT;
    case _CHARACTER_:
        return TPC_CHAR;
    case _CALL_FUNCT_:
        return _getTypeOfCallFunct(node, global, local);
    case _STRUCT_FIELD_:
        return _getTypeOfStructField(node, global, local);
    default:
        return TPC_VOID;
    }
}

tpc_type _getTypeOfIdentifier(Node *node, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    if (!getVar(*local, node->u.identifier, &tmp))
    {
        if (!getVar(*global, node->u.identifier, &tmp))
        {
            fprintf(stderr, "error: '%s' undeclared, near line %d, character %d\n",
                    node->u.identifier, node->lineno, node->charno);
            exit(SEM_ERR);
        }
    }
    return tmp.type;
}

tpc_type _getTypeOfBinaryOp(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type a, b;
    a = _getTypeOfExp(FIRSTCHILD(node), global, local);
    b = _getTypeOfExp(SECONDCHILD(node), global, local);
    if (!isPrimitive(a) || !isPrimitive(b))
    {
        fprintf(stderr, "error: invalid operands to binary %s (have '%s' and '%s'), near line %d, character %d\n",
                _getSymbolFromBinaryKind(node->kind), getStringFromType(a), getStringFromType(b),
                node->lineno, node->charno);
        exit(SEM_ERR);
    }
    return TPC_INT;
}

tpc_type _getTypeOfLogicalOp(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type a, b;
    a = _getTypeOfExp(FIRSTCHILD(node), global, local);
    b = _getTypeOfExp(SECONDCHILD(node), global, local);
    if (!isPrimitive(a) || !isPrimitive(b))
    {
        fprintf(stderr, "error: used struct type where scalar is required, near line %d, character %d\n",
                node->lineno, node->charno);
        exit(SEM_ERR);
    }
    return TPC_INT;
}

tpc_type _getTypeOfUnaryOp(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type a;
    a = _getTypeOfExp(FIRSTCHILD(node), global, local);
    if (!isPrimitive(a))
    {
        fprintf(stderr, "error: wrong type argument to unary operator (have '%s'), near line %d, character %d\n",
                getStringFromType(a), node->lineno, node->charno);
        exit(SEM_ERR);
    }
    return a;
}

tpc_type _getTypeOfCallFunct(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *func_name = FIRSTCHILD(node)->u.identifier;
    ST_Entry function;
    if (!getVar(*global, func_name, &function))
    {
        fprintf(stderr, "error: implicit declaration of '%s', near line %d, character %d\n",
                func_name, node->lineno, node->charno);
        exit(SEM_ERR);
    }
    if (function.kind != FUNCTION)
    {
        fprintf(stderr, "error: called object '%s' is not a function, near line %d, character %d\n",
                node->lineno, node->charno);
        exit(SEM_ERR);
    }
    _checkArguments(SECONDCHILD(node), global, local, function);
    return function.type;
}

void _checkArguments(Node *node, SymbolTable *global, SymbolTable *local, ST_Entry function)
{
    tpc_type arg_type, param_type;
    Node *arguments = FIRSTCHILD(node);
    Parameter *parameters = function.u.parameters;

    while (parameters != NULL && arguments != NULL)
    {
        arg_type = _getTypeOfExp(arguments, global, local);
        param_type = parameters->type;
        _checkIfTypeCompatible(arg_type, param_type, node->lineno, node->charno);
        _checkForImplicitConversion(arg_type, param_type, node->lineno, node->charno);
        arguments = arguments->nextSibling;
        parameters = parameters->next;
    }

    if (arguments == NULL && parameters != NULL)
    {
        fprintf(stderr, "error: not enough arguments was passed to '%s', near line %d, character %d\n",
                function.name, node->lineno, node->charno);
        exit(SEM_ERR);
    }
    else if (arguments != NULL && parameters == NULL)
    {
        fprintf(stderr, "error: too many arguments was passed to '%s', near line %d, character %d\n",
                function.name, node->lineno, node->charno);
        exit(SEM_ERR);
    }
}

tpc_type _getTypeOfStructField(Node *node, SymbolTable *global, SymbolTable *local)
{
    tpc_type type;
    char *struct_name = FIRSTCHILD(node)->u.identifier;
    char *field_name = SECONDCHILD(node)->u.identifier;
    ST_Entry tmp;
    if (!getVar(*local, struct_name, &tmp))
    {
        if (!getVar(*global, struct_name, &tmp))
        {
            fprintf(stderr, "error: '%s' was not declared, near line %d, character %d\n",
                struct_name, node->lineno, node->charno);
            exit(SEM_ERR);
        }
    }

    if (tmp.kind != STRUCT_VAR)
    {
        fprintf(stderr, "error: request for member ‘%s’ in something not a structure, near line %d, character %d\n",
            field_name, node->lineno, node->charno);
        exit(SEM_ERR);
    }

    char *struct_ident = tmp.type.struct_ident;
    if (!getStruct(global, struct_ident, &tmp))
    {
        fprintf(stderr, "error: 'struct %s' was not declared, near line %d, character %d\n",
                struct_ident + 1, field_name, node->lineno, node->charno);
        exit(SEM_ERR);
    }

    ST_Entry dest;
    if (!getStructField(local, field_name, struct_name, &dest))
    {
        if (!getStructField(global, field_name, struct_name, &dest))
        {
            fprintf(stderr, "error: 'struct %s' has no member named '%s', near line %d, character %d\n",
                    struct_ident, field_name, node->lineno, node->charno);
            exit(SEM_ERR);
        }
    }

    ST_Entry sf;
    if (getVar(*local, struct_name, &tmp))
    {
        getStructField(local, field_name, struct_name, &sf);
    }
    else
    {
        getStructField(global, field_name, struct_name, &sf);
    }
    return sf.type;
}

/* -------------------------- Error messages -------------------------- */

void _checkIfMainExists(Node *node, int lineno, int charno)
{
    ST_Entry tmp;
    if (!getVar(*(node->st), "main", &tmp))
    {
        fprintf(stderr, "error: no main was found, near line %d, character %d\n",
                lineno, charno);
        exit(SEM_ERR);
    }
}

void _checkIfTypeCompatible(tpc_type a, tpc_type b, int lineno, int charno)
{
    if (!isCompatible(a, b))
    {
        fprintf(stderr, "error: incompatible type when passing type '%s' but '%s' was expected, near line %d, character %d\n",
                getStringFromType(a), getStringFromType(b), lineno, charno);
        exit(SEM_ERR);
    }
}

void _checkIfFuncReturnTypeIsVoid(tpc_type func_type, tpc_type return_type, int lineno, int charno)
{
    if (func_type.type == _VOID && return_type.type != _VOID)
    {
        fprintf(stderr, "warning: 'return' with a value in function returning void, near line %d, character %d\n", lineno);
    }
}

void _validNameAddVar(SymbolTable *st, const char *name, tpc_kind kind, tpc_type type, int lineno, int charno)
{
    _checkIfNameExists(st, name, lineno, charno);
    addVar(st, name, kind, type);
}

ST_Entry *_validNameAddFunction(SymbolTable *st, const char *name, tpc_type type, int lineno, int charno)
{
    _checkIfNameExists(st, name, lineno, charno);
    return addFunction(st, name, type);
}

ST_Entry *_validNameAddStruct(SymbolTable *st, const char *name, int lineno, int charno)
{
    char buf[MAXNAME];
    sprintf(buf, ".%s", name);
    _checkIfNameExists(st, buf, lineno, charno);
    return addStruct(st, name);
}

void _validNameAddStructVar(SymbolTable *global, SymbolTable *st, const char *name, const char *struct_name, int lineno, int charno)
{
    _checkIfNameExists(st, name, lineno, charno);
    addStructVar(global, st, name, struct_name);
}

void _checkIfNameExists(SymbolTable *st, const char *name, int lineno, int charno)
{
    ST_Entry tmp;
    if (getVar(*st, name, &tmp))
    {
        fprintf(stderr, "error: previous declaration of '%s', near line %d, character %d\n",
                name, lineno, charno);
        exit(SEM_ERR);
    }
}

void _checkForImplicitConversion(tpc_type a, tpc_type b, int lineno, int charno)
{
    if (!isEqual(a, b))
    {
        fprintf(stderr, "warning: implicit conversion from '%s' to '%s', near line %d, character %d\n",
                getStringFromType(a), getStringFromType(b), lineno, charno);
    }
}

void _checkIfNonVoidFuncContainsReturn(Node *node, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    getVar(*global, local->name, &tmp);
    if (tmp.type.type != _VOID)
    {
        if (!_checkIfContainsReturn(SECONDCHILD(node)))
        {
            fprintf(stderr, "warning: control reaches end of non-void function '%s', near line %d, character %d\n",
                local->name, node->lineno, node->charno);
        }
    }
}

int _checkIfContainsReturn(Node *node)
{
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        switch (child->kind)
        {
        case _IF_: break;
        case _IFELSE_:
            return _checkIfContainsReturn(SECONDCHILD(child)) &&
                _checkIfContainsReturn(THIRDCHILD(child));
        case _RETURN_:
            return 1;
        default:
            if (_checkIfContainsReturn(child)) return 1;
        }
    }
    return 0;
}

void _checkIfExpIsScalar(Node *node, SymbolTable *global, SymbolTable *local) {
    tpc_type exp_type = _getTypeOfExp(node, global, local);
    if (!isPrimitive(exp_type))
    {
        fprintf(stderr, "error: used struct type value where scalar is required, near line %d, character %d\n",
                node->lineno, node->charno);
        exit(SEM_ERR);
    }
}