#pragma once

#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define LOG_PREFIX_FORMAT "[%s -- %18s -- %4d] : "
#define PANIC_PREFIX_FORMAT "[%s -- %18s -- %4d] # "

/* Common format for all messages terminated with new line character. */
#define FORMAT_STREAM_PREFIXED(stream, prefix, fmt, file, func, line, ...)     \
  fprintf(stream, prefix fmt, file, func, line, __VA_ARGS__)

/* Common format for diagnostic messages. */
#define FORMAT_STREAM(stream, fmt, file, func, line, ...)                                        \
  FORMAT_STREAM_PREFIXED(stream, LOG_PREFIX_FORMAT, fmt, file, func, line, __VA_ARGS__)

/* Common format for panic messages. */
#define FORMAT_PANIC(stream, fmt, file, func, line, ...)                       \
  FORMAT_STREAM_PREFIXED(stream, PANIC_PREFIX_FORMAT, fmt, file, func, line, __VA_ARGS__)

#define PANIC_CONTEXT __FILE__, __func__, __LINE__

/* Irrecoverable error with formatted input. */
#define PANIC_WITH_CONTEXT(fmt, file, func, line, ...)                       \
  do {                                                                       \
    FORMAT_PANIC(stdout, fmt, file, func, line, __VA_ARGS__);                \
    exit(EXIT_FAILURE);                                                      \
  } while (0)

/* Irrecoverable error with formatted input. */
#define PANIC(fmt, ...) PANIC_WITH_CONTEXT(fmt, __FILE__, __func__, __LINE__, __VA_ARGS__)

/* Irrecoverable error with  diagnostic message `msg`. */
#define PANICM(msg) PANIC("%s", msg)

#if defined(_DEBUG) && defined(_LOGGING)
#define LOGLN(fmt, ...) FORMAT_STREAM(stdout, fmt "\n", __FILE__, __func__, __LINE__, __VA_ARGS__)
#define LOGF(fmt, ...) FORMAT_STREAM_PREFIXED(stdout, "\r" LOG_PREFIX_FORMAT, fmt, __FILE__, __func__, __LINE__, __VA_ARGS__)
#else
#define LOGLN(fmt, ...)
#define LOGF(fmt, ...)
#endif

#define LOGLNM(msg) LOGLN("%s", msg)
#define LOGFM(msg) LOGF("%s", msg)

#ifdef _DEBUG
/* Print formatted string and add new line. */
#define PRINTLN(fmt, ...) fprintf(stdout, fmt "\n", __VA_ARGS__)
/* Print line with diagnostic message. */
#define PRINTLNM(msg) PRINTLN("%s", msg)
/// TODO: Add docs
#define PRINTF(fmt, ...) fprintf(stdout, "\r" fmt, __VA_ARGS__)
/// TODO: Add docs
#define PRINTFM(msg) PRINTF("%s", msg)
#else
#define PRINTLN(fmt, ...)
#define PRINTF(fmt, ...)
#endif

#ifdef _DISABLE_ASSERTS_
#define ASSERT_FMT(cond, fmt, ...)
#else
#define ASSERT_FMT(cond, fmt, ...)                                             \
  do {                                                                         \
    if (!cond) {                                                               \
      PANIC(fmt, __VA_ARGS__);                                             \
    }                                                                          \
  } while (0)
#endif

/* Assert that condition `cond` is `true`. */
#ifdef _DISABLE_ASSERTS_
#define ASSERT(cond)
#else
#define ASSERT(cond) do { if (!(cond)) { PANICM("Assertion failed: " #cond ); } } while (0) // all in one line for better __LINE__ reporting
#endif

/* Assert that left-hand side operand `lhs` is equal to right-hand size operand
 * `rhs`. */
#define ASSERT_EQ(lhs, rhs) ASSERT((lhs) == (rhs))

/* Assert that left-hand side operand `lhs` is not equal to right-hand size
 * operand `rhs`. */
#define ASSERT_NEQ(lhs, rhs) ASSERT((lhs) != (rhs))

/* Assert that pointer `ptr` is not `NULL`. */
#define ASSERT_PTR(ptr) ASSERT_NEQ(ptr, NULL)
