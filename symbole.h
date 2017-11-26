#ifndef SYMBOLES_H
#define SYMBOLES_H
typedef enum boolean
{
	True, False
} boolean;
typedef struct symbole
{
    int indice;
    char *nom;
	boolean isConstant;
	double valeur;
} symbole;

/* liste chainee de symboles */
typedef struct Element Element;
struct Element
{
	symbole sb;
    Element *suivant;
};
typedef struct TableDesSymboles TableDesSymboles;
struct TableDesSymboles
{
	Element *premier;
    int taille;
};

void push_front(TableDesSymboles *tds, symbole s);
void push_back(TableDesSymboles *tds, symbole s);
void show_table(TableDesSymboles *tds);
void erase_first(TableDesSymboles *tds);
#endif
