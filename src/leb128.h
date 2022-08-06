#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    uint8_t* array;
    size_t   used;
    size_t   size;
} bytearray;

bytearray bytearray_init(size_t);
void      bytearray_free(bytearray*);
void      bytearray_resize(bytearray*, size_t);
void      bytearray_insert(bytearray*, uint8_t);
bytearray unsigned_encode(size_t);
size_t    unsigned_decode(bytearray*);
bytearray signed_encode(size_t);
size_t    signed_decode(bytearray*);
