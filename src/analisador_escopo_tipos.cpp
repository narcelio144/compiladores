#include "analisador_escopo_tipos.hpp"

listObject* symbolTable[MAX_NEST_LEVEL];
listObject* symbolTableLast[MAX_NEST_LEVEL];
listObject int_ = {-1, nullptr, SCALAR_TYPE_};
listObject* pInt = &int_;
listObject char_ = {-1, nullptr, SCALAR_TYPE_};
listObject* pChar = &char_;
listObject bool_ = {-1, nullptr, SCALAR_TYPE_};
listObject* pBool = &bool_;
listObject string_ = {-1, nullptr, SCALAR_TYPE_};
listObject* pString = &string_;
listObject universal_ = {-1, nullptr, SCALAR_TYPE_};
listObject* pUniversal = &universal_;

stack<t_attrib> semanticStack = stack<t_attrib>();

void semantics (int rule, int tokenSecundario){
	static int name,n,l,l1,l2;
	static int currentLevel = 0;
  static listObject *p,*t,*f;
	static t_attrib IDD_,IDU_,IDT_;
	switch (rule){

		case IDD_RULE:
			name = tokenSecundario;
      IDD_.nont = IDD;
      IDD_._.IDT.name = name;
      if( (p = search(name,currentLevel)) != nullptr){
      	errorRoutines::throwError(ERR_REDCL);
      } else{
			    p = define(name,currentLevel);
      }
			IDD_._.IDT.obj = p;
			break;

		case IDU_RULE:
			name = tokenSecundario;
			IDU_.nont = IDU;
			IDU_._.IDT.name = name;
			if((p = find(name,currentLevel)) == nullptr){
				errorRoutines::throwError(ERR_NO_DECL);
				p = define(name,currentLevel);
			}
			IDU_._.IDT.obj = p;
			break;

		case IDT_RULE:
			name = tokenSecundario;
			IDT_.nont = IDT;
			IDT_._.IDT.name = name;
			IDT_._.IDT.obj = nullptr;
			break;

		case DF_RULE:
			endBlock(currentLevel);
			break;

		case DT_STRUCT_RULE:
			endBlock(currentLevel);
			break;

		case NB_RULE:
			newBlock(currentLevel);
			break;

		case NF_RULE:
			newBlock(currentLevel);
			break;

		default:
			break;
	}
}

int newBlock(int &currentLevel){
	symbolTable[++currentLevel] = nullptr;
	symbolTableLast[currentLevel] = nullptr;
	return currentLevel;
}

int endBlock(int &currentLevel){
	return --currentLevel;
}

listObject* define (int name, int currentLevel){
	listObject *obj = new listObject;
	obj->nName = name;
	obj->pNext = nullptr;
	if(symbolTable[currentLevel] == nullptr ){
		symbolTable[currentLevel] = obj;
		symbolTableLast[currentLevel] = obj;
	} else {
		symbolTableLast[currentLevel]->pNext = obj;
		symbolTableLast[currentLevel] = obj;
	}
	return obj;
}

listObject* search (int name, int currentLevel){
	listObject *obj = symbolTable[currentLevel];
	while(obj != nullptr)	{
		if( obj->nName == name )
			break;
		else
			obj = obj->pNext;
	}
	return obj;
}

listObject* find (int name, int currentLevel){
	int i;
	listObject* obj = nullptr;
	for( i = currentLevel; i >= 0; --i ){
		obj = symbolTable[i];
		while( obj != nullptr ){
			if( obj->nName == name )
				break;
			else
				obj = obj->pNext;
		}
		if( obj != nullptr )
			break;
	}
	return obj;
}
