#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
extern SEXP R_int32_signed_encode(SEXP);
extern SEXP R_int32_signed_decode(SEXP);

//
static const R_CallMethodDef CallEntries[] = {
    { "R_int32_signed_encode", (DL_FUNC)&R_int32_signed_encode, 1 },
    { "R_int32_signed_decode", (DL_FUNC)&R_int32_signed_decode, 1 },
    { NULL, NULL, 0 }
};

void R_init_leb128(DllInfo* dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
