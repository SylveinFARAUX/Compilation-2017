#include "symbole.h"
#include "table_symboles_fonctions.h"
#include "liste_quad_fonctions.h"


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
	
	//génère le code mips dans le fichier ex.s, fichier chargeable avec l'interpreteur MARS4_5 (ou QtSpim)
	generercodemips(tds, lq);  
	return 0;
}
