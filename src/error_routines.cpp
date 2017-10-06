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
      default:
          break;
  }
  cout << endl;
}
