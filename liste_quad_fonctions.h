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
 */
void genquad(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label){
	qpush_back(lq, op, arg1, arg2, result, label);
}

/**
 * @brief Affiche le contenu de la liste des quads
 * @param tds Pointeur sur la liste des quads
 */
void qshow_liste(ListeQuad *lq)
{
	if (lq == NULL)
	{
		printf("toString : La liste de quads n'existe pas\n");
		exit(EXIT_FAILURE);
	}

	QElement *elem = lq->premier;
	printf("La liste des quads contient %d elts :\nindice\tlabel\toperateur\targ1\targ2\targ3\tresult\n", lq->taille);

	while (elem != NULL)
	{
		char *op;
		switch(elem->q.operateur){
			case ASSIGN:
				op = "ASSIGN";
			break;
			case PLUS:
				op = "PLUS";
			break;
			case MULT:
				op = "MULTIPLICATION";
			break;
			case MINUS:
				op = "MINUS";
			break;
			case DIV:
				op = "DIVISION";
			break;
			case GOTO:
				op = "GOTO";
			break;
			case EQUAL:
				op = "EQUAL";
			break;
			default:
				op = "non reconnu";
			break;
		}

        printf("%d\t%s\t%s\t%s\t%s\t%s\n", elem->q.indice, elem->q.label, op, elem->q.arg1, elem->q.arg2, elem->q.result);
        elem = elem->suivant;
	}
}

/* Fonctions internes */
void qpush_back(ListeQuad *lq, Operateur op, char * arg1, char * arg2, char * result, char * label)
{
	QElement *nouveau = malloc(sizeof(*nouveau));

	if (lq == NULL || nouveau == NULL)
	{
		printf("qpush_back : Impossible d'allouer de la memoire a la liste de quads\n");
		exit(EXIT_FAILURE);
	}

	Quad q;
	q.label		= label;
	q.arg1		= arg1;
	q.arg2		= arg2;
	q.result	= result;
	q.operateur = op;

    nouveau->q = q;
    nouveau->suivant = NULL;
    nouveau->q.indice = lq->taille;

    if (lq->taille == 0)
		lq->premier = nouveau;
	else if (lq->taille == 1)
		lq->premier->suivant = nouveau;
    else if (lq->taille > 1)
	{
        QElement *elem = lq->premier;

		while(elem->suivant != NULL)
			elem = elem->suivant;

        elem->suivant = nouveau;
    }
    lq->taille = lq->taille + 1;
}

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
#endif
