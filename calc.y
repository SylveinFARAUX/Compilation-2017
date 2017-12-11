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
%token <identifiant> ASCII
%token DEF_CONSTANT MAIN_FUNCTION MAIN_RETURN INT PRINTI DECREMENT INCREMENT PRINTF

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

file	:	prepro MAIN_FUNCTION '{' liststatement MAIN_RETURN ';' '}'	{printf("compilation terminated successfully\n");return;}
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
					
					s.valeur = $3;
					add(tds, s);
					genquad(lq, CREATEVAR, s.nom, NULL, NULL, NULL);//*/
				}
				|	{/*Il peut ne pas y avoir de definition de constant dans la zone préprocesseur*/}
				;

liststatement: statement ';' liststatement			{}
		|statement ';'                      {}
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
			genquad(lq, ASSIGN, s.nom, $4->nom, NULL, NULL);
		}
		|expr '=' expr		{
			genquad(lq, ASSIGN, $1->nom, $3->nom, NULL, NULL);
		}
		|PRINTI '(' expr ')'	{
			genquad(lq, SHOW, $3->nom, NULL, NULL, NULL);
		}
		|PRINTF '(' ASCII ')' {
			int i;
			char intermediaire[$3.tailleID-2];
			for (i = 1 ; i < $3.tailleID-1 ; i++)
				intermediaire[i-1] = $3.chaine[i];
			intermediaire[$3.tailleID-2] = '\0';
			char *p = strdup(intermediaire);
			
			Symbole * temp = new_stringTemp(tds, p);
			
			genquad(lq, CREATESTRING, temp->nom, NULL, NULL, NULL);
			genquad(lq, SHOWSTRING, temp->nom, NULL, NULL, NULL);
		}
		;
		
expr	:	ID {
	
			int i;
			char intermediaire[$1.tailleID];
			for (i = 0 ; i < $1.tailleID ; i++)
				intermediaire[i] = $1.chaine[i];
			intermediaire[$1.tailleID] = '\0';
			
			Symbole *trouve = get_symbol(tds, intermediaire);
			
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
		| ID INCREMENT	{
			$$ = new_temp(tds, 0);
			Symbole* temp = new_temp(tds, 1);
			
			int i;
			char intermediaire[$1.tailleID];

			for (i = 0 ; i < $1.tailleID ; i++)
				intermediaire[i] = $1.chaine[i];
			intermediaire[$1.tailleID] = '\0';
			
			char *p = strdup(intermediaire);
			
			genquad(lq, CREATEVAR, $$->nom, NULL, NULL, NULL);
			genquad(lq, CREATEVAR, temp->nom, NULL, NULL, NULL);
			genquad(lq, PLUS, p, temp->nom, $$->nom, NULL);
		}
		| ID DECREMENT	{
			$$ = new_temp(tds, 0);
			Symbole* temp = new_temp(tds, 1);
			
			int i;
			char intermediaire[$1.tailleID];

			for (i = 0 ; i < $1.tailleID ; i++)
				intermediaire[i] = $1.chaine[i];
			intermediaire[$1.tailleID] = '\0';
			
			char *p = strdup(intermediaire);
			
			genquad(lq, CREATEVAR, $$->nom, NULL, NULL, NULL);
			genquad(lq, CREATEVAR, temp->nom, NULL, NULL, NULL);
			genquad(lq, MINUS, p, temp->nom, $$->nom, NULL);
		}
		;
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
