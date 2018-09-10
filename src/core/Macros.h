#ifndef MACROS_H
#define MACROS_H

#define NO_COPY_AND_ASSIGN(T) \
  T(const T&) = delete;   \
  T& operator=(const T&)  = delete;

#endif
