#ifndef ANALISADOR_LEXICO
#define ANALISADOR_LEXICO

#include <fstream>
#include <iostream>

#include <string>
#include <unordered_map>
#include <vector>

#define MAX_ID_LEN 20
#define MAX_CONST 200
#define MAX_NUM_LEN 20
#define MAX_STR_LEN 200

using std::ifstream;
using std::endl;
using std::cin;
using std::cout;

using std::string;
using std::unordered_map;
using std::vector;

//Enumeração para os tokens da linguagem
typedef enum {
		// Palavras reservadas
		ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO,
		ELSE, FALSE, FUNCTION, IF, INTEGER, OF, RETURN,
		STRING, STRUCT, TRUE, TYPE, VAR, WHILE,
		// Símbolos
		COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE,
		RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES,
		LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR,
		LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL,
		NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS,
		MINUS, MINUS_MINUS, TIMES, DIVIDE, DOT, NOT,
		// Token Regulares
		CHARACTER, NUMERAL, STRINGVAL, ID,
    //EOF
    ENDFILE,
		// Token Desconhecido
		UNKNOWN
} t_token;

//Enumeração dos tipos de constante
typedef enum{
    CHR,INT,STR
} const_type;

//Definição do tipo constante
typedef struct{
	const_type type; // 0-CHR, 1-INT, 2-STR
	union
	{
        char   cVal;
        int    nVal;
        char * sVal;
	} _;
} t_const;

//Estrutura retornada pela função nextToken contendo o token e, se for o caso, o token secundário
typedef struct{
    t_token token;
    int tokenSecundario;
    int constPosition;
} token_struct;

//Definição de algumas variáveis globais úteis
extern unordered_map<string,int> tokenSecundarioIDMap;
extern unordered_map<string,t_token> reservedWordMap;
extern unordered_map<int,string> t_terminalNames;
extern vector<t_const> vConst;
extern ifstream inputFile;
extern int currentLine;


//Métodos para inicialização das estruturas de dados necessárias
void initializeReservedWordMap();
void initializeTerminalNames();
//Métodos para tratamento de constantes
int addCharConst(char c);
int addIntConst(int n);
int addStringConst(char* s);
char getCharConst(int n);
int getIntConst(int n);
char* getStringConst(int n);

//Métodos auxiliares usados pelo analisador léxico para leitura do arquivo
char readChar(char& nextChar);
token_struct getNewTokenStruct();
void scanWord(token_struct& s_token,char& nextChar);
void scanNum(token_struct& s_token,char& nextChar);
t_token searchKeyWord(string);
int searchName(string);
token_struct nextToken();

//Método que será chamado pela função main do compilador para realizar a somente a análise léxica
void lexical_analysis();

void getCurrentLine();

#endif
