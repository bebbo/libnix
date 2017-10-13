#include "stabs.h"
extern char __mathieeesingbasname[];
void *__MathIeeeSingBasBase[2]={ 0l,__mathieeesingbasname };
ADD2LIB(__MathIeeeSingBasBase);

extern char __mathieeedoubbasname[];
void *__MathIeeeDoubBasBase[2]={ 0l,__mathieeedoubbasname };
ADD2LIB(__MathIeeeDoubBasBase);
