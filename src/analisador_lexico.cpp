typedef enum {
		// palavras reservadas
		ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO, ELSE, FALSE, FUNCTION, IF, INTEGER, OF, STRING, STRUCT, TRUE, TYPE, VAR, WHILE,
		// simbolos
		COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE, RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES, LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR, LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL, NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS, MINUS, MINUS_MINUS, TIMES, DIVIDE, DOT, NOT,
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
        char * sVal;
	} _; 
} t_const;

const char *reserv_words[] {"ARRAY", "BOOLEAN", "BREAK", "CHAR", "CONTINUE", "DO", "ELSE", "FALSE", "FUNCTION", "IF", "INTEGER", "OF", "STRING", "STRUCT", "TRUE", "TYPE", "VAR", "WHILE"};

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

void mope(){
}

