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

/**
 *  @brief Génère le code MIPS à partir des quads (dans l'ordre)
 *  
 *  @param [in] tds Pointeur sur la table des symboles
 *  @param [in] lq Pointeur sur la liste de quads
 */
void genererCodeMIPS(TableDesSymboles *tds, ListeQuad *lq)
{
	FILE *fichier_mips = NULL;
	fichier_mips = fopen("ex.s", "w+");
	
	if (fichier_mips == NULL){
		printf("Erreur lors de l'ouverture de ex.spi\n");
		return;
	}
	
	QElement *elem = lq->premier;
	Quad *dataQuad = &elem->q;
	
	/*zone data du code mips*/
	fprintf(fichier_mips, ".data\n");
	while (dataQuad != NULL)
	{
		if (dataQuad->operateur == CREATEVAR)//si le quad demande la création d'une variable
		{
			//on recherche le symbole dans la table des symboles
			Symbole *trouve = get_symbol(tds, dataQuad->arg1);
			
			if (trouve != NULL)//Si on a trouvé le symbole en question
				fprintf(fichier_mips, "\t%s:\t.float %f  #chargement du symbole %s\n", trouve->nom, trouve->valeur, trouve->nom);
			else
				printf("Erreur : symbole %s non référencé dans la table des symboles\n", dataQuad->arg1);
		}
		elem = elem->suivant;
		dataQuad = &elem->q;
	}
	fprintf(fichier_mips, "\tnewline:\t.asciiz \"\\n\"\n\tspace:\t.asciiz \" \"\n\ttermin:\t.asciiz \"program terminated\"\n");
	
	/*zone intructions du code mips (calcul arithmetique)*/
	elem = lq->premier;
	dataQuad = &elem->q;
	fprintf(fichier_mips, "\n\n");
	fprintf(fichier_mips, ".text\n\tmain:\n");
	show_table(tds);

	while (dataQuad != NULL)
	{
		switch(dataQuad->operateur)
		{
			case PLUS: //Si le quad demande de faire une addition
				//on recherche les symboles dans la table des symboles
				Symbole *op1 = get_symbol(tds, dataQuad->arg1);
				Symbole	*op2 = get_symbol(tds, dataQuad->arg2);
				Symbole	*res = get_symbol(tds, dataQuad->result);
				if (op1 == NULL)printf("%s est NULL !\n", dataQuad->arg1);
				if (op2 == NULL)printf("%s est NULL !\n", dataQuad->arg2);
				if (res == NULL)printf("%s est NULL !\n", dataQuad->result);
				if (op1 != NULL && op2 != NULL && res != NULL)
				{
					fprintf(fichier_mips, "\tlw $t0, %s  #chargement de l'entier dans $t0\n", op1->nom);
					fprintf(fichier_mips, "\tlw $t1, %s\n", op2->nom);
					fprintf(fichier_mips, "\tadd $t2, $t0, $t1  #addition d'entiers, $t2 <- $t0 + $t1\n");
					fprintf(fichier_mips, "\tsw $t2, %s  #store an integer in the %s variable\n", res->nom, res->nom);
				}
				else
					printf("Erreur : addition avec des symboles qui n'existent pas");
			break;
			case MINUS: //Si le quad demande de faire une soustraction
				//on recherche les symboles dans la table des symboles
				Symbole *op1 = get_symbol(tds, dataQuad->arg1);
				Symbole	*op2 = get_symbol(tds, dataQuad->arg2);
				Symbole	*res = get_symbol(tds, dataQuad->result);
				if (op1 == NULL)printf("%s est NULL !\n", dataQuad->arg1);
				if (op2 == NULL)printf("%s est NULL !\n", dataQuad->arg2);
				if (res == NULL)printf("%s est NULL !\n", dataQuad->result);
				if (op1 != NULL && op2 != NULL && res != NULL)
				{
					fprintf(fichier_mips, "\tlw $t0, %s  #chargement de l'entier dans $t0\n", op1->nom);
					fprintf(fichier_mips, "\tlw $t1, %s\n", op2->nom);
					fprintf(fichier_mips, "\tsub $t2, $t0, $t1  #soustraction d'entiers, $t2 <- $t0 - $t1\n");
					fprintf(fichier_mips, "\tsw $t2, %s  #store an integer in the %s variable\n", res->nom, res->nom);
				}
				else
					printf("Erreur : soustraction avec des symboles qui n'existent pas");
			break;
			case MULT:
				//on recherche les symboles dans la table des symboles
				Symbole *op1 = get_symbol(tds, dataQuad->arg1);
				Symbole	*op2 = get_symbol(tds, dataQuad->arg2);
				Symbole	*res = get_symbol(tds, dataQuad->result);
				if (op1 == NULL)printf("%s est NULL !\n", dataQuad->arg1);
				if (op2 == NULL)printf("%s est NULL !\n", dataQuad->arg2);
				if (res == NULL)printf("%s est NULL !\n", dataQuad->result);
				if (op1 != NULL && op2 != NULL && res != NULL)
				{
					fprintf(fichier_mips, "\tlw $t0, %s  #chargement de l'entier dans $t0\n", op1->nom);
					fprintf(fichier_mips, "\tlw $t1, %s\n", op2->nom);
					fprintf(fichier_mips, "\tmul $t2, $t0, $t1  #multiplication d'entiers, $t2 <- $t0 * $t1\n");
					fprintf(fichier_mips, "\tsw $t2, %s  #store an integer in the %s variable\n", res->nom, res->nom);
				}
				else
					printf("Erreur : multiplication avec des symboles qui n'existent pas");
			break;
			case DIV:
				//on recherche les symboles dans la table des symboles
				Symbole *op1 = get_symbol(tds, dataQuad->arg1);
				Symbole	*op2 = get_symbol(tds, dataQuad->arg2);
				Symbole	*res = get_symbol(tds, dataQuad->result);
				if (op1 == NULL)printf("%s est NULL !\n", dataQuad->arg1);
				if (op2 == NULL)printf("%s est NULL !\n", dataQuad->arg2);
				if (res == NULL)printf("%s est NULL !\n", dataQuad->result);
				if (op1 != NULL && op2 != NULL && res != NULL)
				{
					fprintf(fichier_mips, "\tlw $t0, %s  #chargement de l'entier dans $t0\n", op1->nom);
					fprintf(fichier_mips, "\tlw $t1, %s\n", op2->nom);
					fprintf(fichier_mips, "\tdiv $t2, $t0, $t1  #division d'entiers, $t2 <- $t0 / $t1\n");
					fprintf(fichier_mips, "\tsw $t2, %s  #store an integer in the %s variable\n", res->nom, res->nom);					
				}
				else
					printf("Erreur : division avec des symboles qui n'existent pas");
			break;
			case SHOW:
				Symbole *var = get_symbol(tds, dataQuad->arg1);
			
				//Affichage du resultat
				fprintf(fichier_mips, "\n\tli $v0, 1  #appel systeme pour printer un ingeger\n");
				fprintf(fichier_mips, "\tlw $a0, %s  #chargement dans $a0 (le parametre) l'adresse de l'entier à printer\n", var->nom);
				fprintf(fichier_mips, "\tsyscall\n");//je submit au système
				
				//retour à la ligne
				fprintf(fichier_mips, "\tli $v0,4\n\tla $a0,newline\n\tsyscall\n");
			break;
		}
		
		elem = elem->suivant;
		dataQuad = &elem->q;
	}
	
	//affichage de program terminated
	fprintf(fichier_mips, "\n\t#affichage de \"program terminated\"\n");
	fprintf(fichier_mips, "\tli $v0,4\n\tla $a0,newline\n\tsyscall\n");
	fprintf(fichier_mips, "\tli $v0,4\n\tla $a0,termin\n\tsyscall\n"); 
	fprintf(fichier_mips, "\tli $v0,4\n\tla $a0,newline\n\tsyscall\n");

	fprintf(fichier_mips, "\n\t#exit\n\tli $v0,10  # on sort du programme proprement\n\tsyscall\n");
	
	if (fclose(fichier_mips) != 0)
		printf("Erreur lors de la fermeture du fichier ex.spi\n");
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
