#ifndef TABLEDESSYMBOLESFN_H
#define TABLEDESSYMBOLESFN_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "symbole.h"

/* Contient les fonctions de la table des symboles */

/**
 * @brief initialise la table des symboles
 * @return Pointeur sur la table des symboles initialisée
 */
static TableDesSymboles * const init_table();


/**
 *  \brief crée un nouveau temporaire dans la table des symboles
 *  
 *  \param [in] tds Pointeur sur la table des symboles
 *  \param [in] v Valeur du temporaire créé
 *  \param [in] result stockage du mot final à rendre à gencode
 */
void new_temp(TableDesSymboles *tds, double v, char **result)
{
	int nDigits;
	if (tds->taille > 0)
		nDigits = floor(log10(abs(tds->taille))) + 1;
	else
		nDigits = 1;

	char taille[nDigits+1];
	sprintf(taille, "%d", tds->taille);
	
	//creation du mot final
	char buffer[5+nDigits];
	strcpy(buffer, "temp");
	strcat(buffer, taille);
	buffer[4+nDigits] = '\0';
	Symbole sb;
	sb.nom = strdup(buffer);
	sb.isConstant = True;
	sb.valeur = v;

	push_back(tds, sb);
	
	//stockage de symbl:tempx dans result
	char symbl[7+strlen(buffer)];
	strcpy(symbl, "symbl:");
	strcat(symbl, buffer);
	*result = strdup(symbl);
}

/**
 * @brief Ajoute un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param s Symbole à ajouter
 */
int add(TableDesSymboles *tds, Symbole s);

/**
 * @brief Recherche d'un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param name Nom du symbole à chercher
 * @return Pointeur sur le symbole trouvé (sinon pointeur sur NULL)
 */
Symbole * get_symbol(TableDesSymboles *tds, char * name);
/**
 * @brief Recherche d'un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param id Indice du symbole à chercher
 * @return Pointeur sur le symbole trouvé (sinon pointeur sur NULL)
 */
Symbole * get_symbol_by_id(TableDesSymboles *tds, int id);

Symbole * next_symbol(TableDesSymboles *tds, Symbole * sb);
/**
 * @brief Affiche le contenu de la table des symboles
 * @param tds Pointeur sur la table des symboles
 */
void show_table(TableDesSymboles *tds);

/* Fonctions internes */
void push_front(TableDesSymboles *tds, Symbole s);

void push_back(TableDesSymboles *tds, Symbole s);

void erase_first(TableDesSymboles *tds);

#endif
