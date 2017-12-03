#include "symbole.h"
#include "table_symboles_fonctions.h"
#include "liste_quad_fonctions.h"


void generercodemips(TableDesSymboles *tds, ListeQuad *lq)
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
		if (dataQuad->operateur == PLUS)//Si le quad demande de faire une addition
		{
			//on recherche les symboles dans la table des symboles
			Symbole *op1 = get_symbol(tds, dataQuad->arg1);
			Symbole	*op2 = get_symbol(tds, dataQuad->arg2);
			Symbole	*res = get_symbol(tds, dataQuad->result);
			if (op1 == NULL)printf("%s est NULL !\n", dataQuad->arg1);
			if (op2 == NULL)printf("%s est NULL !\n", dataQuad->arg2);
			if (res == NULL)printf("%s est NULL !\n", dataQuad->result);
			if (op1 != NULL && op2 != NULL && res != NULL)
			{
				//fprintf(fichier_mips, "lw $t0, %s", "li $v0,3\nl.s $f12,%s\n", nom);
				fprintf(fichier_mips, "\tl.s $f0, %s  #chargement du flottant dans $f0\n", op1->nom);
				fprintf(fichier_mips, "\tl.s $f1, %s\n", op2->nom);
				fprintf(fichier_mips, "\tadd.s $f2, $f0, $f1  #addition de flottants, $f2 <- $f0 + $f1\n");
				fprintf(fichier_mips, "\ts.s $f2, %s  #store simple float in the %s variable\n", res->nom, res->nom);
				
				//Affichage du resultat
				fprintf(fichier_mips, "\n\tli $v0, 2  #appel systeme pour printer un simple flottant\n");
				fprintf(fichier_mips, "\tl.s $f12, %s  #chargement dans f12(le parametre) l'adresse du reel à printer\n", res->nom);
				fprintf(fichier_mips, "\tsyscall\n");//je submit au système
				
				//retour à la ligne
				fprintf(fichier_mips, "\tli $v0,4\n\tla $a0,newline\n\tsyscall\n");
			}
			else
				printf("Erreur : addition avec des symboles qui n'existent pas");
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

int main(){
	
	char * buffer;
	
	//Initialiser la table
	TableDesSymboles *tds = init_table();
	
	//Création des symboles a, b et c
	Symbole a, b;
	a.nom = "a";
	a.isConstant = True;
	a.valeur = 142;
	
	b.nom = "bBack";
	b.isConstant = False;
	b.valeur= 20;

	//Ajout d'un symbole (ici a)
	add(tds, a);
	
	//Ajout d'un temporaire qui a pour valeur 42
	Symbole * temp = new_temp(tds, 42);
	
	//Ajout d'un symbole (ici b)
	add(tds,b);
	
	//Afficher le contenue de la table
	show_table(tds);
	
	//recherche d'un symbole dans la table des symboles
	Symbole *trouve = get_symbol(tds, "bBack");
	
	ListeQuad *lq = init_QList();

	//Génération des quads correspondant
	genquad(lq, CREATEVAR, a.nom, NULL, NULL, NULL);
	genquad(lq, CREATEVAR, temp->nom, NULL, NULL, NULL);
	genquad(lq, CREATEVAR, b.nom, NULL, NULL, NULL);
	
	//Génération d'un quad de calcul (exemple addition) :
	//création du temporaire dans lequel sera stoqué le résultat
	Symbole * ptr = new_temp(tds,0);
	genquad(lq, CREATEVAR, ptr->nom, NULL, NULL, NULL);
	//Quad de calcul
	genquad(lq, PLUS, a.nom, temp->nom, ptr->nom, NULL);
	
	//génère le code mips dans le fichier ex.s, fichier chargeable avec l'interpreteur MARS4_5 (ou QtSpim)
	generercodemips(tds, lq);  
	return 0;
}
