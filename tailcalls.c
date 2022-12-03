#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// Tests to see if an infinite loop between two functions and the new
// clang attribute "musttail"
//
// aka: __attribute((musttail)) or [[clang:musttail]]

// For tail calls to work with gcc, you must have optimizations turned
// on.

// clang appears to impersonate gcc so we keep the test when clang is
// defined.
#ifndef __clang__
#ifdef __GNUC__
#ifndef __OPTIMIZE__
  #error gcc will not produce tail calls without optimization
#endif
#endif
#endif

// Note, if you want tail calls with gcc, maybe you probably want something
// like this (O2 seems good enough but I copied pasted from the web)
//
// #pragma GCC optimize("O3")

typedef void (*bblock_pointer_t)(uint64_t continuation, uint64_t arg1, uint64_t arg2);

void bblock_1(uint64_t continuation, uint64_t arg1, uint64_t arg2);
void bblock_2(uint64_t continuation, uint64_t arg1, uint64_t arg2);

void bblock_0(uint64_t continuation, uint64_t arg1, uint64_t arg2) {
  exit(0);
}

void bblock_1(uint64_t continuation, uint64_t arg1, uint64_t arg2) {
  if ((arg1 & 0xffff) == 0) {
    printf("bblock_1 %" PRIu64 "\n", arg1);
  }

  int flag = (rand() & 1);
  bblock_pointer_t next = flag ? ((bblock_pointer_t)&(bblock_1)) : ((bblock_pointer_t)&(bblock_2));

#ifdef __clang__
  __attribute((musttail)) 
#endif
    return (*next)(continuation, ++arg1, arg2);
}

void bblock_2(uint64_t continuation, uint64_t arg1, uint64_t arg2) {
  if ((arg1 & 0xffff) == 0) {
    printf("bblock_2 %" PRIx64 "\n", arg1);
  }

  int flag = (rand() & 1);
  bblock_pointer_t next = flag ? ((bblock_pointer_t)&(bblock_1)) : ((bblock_pointer_t)&(bblock_2));

#ifdef __clang__
  __attribute((musttail)) 
#endif
    return (*next)(continuation, rand() & 0xffff, arg2);
}

int main(int argc, char** argv) {
  bblock_1((uint64_t) &bblock_0, 0, 0);
  return 0;
}



