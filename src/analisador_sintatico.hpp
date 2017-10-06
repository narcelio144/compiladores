#ifndef ANALISADOR_SINTATICO
#define ANALISADOR_SINTATICO

#include "analisador_lexico.hpp"
#include "analisador_escopo_tipos.hpp"
#include "definitions.hpp"
#include "error_routines.hpp"
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>

using std::make_pair;
using std::pair;
using std::stack;
using std::vector;
using std::unordered_map;

extern vector<pair<t_nont,int>> vec_rules;
extern vector<unordered_map<int,int>> actionTable;
extern stack<int> states;

void build_rule_vector();
void build_action_table();
void getToken(int &token, int &tokenSecundario);
void parse();

#endif
