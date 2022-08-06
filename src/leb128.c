#include "leb128.h"

bytearray bytearray_init(size_t initial_size)
{
    bytearray x;
    uint8_t*  new_array = malloc(initial_size);
    if (new_array == NULL) {
        printf("\nFailed to malloc bytearray.");
        exit(1);
    }

    x.array = new_array;
    x.used  = 0;
    x.size  = initial_size;
    return x;
}

void bytearray_free(bytearray* x)
{
    if (x->array == NULL) {
        printf("\nArray pointer does not exist!");
    } else {
        free(x->array);
        x->array = NULL;
        x->used  = 0;
        x->size  = 0;
    }
}

void bytearray_resize(bytearray* x, size_t new_size)
{
    uint8_t* new_array = realloc(x->array, new_size);
    if (new_array == NULL) {
        printf("\nFailed to realloc bytearray.");
        bytearray_free(x);
        exit(1);
    } else {
        x->size  = new_size;
        x->array = new_array;
    }
}

void bytearray_insert(bytearray* x, uint8_t element)
{
    if (x->used == x->size) {
        bytearray_resize(x, x->size * 2);
    }

    x->array[x->used++] = element;
}

bytearray unsigned_encode(size_t x)
{
    uint8_t   byte;
    bytearray buf = bytearray_init(512);

    while (1) {
        byte = x & 0x7f;
        x >>= 7;
        if (x == 0) {
            bytearray_insert(&buf, byte);
            bytearray_resize(&buf, buf.used);
            return buf;
        }
        bytearray_insert(&buf, 0x80 | byte);
    }
}

size_t unsigned_decode(bytearray* x)
{
    size_t ret = 0;
    for (size_t i = 0; i < x->size; ++i) {
        ret += (x->array[i] & 0x7f) << (i * 7);
    }
    return ret;
}

bytearray signed_encode(size_t x)
{
    uint8_t   byte;
    bytearray buf = bytearray_init(512);

    while (1) {
        byte = x & 0x7f;
        x >>= 7;
        if ((x == 0 && ((byte & 0x40) == 0)) || (x == -1 && ((byte & 0x40) != 0))) {
            bytearray_insert(&buf, byte);
            bytearray_resize(&buf, buf.used);
            return buf;
        }
        bytearray_insert(&buf, 0x80 | byte);
    }
}

size_t signed_decode(bytearray* x)
{
    size_t ret = 0;
    size_t i;
    for (i = 0; i < x->size; ++i) {
        ret += (x->array[i] & 0x7f) << (i * 7);
    }

    if ((x->array[i] & 0x40) != 0) {
        ret |= -(1 << ((i * 7) + 7));
    }

    return ret;
}
