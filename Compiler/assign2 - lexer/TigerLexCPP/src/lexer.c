/*
 * lexer.c
 *
 *  Created on: 2012. 9. 20.
 *      Author: cskim
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "util.h"
#include "errormsg.h"
#include "tokens.h"

FILE *yyin;

char ch = -1;
int state = 0;

enum { DIGIT, LETTER, SPECIAL, WHITESPACE };
int charClass(char ch){
	if (ch >= '0' && ch <= '9')
		return DIGIT;
	else if ((ch >= 'a' && ch <= 'z') || (ch >='A' && ch <='Z') || ch == '$' || ch == '_')
		return LETTER;
	else if ((ch == ' ' || ch == '\t' || ch == '\n'))
		return WHITESPACE;
	else
		return SPECIAL;
}

string TokensName[17] = {
    "array", "if", "then", "else", "while", "for", "to", "do", "let", 
    "in", "end", "of", "break", "nil", "function", "var", "type"
};

int yylex(){
	clearbuf();
	if (ch == -1)
		ch = getc(yyin);

	while (1){
        //Simillar to Hangle Automata
		switch (state) {
		case 0://start?
			if (charClass(ch) == DIGIT){
				putbuf(ch);
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 1;
			}
			else if (charClass(ch) == LETTER){
				putbuf(ch);
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 2;
			}
			else {
				state = 99;//special or white space
			}
			break;
		case 1://digit
			if (charClass(ch) == DIGIT){
				putbuf(ch);
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 1;
			}
			else {
				yylval.ival = atoi(String(strbuf));//int type
				state = 0;
				return INT;
			}
			break;
		case 2://letter
			if (charClass(ch) == DIGIT || charClass(ch) == LETTER){
				putbuf(ch);
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 2;
			}
			else {
				yylval.sval = String(strbuf);
                int flag = 0;//false;
                int index;
                for(int i=0; i<17; i++) {//find token in TokensName array
                    if(strcmp(yylval.sval, TokensName[i]) == 0){
                            index = i; 
                            flag = 1;
                    }
                }
				state = 0;
                if(flag)
                    return index+283;//return token's num
                else
				    return ID;//257
			}
			break;
		case 99://white space or special
			if (charClass(ch) == WHITESPACE){
				ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 0; 
			}
			else {//special
				int tok = ch;
				//ch = getc(yyin);
				if (ch==EOF) return 0;
				state = 0;
                switch(tok) {
                    case ',' :
                        ch = -1;
                        return COMMA;
                    case ':' ://assign(:=) or colon(:)
                        ch = getc(yyin);
                        if(ch == '=') {
                            ch = -1;
                            return ASSIGN;
                        }
                        else {
                            ungetc(ch, yyin);
                            ch = -1;
                            return COLON;
                        }
                       // break;
                    case ';' :
                        ch = -1;
                        return SEMICOLON;
                    case '(' :
                        ch = -1;
                        return LPAREN;
                    case ')' :
                        ch = -1;
                        return RPAREN;
                    case '[' :
                        ch = -1;
                        return LBRACK;
                    case ']' :
                        ch = -1;
                        return RBRACK;
                    case '{' :
                        ch = -1;
                        return LBRACE;
                    case '}' :
                        ch = -1;
                        return RBRACE;
                    case '.' :
                        ch = -1;
                        return DOT;
                    case '+' :
                        ch = -1;
                        return PLUS;
                    case '-' :
                        ch = -1;
                        return MINUS;
                    case '*' :
                        ch = -1;
                        return TIMES;
                    case '/' ://comment or divide
                        ch = getc(yyin);
                        if(ch == '*') {
                            //go to comment or while loop?
                            //referrence the book's code
                            do {
                                while(ch != '*') ch = getc(yyin);
                                ch = getc(yyin);
                            } while(ch != '/');
                            ch = -1;
                            break;
                        }
                        else {
                            ungetc(ch, yyin);
                           // cout<<"*****  ch *****  "<<ch<<endl;
                            ch = -1; //Is it necessary? [y], very important
                            return DIVIDE;
                        }
                        break;
                    case '=' :
                        ch = -1;
                        return EQ;
                    case '!' :
                        ch = getc(yyin);
                        if(ch == '=') {
                            ch = -1;
                            //cout<<"*****  ch *****  "<<ch<<endl;
                            return NEQ;
                        }
                        else
                             break;//error?
                    case '&' :
                        ch = -1;
                        return AND;
                    case '|' :
                        ch = -1;
                        return OR;
                    case '<' : //LE | LT
                        ch = getc(yyin);
                        if(ch == '=') {
                            ch = -1;
                            return LE;
                        }
                        else {
                            ungetc(ch, yyin);
                            ch = -1;
                            return LT;
                        }
                        break;
                    case '>' : //GE | GT
                        ch = getc(yyin);
                        if(ch == '=') {
                            ch = -1;
                            return GE;
                        }
                        else {
                            ungetc(ch, yyin);
                            ch = -1;
                            return GT;
                        }
                        break;
                    case '"' ://string
                        ch = getc(yyin);
                        while(ch != '"') {
                            if(ch == '\\') {
                                ch = getc(yyin);
                                if(ch == '\\') {
                                    putbuf('\\');
                                    putbuf('\\');
                                }
                                else if(ch == '"'){
                                    putbuf('"');
                                }
                                else {
                                    putbuf('\\');
                                    ungetc(ch, yyin);
                                }
                                ch = getc(yyin);
                            }
                            else{
                                putbuf(ch);
                                ch = getc(yyin);
                            }
                        }
                        yylval.sval = String(strbuf);
                        //end of string
                        ch = -1;
                        return STRING;
                    default :
                        //something doing?
                        if(ch == EOF) return 0;
                        ch = getc(yyin);
                        break;
                }
				return tok;//error?
			}
			break;
		}
	}
}
