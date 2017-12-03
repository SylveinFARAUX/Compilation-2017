#include "symbole.h"
#include "table_symboles_fonctions.h"
#include "liste_quad_fonctions.h"

void affichercodemips(TableDesSymboles *tds)
{
	/*zone code du code mips*/
	Symbole *s = &tds->premier->sb;
	printf("\n\n");
	printf(".text\nmain:\n");
	while (s != NULL)
	{
		printf("li $v0,3\nl.s $f12,%s\nsyscall\n", s->nom);
		s = next_symbol(tds, s);
	}

	//affichage de program terminated
	printf("li $v0,4\nla $a0,str1\nsyscall\n");
	printf("li $v0,4\nla $a0,strt\nsyscall\n"); 
	printf("li $v0,4\nla $a0,str1\nsyscall\n");

	printf("# exit\nli $v0,10        # on sort du programme proprement\nsyscall\n");
	/*li $v0, 3         # appel système pour afficher un réel
  	l.s $f12,temp0   # chargement du réel à afficher
  	syscall          # affichage*/
		
	
	/*zone data du code mips*/
	s = &tds->premier->sb;
	printf(".data\n");
	while (s != NULL)
	{
		printf("%s: .double %f\n", s->nom, s->valeur);
		s = next_symbol(tds, s);
	}
	printf("str1:  .asciiz \"\\n\"\nstr2:  .asciiz \" \"\nstrt:  .asciiz \"program terminated\"\n");
}

int main(){
	
	char * buffer;
	
	//Initialiser la table
	TableDesSymboles *tds = init_table();
	
	//Création des symboles a, b et c
	Symbole a, b, c;
	a.nom = "a";
	a.isConstant = True;
	a.valeur = 142;
	
	b.nom = "bBack";
	b.isConstant = False;
	b.valeur= 20;

	c.nom = "c";
	c.isConstant = False;
	c.valeur = 4.79;

	//Ajout d'un symbole (ici a)
	add(tds, a);
	
	//Ajout d'un temporaire qui a pour valeur 42
	new_temp(tds, 42.6, &buffer);
	
	//Ajout d'un symbole (ici b)
	add(tds,b);
	
	//Afficher le contenue de la table
	show_table(tds);
	
	//recherche d'un symbole dans la table des symboles
	Symbole *trouve = get_symbol(tds, "bBack");
	
	ListeQuad *lq = init_QList();

	/*qpush_back(lq, PLUS, "symbl:hehe", "symbl:hi", "symbl:boubou", NULL);
	qpush_back(lq, GOTO, "label:momo", NULL, NULL, NULL);
	qpush_back(lq, EQUAL, "symbl:s1", "symbl:s2", NULL, NULL);
	//qshow_table(lq);//*/
	
	new_temp(tds, 1, &buffer);
	genquad(lq, CREATEVAR, buffer, NULL, NULL, NULL);
	return 0;
}
