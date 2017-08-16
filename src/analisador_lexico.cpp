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

t_token searchKeyWord( char *name );
int searchName( char *name );
typedef struct{
	unsigned char type; // 0-char, 1-int, 2- string union
	union
	{
        char   cVal;
        int    nVal;
        char * sVal;
	} _; 
} t_const;


void mope(){
}

