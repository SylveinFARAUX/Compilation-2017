%{
  #include <stdio.h>
//#include "calc.tab.h"
%}

%%

0|[1-9][0-9]*|0[0-7]+|0x[0-9a-fA-F]+ {
    /*sscanf(yytext,"%li",&(yylval.intval));
    /*return NUM;*/
}

"#define"						  {printf("%s reconnu\n", yytext);/*return DEF_CONSTANT;*/}
stencil						  {printf("%s reconnu\n", yytext);/*return STENCIL;*/}
"int main()"				  {printf("%s reconnu\n", yytext);/*return MAIN_FUNCTION;*/}

int     		              {printf("%s reconnu\n", yytext);/*return INT;*/}
if      		              {printf("%s reconnu\n", yytext);/*return IF;*/}
else     		              {printf("%s reconnu\n", yytext);/*return ELSE;*/}
while     		            {printf("%s reconnu\n", yytext);/*return WHILE;*/}
for     		              {printf("%s reconnu\n", yytext);/*return FOR;*/}
break                     {printf("%s reconnu\n", yytext);/*return BREAK;*/}
goto                      {printf("%s reconnu\n", yytext);/*return GOTO;*/}
return                    {printf("%s reconnu\n", yytext);/*return RETURN;*/}
continue                  {printf("%s reconnu\n", yytext);/*return CONTINUE;*/}
const                     {printf("%s reconnu\n", yytext);/*return CONST;*/}
sizeof                    {printf("%s reconnu\n", yytext);/*return SIZEOF;*/}
static                    {printf("%s reconnu\n", yytext);/*return STATIC;*/}
typedef                   {printf("%s reconnu\n", yytext);/*return TYPEDEF;*/}
void                      {printf("%s reconnu\n", yytext);/*return VOID;*/}
main                      {printf("%s reconnu\n", yytext);/*return MAIN;*/}
printf                    {printf("%s reconnu\n", yytext);/*return PRINTF;*/}
printi                    {printf("%s reconnu\n", yytext);/*return PRINTI;*/}
[or]                      {printf("%s reconnu\n", yytext);/*return OR;*/}
[&&]                      {printf("%s reconnu\n", yytext);/*return AND;*/}

";"|"="|"+"|"-"|"*"|"/"|"^"|"<"|">"|"("|")"			  {printf("%s reconnu\n", yytext);/*return yytext[0];*/}

"++"                      {printf("%s reconnu\n", yytext);/*return INCREM;*/}
"--"                      {printf("%s reconnu\n", yytext);/*return DECRINCREM;*/}
"=="                      {printf("%s reconnu\n", yytext);/*return(EQ);*/}
"<="                      {printf("%s reconnu\n", yytext);/*return(SUPEQ);*/}
">="                      {printf("%s reconnu\n", yytext);/*return(INFEQ);*/}

true                      {printf("%s reconnu\n", yytext);/*return TRUE;*/}
false                     {printf("%s reconnu\n", yytext);/*return FALSE;*/}

'\n'                      {/*yyterminate();*/}



[[:alpha:]][[:alnum:]]* {
    /*if ( yyleng > 7 )
        fprintf(stderr,"Identifier '%s' too long, truncated\n",yytext);
    strncpy(yylval.strval,yytext,7);
    yylval.strval[7] = '\0';
    /*return ID;*/
}
" "						  {}
.+						  {printf("Erreur de syntaxe : %s\n", yytext); exit(0);}
%%

int yywrap (void)
{
  return 1;
}
main(int argc, char *argv[]){
	yylex();
	return 0;
}
