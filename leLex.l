%{
  #include <stdio.h>
%}

%%

int     		              {printf("%s reconnu\n", yytext);/*return INT;*/}
" "						  {}
.+[^int]						  {printf("Erreur de syntaxe : %s\n", yytext); exit(0);}

%%
#define GG 41 int main
int yywrap (void)
{
  return 1;
}
main(int argc, char *argv[]){
	yylex();
	return 0;
}
