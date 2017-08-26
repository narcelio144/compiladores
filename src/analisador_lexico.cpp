#include <string>
#include <iostream>

#define MAX_ID_LEN 20
#define MAX_CONST 200
#define MAX_NUM_LEN 20
#define MAX_STR_LEN 200

typedef enum {
		// palavras reservadas
		ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, 
		ELSE, FALSE, FUNCTION, IF, INTEGER, OF, 
		STRING, STRUCT, TRUE, TYPE, VAR, WHILE,
		// simbolos
		COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, 
		RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES, 
		LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR,
		LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL,
		NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS,
		MINUS, MINUS_MINUS, TIMES, DIVIDE, DOT, NOT,
		// tokens regulares
		CHARACTER, NUMERAL, STRINGVAL, ID,
		// token deconhecido
		UNKNOWN 
} t_token;


typedef struct{
	unsigned char type; // 0-char, 1-int, 2- string union
	union
	{
        char   cVal;
        int    nVal;
        char * sVal[MAX_ID_LEN + 1];
	} _; 
} t_const;

const char *reserv_words[] = {"ARRAY", "BOOLEAN", "BREAK", "CHAR", "CONTINUE", "DO", "ELSE", "FALSE", "FUNCTION", "IF", "INTEGER", "OF", "STRING", "STRUCT", "TRUE", "TYPE", "VAR", "WHILE"};

int searchName( char *name );

t_token searchKeyWord( char *name ){ //função que será usada para buscar as palavras reservadas na tabela de palavras reservadas.
	for(int i=0;i<18;i++){
		if(strcmp(name,reserv_words[i])){
			printf("Eh uma palavra reservada.\n");
			return (t_token)i;
		}
	}
	printf("Nao eh uma palavra reservada. \n");
	return ID;
}

//lê o próximo caractere
char readChar(FILE *fp){
	char c = fgetc(fp);
	return c;
}

t_token scanWord(char ch){
	char text[MAX_ID_LEN + 1];
    int i = 0;
	while ( isalnum(ch) || ch == '_' ) {
        text[i++] = ch;
        ch = readChar();
    }
    text[i] = '\0';
	token = searchKeyWord(text);
	if ( token == ID  ) {
		tokenSecundario = searchName(text, &count);                            
    }
    return token;
}
t_token scanNum(char ch){
	char numeral[MAX_NUM_LEN + 1];
	int i = 0;
    while (isdigit(ch)) {
        numeral[i++] = ch;
        ch = readChar();    
	}            
    numeral[i] = '\0';
    token = NUMERAL;
    tokenSecundario = addIntConst(numeral);
    return token;
}

t_token nextToken(void) {
    char nextChar = '\x20';
    t_token token;
    // loop do estado inicial para pular os separadores
    while (isspace(nextChar)) {
        nextChar=readChar();
    }
    if (isalpha(nextChar)) {
        token=scanWord(nextChar);  
    }

    else if ( isdigit(nextChar) ) {
    	token=scanNum(nextChar);
    }
    else if ( nextChar == '"' ){
        char string[MAX_STR_LEN + 1];
		int i = 0;
	    nextChar = readChar();
	    while ( nextChar != '"' ) {
			string[i++] = nextChar;
			nextChar = readChar();
		}
	    string[i] = '\0';
	    nextChar = readChar(); 
	    token = STRINGVAL;
	    tokenSecundario = addStringConst(string);
    }
    else {
        switch(nextChar) {
            case '\'':
                nextChar = readChar();
                token = CHARACTER;
                tokenSecundario = addCharConst(nextChar);
                nextChar = readChar(); // pular o '
                break;
            case ':':
                token = COLON;
                break;
            case '+':
                nextChar = readChar();
                if (nextChar == '+') {
                    token = PLUS_PLUS;
                }                                         
                else  
                    token = PLUS;                    
                break;
            case ';':
                token = SEMI_COLON;
                break;
            case ',':
                token = COMMA;
                break;
            case '=':
                nextChar = readChar();
                if (nextChar == '=') {
                    token = EQUAL_EQUAL;
                } else 
                    token = EQUALS;                    
                break;
            case '[':   
                token = LEFT_SQUARE;
                break;
            case ']':
                token = RIGHT_SQUARE;
                break;
            case '{':
                token = LEFT_BRACES;
                break;
            case '}':
                token = RIGHT_BRACES;
                break;
            case '(':
                token = LEFT_PARENTHESIS;
                break;
            case ')':
                token = RIGHT_PARENTHESIS;
                break;
            case '&':
                token = AND;
                break;
            case '|':
                token = OR;
                break;
            case '<':
                nextChar = readChar();
                if (nextChar == '=' ) {
                    token = LESS_OR_EQUAL;
                } else {
                    token = LESS_THAN;
                    break;
                }
            case '>':
                nextChar = readChar();
                if (nextChar == '=') {
                    token = GREATER_OR_EQUAL;
                } else
                    token = GREATER_THAN;
                break;
            case '-':
                nextChar = readChar();
                if (nextChar == '-') {
                    token = MINUS_MINUS;
                } else 
                    token = MINUS;
                break;
            case '*':
                token = TIMES;
                break;
            case '/':
                token = DIVIDE;
                break;
            case '.':
                token = DOT;
                break;
            case '!':
                nextChar = readChar();
                if (nextChar == '=') {
                    token = NOT_EQUAL;
                } else 
                    token = NOT;
                break;                 
            default:
                token = UNKNOWN;
                break;
        }
    }
    return token;
}

void mope(){
}

