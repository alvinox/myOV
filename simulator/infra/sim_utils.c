#include "utils.h"

const int N = 4;

uint8  getvalue8 (char* arr, uint32 offset, uint8  mask, uint8 shift) {
    uint8  value = 0;
    value  |= arr[offset + 0];

    value >>= shift;
    value  &= mask;

    return value;
}

uint16 getvalue16(char* arr, uint32 offset, uint16 mask, uint8 shift) {

    uint16 value = 0;
    value  |= uint16(arr[offset + 0]) <<  0;
    value  |= uint16(arr[offset + 1]) <<  8;

    value >>= shift;
    value  &= mask;

    return value;
}

void   setvalue8 (char* arr, uint32 offset, uint8  mask, uint8 shift, uint8  value) {
    value  &= mask;
    value <<= shift;

    arr[offset + 0] |= value;
}

void   setvalue16(char* arr, uint32 offset, uint16 mask, uint8 shift, uint16 value) {
    value  &= mask;
    value <<= shift;

    arr[offset + 0] |= uint8(value >> 0);
    arr[offset + 1] |= uint8(value >> 8);
}