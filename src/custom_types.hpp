#ifndef CUSTOM_TYPES
#define CUSTOM_TYPES

#define P_RULE 0
#define LDE_REC_RULE 1
#define LDE_RULE 2
#define DE_DF_RULE 3
#define DE_DT_RULE 4
#define T_INTEGER_RULE 5
#define T_CHAR_RULE 6
#define T_BOOLEAN_RULE 7
#define T_STRINGVAL_RULE 8
#define T_IDU_RULE 9
#define DT_ARRAY_RULE 10
#define DT_STRUCT_RULE 11
#define DT_ALIAS_RULE 12
#define DC_REC_RULE 13
#define DC_LI_RULE 14
#define DF_RULE 15
#define LP_REC_RULE 16
#define LP_IDD_RULE 17
#define LP_EMPTY_RULE 18
#define B_RULE 19
#define LDV_REC_RULE 20
#define LDV_DV_RULE 21
#define LDV_EMPTY_RULE 22
#define LS_REC_RULE 23
#define LS_S_RULE 24
#define DV_RULE 25
#define LI_REC_RULE 26
#define LI_IDD_RULE 27
#define S_IF_RULE 28
#define S_IF_ELSE_RULE 29
#define S_WHILE_RULE 30
#define S_DO_WHILE_RULE 31
#define S_BLOCK_RULE 32
#define S_LV_EQUALS_E_RULE 33
#define S_BREAK_RULE 34
#define S_CONTINUE_RULE 35
#define S_RETURN_RULE 36
#define E_AND_RULE 37
#define E_OR_RULE 38
#define E_L_RULE 39
#define L_LESSTHAN_RULE 40
#define L_GREATHERTHAN_RULE 41
#define L_LESSOREQUAL_RULE 42
#define L_GREATHEROREQUAL_RULE 43
#define L_EQUALEQUAL_RULE 44
#define L_NOTEQUAL_RULE 45
#define L_R_RULE 46
#define R_PLUS_RULE 47
#define R_MINUS_RULE 48
#define R_Y_RULE 49
#define Y_TIMES_RULE 50
#define Y_DIVIDE_RULE 51
#define Y_F_RULE 52
#define F_LV_RULE 53
#define F_PLUSPLUS_LV_RULE 54
#define F_MINUSMINUS_LV_RULE 55
#define F_LV_PLUSPLUS_RULE 56
#define F_LV_MINUSMINUS_RULE 57
#define F_PARENTHESIS_RULE 58
#define F_FUNCTIONUSE_RULE 59
#define F_MINUSF_RULE 60
#define F_NOTF_RULE 61
#define F_TRU_RULE 62
#define F_FALS_RULE 63
#define F_CH_RULE 64
#define F_ST_RULE 65
#define F_NU_RULE 66
#define LE_REC_RULE 67
#define LE_E_RULE 68
#define LE_EMPTY_RULE 69
#define LV_REC_RULE 70
#define LV_SQUARES_E_USE 71
#define LV_IDU_RULE 72
#define TRU_TRUE_RULE 73
#define FALS_FALSE_USE 74
#define CH_CHARACTER_RULE 75
#define ST_STRINGVAL_RULE 76
#define NU_NUMERAL_RULE 77
#define IDT_RULE 78
#define IDU_RULE 79
#define IDD_RULE 80
#define NB_RULE 81
#define NF_RULE 82
#define MA_RULE 83
#define ME_RULE 84
#define MC_RULE 85
#define MF_RULE 86
#define MT_RULE 87
#define MW_RULE 88

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
	 P=UNKNOWN+16,LDE,DE,DF,DT,DC,LI,DV,LP,B,LDV,LS,S,E,L,R,Y,F,LE,LV,T,TRU,FALS,CH,ST,NU,IDT,IDU,IDD,NF,NB,MA,MC,ME,MF,MT,MW
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

typedef struct{
	t_attrib _IDD,_IDU,_IDT,_T,_LI,_LI0,_LI1,_TRU,_FALS,_ST,_CH,_NU,_DC,_DC0,_DC1,_LP,_LP0,_LP1,_E,_E0,_E1,_L,_L0,_L1,_R,_R0,_R1,_Y,_Y0,_Y1,_F,_F0,_F1,_LV,_LV0,_LV1,_LE,_LE0,_LE1,_MC,_MT,_ME,_MW;
} attributes;
#endif
