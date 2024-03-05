#pragma once

#define COMMENT(...)

COMMENT(---------=========[ Syntactic Improvements ]=========---------)

/** Internal Storage specifier */
#define internal static
#define in
#define out
#define NOOP


COMMENT(---------=========[ C Array Utilities ]=========---------)

/** Compute length of c array */ 
#define ARRAY_LENGTH(arr) (sizeof arr / sizeof* arr)


#define SIZE_OF_N(type, count) (sizeof (type) * (count))
#define STRINGIFY(x) #x
