// -*- mode: C++; -*-
#ifndef array_H
#define array_H

#include "_target.h"

/* Minimal CUDA-compatible std::array replacement */

template <typename T, size_t N>
class array
{
  T data[N];
  BOTH void Init(const size_t& i, const T& a) {
    data[i] = a;
  }
  template<typename... ARGS>
  BOTH void Init(const size_t& i, const T& a, ARGS... args) {
    data[i] = a;
    Init(i+1, args...);
  }

public:
  BOTH static constexpr size_t size() {
    return N;
  }
  
  BOTH array() {
    for (size_t i = 0; i<N; ++i)
      data[i] = T();
  }
  
  template<typename... ARGS>
  BOTH array(ARGS... args) {
    static_assert(sizeof...(args) == N, "Wrong number of arguments");
    Init(0, args...);
  }
    
  BOTH T& operator[](size_t i) {
    return data[i];
  }
  BOTH const T& operator[](size_t i) const {
    return data[i];
  }
};

template <typename T, size_t N>
BOTH bool operator!=(const array<T,N>& a, const array<T,N>& b) {

  for (size_t i = 0; i< N; ++i) {
    if (a[i] != b[i])
      return true;
  }
  return false;
}

#endif
