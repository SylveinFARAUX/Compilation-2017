
%{

extern void yyerror(const char * s);
extern int yylex();





%}


%union
{
     TableDesSymboles * tabDs;
     bool boolean;
}

%token <tabDs> NUM ID
%type INT IF ELSE WHILE FOR BREAK CASE RETURN CONTINUE CONST
%type SIZEOF STATIC TYPEDEF VOID MAIN PRINTF PRINTI SEMICOLON COND

%type <boolean> COND
%type <tabDs> debut expr


%nonassoc IFX
%nonassoc ELSE

%left "+" "-"
%left "*" "/"
%right "^"
%nonassoc UMINUS

%start debut

%%


debut   :
        expr ";"                      {}
        | ID "=" expr SEMICOLON         { }
        | WHILE "(" COND ")" debut       { }
        | FOR "(" expr ";" COND ";" expr ")" debut       { }
        | IF "(" expr ")" debut %prec IFX        {}
        | IF "(" expr ")" debut ELSE  debut       {}
        ;

expr :
        INTEGER                         { }
        | ID                      { }
        | MINUS expr %prec UMINUS         {}
        | expr "+" expr                 { }
        | expr "-" expr                 {}
        | expr "*" expr                 { }
        | expr "/" expr                 { }
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
