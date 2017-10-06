#ifndef DEFINITIONS
#define DEFINITIONS

#define IDT_RULE 74
#define IDU_RULE 76
#define IDD_RULE  77
#define NB_RULE 78
#define DF_RULE 15
#define DT_STRUCT_RULE 11
#define NF_RULE 79

#define IS_TYPE_KIND(k) ((k)==ARRAY_TYPE_ || \
													(k)==STRUCT_TYPE_|| \
													(k)==ALIAS_TYPE_ || \
													(k)==SCALAR_TYPE_)


#define IS_SHIFT(p) ((p)>0)
#define IS_REDUCTION(p) ((p)<0)
#define RULE(p) (-(p))

#define MAX_ACTION_TABLE_SIZE 300
#define MAX_NEST_LEVEL 25
#define MAX_ID_LEN 20
#define MAX_CONST 200
#define MAX_NUM_LEN 20
#define MAX_STR_LEN 200

//Enumeração para os tokens da linguagem
typedef enum {
		// Palavras reservadas
		ARRAY, BOOLEAN, BREAK, CHAR, CONTINUE, DO,
		ELSE, FALSE, FUNCTION, IF, INTEGER, OF, RETURN,
		STRING, STRUCT, TRUE, TYPE, VAR, WHILE,
		// Símbolos
		COLON, SEMI_COLON, COMMA, EQUALS, LEFT_SQUARE,
		RIGHT_SQUARE, LEFT_BRACES, RIGHT_BRACES,
		LEFT_PARENTHESIS, RIGHT_PARENTHESIS, AND, OR,
		LESS_THAN, GREATER_THAN, LESS_OR_EQUAL, GREATER_OR_EQUAL,
		NOT_EQUAL, EQUAL_EQUAL, PLUS, PLUS_PLUS,
		MINUS, MINUS_MINUS, TIMES, DIVIDE, DOT, NOT,
		// Token Regulares
		CHARACTER, NUMERAL, STRINGVAL, ID,
    //EOF
    ENDFILE,
		// Token Desconhecido
		UNKNOWN
} t_token;

typedef enum{
    CHR,INT,STR
} const_type;

typedef struct{
	const_type type; // 0-CHR, 1-INT, 2-STR
	union
	{
        char   cVal;
        int    nVal;
        char * sVal;
	} _;
} t_const;

//Estrutura retornada pela função nextToken contendo o token e, se for o caso, o token secundário
typedef struct{
    t_token token;
    int tokenSecundario;
    int constPosition;
} token_struct;

#define ACC (MAX_ACTION_TABLE_SIZE+1)
typedef enum{
	 P=1,LDE,DE,DF,DT,DC,LI,DV,LP,B,LDV,LS,S,E,L,R,Y,F,LE,LV,T,TRU,FALS,CH,ST,NU,IDT,IDU,IDD,NF,NB,MA,MC,ME,MF,MT,MW
} t_nont;

typedef enum {
  NO_KIND_DEF_=-1, VAR_, PARAM_, FUNCTION_, FIELD_, ARRAY_TYPE_, STRUCT_TYPE_, ALIAS_TYPE_, SCALAR_TYPE_ , UNIVERSAL_
} t_kind;

typedef enum {
    ERR_REDCL,ERR_NO_DECL,ERR_TYPE_EXPECTED,ERR_BOOL_TYPE_EXPECTED,ERR_TYPE_MISMATCH,ERR_INVALID_TYPE,ERR_KIND_NOT_STRUCT,ERR_FIELD_NOT_DECL,ERR_KIND_NOT_ARRAY,ERR_INVALID_INDEX_TYPE,ERR_KIND_NOT_VAR,ERR_KIND_NOT_FUNCTION,ERR_TOO_MANY_ARGS,ERR_PARAM_TYPE,ERR_TOO_FEW_ARGS,ERR_RETURN_TYPE_MISMATCH
} error_code;

typedef struct listObject{
    int nName;
    struct listObject *pNext;
    t_kind eKind;

    union {
        struct {
            struct listObject *pType;
            int nIndex;
            int nSize;
        } Var, Param, Field;
        struct {
            struct listObject *pRetType;
            struct listObject *pParams;
            int nIndex;
            int nParams;
            int nVars;
        } Function;
        struct {
            struct listObject *pElemType; int nNumElems;
            int nSize;
        } Array;
        struct {
            struct listObject *pFields;
            int nSize;
        } Struct;
        struct {
            struct listObject *pBaseType;
            int nSize;
        } Alias,Type;
    }_;

} listObject;

typedef struct {
    t_nont nont;
    int nSize;
    union {
        struct {
            listObject* obj;
            int name;}
        IDT;
        struct {
            listObject* type;
        } T,E,L,R,Y,F,LV;
        struct {
            listObject* type;
            listObject* param;
            bool err;
        } MC;
        struct {
            int label;
        } MT,ME,MW,MA;
        struct{
            listObject* type;
            listObject* param;
            bool err;
            int n;
        } LE;
        struct {
            listObject* list;
        } LI,DC,LP;
        struct {
            listObject* type;
            bool val;
        } TRU,FALS;
        struct {
            listObject* type;
            int pos;
            char val;
        } CH;
        struct {
            listObject* type;
            char* val;
            int pos;
        } ST;
        struct {
            listObject* type;
            int val;
            int pos;
        } NU;
    }_;
} t_attrib;

#endif
