#ifndef ANALISADOR_LEXICO
#define ANALISADOR_LEXICO

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "custom_types.hpp"

using std::ifstream;
using std::endl;
using std::cin;
using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

//Definição de algumas variáveis globais úteis
extern unordered_map<string,int> tokenSecundarioIDMap;
extern unordered_map<string,t_token> reservedWordMap;
extern unordered_map<int,string> t_terminalNames;
extern vector<t_const> vConst;
extern ifstream inputFile;
extern int currentLine;

//Métodos para inicialização das estruturas de dados necessárias
void initializeReservedWordMap();
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

void getCurrentLine();

#endif
