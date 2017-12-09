%{
//C includes
#include <stdio.h>
#include <stdlib.h>

#include "symbole.h"
#include "table_symboles_fonctions.h"
//#include "quad.h"
#include "liste_quad_fonctions.h"

int yylex(); // sert si on ne fournit pas nous-meme la fonction yylex
int yyerror (char *s) {
   printf ("error %s\n", s);
   return 0;
 }
int yyparse(void);
int yywrap(){return -1;}
ListeQuad * lq;
TableDesSymboles * TdS;
%}
%union {
	int val;
	Symbole* ptr;
}
%token <val> ENTIER
%token END
%type <ptr> E
%start axiom
%left '='
%left '+' '-'
%left '*' '/'
%left UMOINS

%%
axiom	:	E END	  {return;}
	|	END	  {return;};
E	:	E '+' E	  {
		$$ = new_temp(TdS, $1->valeur + $3->valeur);
		genquad(lq, PLUS, $1->nom, $3->nom, $$->nom, NULL);
	}
	|	E '-' E	  {
		$$ = new_temp(TdS, $1->valeur - $3->valeur);
		genquad(lq, MINUS, $1->nom, $3->nom, $$->nom, NULL);
	}
	|	E '*' E	  {
		$$ = new_temp(TdS, $1->valeur * $3->valeur);
		genquad(lq, MULT, $1->nom, $3->nom, $$->nom, NULL);
	}
	|	'(' E ')' {
		$$ = $2;
	}
	|	ENTIER	  {
		$$ = new_temp(TdS, $1);
		genquad(lq, CREATEVAR, $$->nom, NULL, NULL, NULL);
	}
	|	'-' E	  {} %prec UMOINS
;
%%

int main(void){
	TdS = init_table();
	lq = init_QList();
	Symbole *ptr;
	yyparse();
	
	show_liste(lq);
}
