
%{

extern void yyerror(const char * s);
extern int yylex();

TableDesSymboles *tds = NULL;



%}

/*
%union{
     ...
     int value;
}
*/

%token NUM ID STENCIL
%type INT IF ELSE WHILE FOR BREAK CASE RETURN CONTINUE CONST
%type SIZEOF STATIC TYPEDEF VOID MAIN PRINTF PRINTI ';' COND
%type ASSIGN '+' INCREM '-' DECRINCREM '*' '/' '^'  '('  ')'
%type EQ SUPEQ INFEQ TRUE FALSE

%nonassoc IFX
%nonassoc ELSE

%left '+' '-'
%left '*' '/'
%right '^'
%nonassoc UMINUS

%type  expr

%start debut

%%


debut   :
        expr ';'                      {}
        | ID ASSIGN expr ';'         { }
        | WHILE '(' COND ')' debut       { }
        | FOR '(' expr ';' COND ';' expr ')' debut       { }
        | IF '(' expr ')' debut %prec IFX        {}
        | IF '(' expr ')' debut ELSE  debut       {}
        ;

expr :
        INTEGER                         { }
        | ID                      { }
        | '-' expr %prec UMINUS         {}
        | expr '+' expr                 { }
        | expr '-' expr                 {}
        | expr '*' expr                 { }
        | expr '/' expr                 { }
        | expr '>' expr                 { }
        | expr '<' expr                 { }
        ;

COND :
        expr EQ expr                 {}
        | expr SUPEQ expr                 { }
        | expr INFEQ expr                 { }
        | TRUE                 { }
        | FALSE                 { }
        ;


%%

void yyerror(const char * s)
{
    fprintf(stderr,"%s\n",s);
}

int main (void)
{
        yyparse();
        return 1;
}
