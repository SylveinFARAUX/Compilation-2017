#ifndef SYMBOLES_H
#define SYMBOLES_H

typedef enum Boolean Boolean;
typedef struct Symbole Symbole;
typedef struct Element Element;
typedef struct TableDesSymboles TableDesSymboles;
typedef struct Identificateur Identificateur;

struct Identificateur
{
	char * chaine;
	int tailleID;
}; 
	
/**
 * @enum les booleens qui seront utilisés seront de type "boolean" et prendront True ou False
 */
enum Boolean
{
	True, 
	False
};

/**
 * @struct symbole symbole.h "Définition des symboles et de la table des symboles"
 */
struct Symbole
{
    int indice;
    char *nom;
	Boolean isConstant;
	int valeur;
};

/**
 * @struct élément de la liste chainée
 */
struct Element
{
	Symbole sb;
    Element *suivant;
};

/**
 * @struct Liste chainée représentant la table des symboles
 */
struct TableDesSymboles
{
	Element *premier;
    	int taille;
};

/* fonctions internes de la liste chainée */
void push_front(TableDesSymboles *tds, Symbole s);
void push_back(TableDesSymboles *tds, Symbole s);
void show_table(TableDesSymboles *tds);
void erase_first(TableDesSymboles *tds);
/* fonctions de la table des symboles */
static TableDesSymboles * const init_table();
Symbole * get_symbol(TableDesSymboles *tds, char * name);
Symbole * get_symbol_by_id(TableDesSymboles *tds, int id);
Symbole * next_symbol(TableDesSymboles *tds, Symbole * sb);
Symbole * new_temp(TableDesSymboles *tds, int v);
Symbole * add(TableDesSymboles *tds, Symbole s);
#endif
