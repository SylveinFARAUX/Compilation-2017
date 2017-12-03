#ifndef QUAD_H
#define QUAD_H

#include "symbole.h"

typedef enum OPERATEUR Operateur;
typedef enum ARGUMENT_TYPE ArgumentType;
typedef struct quad Quad;
typedef struct QElement QElement;
typedef struct ListeQuad ListeQuad;

enum OPERATEUR{ASSIGN, CREATEVAR, PLUS, MULT, MINUS, DIV, GOTO, EQUAL};
enum ARGUMENT_TYPE{SYMBOLE, LABEL, UNDEFINED};

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

char const type_symbole[] = "symbl:";
char const type_label[] = "label:";

/* fonctions internes de la liste chainée */
void qpush_back(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label);
void qshow_table(ListeQuad *lq);
char * get_arg(char * arg);
ArgumentType getArgType(char * arg);
#endif
