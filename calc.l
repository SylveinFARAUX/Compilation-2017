%{
  #include <stdio.h>
  #include "calc.tab.h"
%}

%%


[[:alpha:]][[:alnum:]]* {
    if ( yyleng > 7 )
        fprintf(stderr,"Identifier '%s' too long, truncated\n",yytext);
    strncpy(yylval.strval,yytext,7);
    yylval.strval[7] = '\0';
    return ID;
}
0|[1-9][0-9]*|0[0-7]+|0x[0-9a-fA-F]+ {
    sscanf(yytext,"%li",&(yylval.intval));
    return NUM;
}

stencil						  {return STENCIL;}
int     		              { return INT;}
if      		              { return IF;}
else     		              { return ELSE;}
while     		            { return WHILE;}
for     		              { return FOR;}
break                     { return BREAK;}
goto                      { return GOTO;}
return                    { return RETURN;}
continue                  { return CONTINUE;}
const                     { return CONST;}
sizeof                    { return SIZEOF;}
static                    { return STATIC;}
typedef                   { return TYPEDEF;}
void                      { return VOID;}
main                      { return MAIN;}
printf                    { return PRINTF;}
printi                    { return PRINTI;}
[or]                      { return OR;}
[&&]                      { return AND;}

[;=+-*/^<>()]			  { return yytext[0];}

"++"                      { return INCREM;}
"--"                      { return DECRINCREM;}
"=="                      { return(EQ);}
"<="                      { return(SUPEQ);}
">="                      { return(INFEQ);}

true                      { return TRUE;}
false                     { return FALSE; }

'\n'                      { yyterminate();}


%%

int yywrap (void)
{
  return 1;
}
