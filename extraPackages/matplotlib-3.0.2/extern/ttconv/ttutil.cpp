/* -*- mode: c++; c-basic-offset: 4 -*- */

/*
 * Modified for use within matplotlib
 * 5 July 2007
 * Michael Droettboom
 */

/* Very simple interface to the ppr TT routines */
/* (c) Frank Siegert 1996 */
#undef DEBUG

#include "global_defines.h"
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include "pprdrv.h"

#if DEBUG_TRUETYPE
void debug(const char *format, ... )
{
  va_list arg_list;
  va_start(arg_list, format);

  printf(format, arg_list);

  va_end(arg_list);
}
#endif

#define PRINTF_BUFFER_SIZE 512
void TTStreamWriter::printf(const char* format, ...)
{
  va_list arg_list;
  va_start(arg_list, format);
  char buffer[PRINTF_BUFFER_SIZE];

#if defined(WIN32) || defined(_MSC_VER)
  int size = _vsnprintf(buffer, PRINTF_BUFFER_SIZE, format, arg_list);
#else
  int size = vsnprintf(buffer, PRINTF_BUFFER_SIZE, format, arg_list);
#endif
  if (size >= PRINTF_BUFFER_SIZE) {
    char* buffer2 = (char*)malloc(size);
#if defined(WIN32) || defined(_MSC_VER)
    _vsnprintf(buffer2, size, format, arg_list);
#else
    vsnprintf(buffer2, size, format, arg_list);
#endif
    free(buffer2);
  } else {
    this->write(buffer);
  }

  va_end(arg_list);
}

void TTStreamWriter::put_char(int val)
{
  char c[2];
  c[0] = (char)val;
  c[1] = 0;
  this->write(c);
}

void TTStreamWriter::puts(const char *a)
{
  this->write(a);
}

void TTStreamWriter::putline(const char *a)
{
  this->write(a);
  this->write("\n");
}

void replace_newlines_with_spaces(char *a) {
  char* i = a;
  while (*i != 0) {
    if (*i == '\r' || *i == '\n')
      *i = ' ';
    i++;
  }
}
