#include "main.h"

int main (void)
{
    tabDs = init_table();
    //CODE = code_new();
    int r = yyparse();
    //symtable_dump(SYMTAB);
    //code_dump(CODE);
    //symtable_free(SYMTAB);

    return r;
}
