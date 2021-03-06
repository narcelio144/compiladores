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

int newLabel(void){
	static int labelNo = 0;
	return labelNo++;
}

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
	cout << "Rule: " << rule << endl;
	static int name,n,l,l1,l2;
	static int currentLevel = 0;
	static listObject *p,*t,*f,*curFunction,*t1,*t2;
	static bool attributesInitialized = false;
	static attributes attr;
	if (!attributesInitialized)
		initializeAttribuites(attr,attributesInitialized);

	switch (rule){
		case IDD_RULE:
			name = tokenSecundario;
      		attr._IDD._.IDT.name = name;
      		attr._IDD.nont = IDD;
      		if((p = search(name,currentLevel)) != nullptr){
      			errorRoutines::throwError(ERR_REDCL);
      		} else{
			    p = define(name,currentLevel);
      		}
			p->eKind = NO_KIND_DEF_;
			attr._IDD._.IDT.obj = p;
			semanticStack.push(attr._IDD);
			break;

		case IDU_RULE:
			name = tokenSecundario;
			attr._IDU._.IDT.name = name;
			attr._IDU.nont = IDU;
			if((p = find(name,currentLevel)) == nullptr){
				errorRoutines::throwError(ERR_NO_DECL);
				p = define(name,currentLevel);
			}
			attr._IDU._.IDT.obj = p;

			semanticStack.push(attr._IDU);
			break;

		case IDT_RULE:
			name = tokenSecundario;
			attr._IDT.nont = IDT;
			attr._IDT._.IDT.name = name;
			attr._IDT._.IDT.obj = nullptr;
			semanticStack.push(attr._IDT);
			break;

		case T_INTEGER_RULE:
			attr._T._.T.type = pInt;
			attr._T.nont = T;
			attr._T.nSize=1;
			semanticStack.push(attr._T);
			break;
		case T_CHAR_RULE:
			attr._T._.T.type = pChar;
			attr._T.nont = T;
			attr._T.nSize=1;
			semanticStack.push(attr._T);
			break;;
		case T_STRINGVAL_RULE:
			attr._T._.T.type = pString;
			attr._T.nont = T;
			attr._T.nSize=1;
			semanticStack.push(attr._T);
			break;
		case T_BOOLEAN_RULE:
			attr._T._.T.type = pBool;
			attr._T.nont = T;
			attr._T.nSize=1;
			semanticStack.push(attr._T);
			break;

		

		// Figura 6.5
		case T_IDU_RULE:
			attr._IDU = semanticStack.top();
			p= attr._IDU._.IDT.obj;
			semanticStack.pop();
			
			if (IS_TYPE_KIND(p->eKind) || p->eKind == UNIVERSAL_){
				attr._T._.T.type = p;
				if(p->eKind == ALIAS_TYPE_){
					attr._T.nSize = p->_.Alias.nSize;
				}
				else if(p->eKind == ARRAY_TYPE_){
					attr._T.nSize = p->_.Array.nSize;
				}
				else if(p->eKind == STRUCT_TYPE_){
					attr._T.nSize = p->_.Struct.nSize;
				}
			} else {
				attr._T._.T.type = pUniversal;
				attr._T.nSize=0;
				errorRoutines::throwError(ERR_TYPE_EXPECTED);
			}
			attr._T.nont=T;
			semanticStack.push(attr._T);
			break;
		
		// Figura 6.6
		case LI_IDD_RULE:
			attr._IDD = semanticStack.top();
			attr._LI._.LI.list = attr._IDD._.IDT.obj;
			attr._LI.nont = LI;
			semanticStack.pop();
			semanticStack.push(attr._LI);
			break;

		case LI_REC_RULE:
			attr._IDD = semanticStack.top();
			semanticStack.pop();
			attr._LI1 = semanticStack.top();
			semanticStack.pop();
			attr._LI0._.LI.list = attr._LI1._.LI.list;
			attr._LI0.nont = LI;
			semanticStack.push(attr._LI0);
			break;
		
		case DV_RULE:
			attr._T = semanticStack.top();
			t=attr._T._.T.type;
			semanticStack.pop();
			attr._LI = semanticStack.top();
			semanticStack.pop();
			p=attr._LI._.LI.list;
			n = curFunction->_.Function.nVars;

			while(p!=nullptr && p->eKind == NO_KIND_DEF_){
				p->eKind=VAR_;
				p->_.Var.pType = t;
				p->_.Var.nSize = attr._T.nSize;
				p->_.Var.nIndex = n;
				n += attr._T.nSize;
				p=p->pNext;
			}

			curFunction->_.Function.nVars = n;
			break;
		
		//figura 6.7
		case TRU_TRUE_RULE:
			attr._TRU.nont = TRU;
			attr._TRU._.TRU.type = pBool;
			attr._TRU._.TRU.val = true;
			semanticStack.push(attr._TRU);
			break;

		case FALS_FALSE_USE:
			attr._FALS.nont = FALS;
			attr._FALS._.FALS.type = pBool;
			attr._FALS._.FALS.val = false;
			semanticStack.push(attr._FALS);
			break;

		case CH_CHARACTER_RULE:
			attr._CH.nont = CH;
			attr._CH._.CH.type = pChar;
			attr._CH._.CH.pos = tokenSecundario;
			attr._CH._.CH.val = getCharConst(tokenSecundario);
			semanticStack.push(attr._CH);
			break;
		
		case ST_STRINGVAL_RULE:
			attr._ST.nont = ST;
			attr._ST._.ST.type = pString;
			attr._ST._.ST.pos = tokenSecundario;
			attr._ST._.ST.val = getStringConst(tokenSecundario);
			semanticStack.push(attr._ST);
			break;

		case NU_NUMERAL_RULE:
			attr._NU.nont = NU;
			attr._NU._.NU.type = pString;
			attr._NU._.NU.pos = tokenSecundario;
			attr._NU._.NU.val = getIntConst(tokenSecundario);
			semanticStack.push(attr._NU);
			break;

		//figura 6.8
		case DT_ARRAY_RULE:
			attr._T = semanticStack.top();
			semanticStack.pop();
			
			attr._NU = semanticStack.top();
			semanticStack.pop();
			
			attr._IDD = semanticStack.top();
			semanticStack.pop();

			p=attr._IDD._.IDT.obj; 
			n=attr._NU._.NU.val;
			t=attr._T._.T.type;
			
			p->eKind=ARRAY_TYPE_;
			p->_.Array.nNumElems = n;
			p->_.Array.pElemType = t;
			p->_.Array.nSize = n * attr._T.nSize;
			break;

		//figura 6.9
		case DT_ALIAS_RULE:
			attr._T = semanticStack.top();
			semanticStack.pop();
			attr._IDD = semanticStack.top();
			semanticStack.pop();

			p=attr._IDD._.IDT.obj;
			t=attr._T._.T.type;

			p->eKind=ALIAS_TYPE_;
			p->_.Alias.pBaseType=t;
			p->_.Alias.nSize = attr._T.nSize;
			break;
		

		//figura 6.10 
		case DC_LI_RULE:
			attr._T = semanticStack.top();
			semanticStack.pop();
			attr._LI = semanticStack.top();
			semanticStack.pop();
			p=attr._LI._.LI.list;
			t=attr._T._.T.type;
			n=0;
			while( p!=nullptr && p->eKind == NO_KIND_DEF_){
				p->eKind=FIELD_;
				p->_.Field.pType=t;
				p->_.Field.nIndex=n;
				n= n + attr._T.nSize;
				p=p->pNext;
			}
			attr._DC._.DC.list = attr._LI._.LI.list; 
			attr._DC.nSize = n;
			attr._DC.nont = DC;
			semanticStack.push(attr._DC);
			break;

		case DC_REC_RULE:
			attr._T = semanticStack.top();
			semanticStack.pop();
			attr._LI = semanticStack.top();
			semanticStack.pop();
			attr._DC1 = semanticStack.top();
			semanticStack.pop();
			p=attr._LI._.LI.list;
			t=attr._T._.T.type;
			n=attr._DC1.nSize;

			while( p!=nullptr && p->eKind == NO_KIND_DEF_){
				p->eKind=FIELD_;
				p->_.Field.pType=t;
				p->_.Field.nIndex=n;
				p->_.Field.nSize = attr._T.nSize;
				n= n + attr._T.nSize;

				p=p->pNext;
			}
			attr._DC0._.DC.list = attr._DC1._.DC.list;
			attr._DC0.nSize = n;
			attr._DC0.nont = DC;
			semanticStack.push(attr._DC0);
			break;

		//figura6.11
		case DT_STRUCT_RULE:
			attr._DC = semanticStack.top();
			semanticStack.pop();
			attr._IDD = semanticStack.top();
			semanticStack.pop();

			p=attr._IDD._.IDT.obj;
			p->eKind=STRUCT_TYPE_;
			p->_.Struct.pFields=attr._DC._.DC.list;
			p->_.Struct.nSize = attr._DC.nSize;
			endBlock(currentLevel);
			break;

		case NB_RULE:
			newBlock(currentLevel);
			break;

		//figura 6.12
		case LP_IDD_RULE:
			attr._T = semanticStack.top();
			semanticStack.pop();
			attr._IDD = semanticStack.top();
			semanticStack.pop();

			p=attr._IDD._.IDT.obj;
			t=attr._T._.T.type;
			p->eKind = PARAM_;
			p->_.Param.pType=t;
			p->_.Param.nIndex = 0;
			p->_.Struct.nSize = attr._T.nSize;
			attr._LP._.LP.list=p;
			attr._LP.nSize=attr._T.nSize;
			attr._LP.nSize = LP;
			semanticStack.push(attr._LP);
			break;

		case LP_REC_RULE:
			attr._T = semanticStack.top();
			semanticStack.pop();
			attr._IDD = semanticStack.top();
			semanticStack.pop();
			attr._LP1 = semanticStack.top();
			semanticStack.pop();
			
			p = attr._IDD._.IDT.obj;
			t = attr._T._.T.type;
			n = attr._LP1.nSize;

			p->eKind = PARAM_;
			p->_.Param.pType=t;
			p->_.Param.nIndex = n;
			p->_.Struct.nSize = attr._T.nSize;

			attr._LP0._.LP.list=attr._LP1._.LP.list;
			attr._LP0.nSize = n + attr._T.nSize;
			attr._LP0.nont = LP;
			semanticStack.push(attr._LP0);
			break;

		//figura 6.13
		case MF_RULE:
			attr._T = semanticStack.top();
			semanticStack.pop(); 
			attr._LP = semanticStack.top();
			semanticStack.pop();  
			attr._IDD = semanticStack.top();
			semanticStack.pop();

			f=attr._IDD._.IDT.obj;
			f->eKind= FUNCTION_;
			f->_.Function.pRetType = attr._T._.T.type;
			f->_.Function.pParams = attr._T._.T.type;
			f->_.Function.pParams = attr._LP._.LP.list;
			f->_.Function.nParams = attr._LP.nSize;
			f->_.Function.nVars = attr._LP.nSize;

			curFunction = f;
			break;

		case DF_RULE:
			endBlock(currentLevel);
			break;

		//figura 6.14
		case S_BLOCK_RULE:
			endBlock(currentLevel);
			break;

		case S_RETURN_RULE:
			attr._E=semanticStack.top();
			semanticStack.pop();

			if(!checkTypes(curFunction->_.Function.pRetType,attr._E._.E.type)){
               errorRoutines::throwError(ERR_RETURN_TYPE_MISMATCH);
            }

            break;

        case MT_RULE:
        	l = newLabel();
        	attr._MT.label = l;
        	attr._MT.nont = MT;
			semanticStack.push(attr._MT);
			break;
			
		case ME_RULE:
			attr._MT = semanticStack.top();
            l1 = attr._MT._.MT.label;
            l2 = newLabel();
            attr._ME._.ME.label = l2;
            attr._ME.nont = ME;
			semanticStack.push(attr._ME);
			break;

		case MW_RULE:
			l = newLabel();
			attr._MW._.MW.label = l;
			semanticStack.push(attr._MW);
			break;
		// case ME_RULE:
  //           
		//figura 6.15
		case S_IF_RULE:
			attr._MT = semanticStack.top();
			semanticStack.pop();
			attr._E=semanticStack.top();
			semanticStack.pop();

			t=attr._E._.E.type;
			if(!checkTypes(t,pBool))
				errorRoutines::throwError(ERR_BOOL_TYPE_EXPECTED);
			break;


		case S_IF_ELSE_RULE:
			attr._ME=semanticStack.top();
			semanticStack.pop();
			attr._MT = semanticStack.top();
			semanticStack.pop();
			attr._E=semanticStack.top();
			semanticStack.pop();


			l = attr._ME._.ME.label;
			
			t=attr._E._.E.type;
			if(!checkTypes(t,pBool))
				errorRoutines::throwError(ERR_BOOL_TYPE_EXPECTED);
			break;

		case S_WHILE_RULE:
			attr._MT = semanticStack.top();
			semanticStack.pop();
			attr._E=semanticStack.top();
			semanticStack.pop();
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
			attr._L = semanticStack.top();
			semanticStack.pop();
			attr._E1 = semanticStack.top();
			semanticStack.pop();

			if( !checkTypes( attr._E1._.E.type, pBool ) )
				errorRoutines::throwError( ERR_BOOL_TYPE_EXPECTED );
			if( !checkTypes( attr._L._.L.type, pBool ) )
				errorRoutines::throwError( ERR_BOOL_TYPE_EXPECTED );
			attr._E0._.E.type = pBool;
			attr._E0.nont = E;
			semanticStack.push(attr._E0);
			break;

		case E_OR_RULE:
			attr._L=semanticStack.top();
			semanticStack.pop();
			attr._E1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._E1._.E.type, pBool ) )
				errorRoutines::throwError( ERR_BOOL_TYPE_EXPECTED );
			if( !checkTypes( attr._L._.L.type, pBool ) )
				errorRoutines::throwError( ERR_BOOL_TYPE_EXPECTED );
			attr._E0._.E.type = pBool;
			attr._E0.nont=E;
			semanticStack.push(attr._E0);
			break;

		case E_L_RULE:
			attr._L=semanticStack.top();
			semanticStack.pop();
			attr._E._.E.type=attr._L._.L.type; 
			attr._E.nont = E;
			semanticStack.push(attr._E);
			break;

		//figura 6.19
		case L_LESSTHAN_RULE:
			attr._R=semanticStack.top();
			semanticStack.pop();
			attr._L1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._L1._.L.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L.type = pBool;
			attr._L0.nont = L;
			semanticStack.push(attr._L0);
			break;
		case L_GREATHERTHAN_RULE:
			attr._R=semanticStack.top();
			semanticStack.pop();
			attr._L1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._L1._.L.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L.type = pBool;
			attr._L0.nont = L;
			semanticStack.push(attr._L0);
			break;

		case L_LESSOREQUAL_RULE:
			attr._R=semanticStack.top();
			semanticStack.pop();
			attr._L1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._L1._.L.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L.type = pBool;
			attr._L0.nont = L;
			semanticStack.push(attr._L0);
			break;

		case L_GREATHEROREQUAL_RULE:
			attr._R=semanticStack.top();
			semanticStack.pop();
			attr._L1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._L1._.L.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L.type = pBool;
			attr._L0.nont = L;
			semanticStack.push(attr._L0);
			break;

		case L_EQUALEQUAL_RULE:
			attr._R=semanticStack.top();
			semanticStack.pop();
			attr._L1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._L1._.L.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L.type = pBool;
			attr._L0.nont = L;
			semanticStack.push(attr._L0);
			break;

		case L_NOTEQUAL_RULE:
			attr._R=semanticStack.top();
			semanticStack.pop();
			attr._L1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._L1._.L.type, attr._R._.R.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			attr._L0._.L.type = pBool;
			attr._L0.nont = L;
			semanticStack.push(attr._L0);
			break;

		case L_R_RULE:
			attr._R=semanticStack.top();
			semanticStack.pop();
			attr._L._.L.type = attr._R._.R.type;
			attr._L.nont = L;
			semanticStack.push(attr._L);
			break;

		//figura 6.20
		case R_PLUS_RULE:
			attr._Y=semanticStack.top();
			semanticStack.pop();
			attr._R1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._R1._.R.type, attr._Y._.Y.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			if( !checkTypes( attr._R1._.R.type, pInt ) && !checkTypes( attr._R1._.R.type, pString ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._R0._.R.type=attr._R1._.R.type;
			attr._R0.nont = R;
			semanticStack.push(attr._R0);
			break;
		case R_MINUS_RULE:
			attr._Y=semanticStack.top();
			semanticStack.pop();
			attr._R1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._R1._.R.type, attr._Y._.Y.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			if( !checkTypes( attr._R1._.R.type, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._R0._.R.type=attr._R1._.R.type;
			attr._R0.nont = R;
			semanticStack.push(attr._R0);
			break;
		case R_Y_RULE:
			attr._Y=semanticStack.top();
			semanticStack.pop();
			attr._R._.R.type=attr._Y._.Y.type;
			attr._R.nont = R;
			semanticStack.push(attr._R);
			break;
		case Y_TIMES_RULE:
			attr._F=semanticStack.top();
			semanticStack.pop();
			attr._Y1=semanticStack.top();
			semanticStack.pop();
			if( !checkTypes( attr._Y1._.Y.type, attr._F._.F.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			if( !checkTypes( attr._Y1._.Y.type, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._Y0._.Y.type=attr._Y1._.Y.type;
			attr._Y0.nont= Y;
			semanticStack.push(attr._Y0);
			break;
		case Y_DIVIDE_RULE:
			attr._F=semanticStack.top();
			semanticStack.pop();
			attr._Y1=semanticStack.top();
			semanticStack.pop();

			if( !checkTypes( attr._Y1._.Y.type, attr._F._.F.type ) )
				errorRoutines::throwError( ERR_TYPE_MISMATCH );
			if( !checkTypes( attr._Y1._.Y.type, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._Y0._.Y.type=attr._Y1._.Y.type;
			attr._Y0.nont= Y;
			semanticStack.push(attr._Y0);
			break;
		case Y_F_RULE:
			attr._F=semanticStack.top();
			semanticStack.pop();
			attr._Y._.Y.type=attr._F._.F.type;
			attr._Y.nont= Y;
			semanticStack.push(attr._Y);
			break;

		//figura 6.21
		case F_LV_RULE:
			attr._LV=semanticStack.top();
			semanticStack.pop();
			attr._F._.F.type= attr._LV._.LV.type;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;


		case F_PLUSPLUS_LV_RULE:
			attr._LV=semanticStack.top();
			semanticStack.pop();

			t= attr._LV._.LV.type;
			if( !checkTypes( t, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._F._.F.type=pInt;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_MINUSMINUS_LV_RULE:
			attr._LV=semanticStack.top();
			semanticStack.pop();
			t= attr._LV._.LV.type;
			if( !checkTypes( t, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._F._.F.type=pInt;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_LV_PLUSPLUS_RULE:
			attr._LV=semanticStack.top();
			semanticStack.pop();
			t= attr._LV._.LV.type;
			if( !checkTypes( t, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._F._.F.type=pInt;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_LV_MINUSMINUS_RULE:
			attr._LV=semanticStack.top();
			semanticStack.pop();
			t= attr._LV._.LV.type;
			if( !checkTypes( t, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._F._.F.type=pInt;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_PARENTHESIS_RULE:
			attr._E=semanticStack.top();
			semanticStack.pop();
			attr._F._.F.type= attr._E._.E.type;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_MINUSF_RULE:
			attr._F1=semanticStack.top();
			semanticStack.pop();
			t= attr._F1._.F.type;
			if( !checkTypes( t, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._F0._.F.type=t;
			attr._F0.nont= F;
			semanticStack.push(attr._F0);
			break;

		case F_NOTF_RULE:
			attr._F1=semanticStack.top();
			semanticStack.pop();

			t= attr._F1._.F.type;
			if( !checkTypes( t, pInt ))
				errorRoutines::throwError( ERR_INVALID_TYPE );
			attr._F0._.F.type=t;	
			attr._F0.nont= F;
			semanticStack.push(attr._F0);
			break;

		case F_TRU_RULE:
			attr._TRU=semanticStack.top();
			semanticStack.pop();

			attr._F._.F.type=pBool;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_FALS_RULE:
			attr._FALS=semanticStack.top();
			semanticStack.pop();
			attr._F._.F.type=pBool;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_CH_RULE:
			attr._CH=semanticStack.top();
			semanticStack.pop();
			attr._F._.F.type=pChar;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_ST_RULE:
			attr._ST=semanticStack.top();
			semanticStack.pop();
			attr._F._.F.type=pString;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		case F_NU_RULE:
			attr._NU=semanticStack.top();
			semanticStack.pop();
			attr._F._.F.type=pInt;
			attr._F.nont= F;
			semanticStack.push(attr._F);
			break;

		//figura 6.22
		case LV_REC_RULE:
			attr._IDT=semanticStack.top();
			semanticStack.pop();
			attr._LV1=semanticStack.top();
			semanticStack.pop();

			t=attr._LV1._.LV.type;
			if( t->eKind != STRUCT_TYPE_ ){
				if( t->eKind != UNIVERSAL_ )
					errorRoutines::throwError( ERR_KIND_NOT_STRUCT );
				attr._LV0._.LV.type = pUniversal;
			}
			else{
				p = t->_.Struct.pFields;
				while( p!= NULL ){
					if( p->nName == attr._IDT._.IDT.name )	//ID.name esta onde???
						break;
				p = p->pNext;
				}
				if( p == NULL ){
					errorRoutines::throwError( ERR_FIELD_NOT_DECL );
					attr._LV0._.LV.type = pUniversal;
				}
				else{
					attr._LV0._.LV.type = p->_.Field.pType;
				}
			}
			attr._LV0.nont = LV;
			semanticStack.push(attr._LV0);
			break;

		case LV_SQUARES_E_USE:
			attr._E = semanticStack.top();
			semanticStack.pop();
			attr._LV1 = semanticStack.top();
			semanticStack.pop();
			t = attr._LV1._.LV.type;
			if( t == pString ){
				attr._LV0._.LV.type = pChar;
			} 
			else if( t->eKind != ARRAY_TYPE_ ){
				if( t->eKind != UNIVERSAL_ )
					errorRoutines::throwError( ERR_KIND_NOT_ARRAY );
				attr._LV0._.LV.type = pUniversal;
			} 
			else {
				attr._LV0._.LV.type = t->_.Array.pElemType;
			}
			if( !checkTypes( attr._E._.E.type, pInt ) )
				errorRoutines::throwError( ERR_INVALID_INDEX_TYPE );
			semanticStack.push(attr._LV0);

			break;

		case LV_IDU_RULE:
			attr._IDU = semanticStack.top();
			semanticStack.pop();
			p = attr._IDU._.IDT.obj;
			if( p->eKind != VAR_ && p->eKind != PARAM_ ){
				if( p->eKind != UNIVERSAL_ )
					errorRoutines::throwError( ERR_KIND_NOT_VAR );
				attr._LV._.LV.type = pUniversal;
			}
			else{
				attr._LV._.LV.type = p->_.Var.pType;
				attr._LV._.LV.type->_.Type.nSize = p->_.Var.nSize;
			}
			semanticStack.push(attr._LV);
			break;
		//figura 6.23

		case MC_RULE:
			attr._IDU = semanticStack.top(); //nao tenho certeza se eh assim msm
			f = attr._IDU._.IDT.obj;

			if( f->eKind != FUNCTION_ ){
				errorRoutines::throwError( ERR_KIND_NOT_FUNCTION );
				attr._MC._.MC.type = pUniversal;
				attr._MC._.MC.param = NULL;
				attr._MC._.MC.err = true;
			}
			else{
				attr._MC._.MC.type = f->_.Function.pRetType;
				attr._MC._.MC.param = f->_.Function.pParams;
				attr._MC._.MC.err = false;
			}
			attr._MC.nont = MC;
			semanticStack.push(attr._MC);
			break;

		case LE_E_RULE:
			attr._E = semanticStack.top(); //nao tenho certeza se eh assim msm
			semanticStack.pop();
			attr._MC = semanticStack.top(); // idem sem certeza
			attr._LE._.LE.param = NULL;
			attr._LE._.LE.err = attr._MC._.MC.err;
			n = 1;
			if(!attr._MC._.MC.err){
				p = attr._MC._.MC.param;
				if( p == NULL ){
					errorRoutines::throwError(ERR_TOO_MANY_ARGS);
					attr._LE._.LE.err = true;
				}
				else{
					if( !checkTypes(p->_.Param.pType,attr._E._.E.type ) ){
						errorRoutines::throwError( ERR_PARAM_TYPE );
					}
					attr._LE._.LE.param = p->pNext;
					attr._LE._.LE.n = n+1;
				}
			}
			semanticStack.push(attr._LE);
			break;

		case LE_REC_RULE:
			attr._E = semanticStack.top();
			semanticStack.pop();
			attr._LE1 = semanticStack.top();
			semanticStack.pop();
			attr._LE0._.LE.param = nullptr;
			attr._LE0._.LE.err = attr._LE1._.LE.err;
			n = attr._LE1._.LE.n;
			if( !attr._LE1._.LE.err ){
				p = attr._LE._.LE.param;
				if( p == NULL ){
						errorRoutines::throwError(ERR_TOO_MANY_ARGS);
						attr._LE0._.LE.err = true;
				}
				else{
				if( !checkTypes(p->_.Param.pType,attr._E._.E.type ) ){
					errorRoutines::throwError(ERR_PARAM_TYPE);
				}
				attr._LE0._.LE.param = p->pNext;
				attr._LE0._.LE.n = n+1;
				}
			}
			semanticStack.push(attr._LE0);
			break;

		case F_FUNCTIONUSE_RULE:
			attr._LE = semanticStack.top();
			semanticStack.pop();
			attr._MC = semanticStack.top();
			semanticStack.pop();
			attr._IDU = semanticStack.top();
			semanticStack.pop();

			attr._F._.F.type = attr._MC._.MC.type;
			if(!attr._MC._.MC.err){
				if( attr._LE._.LE.param != NULL )
					errorRoutines::throwError( ERR_TOO_FEW_ARGS );
			}
			semanticStack.push(attr._F);
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
