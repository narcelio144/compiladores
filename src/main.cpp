#include "analisador_lexico.h"

//Definição da variável global de entrada
ifstream inputFile;

//Função descrevendo o uso do compilador
void usage(){
	cout << "Simple script compiler" << endl;
	cout << "Usage:" << endl;
	cout << "ss_compiler [program_file]" << endl;
}

int main(int argc, char **argv){
	
	if(argc < 2){
        usage();
		return 1;    
	}

	inputFile.open(argv[1]);
	if (!inputFile.is_open()){
		cout << "[!] Unable to open file " << argv[1] << endl;
		return 1;
	}
    
	lexical_analysis();

	return 0;
}
