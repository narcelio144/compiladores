#ifndef ANALISADOR_SINTATICO
#define ANALISADOR_SINTATICO

#define ACTION_TABLE_SIZE 160

#define IS_SHIFT(p) ((p)>0)
#define IS_REDUCTION(p) ((p)<0)
#define RULE(p) (-(p))

#include "analisador_lexico.h"
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

using std::make_pair;
using std::pair;
using std::stack;
using std::vector;
using std::unordered_map;

typedef enum{
    ACC=63,P,LDE,DE,DF,DT,DC,LI,DV,LP,B,LDV,LS,S,E,L,R,Y,F,LE,LV,T,TRU,FALS,CH,ST,NU,IDT
} t_nont;

extern vector<pair<t_nont,int>> vec_rules;
extern vector<unordered_map<int,int>> actionTable;
extern stack<int> states;

void build_rule_vector();
void build_action_table();
void throwSyntaxError();
void parse();

#endif
