#include <stdio.h>
#include "symbole.h"
//#include "table_symboles_fonctions.h"
//#include "liste_quad_fonctions.h"

int main(){
	
	char * buffer;
	
	//Initialiser la table
	//TableDesSymboles *tds = init_table();
	
	//Création des symboles a, b et c
	Symbole a, b;
	a.nom = "a";
	a.isConstant = True;
	a.valeur = 142;
	printf("auyyhudd a symbole with %d\n", a.valeur);
	b.nom = "bBack";
	b.isConstant = False;
	b.valeur= 20;

		
	//Ajout d'un symbole (ici a)
	/*add(tds, a);
	
	//Ajout d'un temporaire qui a pour valeur 42
	Symbole * temp = new_temp(tds, 42);
	
	//Ajout d'un symbole (ici b)
	add(tds,b);
	
	//Afficher le contenue de la table
	//show_table(tds);
	show_table(tds);
	//recherche d'un symbole dans la table des symboles
	//Symbole *trouve = get_symbol(tds, temp->nom);
	
	//ListeQuad *lq = init_QList();

	//Génération des quads correspondant
	//genquad(lq, CREATEVAR, a.nom, NULL, NULL, NULL);
	//genquad(lq, CREATEVAR, temp->nom, NULL, NULL, NULL);
	//genquad(lq, CREATEVAR, b.nom, NULL, NULL, NULL);
	
	//Génération d'un quad de calcul (exemple addition) :
	//création du temporaire dans lequel sera stoqué le résultat
	//Symbole * resultat = new_temp(tds,0);
	//genquad(lq, CREATEVAR, resultat->nom, NULL, NULL, NULL);
	//Quad de calcul
	//genquad(lq, PLUS, a.nom, temp->nom, resultat->nom, NULL);
	
	//Symbole * temp2 = new_temp(tds, 0);
	//genquad(lq, ASSIGN, temp2->nom, resultat->nom, NULL, NULL);
	
	
	//qshow_liste(lq);
	//génère le code mips dans le fichier ex.s, fichier chargeable avec l'interpreteur MARS4_5 (ou QtSpim)
	//genererCodeMIPS(tds, lq);*/
	
	return 0;
}
