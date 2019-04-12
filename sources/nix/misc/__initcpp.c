#include "stabs.h"

typedef void (*func_ptr) (void);

extern func_ptr __CTOR_LIST__[];
extern func_ptr __DTOR_LIST__[];

void __initcpp() {
  func_ptr *p0 = __CTOR_LIST__ + 1;
  func_ptr *p;
  for (p = p0; *p; p++);
  while (p > p0)
    (*--p)();
}

void __exitcpp() {
  func_ptr *p = __DTOR_LIST__ + 1;
  while (*p)
    (*p++)();
}

ADD2INIT(__initcpp,100);
ADD2EXIT(__exitcpp,100);
