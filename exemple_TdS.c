#include "symbole.h"
#include "table_symboles_functions.h"

int main(){
	TableDesSymboles *tds = init_table();
	symbole a, b, c;
	a.nom = "a";
	a.isConstant = True;
	a.valeur = 142;
	
	b.nom = "bBack";
	b.isConstant = False;
	
	c.nom = "c";
	c.isConstant = False;
	c.valeur = 142;
	
	add(tds, a);
	new_temp(tds, 42);
	add(tds,b);
	
	show_table(tds);
	return 0;
}