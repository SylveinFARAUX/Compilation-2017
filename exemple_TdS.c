#include "symbole.h"
#include "table_symboles_fonctions.h"

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
	
	c.nom = "c";
	c.isConstant = False;
	c.valeur = 142;

	//Ajout d'un symbole (ici a)
	add(tds, a);
	
	//Ajout d'un temporaire qui a pour valeur 42
	new_temp(tds, 42);
	
	//Ajout d'un symbole (ici b)
	add(tds,b);
	
	//Afficher le contenue de la table
	show_table(tds);
	
	//recherche d'un symbole dans la table des symboles
	Symbole *trouve = get_symbol(tds, "bBack");
	
	if (trouve != NULL)
	{
		char *cons;
		if (trouve->isConstant == True)
			cons= "constant";
		else
			cons = "variable";
		
        printf("\nSymbole trouve : \n%s\t%d\t%s\t%f\n", trouve->nom, trouve->indice, cons, trouve->valeur);
	}
	else 
		printf("\nLe symbole n'existe pas\n");
	return 0;
}