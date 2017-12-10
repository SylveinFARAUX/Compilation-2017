%{
//C includes
#include <stdio.h>
#include <stdlib.h>

#include "symbole.h"
#include "table_symboles_fonctions.h"
#include "liste_quad_fonctions.h"

extern void yyerror(const char * s);
extern int yylex();

extern FILE * yyin;

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
%token DEF_CONSTANT MAIN_FUNCTION MAIN_RETURN INT

%type <Null> prepro
%type <Null> statement
%type <Null> liststatement
%type <Null> defConstant
%type <ptr> expr
//%type COND expr


%left '+' '-'
%left '*' '/'
%right '^'

%start file

%%

file	:	prepro MAIN_FUNCTION '{' liststatement MAIN_RETURN ';' '}'	{printf("file -> prepro MAIN_FUNCTION { }\n");return;}
		;

prepro	:	prepro defConstant		{}
		|	defConstant				{}
		;
		
defConstant:	DEF_CONSTANT ID NUM	
				{
					Symbole s;
					
					int i;
					char intermediare[$2.tailleID];
					for (i = 0 ; i < $2.tailleID ; i++)
						intermediare[i] = $2.chaine[i];
					intermediare[$2.tailleID] = '\0';
					
					s.nom = strdup(intermediare);
					
					//s.isConstant = True;
					s.valeur = $3;
					add(tds, s);
					genquad(lq, CREATEVAR, s.nom, NULL, NULL, NULL);//*/
				}
				|	{/*Il peut ne pas y avoir de definition de constant dans la zone préprocesseur*/}
				;

liststatement:	liststatement statement ';'			{}
		|statement ';'                      {}
        /*| ID ASSIGN expr ';'         { }
        | WHILE '(' COND ')' debut       { }
        | FOR '(' expr ';' COND ';' expr ')' debut       { }
        | IF '(' expr ')' debut %prec IFX        {}
        | IF '(' expr ')' debut ELSE  debut       {}*/
		|	{}
        ;
	
statement :	INT ID					
		{
			Symbole s;
			
			int i;
			char intermediare[$2.tailleID];
			for (i = 0 ; i < $2.tailleID ; i++)
				intermediare[i] = $2.chaine[i];
			intermediare[$2.tailleID] = '\0';
			
			s.nom = strdup(intermediare);
			
			add(tds, s);
			genquad(lq, CREATEVAR, s.nom, NULL, NULL, NULL);
		}
		
		|INT ID '=' expr					
		{
			Symbole s;
			
			int i;
			char intermediare[$2.tailleID];
			for (i = 0 ; i < $2.tailleID ; i++)
				intermediare[i] = $2.chaine[i];
			intermediare[$2.tailleID] = '\0';
			
			s.nom = strdup(intermediare);
			s.valeur = $4->valeur;
			add(tds, s);
			genquad(lq, CREATEVAR, s.nom, NULL, NULL, NULL);
		}
		|expr '=' expr		{
			genquad(lq, ASSIGN, $1->nom, $2->nom, NULL, NULL);
		}
		;
		
expr	:	ID {
			Symbole *trouve = get_symbol(tds, $1.chaine);
			
			if (trouve == NULL){
				printf("erreur : la variable %s n'existe pas dans la table des symboles\n", $1.chaine);
				return;
			}
			$$ = trouve;
		}	
		|	NUM	{
			$$ = new_temp(tds, $1);
			genquad(lq, CREATEVAR, $$->nom, NULL, NULL, NULL);
		}
		| expr '+' expr	{
			$$ = new_temp(tds, 0);
			genquad(lq, CREATEVAR, $$->nom, NULL, NULL, NULL);
			genquad(lq, PLUS, $1->nom, $3->nom, $$->nom, NULL);
		}
		| expr '-' expr	{
			$$ = new_temp(tds, 0);
			genquad(lq, CREATEVAR, $$->nom, NULL, NULL, NULL);
			genquad(lq, MINUS, $1->nom, $3->nom, $$->nom, NULL);
		}
		| expr '/' expr	{
			$$ = new_temp(tds, 0);
			genquad(lq, CREATEVAR, $$->nom, NULL, NULL, NULL);
			genquad(lq, DIV, $1->nom, $3->nom, $$->nom, NULL);
		}
		| expr '*' expr	{
			$$ = new_temp(tds, 0);
			genquad(lq, CREATEVAR, $$->nom, NULL, NULL, NULL);
			genquad(lq, MULT, $1->nom, $3->nom, $$->nom, NULL);
		}
		;
        /*| ID                      { }
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
	
	yyin = fopen(argv[1],"r");
	
    yyparse();
	
	show_table(tds);
	qshow_liste(lq);
	
	genererCodeMIPS(tds, lq);
	
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
