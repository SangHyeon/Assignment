
/* Main routine of Calculator */

#include	<stdio.h>

#include	"calcul.h"
YYSTYPE yylval;

double store [26];
int loc;
int tok;

double term (void);
double uterm(void);
double expression (void);
void statements (void);
void statement (void);
double term_ (void);
double term_u (void);
double factor (void);
double factor_u (void);
double expression_ (void);

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
	temp = term ();//t//Tu
    //printf("temp is : %f\n", temp);
    while (tok == PLUS || tok == MINUS) {//E'?
	   if(tok == PLUS) {
           tok = yylex ();
	       temp = temp + term_ ();//tu //T
       }
       else {
           tok = yylex ();
	       temp = temp - term_ ();//tu //T
       }
	}
	return temp;
}
/*
double expression_ (void) {
    return 0;
}
*/
/*
double uterm (void) {//Tu  Tu->FuTu'
	double temp=factor_u();
    temp = temp * factor();//Tu' -> *FTu'
    
    return temp;
}*/

double term (void) {//T  T->FuT'
	double temp = factor_u();
    while (tok == TIMES || tok == DIVIDE) {//T'
	   if(tok == TIMES) {
           tok = yylex ();
	       temp = temp * factor_u();
       }
       else {
           tok = yylex ();
	       temp = temp / factor_u();
       }
	}
	return temp;
}

double term_(void) {//T'  T'->*FT'
    double temp = factor();
    while (tok == TIMES || tok == DIVIDE) {//T'
	   if(tok == TIMES) {
           tok = yylex ();
	       temp = temp * factor_u();
       }
       else {
           tok = yylex ();
	       temp = temp / factor_u();
       }
	}
	return temp;
}

double factor(void) {//F
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

double factor_u(void) {//Fu
    double temp;
    if(tok == MINUS) {
        tok = yylex();
        temp = -factor();
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
