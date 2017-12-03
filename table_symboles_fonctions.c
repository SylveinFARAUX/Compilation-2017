#include "table_symboles_fonctions.h"

/* Contient les fonctions de la table des symboles */

/**
 * @brief initialise la table des symboles
 * @return Pointeur sur la table des symboles initialisée
 */
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

/**
 *  @brief crée un nouveau temporaire dans la table des symboles
 *  
 *  @param [in] tds Pointeur sur la table des symboles
 *  @param [in] v Valeur du temporaire créé
 *  @param [in] result stockage du mot final à rendre à gencode
 */
int new_temp(TableDesSymboles *tds, double v)
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
	/*char symbl[7+strlen(buffer)];
	strcpy(symbl, "symbl:");
	strcat(symbl, buffer);*/
	*result = strdup(buffer);
}

/**
 * @brief Ajoute un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param s Symbole à ajouter
 */
int add(TableDesSymboles *tds, Symbole s)
{
	push_back(tds, s);
	return tds->taille-1;
}

/**
 * @brief Recherche d'un symbole dans la table des symboles
 * @param tds Pointeur sur la table des symboles
 * @param name Nom du symbole à chercher
 * @return Pointeur sur le symbole trouvé (sinon pointeur sur NULL)
 */
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
 */
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

Symbole * next_symbol(TableDesSymboles *tds, Symbole * sb)
{
	if (tds == NULL || sb == NULL)
	{
		printf("toString : La table des symboles ou le symbole n'existe pas\n");
		exit(EXIT_FAILURE);
	}

	Element *elem = tds->premier;
	while (&elem->sb != sb && elem != NULL)
		elem = elem->suivant;
	if (elem == NULL)
		return NULL;
	else
		return &elem->suivant->sb;
}
/**
 * @brief Affiche le contenu de la table des symboles
 * @param tds Pointeur sur la table des symboles
 */
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
void push_front(TableDesSymboles *tds, Symbole s)
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

void push_back(TableDesSymboles *tds, Symbole s)
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
