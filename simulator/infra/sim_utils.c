#include "utils.h"

/*
  the offset is always uint32
  the mask depends on bits of the field
  the shift is always uint8
*/
struct Variable8 {
    uint32 offset;
    uint8  mask;
    uint8  shift;
};

struct Variable16 {
    uint32 offset;
    uint16  mask;
    uint8  shift;
};

uint8  getvalue8 (char* arr, Variable8* v) {
    uint8  value = 0;
    value  |= arr[v->offset + 0];

    value >>= v->shift;
    value  &= v->mask;

    return value;
}

void   setvalue8 (char* arr, Variable8* v, uint8  value) {
    value  &= v->mask;
    value <<= v->shift;

    arr[v->offset + 0] |= value;
}

uint16 getvalue16(char* arr, Variable16* v) {

    uint16 value = 0;
    value  |= uint16(arr[v->offset + 0]) <<  0;
    value  |= uint16(arr[v->offset + 1]) <<  8;

    value >>= v->shift;
    value  &= v->mask;

    return value;
}

void   setvalue16(char* arr, Variable16* v, uint16 value) {
    value  &= v->mask;
    value <<= v->shift;

    arr[v->offset + 0] |= uint8(value >> 0);
    arr[v->offset + 1] |= uint8(value >> 8);
}
