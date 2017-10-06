#include "error_routines.hpp"

bool errorRoutines::hasError = false;

void errorRoutines::throwSyntaxError(){
	cout << "[!] Erro de sintaxe na linha: " << currentLine << endl;
	exit(1);
}

void errorRoutines::throwError(error_code err){
  errorRoutines::hasError = true;
  cout << "[!] Erro na linha: " << currentLine << ". ";
  switch(err){
      case ERR_NO_DECL:
          cout << "Uso de variável não declarada";
          break;
      case ERR_REDCL:
          cout << "Redeclaração de variável";
          break;
			case ERR_TYPE_EXPECTED:
					cout << "Um tipo era esperado";
					break;
			case ERR_BOOL_TYPE_EXPECTED:
					cout << "Tipo bool esperado para a operação";
					break;
			case ERR_INVALID_TYPE:
					cout << "Tipo inválido para operação";
					break;
			case ERR_TYPE_MISMATCH:
					cout << "Tipos não compatíveis";
					break;
			case ERR_KIND_NOT_STRUCT:
					cout << "Operação suportada somente com structs";
					break;
			case ERR_FIELD_NOT_DECL:
					cout << "Campo da estrutura não declarado";
					break;
			case ERR_KIND_NOT_ARRAY:
					cout << "O tipo da operação não é um array";
					break;
			case ERR_INVALID_INDEX_TYPE:
					cout << "Indice de array inválido";
					break;
			case ERR_KIND_NOT_VAR:
					cout << "Operação suportada somente para var";
					break;
			case ERR_KIND_NOT_FUNCTION:
					cout << "Operação suportada somente para funções";
					break;
			case ERR_TOO_FEW_ARGS:
					cout << "Argumentos insuficientes";
					break;
			case ERR_TOO_MANY_ARGS:
					cout << "Excesso de argummentos";
					break;
			case ERR_PARAM_TYPE:
					cout << "Tipo de parametros inválidos";
					break;
			case ERR_RETURN_TYPE_MISMATCH:
					cout << "Tipo do retorno incompatível com o definido pela função" << endl;
					break;
      default:
          break;
  }
  cout << endl;
}
