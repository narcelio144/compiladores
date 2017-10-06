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

bool checkTypes(listObject *t1, listObject *t2){
	if( t1 == t2 )
		return true;
	else if( t1 == pUniversal || t2 == pUniversal )
		return true;
	else if( t1->eKind == UNIVERSAL_ || t2->eKind == UNIVERSAL_ )
		return true;

	//Supporting operations between an alias and a type
	else if(t1->eKind == ALIAS_TYPE_ && t2->eKind != ALIAS_TYPE_){
		return checkTypes(t1->_.Alias.pBaseType,t2);
	}
	//Supporting operations between type and an alias
	else if(t1->eKind != ALIAS_TYPE_ && t2->eKind == ALIAS_TYPE_){
		return checkTypes(t1,t2->_.Alias.pBaseType);
	}

	else if( t1->eKind == t2->eKind ){
		if( t1->eKind == ALIAS_TYPE_ ){
			return checkTypes(t1->_.Alias.pBaseType,t2->_.Alias.pBaseType);
		}
		else if( t1->eKind == ARRAY_TYPE_ ){
			if( t1->_.Array.nNumElems ==t2->_.Array.nNumElems ){
				return checkTypes(t1->_.Array.pElemType,t2->_.Array.pElemType);
			}
		else if( t1->eKind == STRUCT_TYPE_ ){
		}
			listObject *f1 = t1->_.Struct.pFields;
			listObject *f2 = t2->_.Struct.pFields;
			while( f1 != nullptr && f2 != nullptr ){
				if( !checkTypes(f1->_.Field.pType,f2->_.Field.pType) )
					return false;

				//Coloquei isso aqui pois pra mim, esse while da apostila sem as duas linhas de baixo não faz o menor sentido
				f1 = f1->pNext;
				f2 = f2->pNext;

			}
		return ( f1 == nullptr && f2 == nullptr );
		}
	}
	return false;
}
void initializeAttribuites(attributes &attr, bool &attributesInitialized){
	attr._IDD.nont = IDD;
	attr._IDU.nont = IDU;
	attr._IDT.nont = IDT;
	attr._T.nont = T;
	attr._LI.nont = LI;
	attr._LI0.nont = LI;
	attr._LI1.nont = LI;
	attr._TRU.nont = TRU;
	attr._FALS.nont = FALS;
	attr._ST.nont = ST;
	attr._CH.nont = CH;
	attr._NU.nont = NU;
	attr._DC.nont = DC;
	attr._DC0.nont = DC;
	attr._DC1.nont = DC;
	attr._LP.nont = LP;
	attr._LP0.nont = LP;
	attr._LP1.nont = LP;
	attr._E.nont = E;
	attr._E0.nont = E;
	attr._E1.nont = E;
	attr._L.nont = L;
	attr._L0.nont = L;
	attr._L1.nont = L;
	attr._R.nont = R;
	attr._R0.nont = R;
	attr._R1.nont = R;
	attr._Y.nont = Y;
	attr._Y0.nont = Y;
	attr._Y1.nont = Y;
	attr._F.nont = F;
	attr._F0.nont = F;
	attr._F1.nont = F;
	attr._LV.nont = LV;
	attr._LV0.nont = LV;
	attr._LV1.nont = LV;
	attr._LE.nont = LE;
	attr._LE0.nont = LE;
	attr._LE1.nont = LE;
	attr._MC.nont = MC;
	attr._MT.nont = MT;
	attr._ME.nont = ME;
	attr._MW.nont = MW;
	attributesInitialized = true;
}

void semantics (int rule, int tokenSecundario){
	static int name,n,l,l1,l2;
	static int currentLevel = 0;
	static listObject *p,*t,*f;
	static bool attributesInitialized = false;
	static attributes attr;
	if (!attributesInitialized)
		initializeAttribuites(attr,attributesInitialized);

	switch (rule){
		case IDD_RULE:
			name = tokenSecundario;
      attr._IDD._.IDT.name = name;
      if( (p = search(name,currentLevel)) != nullptr){
      	errorRoutines::throwError(ERR_REDCL);
      } else{
			    p = define(name,currentLevel);
      }
			p->eKind = NO_KIND_DEF_;
			attr._IDD._.IDT.obj = p;
			break;

		case IDU_RULE:
			name = tokenSecundario;
			attr._IDU._.IDT.name = name;
			if((p = find(name,currentLevel)) == nullptr){
				errorRoutines::throwError(ERR_NO_DECL);
				p = define(name,currentLevel);
			}
			attr._IDU._.IDT.obj = p;
			break;

		case IDT_RULE:
			name = tokenSecundario;
			attr._IDT._.IDT.name = name;
			attr._IDT._.IDT.obj = nullptr;
			break;

		case T_INTEGER_RULE:
			attr._T._.T.type = pInt;
			semanticStack.push(attr._T);
			break;
		case T_CHAR_RULE:
			attr._T._.T.type = pChar;
			semanticStack.push(attr._T);
			break;;
		case T_STRINGVAL_RULE:
			attr._T._.T.type = pString;
			semanticStack.push(attr._T);
			break;
		case T_BOOLEAN_RULE:
			attr._T._.T.type = pBool;
			semanticStack.push(attr._T);
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
