%{
	#include <stdio.h>
	#include <stdlib.h>
	
	
	#include "symbole.h"
	#include "y.tab.h"
	
	
%}

LETTRE	[a-zA-Z]
CHIFFRE [0-9]
%%

{CHIFFRE}+					{
							//sscanf(yytext,"%li",&(yylval.intval));
							yylval.val = atoi(yytext);
							return NUM;
						}

"#define"						  {/*printf("%s reconnu\n", yytext);*/return DEF_CONSTANT;}
stencil						  {/*printf("%s reconnu\n", yytext);return STENCIL;*/}
"int main()"				  {return MAIN_FUNCTION;}
"return 0"					  {return MAIN_RETURN;}
int     		              {return INT;}
"printi"	                  {return PRINTI;}

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
printf                    {return PRINTF;}                               
[or]                      {printf("%s reconnu\n", yytext);/*return OR;*/}
[&&]                      {printf("%s reconnu\n", yytext);/*return AND;*/}

";"|"="|"+"|"-"|"*"|"/"|"^"|"<"|">"|"("|")"|"{"|"}"|"\""		  {return yytext[0];}

"++"                      {return INCREMENT;}
"--"                      {return DECREMENT;}
"=="                      {printf("%s reconnu\n", yytext);/*return(EQ);*/}
"<="                      {printf("%s reconnu\n", yytext);/*return(SUPEQ);*/}
">="                      {printf("%s reconnu\n", yytext);/*return(INFEQ);*/}

true                      {printf("%s reconnu\n", yytext);/*return TRUE;*/}
false                     {printf("%s reconnu\n", yytext);/*return FALSE;*/}

" "|"\n"|"\t"			  {}
<<EOF>>					  {printf("EOF\n"); yyterminate();}

\"(\\.|[^"\\])*\"								{
								yylval.identifiant.chaine = yytext;
								yylval.identifiant.tailleID = yyleng;
								return ASCII;
							}
							
[a-zA-Z](([a-zA-Z])|([0-9]))*	{
							yylval.identifiant.chaine = yytext;
							yylval.identifiant.tailleID = yyleng;

							return ID;
						}
%%

int yywrap (void)
{
  return 1;
}
