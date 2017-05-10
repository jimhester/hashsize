#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#define HSIZE 4119
extern SEXP* R_SymbolTable;

SEXP hashsize_symbols() {
  SEXP res = PROTECT(Rf_allocVector(VECSXP, HSIZE));
  for (int i = 0; i < HSIZE; ++i) {
    SET_VECTOR_ELT(res, i, R_SymbolTable[i]);
  }
  UNPROTECT(1);
  return res;
}

SEXP hashsize_lookup_one(SEXP in) { return Rf_install(CHAR(STRING_ELT(in, 0))); }

SEXP hashsize_lookup_bench(SEXP in, SEXP i) {
  const char* name = CHAR(STRING_ELT(in, 0));
  int limit = REAL(i)[0];
  for (int i = 0; i < limit; ++i) {
    Rf_install(name);
  }
  return R_NilValue;
}

static const R_CallMethodDef call_entries[] = {
  {"hashsize_symbols"      , (DL_FUNC)&hashsize_symbols      , 0} ,
  {"hashsize_lookup"       , (DL_FUNC)&hashsize_lookup_one   , 1} ,
  {"hashsize_lookup_bench" , (DL_FUNC)&hashsize_lookup_bench , 2} ,
  {NULL                    , NULL                            , 0}
};

void R_init_hashsize(DllInfo* dll) {
  R_registerRoutines(dll, NULL, call_entries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
