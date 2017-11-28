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
	new_temp(tds, 42.6);
	
	//Ajout d'un symbole (ici b)
	add(tds,b);
	
	//Afficher le contenue de la table
	show_table(tds);
	
	//recherche d'un symbole dans la table des symboles
	Symbole *trouve = get_symbol(tds, "bBack");
	
	ListeQuad *lq = init_QList();
//void qpush_front(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label)
	qpush_front(lq, ADD, "hehe", NULL, NULL, NULL);
	return 0;
}
