#pragma once

#include "common.h"
#include <string.h>

#define DeclareArray(type) struct Array##type { usize len; type* data; }
#define Array(type) struct Array##type
#define AllocateArray(type, length) (struct Array##type){ .len = (length), .data = (type*)calloc(length, sizeof(type)) }
#define MakeArray(data, length) (struct )
#define FreeArray(array) free((array).data)
#define ArrayForEach(index, array) for (usize index = 0; index < (array).len; ++index)
#define ArrayLen(array) (array).len
#define ArrayData(array) (array).data
#define ArrayExtend(self, other) do { \
    const usize len = ArrayLen(self) + ArrayLen(other); \
    ArrayData(self) = realloc(ArrayData(self), len * sizeof(*ArrayData(self))); \
    memcpy(ArrayData(self) + ArrayLen(self), ArrayData(other), ArrayLen(other) * sizeof(*ArrayData(self))); \
    ArrayLen(self) = len; \
} while (0)
