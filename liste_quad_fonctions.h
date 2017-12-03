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
static ListeQuad * const init_QList();

/**
 * @brief Ajoute un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param s Symbole à ajouter
 */
void genquad(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label){
	qpush_back(lq, op, arg1, arg2, result, label);
}

/**
 * @brief Recherche d'un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param name Nom du symbole à chercher
 * @return Pointeur sur le symbole trouvé (sinon pointeur sur NULL)
 *-/
Symbole * get_symbol(TableDesSymboles *tds, char * name);

/**
 * @brief Recherche d'un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param id Indice du symbole à chercher
 * @return Pointeur sur le symbole trouvé (sinon pointeur sur NULL)
 *-/
Symbole * get_symbol_by_id(TableDesSymboles *tds, int id);
/**
 * @brief Affiche le contenu de la liste des quads
 * @param tds Pointeur sur la liste des quads
 */
void qshow_table(ListeQuad *lq);

		switch(getArgType(elem->q.arg1)){
			case SYMBOLE:
				printf("symbole %s\n", get_arg(elem->q.arg1));
			break;
			case LABEL:
				printf("label %s\n", get_arg(elem->q.arg1));
			break;
			case UNDEFINED:
				printf("undefined\n");
			break;
			default:
			printf("defaut\n");
		}
        printf("%d\t%s\t%s\t%s\t%s\t%s\n", elem->q.indice, elem->q.label, op, elem->q.arg1, elem->q.arg2, elem->q.result);
        elem = elem->suivant;
	}
}

/* Fonctions internes */
void qpush_back(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label);

ArgumentType getArgType(char * arg);

ArgumentType getArgType(char * arg)
{
	if (strncmp(arg, type_symbole, 5) == 0)
		return SYMBOLE;
	else if(strncmp(arg, type_label, 5) == 0)
		return LABEL;
	else
		return UNDEFINED;
}

char * get_arg(char * arg)
{
	char retour[strlen(arg)-5];
	int i;
	
	for (i=6; i< strlen(arg); i++)
		retour[i-6] = arg[i];
	retour[strlen(arg)-6] = '\0';
	
	return &retour;
}
/*void erase_first(TableDesSymboles *tds)
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
