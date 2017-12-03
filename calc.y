
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

%token NUM ID
%type INT IF ELSE WHILE FOR BREAK CASE RETURN CONTINUE CONST
%type SIZEOF STATIC TYPEDEF VOID MAIN PRINTF PRINTI SEMICOLON COND
%type ASSIGN PLUS INCREM MINUS DECRINCREM MULT DIV PUISS  OPAR  CPAR
%type EQ SUPEQ INFEQ TRUE FALSE

%nonassoc IFX
%nonassoc ELSE

%left PLUS MINUS
%left MULT DIV
%right PUISS
%nonassoc UMINUS

%type  expr

%start debut

%%


debut   :
        expr SEMICOLON                      {}
        | ID ASSIGN expr SEMICOLON         { }
        | WHILE OPAR COND CPAR debut       { }
        | FOR OPAR SEMICOLON expr SEMICOLON COND SEMICOLON expr CPAR debut       { }
        | IF OPAR expr CPAR debut %prec IFX        {}
        | IF OPAR expr CPAR debut ELSE  debut       {}
        ;

expr :
        INTEGER                         { }
        | ID                      { }
        | MINUS expr %prec UMINUS         {}
        | expr PLUS expr                 { }
        | expr MINUS expr                 {}
        | expr MULT expr                 { }
        | expr DIV expr                 { }
        | expr SUP expr                 { }
        | expr INF expr                 { }
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
