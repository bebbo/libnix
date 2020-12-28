/* taken from fpgnulib.c */

/* This is a stripped down version of floatlib.c.  It supplies only those
   functions which exist in libgcc, but for which there is not assembly
   language versions in m68k/lb1sf68.S.

   It also includes simplistic support for extended floats (by working in
   double precision).  You must compile this file again with -DEXTFLOAT
   to get this support.  */

/*
** gnulib support for software floating point.
** Copyright (C) 1991 by Pipeline Associates, Inc.  All rights reserved.
** Permission is granted to do *anything* you want with this file,
** commercial or otherwise, provided this message remains intact.  So there!
** I would appreciate receiving any updates/patches/changes that anyone
** makes, and am willing to be the repository for said changes (am I
** making a big mistake?).
**
** Pat Wood
** Pipeline Associates, Inc.
** pipeline!phw@motown.com or
** sun!pipeline!phw or
** uunet!motown!pipeline!phw
**
** 05/01/91 -- V1.0 -- first release to gcc mailing lists
** 05/04/91 -- V1.1 -- added float and double prototypes and return values
**                  -- fixed problems with adding and subtracting zero
**                  -- fixed rounding in truncdfsf2
**                  -- fixed SWAP define and tested on 386
*/

/*
** The following are routines that replace the gnulib soft floating point
** routines that are called automatically when -msoft-float is selected.
** The support single and double precision IEEE format, with provisions
** for byte-swapped machines (tested on 386).  Some of the double-precision
** routines work at full precision, but most of the hard ones simply punt
** and call the single precision routines, producing a loss of accuracy.
** long long support is not assumed or included.
** Overall accuracy is close to IEEE (actually 68882) for single-precision
** arithmetic.  I think there may still be a 1 in 1000 chance of a bit
** being rounded the wrong way during a multiply.  I'm not fussy enough to
** bother with it, but if anyone is, knock yourself out.
**
** Efficiency has only been addressed where it was obvious that something
** would make a big difference.  Anyone who wants to do this right for
** best speed should go in and rewrite in assembler.
**
** I have tested this only on a 68030 workstation and 386/ix integrated
** in with -msoft-float.
*/

/* the following deal with IEEE single-precision numbers */
#define EXCESS		126L
#define SIGNBIT		0x80000000L
#define HIDDEN		(1L << 23L)
#define SIGN(fp)	((fp) & SIGNBIT)
#define EXP(fp)		(((fp) >> 23L) & 0xFF)
#define MANT(fp)	(((fp) & 0x7FFFFFL) | HIDDEN)
#define PACK(s,e,m)	((s) | ((e) << 23L) | (m))

/* the following deal with IEEE double-precision numbers */
#define EXCESSD		1022L
#define HIDDEND		(1L << 20L)
#define EXPDBITS	11
#define EXPDMASK	0x7FFL
#define EXPD(fp)	(((fp.l.upper) >> 20L) & 0x7FFL)
#define SIGND(fp)	((fp.l.upper) & SIGNBIT)
#define MANTD(fp)	(((((fp.l.upper) & 0xFFFFF) | HIDDEND) << 10) | \
				(fp.l.lower >> 22))
#define MANTDMASK	0xFFFFFL /* mask of upper part */

/* the following deal with IEEE extended-precision numbers */
#define EXCESSX		16382L
#define HIDDENX		(1L << 31L)
#define EXPXBITS	15
#define EXPXMASK	0x7FFF
#define EXPX(fp)	(((fp.l.upper) >> 16) & EXPXMASK)
#define SIGNX(fp)	((fp.l.upper) & SIGNBIT)
#define MANTXMASK	0x7FFFFFFFL /* mask of upper part */

union double_long
{
  double d;
  struct {
      long upper;
      unsigned long lower;
    } l;
};

union float_long {
  float f;
  long l;
};

union long_double_long
{
  long double ld;
  struct
    {
      long upper;
      unsigned long middle;
      unsigned long lower;
    } l;
};

/* convert long double to double */
double
__truncxfdf2 (long double ld)
{
  register long exp;
  register union double_long dl;
  register union long_double_long ldl;

  ldl.ld = ld;
  /*printf ("xfdf in: %s\n", dumpxf (ld));*/

  dl.l.upper = SIGNX (ldl);
  if ((ldl.l.upper & ~SIGNBIT) == 0 && !ldl.l.middle && !ldl.l.lower)
    {
      dl.l.lower = 0;
      return dl.d;
    }

  exp = EXPX (ldl) - EXCESSX + EXCESSD;
  /* ??? quick and dirty: keep `exp' sane */
  if (exp >= EXPDMASK)
    exp = EXPDMASK - 1;
  dl.l.upper |= exp << (32 - (EXPDBITS + 1));
  /* +1-1: add one for sign bit, but take one off for explicit-integer-bit */
  dl.l.upper |= (ldl.l.middle & MANTXMASK) >> (EXPDBITS + 1 - 1);
  dl.l.lower = (ldl.l.middle & MANTXMASK) << (32 - (EXPDBITS + 1 - 1));
  dl.l.lower |= ldl.l.lower >> (EXPDBITS + 1 - 1);

  /*printf ("xfdf out: %g\n", dl.d);*/
  return dl.d;
}

extern int __cmpdf2 (double x1, double x2);

asm("___eqxf2: .global ___eqxf2");
asm("___nexf2: .global ___nexf2");
asm("___ltxf2: .global ___ltxf2");
asm("___lexf2: .global ___lexf2");
asm("___gtxf2: .global ___gtxf2");
asm("___gexf2: .global ___gexf2");
int
__cmpxf2 (long double x1, long double x2)
{
  return __cmpdf2 ((double) x1, (double) x2);
}
