#include "stabs.h"

extern void __register_frame_info(void *, void *);

// note the different name, it ends up in front of .list___EH_FRAME_BEGINS__
__attribute((section(".list___EH_FRAME_BEGIN")))
void const * _EH_FRAME_BEGINS__[] = {0};

// note the different name, it ends up in front of .list___EH_FRAME_OBJECTS__
__attribute((section(".dlist___EH_FRAME_OBJECT")))
void * _EH_FRAME_OBJECTS__[1] = {0};

void __init_eh() {
    void ** frame = (void **)_EH_FRAME_BEGINS__ + 1;
    void ** object = _EH_FRAME_OBJECTS__ + 1;

    while (*frame) {
      __register_frame_info(*frame++, *object++);
    }
}

ADD2INIT(__init_eh,-5);
