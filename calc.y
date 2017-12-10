%{
//C includes
#include <stdio.h>
#include <stdlib.h>

#include "symbole.h"
#include "table_symboles_fonctions.h"
#include "liste_quad_fonctions.h"

extern void yyerror(const char * s);
extern int yylex();
//extern FILE * yyin;

ListeQuad * lq = NULL;
TableDesSymboles *tds = NULL;
%}

%union {
	int val;
	Symbole* ptr;
	Identificateur identifiant;
	
	char Null;
}

%token <val> NUM 
%token <identifiant> ID 
%token DEF_CONSTANT MAIN_FUNCTION

%type <Null> prepro
%type <Null> defConstant
//%type COND expr


%left '+' '-'
%left '*' '/'
%right '^'

%start file

%%

file	:	prepro MAIN_FUNCTION '{' '}'	{printf("file -> prepro MAIN_FUNCTION { }\n");return;}
		;

prepro	:	prepro defConstant		{printf("prepro -> prepro defConstant\n");}
		|	defConstant				{printf("prepro -> defConstant\n");}
		;
		
defConstant:	DEF_CONSTANT ID NUM	{printf("defConstant -> DEF_CONSTANT ID NUM\n");
			Symbole s;
			
			int i;
			char intermediare[$2.tailleID];
			for (i = 0 ; i < $2.tailleID ; i++)
				intermediare[i] = $2.chaine[i];
			intermediare[$2.tailleID] = '\0';
			
			s.nom = strdup(intermediare);
			
			
			printf("s.nom contient ( %d ) : %s\n", $2.tailleID, s.nom);
			printf("$3 contient : %d\n", $3);
			//s.isConstant = True;
			s.valeur = $3;
			add(tds, s);
			return;
			//genquad(lq, CREATEVAR, s.nom, NULL, NULL, NULL);//*/
		}
		|	{/*Il peut ne pas y avoir de definition de constant dans la zone préprocesseur*/}
		;

/*debut   :	expr ';'                      {}
        | ID ASSIGN expr ';'         { }
        | WHILE '(' COND ')' debut       { }
        | FOR '(' expr ';' COND ';' expr ')' debut       { }
        | IF '(' expr ')' debut %prec IFX        {}
        | IF '(' expr ')' debut ELSE  debut       {}
		|	{}
        ;

expr :	INTEGER                         { }
        | ID                      { }
        | '-' expr %prec UMINUS         {}
        | expr '+' expr                 { }
        | expr '-' expr                 {}
        | expr '*' expr                 { }
        | expr '/' expr                 { }
        | expr '>' expr                 { }
        | expr '<' expr                 { }
        ;

COND	:	expr EQ expr                 {}
        | expr SUPEQ expr                 { }
        | expr INFEQ expr                 { }
        | TRUE                 { }
        | FALSE                 { }
        ;
*/

%%

void yyerror(const char * s)
{
    fprintf(stderr,"%s\n",s);
}

int main (int argc, char *argv[])
{
	//Initialisation de la table des symboles et de la liste des quads
	tds = init_table();
	lq = init_QList();
	
	//yyin = fopen(argv[1],"r");
	
    yyparse();
	
	show_table(tds);
	//qshow_liste(lq);
	
	//fclose(yyin);
	
    return 1;
	
	/*
	%token STENCIL
	%type INT IF ELSE WHILE FOR BREAK CASE RETURN CONTINUE CONST
%type SIZEOF STATIC TYPEDEF VOID MAIN PRINTF PRINTI 
%type ASSIGN INCREM DECRINCREM
%type EQ SUPEQ INFEQ TRUE FALSE

%nonassoc IFX
%nonassoc ELSE
	%nonassoc UMINUS
	*/
}
