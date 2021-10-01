#include "translator.h"

#define ZERO_FLAG "0x0040"
#define SIGN_FLAG "0x0080"

static FILE *output = NULL;

void setOutput(FILE *file)
{
    output = file;
}

/* -------------------------- private prototypes ---------------------------- */

static void _translateProg(Node *node);
static void _translateVarDeclList(Node *node, SymbolTable *st);
static void _translateTypes(Node *node, SymbolTable *st);
static void _translateStructType(Node *node, SymbolTable *st);
static void _translateStructVar(Node *node, SymbolTable *st);
static void _translateType(Node *node, SymbolTable *st);
static void _translateDeclFuncts(Node *node, SymbolTable *global);
static void _translateDeclFunct(Node *node, SymbolTable *global);
static void _createStackBlock(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateParameters(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateBody(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateListInstr(Node *node, SymbolTable *global, SymbolTable *local);

/* Instructions: */
static void _translateInstr(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateAssign(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateLvalueIdentifier(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateLvalueStructVar(const char *name, SymbolTable *global, SymbolTable *local);
static void _translateLvalueStructField(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateIf(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateIfElse(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateWhile(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateReturn(Node *node, SymbolTable *global, SymbolTable *local);
static void _copyFieldToStructVarLocation(const char *name, SymbolTable *global, SymbolTable *local);
static void _translateReade(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateReadc(Node *node, SymbolTable *global, SymbolTable *local);
static void _translatePrint(Node *node, SymbolTable *global, SymbolTable *local);

static void _translateVarAdress(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateStructFieldAdress(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateIdentifierAdress(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateStructVarIdentifier(ST_Entry struct_var, SymbolTable *global, SymbolTable *var_st);

/* Expressions: */
static void _translateExp(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateIdentifier(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateBinaryOp(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateAddition(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateSubstraction(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateMultiplication(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateDivision(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateModulo(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateEqual(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateNotEqual(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateGreaterThan(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateGreaterThanOrEqual(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateLessThan(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateLessThanOrEqual(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateNot(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateMinus(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateAnd(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateOr(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateNum(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateCharacter(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateCallFunct(Node *node, SymbolTable *global, SymbolTable *local);
static void _makeSpaceIfReturnTypeIsStruct(const char *function_name, SymbolTable *global);
static void _translateArguments(Node *node, SymbolTable *global, SymbolTable *local);
static void _translateStructField(Node *node, SymbolTable *global, SymbolTable *local);

/* -------------------------- Utility ---------------------------- */

static const char *_typeToAccessWord(tpc_type t)
{
    switch (getSizeOfType(t))
    {
    case 1:
        return "BYTE";
    case 2:
        return "WORD";
    case 4:
        return "DWORD";
    case 8:
        return "QWORD";
    }
}

static int _isLocalVar(const char *name, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    if (getVar(*local, name, &tmp))
    {
        return 1;
    }
    return 0;
}

static int _isIdentifierStructVar(const char *name, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    if (_isLocalVar(name, global, local))
    {
        getVar(*local, name, &tmp);
    }
    else
    {
        getVar(*global, name, &tmp);
    }
    return !isPrimitive(tmp.type);
}

static char *_generateLabel()
{
    static int id = 2;
    char *buf = malloc(MAXNAME);
    sprintf(buf, ".L%d", id);
    id++;
    return buf;
}

/* -------------------------- AST traduction ---------------------------- */

void generateASM_Instruction(Node *node)
{
    _translateProg(node);
}

void _translateProg(Node *node)
{
    _translateVarDeclList(FIRSTCHILD(node), node->st);
    fprintf(output, "section .text\n");
    fprintf(output, "global main\n");
    fprintf(output, "extern printf\n");
    fprintf(output, "extern scanf\n");
    _translateDeclFuncts(SECONDCHILD(node), node->st);
    clearSymbolTable(node->st);
}

void _translateVarDeclList(Node *node, SymbolTable *st)
{
    fprintf(output, "section .data\n");
    fprintf(output, "\t_.fmt_c_out: db \"%%c\", 0\n");
    fprintf(output, "\t_.fmt_d_out: db \"%%d\", 10, 0\n");
    fprintf(output, "\t_.fmt_c_in: db \"%%c\", 0\n");
    fprintf(output, "\t_.fmt_d_in: db \"%%d\", 0\n");
    fprintf(output, "section .bss\n");
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        switch (child->kind)
        {
        case _TYPE_:
            _translateType(child, st);
            break;
        case _STRUCT_VAR_:
            _translateStructVar(child, st);
            break;
        }
    }
}

void _translateType(Node *node, SymbolTable *st)
{
    ST_Entry tmp;
    tpc_type type;
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        if (!getVar(*st, child->u.identifier, &tmp))
        {
            perror("getVar in _translateType");
            exit(3);
        }
        fprintf(output, "\t%s: resb %d\n", child->u.identifier, getSizeOfType(tmp.type));
    }
}

void _translateStructVar(Node *node, SymbolTable *st)
{
    ST_Entry tmp;
    tpc_type type;
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        if (!getVar(*st, child->u.identifier, &tmp))
        {
            perror("getVar in _translateType");
            exit(3);
        }
        fprintf(output, "\t%s: resb %d\n", child->u.identifier, tmp.offset);
    }
}

void _translateDeclFuncts(Node *node, SymbolTable *global)
{
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        _translateDeclFunct(child, global);
    }
}

void _translateDeclFunct(Node *node, SymbolTable *global)
{
    fprintf(output, "%s:\n", node->st->name);
    _createStackBlock(node, global, node->st);
    fprintf(output, "\tret\n");
    clearSymbolTable(node->st);
}

void _createStackBlock(Node *node, SymbolTable *global, SymbolTable *local)
{
    fprintf(output, "\tpush rbp\n");
    fprintf(output, "\tmov rbp, rsp\n");
    fprintf(output, "\tsub rsp, %d\n", local->total_offset + 8);
    _translateParameters(THIRDCHILD(FIRSTCHILD(node)), global, local);
    _translateBody(SECONDCHILD(node), global, local);
    fprintf(output, "\tmov rsp, rbp\n");
    fprintf(output, "\tpop rbp\n");
}

void _translateParameters(Node *node, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    size_t size_params = getOffsetOfFunction(local->name, global);
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        if (child->kind == _TYPE_)
        {
            getVar(*local, child->firstChild->u.identifier, &tmp);
            fprintf(output, "\tmov rax, QWORD [rbp + %d]\n", 16 - tmp.offset + size_params);
            fprintf(output, "\tmov QWORD [rbp - %d], rax\n", tmp.offset);
        }
        else if (child->kind == _STRUCT_VAR_)
        {
            getStruct(global, child->u.identifier, &tmp);
            ST_Entry dest;
            for (StructField *sf = tmp.u.struct_fields; sf != NULL; sf = sf->next)
            {
                getStructField(local, sf->name, child->firstChild->u.identifier, &dest);
                fprintf(output, "\tmov rax, QWORD [rbp + %d]\n", 16 + size_params - dest.offset);
                fprintf(output, "\tmov QWORD [rbp - %d], rax\n", dest.offset);
            }
        }
    }
}

void _translateBody(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateListInstr(SECONDCHILD(node), global, local);
}

void _translateListInstr(Node *node, SymbolTable *global, SymbolTable *local)
{
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        _translateInstr(child, global, local);
    }
}

void _translateInstr(Node *node, SymbolTable *global, SymbolTable *local)
{
    switch (node->kind)
    {
    case _ASSIGN_:
        _translateAssign(node, global, local);
        break;
    case _IF_:
        _translateIf(node, global, local);
        break;
    case _IFELSE_:
        _translateIfElse(node, global, local);
        break;
    case _WHILE_:
        _translateWhile(node, global, local);
        break;
    case _RETURN_:
        _translateReturn(node, global, local);
        break;
    case _READC_:
        _translateReadc(node, global, local);
        break;
    case _READE_:
        _translateReade(node, global, local);
        break;
    case _PRINT_:
        _translatePrint(node, global, local);
        break;
    default:
        _translateExp(node, global, local);
        break;
    }
}

void _translateAssign(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateExp(SECONDCHILD(node), global, local);
    if (node->firstChild->kind == _IDENTIFIER_)
    {
        _translateLvalueIdentifier(FIRSTCHILD(node), global, local);
    }
    else
    {
        _translateLvalueStructField(FIRSTCHILD(node), global, local);
    }
}

void _translateLvalueIdentifier(Node *node, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    char *lvalue = node->u.identifier;

    if (_isIdentifierStructVar(lvalue, global, local))
    {
        _translateLvalueStructVar(lvalue, global, local);
        return;
    }

    if (_isLocalVar(lvalue, global, local))
    {
        getVar(*local, lvalue, &tmp);
        fprintf(output, "\tpop rax\n");
        fprintf(output, "\tmov QWORD [rbp - %d], rax\n", tmp.offset);
    }
    else
    {
        fprintf(output, "\tpop rax\n");
        fprintf(output, "\tmov QWORD [%s], rax\n", lvalue);
    }
}

void _translateLvalueStructVar(const char *name, SymbolTable *global, SymbolTable *local)
{
    ST_Entry struct_var, struct_type;
    int is_local;

    if (is_local = _isLocalVar(name, global, local))
    {
        getVar(*local, name, &struct_var);
    }
    else
    {
        getVar(*global, name, &struct_var);
    }

    char *struct_type_name = struct_var.type.struct_ident;
    ST_Entry struct_field;
    int total_offset = is_local ? local->total_offset : global->total_offset;
    getStruct(global, struct_type_name, &struct_type);

    StructField *reverse_sf = NULL;
    for (StructField *sf = struct_type.u.struct_fields; sf != NULL; sf = sf->next)
    {
        StructField *sf_next = malloc(sizeof(StructField));
        strcpy(sf_next->name, sf->name);
        sf_next->next = reverse_sf;
        reverse_sf = sf_next;
    }

    StructField *prev;
    for (StructField *sf = reverse_sf; sf != NULL;)
    {
        if(is_local) {
            getStructField(local, sf->name, name, &struct_field);
            fprintf(output, "\tpop rax\n");
            fprintf(output, "\tmov QWORD [rbp - %d], rax\n", struct_field.offset);
        } else {
            getStructField(global, sf->name, name, &struct_field);
            fprintf(output, "\tpop rax\n");
            fprintf(output, "\tmov QWORD [%s + %d], rax\n", name, struct_field.offset - 8);
        }
        prev = sf;
        sf = sf->next;
        free(prev);
    }
}

void _translateLvalueStructField(Node *node, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    char lvalue[MAXNAME];
    char *struct_name = FIRSTCHILD(node)->u.identifier;
    char *field_name = SECONDCHILD(node)->u.identifier;
    sprintf(lvalue, "%s.%s", struct_name, field_name);
    if (_isLocalVar(lvalue, global, local))
    {
        getVar(*local, lvalue, &tmp);
        fprintf(output, "\tpop rax\n");
        fprintf(output, "\tmov QWORD [rbp - %d], rax\n", tmp.offset);
    }
    else
    {
        if (!getVar(*global, struct_name, &tmp))
        {
            perror("getVar in _translateAssign");
            exit(EXIT_FAILURE);
        }
        fprintf(output, "\tpop rax\n");
        fprintf(output, "\tmov QWORD [%s + %d], rax\n", struct_name,
                getOffsetFromFieldInStruct(global, tmp.type.struct_ident, field_name));
    }
}

void _translateIf(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *label = _generateLabel();
    _translateExp(FIRSTCHILD(node), global, local);
    fprintf(output, "\tpop rax\n");
    fprintf(output, "\tcmp rax, 0\n");
    fprintf(output, "\tje %s\n", label);
    _translateListInstr(SECONDCHILD(node), global, local);
    fprintf(output, "%s:\n", label);
    free(label);
}

void _translateIfElse(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *else_label = _generateLabel();
    char *end_label = _generateLabel();
    _translateExp(FIRSTCHILD(node), global, local);
    fprintf(output, "\tpop rax\n");
    fprintf(output, "\tcmp rax, 0\n");
    fprintf(output, "\tje %s\n", else_label);
    _translateListInstr(SECONDCHILD(node), global, local);
    fprintf(output, "\tjmp %s\n", end_label);
    fprintf(output, "%s:\n", else_label);
    _translateListInstr(THIRDCHILD(node), global, local);
    fprintf(output, "%s:\n", end_label);
    free(else_label);
    free(end_label);
}

void _translateWhile(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *while_label = _generateLabel();
    char *end_label = _generateLabel();
    fprintf(output, "%s:\n", while_label);
    _translateExp(FIRSTCHILD(node), global, local);
    fprintf(output, "\tpop rax\n");
    fprintf(output, "\tcmp rax, 0\n");
    fprintf(output, "\tje %s\n", end_label);
    _translateListInstr(SECONDCHILD(node), global, local);
    fprintf(output, "\tjmp %s\n", while_label);
    fprintf(output, "%s:\n", end_label);
    free(while_label);
    free(end_label);
}

void _translateReturn(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateExp(FIRSTCHILD(node), global, local);
    if (node->firstChild->kind == _IDENTIFIER_)
    {
        char *struct_name = node->firstChild->u.identifier;
        if (_isIdentifierStructVar(struct_name, global, local))
        {
            _copyFieldToStructVarLocation(struct_name, global, local);
        }
    }
    fprintf(output, "\tpop rax\n");
    fprintf(output, "\tmov rsp, rbp\n");
    fprintf(output, "\tpop rbp\n");
    fprintf(output, "\tret\n");
    
}

void _copyFieldToStructVarLocation(const char *name, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    char *struct_type_name;
    if (_isLocalVar(name, global, local))
    {
        getVar(*local, name, &tmp);
    }
    else
    {
        getVar(*global, name, &tmp);
    }

    struct_type_name = tmp.type.struct_ident;
    getStruct(global, struct_type_name, &tmp);
    size_t offset_to_struct_location =
        8 + getOffsetOfFunction(local->name, global);

    size_t totat_offset_from_struct_field = 0;
    for (StructField *sf = tmp.u.struct_fields; sf != NULL; sf = sf->next)
    {
        totat_offset_from_struct_field += getSizeOfType(sf->type);
        fprintf(output, "\tpop rax\n");
        fprintf(output, "\tmov QWORD [rbp + %d], rax\n", offset_to_struct_location + totat_offset_from_struct_field);
    }
}

void _translateVarAdress(Node *node, SymbolTable *global, SymbolTable *local)
{
    if (node->kind == _IDENTIFIER_)
    {
        _translateIdentifierAdress(node, global, local);
    }
    else if (node->kind == _STRUCT_FIELD_)
    {
        _translateStructFieldAdress(node, global, local);
    }
}

void _translateIdentifierAdress(Node *node, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    if (_isLocalVar(node->u.identifier, global, local))
    {
        getVar(*local, node->u.identifier, &tmp);
        fprintf(output, "\tlea rax, [rbp - %d]\n", tmp.offset);
        fprintf(output, "\tpush rax\n");
    }
    else
    {
        fprintf(output, "\tlea rax, [%s]\n", node->u.identifier);
        fprintf(output, "\tpush rax\n");
    }
}

void _translateStructFieldAdress(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *struct_name = FIRSTCHILD(node)->u.identifier;
    char *field_name = SECONDCHILD(node)->u.identifier;
    char field_full_name[MAXNAME];
    sprintf(field_full_name, "%s.%s", struct_name, field_name);
    ST_Entry tmp;
    if (_isLocalVar(struct_name, global, local))
    {
        getStructField(local, field_name, struct_name, &tmp);
        fprintf(output, "\tlea rax, [rbp - %d]\n", tmp.offset);
        fprintf(output, "\tpush rax\n");
    }
    else
    {
        if (!getVar(*global, struct_name, &tmp))
        {
            perror("getVar in _translateStructFieldAdress");
            exit(EXIT_FAILURE);
        }
        fprintf(output, "\tlea rax, [rbp + %d]\n", 
            getOffsetFromFieldInStruct(global, tmp.type.struct_ident, field_name));
        fprintf(output, "\tpush rax\n");
    }
}

void _translateReade(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateVarAdress(FIRSTCHILD(node), global, local);
    fprintf(output, "\tpop rax\n");
    fprintf(output, "\tmov rsi, rax\n");
    fprintf(output, "\tmov rdi, _.fmt_d_in\n");
    fprintf(output, "\tcall scanf\n");
}

void _translateReadc(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateVarAdress(FIRSTCHILD(node), global, local);
    fprintf(output, "\tpop rax\n");
    fprintf(output, "\tmov rsi, rax\n");
    fprintf(output, "\tmov rdi, _.fmt_c_in\n");
    fprintf(output, "\tcall scanf\n");
}

void _translatePrint(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateExp(FIRSTCHILD(node), global, local);
    tpc_type t = getTypeFromString(node->u.identifier);
    fprintf(output, "\tpop rsi\n");
    if (t.type == _CHAR)
    {
        fprintf(output, "\tmov rdi, _.fmt_c_out\n");
    }
    else
    {
        fprintf(output, "\tmov rdi, _.fmt_d_out\n");
    }
    fprintf(output, "\tmov rax, 0\n");
    fprintf(output, "\tcall printf\n");
}

void _translateExp(Node *node, SymbolTable *global, SymbolTable *local)
{
    if (node == NULL)
        return;
    switch (node->kind)
    {
    case _STRUCT_FIELD_:
        _translateStructField(node, global, local);
        break;
    case _IDENTIFIER_:
        _translateIdentifier(node, global, local);
        break;
    case _ADD_:
        _translateAddition(node, global, local);
        break;
    case _SUB_:
        _translateSubstraction(node, global, local);
        break;
    case _MULT_:
        _translateMultiplication(node, global, local);
        break;
    case _DIV_:
        _translateDivision(node, global, local);
        break;
    case _MOD_:
        _translateModulo(node, global, local);
        break;
    case _EQ_:
        _translateEqual(node, global, local);
        break;
    case _NEQ_:
        _translateNotEqual(node, global, local);
        break;
    case _GT_:
        _translateGreaterThan(node, global, local);
        break;
    case _GTEQ_:
        _translateGreaterThanOrEqual(node, global, local);
        break;
    case _LT_:
        _translateLessThan(node, global, local);
        break;
    case _LTEQ_:
        _translateLessThanOrEqual(node, global, local);
        break;
    case _NOT_:
        _translateNot(node, global, local);
        break;
    case _MINUS_:
        _translateMinus(node, global, local);
        break;
    case _AND_:
        _translateAnd(node, global, local);
        break;
    case _OR_:
        _translateOr(node, global, local);
        break;
    case _NUM_:
        _translateNum(node, global, local);
        break;
    case _CHARACTER_:
        _translateCharacter(node, global, local);
        break;
    case _CALL_FUNCT_:
        _translateCallFunct(node, global, local);
        break;
    }
}

void _translateIdentifier(Node *node, SymbolTable *global, SymbolTable *local)
{
    ST_Entry tmp;
    char buf[MAXNAME];
    if (_isLocalVar(node->u.identifier, global, local))
    {
        getVar(*local, node->u.identifier, &tmp);
        if (isPrimitive(tmp.type))
        {
            fprintf(output, "\tpush QWORD [rbp - %d]\n", tmp.offset);
        }
        else
        {
            _translateStructVarIdentifier(tmp, global, local);
        }
    }
    else
    {
        getVar(*global, node->u.identifier, &tmp);
        if (isPrimitive(tmp.type))
        {
            fprintf(output, "\tpush QWORD [%s]\n", node->u.identifier);
        }
        else
        {
            _translateStructVarIdentifier(tmp, global, NULL);
        }
    }
}

/* Push all the struct fields onto the stack. */
void _translateStructVarIdentifier(ST_Entry struct_var, SymbolTable *global, SymbolTable *var_st)
{
    ST_Entry struct_type, struct_field;
    SymbolTable *target_st = var_st == NULL ? global : var_st;
    char *struct_ident = struct_var.type.struct_ident;
    char buf[MAXNAME];
    size_t offset = 0;

    sprintf(buf, ".%s", struct_ident);
    getVar(*global, buf, &struct_type);
    for (StructField *sf = struct_type.u.struct_fields; sf != NULL; sf = sf->next)
    {
        sprintf(buf, "%s.%s", struct_var.name, sf->name);
        getVar(*target_st, buf, &struct_field);
        if (var_st == NULL)
        {
            fprintf(output, "\tpush QWORD [%s + %d]\n",
                    struct_var.name, offset);
        }
        else
        {
            fprintf(output, "\tpush QWORD [rbp - %d]\n", struct_field.offset);
        }
        offset += getSizeOfType(sf->type);
    }
}

void _translateBinaryOp(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateExp(FIRSTCHILD(node), global, local);
    _translateExp(SECONDCHILD(node), global, local);
    fprintf(output, "\tpop rbx\n");
    fprintf(output, "\tpop rax\n");
}

void _translateAddition(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tadd rax, rbx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateSubstraction(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tsub rax, rbx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateMultiplication(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateBinaryOp(node, global, local);
    fprintf(output, "\timul rbx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateDivision(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateBinaryOp(node, global, local);
    fprintf(output, "\txor rdx, rdx\n");
    fprintf(output, "\tidiv rbx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateModulo(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateBinaryOp(node, global, local);
    fprintf(output, "\txor rdx, rdx\n");
    fprintf(output, "\tidiv rbx\n");
    fprintf(output, "\tmov rax, rdx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateEqual(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *else_label = _generateLabel();
    char *end_label = _generateLabel();
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tcmp rax, rbx\n");
    fprintf(output, "\tjne %s\n", else_label);
    fprintf(output, "\tpush 1\n");
    fprintf(output, "\tjmp %s\n", end_label);
    fprintf(output, "%s:\n", else_label);
    fprintf(output, "\tpush 0\n");
    fprintf(output, "%s:\n", end_label);
    free(end_label);
    free(else_label);
}

void _translateNotEqual(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateBinaryOp(node, global, local);
    fprintf(output, "\txor rax, rbx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateGreaterThan(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *else_label = _generateLabel();
    char *end_label = _generateLabel();
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tcmp rax, rbx\n");
    fprintf(output, "\tjle %s\n", else_label);
    fprintf(output, "\tpush 1\n");
    fprintf(output, "\tjmp %s\n", end_label);
    fprintf(output, "%s:\n", else_label);
    fprintf(output, "\tpush 0\n");
    fprintf(output, "%s:\n", end_label);
    free(end_label);
    free(else_label);
}

void _translateGreaterThanOrEqual(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *else_label = _generateLabel();
    char *end_label = _generateLabel();
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tcmp rax, rbx\n");
    fprintf(output, "\tjl %s\n", else_label);
    fprintf(output, "\tpush 1\n");
    fprintf(output, "\tjmp %s\n", end_label);
    fprintf(output, "%s:\n", else_label);
    fprintf(output, "\tpush 0\n");
    fprintf(output, "%s:\n", end_label);
    free(end_label);
    free(else_label);
}

void _translateLessThan(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *else_label = _generateLabel();
    char *end_label = _generateLabel();
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tcmp rax, rbx\n");
    fprintf(output, "\tjge %s\n", else_label);
    fprintf(output, "\tpush 1\n");
    fprintf(output, "\tjmp %s\n", end_label);
    fprintf(output, "%s:\n", else_label);
    fprintf(output, "\tpush 0\n");
    fprintf(output, "%s:\n", end_label);
    free(end_label);
    free(else_label);
}

void _translateLessThanOrEqual(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *else_label = _generateLabel();
    char *end_label = _generateLabel();
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tcmp rax, rbx\n");
    fprintf(output, "\tjg %s\n", else_label);
    fprintf(output, "\tpush 1\n");
    fprintf(output, "\tjmp %s\n", end_label);
    fprintf(output, "%s:\n", else_label);
    fprintf(output, "\tpush 0\n");
    fprintf(output, "%s:\n", end_label);
    free(end_label);
    free(else_label);
}

void _translateNot(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateExp(FIRSTCHILD(node), global, local);
    fprintf(output, "\tpop rax\n");
    fprintf(output, "\tnot rax\n");
    fprintf(output, "\tand rax, 1\n");
    fprintf(output, "\tpush rax\n");
}

void _translateMinus(Node *node, SymbolTable *global, SymbolTable *local) {
    _translateExp(FIRSTCHILD(node), global, local);
    fprintf(output, "\tpop rbx\n");
    fprintf(output, "\tmov rax, rbx\n");
    fprintf(output, "\tsub rax, rbx\n");
    fprintf(output, "\tsub rax, rbx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateAnd(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tand rax, rbx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateOr(Node *node, SymbolTable *global, SymbolTable *local)
{
    _translateBinaryOp(node, global, local);
    fprintf(output, "\tor rax, rbx\n");
    fprintf(output, "\tpush rax\n");
}

void _translateCharacter(Node *node, SymbolTable *global, SymbolTable *local)
{
    fprintf(output, "\tpush %d\n", node->u.character);
}

void _translateNum(Node *node, SymbolTable *global, SymbolTable *local)
{
    fprintf(output, "\tpush %d\n", node->u.integer);
}

void _translateCallFunct(Node *node, SymbolTable *global, SymbolTable *local)
{
    _makeSpaceIfReturnTypeIsStruct(node->firstChild->u.identifier, global);
    _translateArguments(SECONDCHILD(node), global, local);
    fprintf(output, "\tcall %s\n", FIRSTCHILD(node)->u.identifier);
    size_t size_params = getOffsetOfFunction(FIRSTCHILD(node)->u.identifier, global);
    fprintf(output, "\tadd rsp, %d\n", size_params);

    ST_Entry tmp;
    getVar(*global, node->firstChild->u.identifier, &tmp);
    if(isPrimitive(tmp.type)) {
        fprintf(output, "\tpush rax\n");
    }
}

void _makeSpaceIfReturnTypeIsStruct(const char *function_name, SymbolTable *global) {
    ST_Entry tmp;
    getVar(*global, function_name, &tmp);
    if(!(isPrimitive(tmp.type))) {
        ST_Entry struct_type;
        getStruct(global, tmp.type.struct_ident, &struct_type);
        fprintf(output, "\tsub rsp, %d\n", struct_type.offset);
    }
}

void _translateArguments(Node *node, SymbolTable *global, SymbolTable *local)
{
    for (Node *child = node->firstChild; child != NULL; child = child->nextSibling)
    {
        _translateExp(child, global, local);
    }
}

void _translateStructField(Node *node, SymbolTable *global, SymbolTable *local)
{
    char *struct_name = FIRSTCHILD(node)->u.identifier;
    char *field_name = SECONDCHILD(node)->u.identifier;
    char field_full_name[MAXNAME];
    sprintf(field_full_name, "%s.%s", struct_name, field_name);
    ST_Entry tmp;
    if (_isLocalVar(struct_name, global, local))
    {
        getVar(*local, field_full_name, &tmp);
        fprintf(output, "\tpush QWORD [rbp - %d]\n", tmp.offset);
    }
    else
    {
        getVar(*global, struct_name, &tmp);
        fprintf(output, "\tpush QWORD [%s + %d]\n",
                struct_name, getOffsetFromFieldInStruct(global, tmp.type.struct_ident, field_name));
    }
}