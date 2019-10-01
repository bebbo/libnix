# AF, Gwd, 9.July 2019
# checks, if correct libraries and startupcodes are linked for -m68020, -m68881, -fbaserel, -fbaserel32, -resident and -resident32
# checks, if CPU and FPU requirements are enforced
#

PREFIX ?= /home/developer/opt/m68k-amigaos_29Sep19

# remove trailing / if there is one
PREFIX_ = $(shell realpath $(PREFIX))

CC = $(PREFIX_)/bin/m68k-amigaos-gcc
VAMOS = vamos

NEED_68020_MESSAGE = 'CALL:  108 Alert( alertNum[d7]=00068020 )'
NEED_68881_MESSAGE = 'CALL:  108 Alert( alertNum[d7]=00068881 )'
NORMAL_MESSAGE ='Hello world, Pi=3.14'

all: m68000 m68020 m68020_m68881 fbaserel_m68000 fbaserel_m68020 fbaserel_m68020_m68881 fbaserel32_m68020 fbaserel32_m68020_m68881 resident resident_m68020 resident_m68020_m68881 resident32_m68020 resident32_m68020_m68881

m68000:
	@$(CC) cpu_test.c  -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/ncrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out | grep -F $(NORMAL_MESSAGE) >/dev/null || (echo missing expected output; false)  # expected string printed?
	@echo $@ " passed. "

m68020:
	@$(CC) cpu_test.c  -m68020 -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libm020/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/ncrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out | grep -F $(NORMAL_MESSAGE) >/dev/null || (echo missing expected output; false)  # expected string printed?
	@echo $@ " passed. "

m68020_m68881:
	@$(CC) cpu_test.c  -m68020 -m68881 -noixemul -lm -Wl,-Map=name.map,--trace  > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libm020/libm881/libnix20.a' deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/ncrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out 2>&1 | grep -F $(NEED_68881_MESSAGE) >/dev/null || (echo missing 68881 message; false)  # expecting 68881 message printed?
	@echo $@ " passed. "

fbaserel_m68000:
	@$(CC) cpu_test.c  -fbaserel -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nbcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out | grep -F $(NORMAL_MESSAGE) >/dev/null || (echo missing expected output; false)  # expected string printed?
	@echo $@ " passed. "

fbaserel_m68020:
	@$(CC) cpu_test.c  -m68020 -fbaserel -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb/libm020/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nbcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out | grep -F $(NORMAL_MESSAGE) >/dev/null || (echo missing expected output; false)  # expected string printed?
	@echo $@ " passed. "

fbaserel_m68020_m68881:
	@$(CC) cpu_test.c  -m68020 -m68881 -fbaserel -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb/libm020/libm881/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nbcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out 2>&1 | grep -F $(NEED_68881_MESSAGE) >/dev/null || (echo missing 68881 message; false)  # expecting 68881 message printed?
	@echo $@ " passed. "

#:fbaserel32:
	@# only possible with 68020 or higher

fbaserel32_m68020:
	@$(CC) cpu_test.c  -m68020 -fbaserel32 -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb32/libm020/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nlbcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out | grep -F $(NORMAL_MESSAGE) >/dev/null || (echo missing expected output; false)  # expected string printed?
	@echo $@ " passed. "

fbaserel32_m68020_m68881:
	@$(CC) cpu_test.c  -m68020 -m68881 -fbaserel32 -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb32/libm020/libm881/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nlbcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out 2>&1 | grep -F $(NEED_68881_MESSAGE) >/dev/null || (echo missing 68881 message; false)  # expecting 68881 message printed?
	@echo $@ " passed. "

resident:
	@$(CC) cpu_test.c  -resident -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nrcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NORMAL_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expected string printed?
	@echo $@ " passed. "

resident_m68020:
	@$(CC) cpu_test.c -m68020 -resident -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb/libm020/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nrcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out 2>&1 | grep -F $(NORMAL_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expected string printed?
	@echo $@ " passed. "

resident_m68020_m68881:
	@$(CC) cpu_test.c -m68020 -m68881 -resident -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb/libm020/libm881/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nrcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out 2>&1 | grep -F $(NEED_68881_MESSAGE) >/dev/null || (echo missing 68881 message; false)  # expecting 68881 message printed?
	@echo $@ " passed. "

#resident32:
	@# only possible with 68020 or higher

resident32_m68020:
	@$(CC) cpu_test.c -m68020 -resident32 -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb32/libm020/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nlrcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out 2>&1 | grep -F $(NORMAL_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expected string printed?
	@echo $@ " passed. "

resident32_m68020_m68881:
	@$(CC) cpu_test.c -m68020 -m68881 -resident32 -noixemul -lm -Wl,-Map=name.map,--trace > deleteme.txt
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/libb32/libm020/libm881/libnix20.a' deleteme.txt >/dev/null  || (echo wrong library; false) # corret library linked?
	@grep '$(PREFIX_)/m68k-amigaos/libnix/lib/nlrcrt0.o'    deleteme.txt >/dev/null  || (echo wrong startup code; false) # corret startup code linked?
	@$(VAMOS) a.out 2>&1 | grep -F $(NEED_68020_MESSAGE) >/dev/null || (echo missing 68020 message; false)  # expecting 68020 message printed?
	@$(VAMOS) -C 68020 a.out 2>&1 | grep -F $(NEED_68881_MESSAGE) >/dev/null || (echo missing 68881 message; false)  # expecting 68881 message printed?
	@echo $@ " passed. "


