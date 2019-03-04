libnix: C link library for AmigaOS/m68k
===

**Maintainer:** [Stefan "Bebbo" Franke](mailto:bebbo@bejy.net)

**Short description:** Fork of [libnix](http://sourceforge.net/projects/libnix/) from [sourceforge.net](http://sourceforge.net).

## Overview

**libnix** is used in conjuction with [amiga-gcc](https://github.com/bebbo/amiga-gcc) project. It's standard C link library (similar to newlib) for gcc cross compiler targeting AmigaOS/m68k systems.

There are several initiatives trying to bring up an updated C link library for AmigaOS/m68k systems:

* [libnix-3.0](https://github.com/diegocr/libnix) by Diego Casorran
* [clib2](http://clib2.cvs.sourceforge.net/) by Olaf Barthel
* [arosc.library](http://repo.or.cz/w/AROS.git/tree/HEAD:/compiler/stdc) in [Amiga Research Operating System](http://aros.sf.net) source tree

I fixed and added plenty files and don't expect the changes to get accepted, since this version relies on system headers from newlib.

Good luck using this^^.
