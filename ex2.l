%{
#include <stdio.h>
#include <stdlib.h>

#include "symbole.h"
#include "y.tab.h"
%}

%%
"\n"	{return END;}
[0-9]+	{yylval.val = atoi(yytext); return ENTIER;}
[()+*/=\-]	{ return yytext[0];}
.	{printf("car inconnu : %s\n", yytext);}
%%
