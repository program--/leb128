#include "interface.h"
#include "Rinternals.h"

SEXP R_int32_signed_encode(SEXP x)
{
    size_t    xx     = asInteger(x);
    bytearray xx_leb = signed_encode(xx);
    SEXP      result = PROTECT(allocVector(RAWSXP, xx_leb.size));

    for (size_t i = 0; i < xx_leb.size; ++i) {
        SET_RAW_ELT(result, i, xx_leb.array[i]);
    }

    bytearray_free(&xx_leb);
    UNPROTECT(1);
    return result;
}

SEXP R_int32_signed_decode(SEXP x)
{
    size_t    len = Rf_length(x);
    bytearray leb = bytearray_init(len);
    for (size_t i = 0; i < len; ++i) {
        bytearray_insert(&leb, RAW_ELT(x, i));
        printf("%hhu\n", leb.array[i]);
    }

    SEXP   result = PROTECT(allocVector(INTSXP, 1));
    size_t res    = signed_decode(&leb);
    printf("%zu\n", res);
    SET_INTEGER_ELT(result, 0, res);

    bytearray_free(&leb);
    UNPROTECT(1);
    return result;
}
