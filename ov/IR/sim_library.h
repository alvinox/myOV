#ifndef _SIM_LIBRARY_H_
#define _SIM_LIBRARY_H_

typedef unsigned char       uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;
typedef signed   char        int8;
typedef signed   short      int16;
typedef signed   int        int32;
typedef signed   long long  int64;

/*
  the offset is always uint32
  the mask depends on bits of the field
  the shift is always uint8
*/
typedef struct Variable8 {
    uint32 offset;
    uint8  mask;
    uint8  shift;
} Variable8;

typedef struct Variable16 {
    uint32  offset;
    uint16  mask;
    uint8   shift;
} Variable16;

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
    value  |= ((uint16)arr[v->offset + 0]) <<  0;
    value  |= ((uint16)arr[v->offset + 1]) <<  8;

    value >>= v->shift;
    value  &= v->mask;

    return value;
}

void   setvalue16(char* arr, Variable16* v, uint16 value) {
    value  &= v->mask;
    value <<= v->shift;

    arr[v->offset + 0] |= (uint8)(value >> 0);
    arr[v->offset + 1] |= (uint8)(value >> 8);
}

#endif // _SIM_LIBRARY_H_