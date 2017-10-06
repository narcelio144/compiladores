#ifndef ANALISADOR_ESCOPO_TIPOS
#define ANALISADOR_ESCOPO_TIPOS

#include "analisador_lexico.hpp"
#include "error_routines.hpp"
#include "custom_types.hpp"
#include <stack>

using std::cout;
using std::endl;
using std::stack;

extern listObject* symbolTable[MAX_NEST_LEVEL];
extern listObject* symbolTableLast[MAX_NEST_LEVEL];
extern stack<t_attrib> semanticStack;

bool checkTypes (listObject *t1, listObject *t2);
extern void semantics(int rule,int tokenSecundario);
int newBlock(int &currentLevel);
int endBlock(int &currentLevel);
listObject* define(int name,int currentLevel);
listObject* search(int name,int currentLevel);
listObject* find(int name,int currentLevel);
void initializeAttribuites(attributes &attr,bool &attributesInitialized);

#endif
