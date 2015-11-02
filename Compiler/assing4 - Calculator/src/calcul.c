
/* Main routine of Calculator */

#include	<stdio.h>

#include	"calcul.h"
YYSTYPE yylval;

double store [26];
int loc;
int tok;

double term_u (void);
double expression (void);
void statements (void);
void statement (void);
double term (void);
double factor (void);
double factor_u (void);

void yyerror (char* s) {
    printf ("*** Error: %s\n", s);
}
void program (void) {
    statements ();
    printf ("END\n");
}
void statements (void) {
    statement ();
    while (tok == SEMI || tok == NL) {
        tok = yylex ();
        statement ();
    }
    printf( "tok = %d\n", tok);
}
void statement (void) {
    if (tok == IDENT) {
        loc = yylval.id - 'a';
        tok = yylex();
        if (tok == ASSIGN) {
            tok = yylex();
            store [loc] = expression();
            printf ("Var %c  = %f\n", loc+'a', store[loc]);
        }
        else
            yyerror ("ASSIGN expected");
    }
    else if (tok == PRINT) {
        tok = yylex();
        printf ("%f\n", expression ());
    }
    /*****
     else
     yyerror ("IDENT or PRINT expected");
     *****/
}

double expression (void) {//E  E->TuE'
    double temp;
    temp = term_u ();//Tu
    //printf("temp is : %f\n", temp);
    while (tok == PLUS || tok == MINUS) {//E'->+TE'
        if(tok == PLUS) {
            tok = yylex ();
            temp = temp + term();//T
        }
        else {
            tok = yylex ();
            temp = temp - term();//T
        }
    }
    return temp;
}

double term_u (void) {//Tu->FuTu'
    double temp = factor_u();//Fu
    while (tok == TIMES || tok == DIVIDE) {//Tu'->*FTu'
        if(tok == TIMES) {
            tok = yylex ();
            temp = temp * factor();//factor_u 사용하면 3*-1 연산 가능
        }
        else {
            tok = yylex ();
            temp = temp / factor();
        }
    }
    return temp;
}

double term(void) {//T->FuT'
    double temp = factor();//F
    while (tok == TIMES || tok == DIVIDE) {//T'
        if(tok == TIMES) {
            tok = yylex ();
            temp = temp * factor_u();//Fu*FT'
        }
        else {
            tok = yylex ();
            temp = temp / factor_u();
        }
    }
    return temp;
}

double factor(void) {//F->(E)
    double temp;
    if(tok == '(') {
        tok = yylex();
        temp = expression();
        if(tok ==')') {
            tok = yylex();
            return temp;
        }
        else {
            yyerror("cant find ')'");
            return 0;
        }
    }
    else if(tok == NUM) {
        temp = yylval.num;
        tok = yylex();
        return temp;
    }
    else if(tok == IDENT) {
        temp = store[yylval.id - 'a'];
        tok = yylex();
        return temp;
    }
    else {
        yyerror("Illegal token");
    }
    return 0;
}

double factor_u(void) {//Fu->F | -F
    double temp;
    if(tok == MINUS) {
        tok = yylex();
        temp = -factor();//F
    }
    else {
        temp = factor();
    }
    return temp;
}


int main (void)
{
    tok = yylex ();
    program ();
    return 0;
}
