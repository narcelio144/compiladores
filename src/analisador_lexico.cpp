#include "analisador_lexico.hpp"

//Definição das variáveis globais declaradas no header
unordered_map<string,t_token> reservedWordMap = unordered_map<string,t_token>();
unordered_map<string,int> tokenSecundarioIDMap = unordered_map<string,int>();
vector<t_const> vConst = vector<t_const>();
unordered_map<int,string> t_terminalNames = unordered_map<int,string>();
int currentLine = 1;

//This structure is used only for debugging purposes
void initializeTerminalNames(void){
    t_terminalNames[ARRAY] = "ARRAY";
    t_terminalNames[BOOLEAN] = "BOOLEAN";
    t_terminalNames[BREAK] = "BREAK";
    t_terminalNames[CHAR] = "CHAR";
    t_terminalNames[CONTINUE] = "CONTINUE";
    t_terminalNames[DO] = "DO";
    t_terminalNames[ELSE] = "ELSE";
	t_terminalNames[ENDFILE] = "ENDFILE";
    t_terminalNames[FALSE] = "FALSE";
    t_terminalNames[FUNCTION] = "FUNCTION";
    t_terminalNames[IF] = "IF";
    t_terminalNames[INTEGER] = "INTEGER";
    t_terminalNames[OF] = "OF";
    t_terminalNames[RETURN] = "RETURN";
    t_terminalNames[STRING] = "STRING";
    t_terminalNames[STRUCT] = "STRUCT";
    t_terminalNames[TRUE] = "TRUE";
    t_terminalNames[TYPE] = "TYPE";
    t_terminalNames[VAR] = "VAR";
    t_terminalNames[WHILE] = "WHILE";
    t_terminalNames[COLON] = "COLON";
    t_terminalNames[SEMI_COLON] = "SEMI_COLON";
    t_terminalNames[COMMA] = "COMMA";
    t_terminalNames[EQUALS] = "EQUALS";
    t_terminalNames[LEFT_SQUARE] = "LEFT_SQUARE";
    t_terminalNames[RIGHT_SQUARE] = "RIGHT_SQUARE";
    t_terminalNames[LEFT_BRACES] = "LEFT_BRACES";
    t_terminalNames[RIGHT_BRACES] = "RIGHT_BRACES";
    t_terminalNames[LEFT_PARENTHESIS] = "LEFT_PARENTHESIS";
    t_terminalNames[RIGHT_PARENTHESIS] = "RIGHT_PARENTHESIS";
    t_terminalNames[AND] = "AND";
    t_terminalNames[OR] = "OR";
    t_terminalNames[LESS_THAN] = "LESS_THAN";
    t_terminalNames[GREATER_THAN] = "GREATER_THAN";
    t_terminalNames[LESS_OR_EQUAL] = "LESS_OR_EQUAL";
    t_terminalNames[GREATER_OR_EQUAL] = "GREATER_OR_EQUAL";
    t_terminalNames[NOT_EQUAL] = "NOT_EQUAL";
    t_terminalNames[EQUAL_EQUAL] = "EQUAL_EQUAL";
    t_terminalNames[PLUS] = "PLUS";
    t_terminalNames[PLUS_PLUS] = "PLUS_PLUS";
    t_terminalNames[MINUS] = "MINUS";
    t_terminalNames[MINUS_MINUS] = "MINUS_MINUS";
    t_terminalNames[TIMES] = "TIMES";
    t_terminalNames[DIVIDE] = "DIVIDE";
    t_terminalNames[DOT] = "DOT";
    t_terminalNames[NOT] = "NOT";
    t_terminalNames[CHARACTER] = "CHARACTER";
    t_terminalNames[NUMERAL] = "NUMERAL";
    t_terminalNames[STRINGVAL] = "STRINGVAL";
    t_terminalNames[ID] = "ID";
    t_terminalNames[UNKNOWN] = "UNKNOWN";
}
void initializeReservedWordMap(){
				reservedWordMap["array"]=ARRAY;
        reservedWordMap["boolean"] = BOOLEAN;
        reservedWordMap["break"] = BREAK;
        reservedWordMap["char"] = CHAR;
        reservedWordMap["continue"] = CONTINUE;
        reservedWordMap["do"] = DO;
        reservedWordMap["else"] = ELSE;
        reservedWordMap["false"] = FALSE;
        reservedWordMap["function"] = FUNCTION;
        reservedWordMap["if"] = IF;
        reservedWordMap["integer"] = INTEGER;
        reservedWordMap["of"] = OF;
				reservedWordMap["return"] = RETURN;
        reservedWordMap["string"] = STRING;
        reservedWordMap["struct"] = STRUCT;
        reservedWordMap["true"] = TRUE;
        reservedWordMap["type"] = TYPE;
        reservedWordMap["var"] = VAR;
        reservedWordMap["while"] = WHILE;
}

int addCharConst(char c){
	t_const _const;
	_const.type = CHR;
	_const._.cVal = c;
	vConst.push_back(_const);
	return vConst.size();
}

int addIntConst(int n){
	t_const _const;
	_const.type = INT;
	_const._.nVal = n;
	vConst.push_back(_const);
	return vConst.size();
}

int addStringConst(char* s){
	t_const _const;
	_const.type = STR;
	_const._.sVal = s;
	vConst.push_back(_const);
	return vConst.size();
}

char getCharConst(int n){
	return vConst[n]._.cVal;
}

int getIntConst(int n){
	return vConst[n]._.nVal;
}

char* getStringConst(int n){
	return vConst[n]._.sVal;
}

char readChar(char& nextChar){
	if (inputFile.eof()){
		nextChar = EOF;
		return nextChar;
	}
	inputFile.get(nextChar);
	if (nextChar == '\n'){
		currentLine++;
	}

	return nextChar;
}

token_struct getNewTokenStruct(){
	token_struct t;
	t.token = UNKNOWN;
	t.tokenSecundario = -1;
	t.constPosition = -1;
	return t;
}

void scanWord(token_struct& s_token,char& nextChar){
	string text = "";
	while (isalnum(nextChar) || nextChar == '_'){
        text += nextChar;
        readChar(nextChar);
	}
	s_token.token = searchKeyWord(text);
	if ( s_token.token == ID  ) {
		s_token.tokenSecundario = searchName(text);
    }
}
void scanNum(token_struct& s_token,char& nextChar){
	string numeral = "";
 	while (isdigit(nextChar)){
		 numeral+=nextChar;
		 readChar(nextChar);
	}
    s_token.token = NUMERAL;
    s_token.constPosition = addIntConst(stoi(numeral));
}

t_token searchKeyWord(string key){
    if(reservedWordMap.count(key) == 1){
        return reservedWordMap[key];
    }
    else{
        return ID;
    }
}

int searchName(string key){
    static int counter = 0;
    if(tokenSecundarioIDMap.count(key) == 1){
        return tokenSecundarioIDMap[key];
    }
    else{
        tokenSecundarioIDMap[key] = counter;
        return counter++;
    }
}

token_struct nextToken() {
	static char nextChar = '\x20';
	token_struct s_token = getNewTokenStruct();

    // Loop do estado inicial para pular os separadores
    while (isspace(nextChar)) {
        readChar(nextChar);
    }

    if (isalpha(nextChar)) {
        scanWord(s_token,nextChar);
    }

    else if (isdigit(nextChar)) {
    	scanNum(s_token,nextChar);
    }
    else if (nextChar == '"'){
        char* string = (char*) malloc(MAX_STR_LEN*sizeof(char)+1);
		int i = 0;
	    readChar(nextChar);
	    while (nextChar != '"') {
			string[i++] = nextChar;
			readChar(nextChar);
		}
	    string[i] = '\0';
	    readChar(nextChar);
	    s_token.token = STRINGVAL;
	    s_token.constPosition = addStringConst(string);
    }
    else {
        switch(nextChar) {
            case '\'':
                readChar(nextChar);
                s_token.constPosition = addCharConst(nextChar);
                readChar(nextChar);
                if (nextChar != '\'')
                    s_token.token = UNKNOWN;
                else
                    s_token.token = CHARACTER;
				readChar(nextChar);
                break;
            case ':':
                s_token.token = COLON;
				readChar(nextChar);
                break;
            case '+':
                readChar(nextChar);
                if (nextChar == '+') {
                    s_token.token =  PLUS_PLUS;
					readChar(nextChar);
                }
                else
                    s_token.token =  PLUS;
                break;
            case ';':
                s_token.token =  SEMI_COLON;
				readChar(nextChar);
                break;
            case ',':
                s_token.token =  COMMA;
				readChar(nextChar);

                break;
            case '=':
                readChar(nextChar);
                if (nextChar == '=') {
                    s_token.token =  EQUAL_EQUAL;
					readChar(nextChar);
                } else
                    s_token.token =  EQUALS;
                break;
            case '[':
                s_token.token =  LEFT_SQUARE;
				readChar(nextChar);
                break;
            case ']':
                s_token.token =  RIGHT_SQUARE;
				readChar(nextChar);
                break;
            case '{':
                s_token.token =  LEFT_BRACES;
				readChar(nextChar);
                break;
            case '}':
                s_token.token =  RIGHT_BRACES;
				readChar(nextChar);
                break;
            case '(':
                s_token.token =  LEFT_PARENTHESIS;
				readChar(nextChar);
                break;
            case ')':
                s_token.token =  RIGHT_PARENTHESIS;
				readChar(nextChar);
                break;
            case '&':
                readChar(nextChar);
                if(nextChar == '&'){
                    s_token.token = AND;
                    readChar(nextChar);
                }
                else{
                    s_token.token = UNKNOWN;
                }
                break;
            case '|':
                readChar(nextChar);
                if(nextChar == '|'){
                    s_token.token = OR;
                    readChar(nextChar);
                }
                else{
                    s_token.token = UNKNOWN;
                }
                break;
            case '<':
                readChar(nextChar);
                if (nextChar == '=' ) {
                    s_token.token =  LESS_OR_EQUAL;
					readChar(nextChar);
                } else {
                    s_token.token =  LESS_THAN;
                    break;
                }
            case '>':
                readChar(nextChar);
                if (nextChar == '=') {
                    s_token.token =  GREATER_OR_EQUAL;
					readChar(nextChar);
                } else
                    s_token.token =  GREATER_THAN;
                break;
            case '-':
                readChar(nextChar);
                if (nextChar == '-') {
                    s_token.token =  MINUS_MINUS;
					readChar(nextChar);
                } else
                    s_token.token =  MINUS;
                break;
            case '*':
                s_token.token =  TIMES;
				readChar(nextChar);
                break;
            case '/':
                s_token.token =  DIVIDE;
				readChar(nextChar);
                break;
						case EOF:
								s_token.token = ENDFILE;
								break;
            case '.':
                s_token.token =  DOT;
				readChar(nextChar);
                break;
            case '!':
                readChar(nextChar);
                if (nextChar == '=') {
                    s_token.token =  NOT_EQUAL;
					readChar(nextChar);
                } else
                    s_token.token =  NOT;
                break;
            default:
                s_token.token =  UNKNOWN;
								cout<<int(nextChar);
				readChar(nextChar);
                break;
        }
    }
    return s_token;
}

void lexical_analysis(){
	initializeTerminalNames();
	initializeReservedWordMap();
	token_struct t;
	do{
		t = nextToken();
		cout << t_terminalNames[t.token] << " ";
	} while (t.token != ENDFILE);
	cout << "[!] Finished lexical analysis" << endl;
}
