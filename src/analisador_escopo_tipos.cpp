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
      		if((p = search(name,currentLevel)) != nullptr){
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

		

		// Figura 6.5
		case T_IDU_RULE:
			p= attr._IDU._.IDT.obj; //nao tenho certeza que eh assim, pelo slide eh IDU.obj;
			if (IS_TYPE_KIND(p->eKind) || p->eKind == UNIVERSAL_){
				attr._T._.T.type = p;
			} else {
				attr._T._.T.type = pUniversal;
				errorRoutines::throwError(ERR_TYPE_EXPECTED);
			}
			break;
		
		// Figura 6.6
		case LI_IDD_RULE:
			attr._LI._.LI.list = attr._IDD._.IDT.obj;
			semanticStack.push(attr._LI);
			break;

		case LI_REC_RULE:
			attr._LI0._.LI.list = attr._LI1.list; //deveria ser LI0.list=LI1.list;
			semanticStack.push(attr._LI0);
			break;
		
		case DV_RULE:
			p=attr._LI._.LI.list;
			t=attr._T._.T.type;
			//tem que fazer algo com o n?

			while(p!=nullptr && p->eKind == NO_KIND_DEF_){
				P->eKind=VAR_;
				p->attr._.Var.pType = t;
				p=p->pNext;
			}
			break;
		
		//figura 6.7
		case TRU_TRUE_RULE:
			attr._TRU._.TRU.type = pBool;
			attr._TRU._.TRU.val = true;
			break;

		case FALS_FALSE_USE:
			attr._FALS._.FALS.type = pBool;
			attr._FALS._.FALS.val = false;
			break;

		case CH_CHARACTER_RULE:
			attr._CH._.CH.type = pChar;
			attr._CH._.CH.pos = tokenSecundario;
			attr._CH._.CH.val = getCharConst(attr._CH._.CH.pos);
			break;
		
		case ST_STRINGVAL_RULE:
			attr._ST._.ST.type = pString;
			attr._ST._.ST.pos = tokenSecundario;
			attr._ST._.ST.val = getStringConst(attr._ST._.ST.pos);
			break;

		case NU_NUMERAL_RULE:
			attr._NU._.NU.type = pString;
			attr._NU._.NU.pos = tokenSecundario;
			attr._NU._.NU.val = getIntConst(attr._NU._.NU.pos);
			break;

		//figura 6.8
		case DT_ARRAY_RULE:
			p=attr._IDD._.IDT.obj; // deveria ser p=IDD.obj;
			n=attr._NU._.NU.val;
			t=attr._T._.T.type;
			p->eKind=ARRAY_TYPE_;
			p->_.Array.nNumElems = n; //deveria ser p->_.Array.nNumElems = n;
			p->_.Array.pElemType = t;	
			break;

		//figura 6.9
		case DT_ALIAS_RULE:
			p=attr._IDD._.IDT.obj;// deveria ser p=IDD.obj;
			t=attr._T._.T.type;
			p->eKind=ALIAS_TYPE_;
			p->attr._.Alias.pBaseType=t;
			break;
		
		//figura 6.10 
		case DC_LI_RULE:
			p=attr._LI._.LI.list;
			t=attr._T._.T.type;
			while( p!=nullptr && p->eKind == NO_KIND_DEF_){
				p->eKind=FIELD_;
				p->_.Field.pType=t;
				p=p->pNext;
			}
			attr._DC._.DC.list = attr._LI._.LI.list; // DC.list = LI.list
			break;

		case DC_REC_RULE:
			p=attr._LI._.LI.list;
			t=attr._T._.T.type;
			while( p!=nullptr && p->eKind == NO_KIND_DEF_){
				p->eKind=FIELD_;
				p->_.Field.pType=t;
				p=p->pNext;
			}
			attr._DC0._.DC0.list = attr._DC1._.DC1.list; // DC0.list = DC1.list
			break;

		//figura6.11
		case DT_STRUCT_RULE:
			p=attr._IDD._.IDT.obj;
			p->eKind=STRUCT_TYPE_;
			p->_.Struct.pFields=attr._DC._.DC.list;
			endBlock(currentLevel);
			break;

		case NB_RULE:
			newBlock(currentLevel);
			break;

		//figura 6.12
		case LP_IDD_RULE:
			p=attr._IDD._.IDT.obj;
			t=attr._T._.T.type;
			p->eKind = PARAM_;
			p->_.Param.pType=t;
			attr._LP._.LP.list=p;
			break;

		case LP_REC_RULE:
			p=attr._IDD._.IDT.obj;
			t=attr._T._.T.type;
			p->eKind = PARAM_;
			p->_.Param.pType=t;
			attr._LP0._.LP0.list=attr._LP1._.LP1.list;
			break;

		//figura 6.13
		case MF_RULE:
			// T = TopSem(0);  WTFFFFFFFFF
			//LP = TopSem(-1);
			//NB = TopSem(-2);
			//IDD = TopSem(-3);
			f=attr._IDD._.IDT.obj;
			f->eKind= FUNCTION_;
			f->_.Function.pParams = attr._T._.T.type;
			f->_.Function.pParams = attr._LP._.LP.list;

		case DF_RULE:
			endBlock(currentLevel);
			break;

		//figura 6.14
		case S_BLOCK_RULE:
			endBlock(currentLevel);
			break;

		//figura 6.15
		case S_IF_RULE:
			t=attr._E._.E.type;
			if(!checkTypes(t,pBool))
				errorRoutines::throwError(ERR_BOOL_TYPE_EXPECTED);
			break;

		case S_IF_ELSE_RULE:
			t=attr._E._.E.type;
			if(!checkTypes(t,pBool))
				errorRoutines::throwError(ERR_BOOL_TYPE_EXPECTED);
			break;

		case S_WHILE_RULE:
			t=attr._E._.E.type;
			if(!checkTypes(t,pBool))
				errorRoutines::throwError(ERR_BOOL_TYPE_EXPECTED);
			break;

		case S_DO_WHILE_RULE:
			t=attr._E._.E.type;
			if(!checkTypes(t,pBool))
				errorRoutines::throwError(ERR_BOOL_TYPE_EXPECTED);
			break;

		case  S_LV_EQUALS_E_RULE:
			t1=attr._LV._.LV.type;
			t2=attr._E._.E.type;
			if(!checkTypes(t1,t2))
				errorRoutines::throwError(ERR_TYPE_MISMATCH);
			break;
		//figura 6.18
		case E_AND_RULE:
			if( !CheckTypes( attr._E1._.E.type, pBool ) )
				errorRoutines::throwError( ERR_BOOL_TYPE_EXPECTED );
			if( !CheckTypes( attr._L._.L.type, pBool ) )
				errorRoutines::throwError( ERR_BOOL_TYPE_EXPECTED );
			attr._E0._.E0.type = pBool;
			break;

		case E_OR_RULE:
			if( !CheckTypes( attr._E1._.E.type, pBool ) )
				errorRoutines::throwError( ERR_BOOL_TYPE_EXPECTED );
			if( !CheckTypes( attr._L._.L.type, pBool ) )
				errorRoutines::throwError( ERR_BOOL_TYPE_EXPECTED );
			attr._E0._.E0.type = pBool;
			break;

		case E_L_RULE:
			attr._E._.E.type=attr._L._.L.type; //E.type=L.Type;
			break;

		//figura 6.19
		case L_LESSTHAN_RULE:
			if( !CheckTypes( attr._L1._.L1.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L0.type = pBool;
			break;
		case L_GREATHERTHAN_RULE:
			if( !CheckTypes( attr._L1._.L1.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L0.type = pBool;
			break;

		case L_LESSOREQUAL_RULE:
			if( !CheckTypes( attr._L1._.L1.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L0.type = pBool;
			break;

		case L_GREATHEROREQUAL_RULE:
			if( !CheckTypes( attr._L1._.L1.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L0.type = pBool;
			break;

		case L_EQUALEQUAL_RULE:
			if( !CheckTypes( attr._L1._.L1.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L0.type = pBool;
			break;

		case L_NOTEQUAL_RULE:
			if( !CheckTypes( attr._L1._.L1.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L0.type = pBool;
			break;

		case L_R_RULE:
			attr._L._.L.type = attr._R._.R.type;
			break;

		//figura 6.20
		case R_PLUS_RULE:
			if( !CheckTypes( attr._R1._.R1.type, attr._Y._.Y.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			if( !CheckTypes( attr._R1._.R1.type, pInteger ) && !CheckTypes( attr._R1._.R1.type, pString ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._R0._.R0.type=attr._R1._.R1.type;
			break;
		case R_MINUS_RULE:
			if( !CheckTypes( attr._R1._.R1.type, attr._Y._.Y.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			if( !CheckTypes( attr._R1._.R1.type, pInteger ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._R0._.R0.type=attr._R1._.R1.type;
			break;
		case R_Y_RULE:
			attr._R._.R.type=attr._Y._.Y.type;
			break;
		case Y_TIMES_RULE:
			if( !CheckTypes( attr._Y1._.Y1.type, attr._F._.F.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			if( !CheckTypes( attr._Y1._.Y1.type, pInteger ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._Y0._.Y0.type=attr._Y1._.Y1.type;
			break;
		case Y_DIVIDE_RULE:
			if( !CheckTypes( attr._Y1._.Y1.type, attr._F._.F.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			if( !CheckTypes( attr._Y1._.Y1.type, pInteger ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._Y0._.Y0.type=attr._Y1._.Y1.type;
			break;
		case Y_F_RULE:
			attr._Y._.Y.type=attr._F._.F.type;
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
