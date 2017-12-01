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
 * @brief crée un nouveau temporaire dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param v Valeur du temporaire créé
 */
int new_temp(TableDesSymboles *tds, double v);


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
