#ifndef QUADLIST_H
#define QUADLIST_H

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include <string.h>
#include "quad.h"

/* Contient les fonctions de la liste de quad */

/**
 * @brief initialise la table des symboles
 * @return Pointeur sur la table des symboles initialisée
 */
static ListeQuad * const init_QList()
{
	ListeQuad *liste = malloc(sizeof(*liste));
	
    if (liste == NULL)
	{
		printf("init_QList : Impossible d'allouer de la memoire a la liste de quad\n");
		exit(EXIT_FAILURE);
	}
	liste->premier = NULL;
    liste->taille = 0;

	return liste;
}

/**
 * @brief Ajoute un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param s Symbole à ajouter
 *-/
int gen(ListeQuad *lq, Symbole s)
{
	push_back(tds, s);
	return tds->taille-1;
}

/**
 * @brief Recherche d'un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param name Nom du symbole à chercher
 * @return Pointeur sur le symbole trouvé (sinon pointeur sur NULL)
 *-/
Symbole * get_symbol(TableDesSymboles *tds, char * name)
{
	if (tds == NULL)
	{
		printf("toString : La table des symboles n'existe pas\n");
		exit(EXIT_FAILURE);
	}
	
	Element *elem = tds->premier;
	
	while (elem != NULL && strcmp(name, elem->sb.nom) != 0)
        elem = elem->suivant;
	
	
	if (elem == NULL)
		return NULL;
	else
		return &elem->sb;
}

/**
 * @brief Recherche d'un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param id Indice du symbole à chercher
 * @return Pointeur sur le symbole trouvé (sinon pointeur sur NULL)
 *-/
Symbole * get_symbol_by_id(TableDesSymboles *tds, int id)
{
	if (tds == NULL)
	{
		printf("toString : La table des symboles n'existe pas\n");
		exit(EXIT_FAILURE);
	}
	
	Element *elem = tds->premier;
	
	while (elem != NULL && id != elem->sb.indice)
        elem = elem->suivant;
	
	
	if (elem == NULL)
		return NULL;
	else
		return &elem->sb;
}

/**
 * @brief Affiche le contenu de la table des symboles
 * @param tds Pointeur sur la table des symboles
 *-/
void show_table(TableDesSymboles *tds)
{
	if (tds == NULL)
	{
		printf("toString : La table des symboles n'existe pas\n");
		exit(EXIT_FAILURE);
	}
	
	Element *elem = tds->premier;
	printf("La table des symboles contient %d elts :\nnom\tindice\tconstance\tvaleur\n", tds->taille);
	
	while (elem != NULL)
	{
		char *cons;
        if (elem->sb.isConstant == True)
			cons= "constant";
		else
			cons = "variable";

        printf("%s\t%d\t%s\t%f\n", elem->sb.nom, elem->sb.indice, cons, elem->sb.valeur);
        elem = elem->suivant;
	}
}
*/
/* Fonctions internes */
void qpush_front(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label)
{
	QElement *nouveau = malloc(sizeof(*nouveau));
	
	if (lq == NULL || nouveau == NULL)
	{
		printf("push_front : Impossible d'allouer de la memoire a la table des symboles\n");
		exit(EXIT_FAILURE);
	}
	
/*struct quad{
	int indice;
	char *label;
	char *arg1, *arg2, *result;
	Operateur operateur;
};*/
	Quad q;
	q.label		= label;
	q.arg1		= arg1;
	q.arg2		= arg2;
	q.result	= result;
	q.operateur = op;

    nouveau->q = q;
    nouveau->suivant = NULL;
    nouveau->q.indice = lq->taille;
	
	if (lq->premier == NULL) //Si la table des symbooles ne contient pas encore d'element
		lq->premier = nouveau;
	else
	{
		nouveau->suivant = lq->premier;
		lq->premier = nouveau;
	}
	
	lq->taille++;
}

/*void push_back(TableDesSymboles *tds, Symbole s)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	
	if (tds == NULL || nouveau == NULL)
	{
		printf("push_back : Impossible d'allouer de la memoire a la table des symboles\n");
		exit(EXIT_FAILURE);
	}
	
    nouveau->sb = s;
    nouveau->suivant = NULL;
    nouveau->sb.indice = tds->taille;

    if (tds->taille == 0)
		tds->premier = nouveau;
	else if (tds->taille == 1)
		tds->premier->suivant = nouveau;
    else if (tds->taille > 1)
	{
        Element *elem = tds->premier;
		
		while(elem->suivant != NULL)
			elem = elem->suivant;
		
        elem->suivant = nouveau;
    }
    tds->taille = tds->taille + 1;
}

void erase_first(TableDesSymboles *tds)
{
	if (tds == NULL)
		exit(EXIT_FAILURE);
	
	if (tds->premier != NULL)
	{
		Element *aSupprimer = tds->premier;
		tds->premier = tds->premier->suivant;
		
		free(aSupprimer);
		tds->taille--;
	}
}*/
#endif
