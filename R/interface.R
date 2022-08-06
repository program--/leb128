#' Convert an integer to a signed LEB128.
#' @param x Integer
int_encode <- function(x) {
    .Call(`R_int32_signed_encode`, x)
}

int_decode <- function(x) {
    .Call(`R_int32_signed_decode`, x)
}
