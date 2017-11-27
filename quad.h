#ifndef QUAD_H
#define QUAD_H

#include "symbole.h"

typedef enum OPERATEUR Operateur;
typedef struct quad quad;

enum OPERATEUR{ADD, MULT, SOUS, DIV, EQ};

struct quad{
	int indice;
	symbole *arg1, *arg2, *result;
	Operateur operateur;
};


#endif