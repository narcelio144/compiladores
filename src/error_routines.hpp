#ifndef ERROR_ROUTINES
#define ERROR_ROUTINES

#include "analisador_lexico.hpp"
#include "definitions.hpp"
#include "error_routines.hpp"

using std::cout;
using std::endl;


class errorRoutines{
  public:
    static bool hasError;
    static void throwSyntaxError();
    static void throwError(error_code err);
};

#endif
