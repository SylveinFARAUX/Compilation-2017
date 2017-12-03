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
	Symbole a, b;
	a.nom = "a";
	a.isConstant = True;
	a.valeur = 142;
	
	b.nom = "bBack";
	b.isConstant = False;
	b.valeur= 20;

	//Ajout d'un symbole (ici a)
	add(tds, a);
	
	//Ajout d'un temporaire qui a pour valeur 42
	Symbole * temp = new_temp(tds, 42);
	
	//Ajout d'un symbole (ici b)
	add(tds,b);
	
	//Afficher le contenue de la table
	show_table(tds);
	
	//recherche d'un symbole dans la table des symboles
	Symbole *trouve = get_symbol(tds, "bBack");
	
	ListeQuad *lq = init_QList();

	//Génération des quads correspondant
	genquad(lq, CREATEVAR, a.nom, NULL, NULL, NULL);
	genquad(lq, CREATEVAR, temp->nom, NULL, NULL, NULL);
	genquad(lq, CREATEVAR, b.nom, NULL, NULL, NULL);
	
	//Génération d'un quad de calcul (exemple addition) :
	//création du temporaire dans lequel sera stoqué le résultat
	Symbole * ptr = new_temp(tds,0);
	genquad(lq, CREATEVAR, ptr->nom, NULL, NULL, NULL);
	//Quad de calcul
	genquad(lq, PLUS, a.nom, temp->nom, ptr->nom, NULL);
	
	qshow_liste(lq);
	
	
	return 0;
}
