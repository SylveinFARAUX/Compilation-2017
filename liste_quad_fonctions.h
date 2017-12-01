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
 *-/
int gen(ListeQuad *lq, Symbole s);

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

/* Fonctions internes */
void qpush_back(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label);

ArgumentType getArgType(char * arg);

/*void erase_first(TableDesSymboles *tds);*/

#endif
