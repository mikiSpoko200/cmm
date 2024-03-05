#pragma once

#include "common.h"

#include <inttypes.h>

#define PRIusize PRIuPTR
#define PRIisize PRIiPTR
#define PRIf32 "f"
#define PRIf64 "f"

#define _REP0(X)
#define _REP1(X) X
#define _REP2(X) _REP1(X) X ", "
#define _REP3(X) _REP2(X) X ", "
#define _REP4(X) _REP3(X) X ", "
#define _REP5(X) _REP4(X) X ", "
#define _REP6(X) _REP5(X) X ", "
#define _REP7(X) _REP6(X) X ", "
#define _REP8(X) _REP7(X) X ", "
#define _REP9(X) _REP8(X) X ", "
#define _REP10(X) _REP9(X) X ", "

#define REP(HUNDREDS, TENS, ONES, X) \
  _REP##HUNDREDS(_REP10(_REP10(X))) \
  _REP##TENS(_REP10(X)) \
  _REP##ONES(X)

// Format specifier
#define FS(type) " %" PRI##type " "
// Format string with additional flags, width and precision
#define FSF(type, flags) " %" flags PRI##type " "
// Format Array by repeating format specifier for `type` `size` times interleaving with `", "`
#define FSA(type, size) _REP ## size(" %" PRI##type)
// FSF for array
#define FSFA(type, flags, size) _REP ## size(" %" flags PRI##type " ")

/// Helper macros for FSA_UNROLL
#define _FSA_UNROLL_1(arr) (arr)[0]
#define _FSA_UNROLL_2(arr) _FSA_UNROLL_1(arr), (arr)[1]
#define _FSA_UNROLL_3(arr) _FSA_UNROLL_2(arr), (arr)[2]
#define _FSA_UNROLL_4(arr) _FSA_UNROLL_3(arr), (arr)[3]
#define _FSA_UNROLL_5(arr) _FSA_UNROLL_4(arr), (arr)[4]
#define _FSA_UNROLL_6(arr) _FSA_UNROLL_5(arr), (arr)[5]
#define _FSA_UNROLL_7(arr) _FSA_UNROLL_6(arr), (arr)[6]
#define _FSA_UNROLL_8(arr) _FSA_UNROLL_7(arr), (arr)[7]
#define _FSA_UNROLL_9(arr) _FSA_UNROLL_8(arr), (arr)[8]

/// Expand array to comma separated values in sequence (intended for use with FSA)
#define FSA_UNROLL(arr, size) _FSA_UNROLL_ ## size (arr)
