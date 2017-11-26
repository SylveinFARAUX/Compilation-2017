#ifndef TABLEDESSYMBOLESFN_H
#define TABLEDESSYMBOLESFN_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "symbole.h"

/* Contient les fonctions de la table des symboles */

static TableDesSymboles * const init_table()
{
	TableDesSymboles *liste = malloc(sizeof(*liste));
	
    if (liste == NULL)
	{
		printf("init_table : Impossible d'allouer de la memoire a la table des symboles\n");
		exit(EXIT_FAILURE);
	}
	liste->premier = NULL;
    liste->taille = 0;

	return liste;
}

//returns 1 if failed, 0 if succeeded 
void  append(char*s, char c) {

     strncat(s, &c, 1);
}
int new_temp(TableDesSymboles *tds, double v)
{
	int nDigits = floor(log10(abs(tds->taille))) + 1;
	char taille[nDigits+1];
	sprintf(taille, "%d", tds->taille);
	
	//creation du mot final
	char buffer[5+nDigits];
	strcpy(buffer, "temp");
	strcat(buffer, taille);
	
	symbole sb;
	sb.nom = strdup(buffer);
	sb.isConstant = True;
	sb.valeur = v;

	push_back(tds, sb);
	return tds->taille-1;
}

int add(TableDesSymboles *tds, symbole s)
{
	push_back(tds, s);
	return tds->taille-1;
}

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

/* Fonctions internes */
void push_front(TableDesSymboles *tds, symbole s)
{
	Element *nouveau = malloc(sizeof(*nouveau));
	
	if (tds == NULL || nouveau == NULL)
	{
		printf("push_front : Impossible d'allouer de la memoire a la table des symboles\n");
		exit(EXIT_FAILURE);
	}
	
    nouveau->sb = s;
    nouveau->suivant = NULL;
    nouveau->sb.indice = tds->taille;
	
	if (tds->premier == NULL) //Si la table des symbooles ne contient pas encore d'element
		tds->premier = nouveau;
	else
	{
		nouveau->suivant = tds->premier;
		tds->premier = nouveau;
	}
	
	tds->taille++;
}

void push_back(TableDesSymboles *tds, symbole s)
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
}
#endif