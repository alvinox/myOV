#ifndef __UTILS_H_
#define __UTILS_H_

#include "std_headers.h"

#include "basic_define.h"

uint8  getvalue8 (char* arr, uint32 offset, uint8  mask, uint8 shift);
uint16 getvalue16(char* arr, uint32 offset, uint16 mask, uint8 shift);
void   setvalue8 (char* arr, uint32 offset, uint8  mask, uint8 shift, uint8  value);
void   setvalue16(char* arr, uint32 offset, uint16 mask, uint8 shift, uint16 value);

#endif // __UTILS_H_