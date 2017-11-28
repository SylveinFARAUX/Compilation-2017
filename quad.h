#ifndef QUAD_H
#define QUAD_H

#include "symbole.h"

typedef enum OPERATEUR Operateur;
typedef struct quad Quad;
typedef struct QElement QElement;
typedef struct ListeQuad ListeQuad;

enum OPERATEUR{ADD, MULT, SOUS, DIV, EQ};

struct quad{
	int indice;
	char *label;
	char *arg1, *arg2, *result;
	Operateur operateur;
};

/**
 * @struct élément de la liste chainée
 */
struct QElement
{
	Quad q;
	QElement *suivant;
};

/**
 * @struct Liste chainée représentant la table des symboles
 */
struct ListeQuad
{
	QElement *premier;
	int taille;
};

/* fonctions internes de la liste chainée */
void qpush_front(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label);
/*void qpush_back(TableDesSymboles *tds, Symbole s);
void qshow_table(TableDesSymboles *tds);
void qerase_first(TableDesSymboles *tds);*/
#endif
