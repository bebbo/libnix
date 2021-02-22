#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include "stdio.h"

// a union to handle the
union _d_bits {
	double d;
	struct {
		unsigned sign :1;
		unsigned exp :11;
		unsigned frac0 :20;
		unsigned frac1 :32;
	} b;
	unsigned u;
};

#ifdef FULL_SPECIFIERS
extern unsigned char *__decimalpoint;
#endif

extern int __vfprintf_total_size(FILE *stream, const char *fmt, va_list args);

/* a little macro to make life easier */

#define OUT(c)  do                           \
                { putc((c),stream);         \
                  outcount++;                \
                }while(0)

#define MINFLOATSIZE (DBL_DIG+3)
#define MININTSIZE (sizeof(unsigned long long)*CHAR_BIT/3+1)
#define MINPOINTSIZE (sizeof(void *)*CHAR_BIT/4+1)
#define REQUIREDBUFFER (MININTSIZE>MINPOINTSIZE? \
                        (MININTSIZE>MINFLOATSIZE?MININTSIZE:MINFLOATSIZE): \
                        (MINPOINTSIZE>MINFLOATSIZE?MINPOINTSIZE:MINFLOATSIZE))

/**
 * '#'
 * Used with o, exponent or X specifiers the value is preceeded with 0, 0x or 0X
 * respectively for values different than zero.
 * Used with a, A, e, E, f, F, g or G it forces the written output
 * to contain a decimal point even if no more digits follow.
 * By default, if no digits follow, no decimal point is written.
 */
#define ALTERNATEFLAG 1  /* '#' is set */

/**
 * '0'
 * Left-pads the number with zeroes (0) instead of spaces when padding is specified
 * (see width sub-specifier).
 */
#define ZEROPADFLAG   2  /* '0' is set */

/**
 * '-'
 * Left-justify within the given field width;
 * Right justification is the default (see width sub-specifier).
 */
#define LALIGNFLAG    4  /* '-' is set */

/**
 * ' '
 * If no sign is going to be written, a blank space is inserted before the value.
 */
#define BLANKFLAG     8  /* ' ' is set */

/**
 * '+'
 * Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers.
 * By default, only negative numbers are preceded with a - sign.
 */
#define SIGNFLAG      16 /* '+' is set */

static const char flagc[] = { '#', '0', '-', ' ', '+' };

/**
 * Set if an explicit precision is given.
 */
#define HAS_PRECI 32

#if 0
static int ___vfprintf_total_size(FILE *stream, const char *format,
		va_list args) {
	unsigned char buf[64];
	FILE fp;
	int ret;

	fp._w = 0;
	fp._flags = stream->_flags & ~(__SWO | __SWR | __SNBF);
	fp.file = stream->file;
	fp._bf._base = buf;
	fp._bf._size = sizeof(buf);
	fp.linebufsize = 0;
#ifdef __posix_threads__
	fp.__spinlock[0] = 0;
#endif
	if (((ret = __vfprintf_total_size(&fp, format, args)) >= 0)
			&& __fflush(&fp))
		ret = -1;
	if (fp._flags & __SERR)
		stream->_flags |= __SERR;
	return ret;
}
#endif

static unsigned __ulldivus(unsigned long long * llp, unsigned short n) {
	struct LL {
		unsigned long hi;
		union {
			unsigned long lo;
			struct {
				unsigned short exponent;
				unsigned short y;
			} s;
		} u;
	}* hl = (struct LL *) llp;

	unsigned r;
	unsigned long h = hl->hi;
	if (h) {
		unsigned l = hl->u.s.exponent;
		unsigned k = hl->u.s.y;
		unsigned c = h % n;
		h = h / n;
		l = l + (c << 16);
		c = l % n;
		l = l / n;
		k = k + (c << 16);
		r = k % n;
		k = k / n;
		hl->u.lo = (l << 16) + k;
		hl->hi = h + (l >> 16);
		return r;
	}

	r = hl->u.lo % n;
	hl->u.lo /= n;
	return r;
}

/**
 *  Differs from vfprintf such that it returns total number of bytes that
 *  would've been written if there were sufficient space in file.
 *  Required for vsnprintf
 */
int __vfprintf_total_size(FILE *stream, const char *format, va_list args) {
	size_t outcount = 0;

	__STDIO_LOCK(stream);

//	/* optimize unbuffered write-only files */
//	if ((stream->_flags & (__SWO | __SNBF)) == (__SWO | __SNBF)) {
//		return ___vfprintf_total_size(stream, format, args);
//	}

	while (*format) {
		if (*format == '%') {
			static const char lowertabel[] = { '0', '1', '2', '3', '4', '5',
					'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
			static const char uppertabel[] = { '0', '1', '2', '3', '4', '5',
					'6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
			short width = 0;
			unsigned short preci = 0x7fff;
			short flags = 0; /* Specifications */
			char type, subtype = 'i';
			char buffer1[2]; /* Signs and that like */
			char buffer[REQUIREDBUFFER]; /* The body */
			char *buffer2 = buffer; /* So we can set this to any other strings */
			size_t size1 = 0, size2 = 0; /* How many chars in buffer? */
			const char *ptr = format + 1; /* pointer to format string */
			unsigned short i, pad; /* Some temporary variables */

			do /* read flags */
				for (i = 0; i < sizeof(flagc); i++)
					if (flagc[i] == *ptr) {
						flags |= 1 << i;
						ptr++;
						break;
					} while (i < sizeof(flagc));

			if (*ptr == '*') /* read width from arguments */
			{
				signed int a;
				ptr++;
				a = va_arg(args, signed int);
				if (a < 0) {
					flags |= LALIGNFLAG;
					width = -a;
				} else
					width = a;
			} else {
				while (isdigit(*ptr))
					width = width * 10 + (*ptr++ - '0');
			}

			if (*ptr == '.') {
				flags |= HAS_PRECI;
				ptr++;
				if (*ptr == '*') /* read precision from arguments */
				{
					signed int a;
					ptr++;
					a = va_arg(args, signed int);
					if (a >= 0)
						preci = a;
				} else {
					preci = 0;
					while (isdigit(*ptr))
						preci = preci * 10 + (*ptr++ - '0');
				}
			}

			if (*ptr == 'h' || *ptr == 'l' || *ptr == 'L' || *ptr == 'j'
					|| *ptr == 'z' || *ptr == 't') {
				subtype = *ptr++;
				if (*ptr == 'h' || *ptr == 'l')
					++ptr, ++subtype;
			} else
				subtype = 0;

			type = *ptr++;

			switch (type) {
			case 'd':
			case 'i':
			case 'o':
			case 'p':
			case 'u':
			case 'x':
			case 'X': {
				unsigned long long v;
				const char *tabel;
				int base;

				if (type == 'p') {
					subtype = 'l'; /* This is written as %#lx */
					type = 'x';
					flags |= ALTERNATEFLAG;
				}

				if (type == 'd' || type == 'i') /* These are signed */
				{
					signed long long v2;
					if (subtype == 'l')
						v2 = va_arg(args, signed long);
					else if (subtype == 'm' || subtype == 'j')
						v2 = va_arg(args, signed long long);
					else
						v2 = va_arg(args, signed int);
					if (subtype == 'h')
						v2 &= 0xffff;
					else if (subtype == 'i')
						v2 &= 0xff;
					if (v2 < 0 || (subtype == 'h' && (short)v2 < 0) || (subtype == 'i' && (char)v2 < 0)) {
						buffer1[size1++] = '-';
						v = -v2;
					} else {
						if (flags & SIGNFLAG)
							buffer1[size1++] = '+';
						else if (flags & BLANKFLAG)
							buffer1[size1++] = ' ';
						v = v2;
					}
				} else /* These are unsigned */
				{
					if (subtype == 'l')
						v = va_arg(args, unsigned long);
					else if (subtype == 'm' || subtype == 'j')
						v = va_arg(args, unsigned long long);
					else
						v = va_arg(args, unsigned int);
					if (subtype == 'h')
						v &= 0xffff;
					else if (subtype == 'i')
						v &= 0xff;
					if (flags & ALTERNATEFLAG) {
						if (type == 'o') {
							if (!preci || v)
								buffer1[size1++] = '0';
						} else if ((type == 'x' || type == 'X') && v) {
							buffer1[size1++] = '0';
							buffer1[size1++] = type;
						}
					}
				}

				buffer2 = &buffer[sizeof(buffer)]; /* Calculate body string */
				base = type == 'x' || type == 'X' ? 16 : (type == 'o' ? 8 : 10);
				tabel = type != 'X' ? lowertabel : uppertabel;
				do {
					*--buffer2 = tabel[__ulldivus(&v, base)];
					size2++;
				} while (v);
				if (preci == 0x7fff) /* default */
					preci = 0;
				else
					flags &= ~ZEROPADFLAG;
				break;
			}
			case 'c':
				if (subtype == 'l')
					*buffer2 = va_arg(args, long);
				else
					*buffer2 = va_arg(args, int);
				size2 = 1;
				preci = 0;
				break;
			case 's':
				buffer2 = va_arg(args, char *);
				size2 = strlen(buffer2);
				size2 = size2 <= preci ? size2 : preci;
				preci = 0;
				break;

#ifdef FULL_SPECIFIERS



			case 'a':
			case 'A':
			case 'f':
			case 'e':
			case 'E':
			case 'g':
			case 'G': {
				union _d_bits d;
				short exponent = 0;
				char sign = 0;
				const char * infnan = 0;
				char pad = (flags & ZEROPADFLAG) ? '0' : ' ';

				if (type == 'f' || type == 'F')
					type = 0;

				d = va_arg(args, union _d_bits);

				// check for negative number and set the sign char if necessary
				if (d.b.sign) {
					d.b.sign = 0;
					sign = '-';
				} else if (flags & SIGNFLAG)
					sign = '+';
				else if (flags & BLANKFLAG)
					sign = ' ';

				// check for inf/nan
				if (d.b.exp == 0x7ff) {
					if (d.b.frac0 || d.b.frac1) {
						infnan = "NaN";
						sign = 0;
					} else {
						infnan = "inf";
					}
					width -= 3;
				}


				{
					short pos;
					unsigned x, y;

				// count of digts:
				// f, F : all digits before dot, preci digits behind. = 1 + preci, add exponent if > 0
				// e, E : one digit before dot, preci digits behind dot = 1 + preci
				// g, G : preci digits total
				int startPos = 1; // first digit
				short stopPos; // behind last digit
				short leading = 1; // digits until dot is inserted
				short dotZero = 0; // insert zeroes after dot
				short postZero = 0; // append zeroes at end
				short killZero = 0; // kill trailing zeroes

				// real number
				if (!infnan) {
					if (type != 'a' && type != 'A') {

						if (preci == 0x7fff) /* old default */
							preci = 6; /* new default */
						stopPos = preci + 1;

						// compute exponent - a tad slow but ok
						if (d.u || d.b.frac1) {
							if (d.d >= 1) {
								while (d.d >= 10000000000) {
									d.d *= 0.0000000001;
									exponent += 10;
								}
								while (d.d >= 10) {
									d.d *= 0.1;
									++exponent;
								}
							} else {
								while (d.d < 0.0000000001) {
									d.d *= 10000000000;
									exponent -= 10;
								}
								while (d.d < 1) {
									d.d *= 10;
									--exponent;
								}
							}
						}

						while ((int) d.d > 9) {
							d.d /= 10;
							++exponent;
						}

						// convert g into e or f
						if (type == 'g' || type == 'G') {
							int limit = preci + 4;
							--preci;
							if (preci >= exponent && exponent >= 0) {
								type = 0;
								preci -= exponent;
							} else if (exponent < 0
									&& limit + exponent + 1 > preci) {
								type = 0;
								preci -= exponent;
							} else {
								type = 'e';
							}
							stopPos = preci + 1;
							if (!(flags & ALTERNATEFLAG))
								killZero = 1;
						}

						// fill it with digits
						buffer[0] = '0';
						pos = 1;
						if (type == 0) { // f, F
							if (exponent >= 0) {
								leading += exponent;
								stopPos += exponent + 1;
							} else {
								dotZero = -exponent - 1;
								buffer[1] = '0';
								if (dotZero > preci) {
									dotZero = preci;
									buffer[2] = '0'; // mandatory - uninitialized values may break rounding
									pos = 3;
								} else
									pos = 2;
								stopPos -= dotZero - 1;
							}
						} else {
							++stopPos; // add one for leading digit
						}
						if (stopPos >= REQUIREDBUFFER) {
							postZero = stopPos - REQUIREDBUFFER + 1;
							if (type == 0 && postZero > preci)
								postZero = preci;
							stopPos = REQUIREDBUFFER - 1;
						}

						// compute the digits + one more for rounding
						for (; pos < stopPos; ++pos) {
							int z = (int) d.d;
							if (z) {
								d.d = (d.d - z) * 10;
								if (d.d <= -0.1) {
									--z;
									d.d += 10;
								}
							} else
								d.d *= 10;
							buffer[pos] = (char) ('0' + z);
						}

						// round up
						if (d.d >= 5.) {
							--pos;
							for (; pos >= startPos; --pos) {
								if (++buffer[pos] <= '9')
									break;
								buffer[pos] = '0';
							}
							// overflow
							if (pos <= startPos) {
								startPos = 0;
								if (type != 0) {
									++exponent;
									--stopPos;
									buffer[0] = '1'; // overflow
								} else if (type == 0 && exponent < 0) {
									if (dotZero > 0)
										--dotZero;
									buffer[1] = '1'; // overflow
								}
							}
						}
					} else {
						if (preci == 0x7fff) /* old default */
							preci = 0; /* new default */
						if (!(flags & HAS_PRECI)) killZero = 1;

						// 'a' 'A'
						OUT('0');
						OUT(type + 'X' - 'A');

						if (!d.b.exp) {
							exponent = x = y = 0;
						} else {
							exponent = d.b.exp - 1023;
							x = d.b.frac0;
							y = d.b.frac1;
							buffer[0] = '1';
							startPos = 0;
							if (HAS_PRECI)
								++preci;
						}
						stopPos = 1;

						{unsigned j; for (j = 16;j <= 28; j += 12) {
							{int i; for (i = j; i >= 0; i -= 4) {
								unsigned c = (x >> i) & 0xf;
								x -= c << i;
								if (c > 9)
									c += type - 10;
								else
									c += '0';
								buffer[stopPos++] = c;
								if (!x && !y && stopPos >= preci)
									break;
							}}
							if (!y && stopPos >= preci)
								break;
							x = y;
							y = 0;
						}}

						type += 'P' - 'A';
					}

					// kill trailing zeroes
					if (killZero != 0) {
						int stop = stopPos - 1;
						while (stop > startPos) {
							if (buffer[stop] != '0')
								break;
							if (type == 0 && stop - startPos == exponent)
								break;
							--stop;
						}
						if (type != 0 && stop - startPos + 5 < width)
							width = stop - startPos + preci + 5;
						else if (type == 0) {
							if (stop + 1 != stopPos
									&& stop - startPos == exponent)
								++width;
						}
						stopPos = stop + 1;
					}

					// calculate width
					if (type != 0) {
						// 1e+00
						width -= 5 + stopPos - startPos + postZero;

						if (exponent < -99) {
							--width;
							if (exponent < -999)
								--width;
						} else if (exponent > 99) {
							--width;
							if (exponent > 999)
								--width;
						}
					} else {
						// 123.456  -> exponent = 2, preci = 3
						if (leading > stopPos - startPos)
							width -= leading + dotZero + postZero;
						else
							width -= stopPos - startPos + dotZero
									+ postZero;
					}

					// dot?
					if (preci > 0 || (flags & ALTERNATEFLAG) != 0)
						--width;
				}
				if (sign != 0)
					--width;

				// pad on left side
				if ((flags & LALIGNFLAG) == 0)
					while (--width >= 0)
						OUT(pad);

				// output sign if set
				if (sign != 0)
					OUT(sign);

				if (infnan) {
					// output inf/nan
					OUT(infnan[0]);
					OUT(infnan[1]);
					OUT(infnan[2]);
				} else {
					// leading digits
					while (leading-- > 0 && startPos < stopPos)
						OUT(buffer[startPos++]);

					// more leading digits than buffer size
					while (leading-- >= 0)
						OUT('0');

					// output dot
					if (startPos < stopPos || dotZero != 0 || postZero != 0
							|| (flags & ALTERNATEFLAG) != 0)
						OUT(__decimalpoint[0]);

					// output zeroes behind dot not in buffer
					while (dotZero-- > 0)
						OUT('0');

					// digits somewhere behind dot
					for (; startPos < stopPos; ++startPos)
						OUT(buffer[startPos]);

					// output trailing zeroes not in buffer
					while (postZero-- > 0)
						OUT('0');

					if (type != 0) {
						int xout;

						OUT(type);
						if (exponent < 0) {
							OUT('-');
							exponent = -exponent;
						} else
							OUT('+');
						--width;

						xout = 0;
						if (exponent > 999) {
							int z = exponent / 1000;
							OUT('0' + z);
							exponent -= z * 1000;
							--width;
							xout = 1;
						}
						if (xout || exponent > 99) {
							int z = exponent / 100;
							OUT('0' + z);
							exponent -= z * 100;
							--width;
							xout = 1;
						}
						if (xout || exponent > 9 || (type | 0x20) != 'p' ) {
							int z = exponent / 10;
							OUT('0' + z);
							exponent -= z * 10;
							--width;
						}
						OUT('0' + exponent);
						--width;
					}
				}

				// pad on right side
				if ((flags & LALIGNFLAG) != 0)
					while (--width >= 0)
						OUT(' ');
				/* Everything already done */
				format = ptr;
				continue;
			}
			}
#endif
			case '%':
				buffer2 = "%";
				size2 = 1;
				preci = 0;
				break;
			case 'n':
				*va_arg(args, int *) = outcount;
				width = preci = 0;
				break;
			default:
				if (!type)
					ptr--; /* We've gone too far - step one back */
				buffer2 = (char *) format;
				size2 = ptr - format;
				width = preci = 0;
				break;
			}

			if (flags & HAS_PRECI) {
				if (size2 == 1 && !preci && buffer2[0] == '0')
					size2 = 0;
			}

			pad = size1 + (size2 >= preci ? size2 : preci); /* Calculate the number of characters */
			pad = pad >= width ? 0 : width - pad; /* and the number of resulting pad bytes */

			if (flags & ZEROPADFLAG) /* print sign and that like */
				for (i = 0; i < size1; i++)
					OUT(buffer1[i]);

			if (!(flags & LALIGNFLAG)) /* Pad left */
				for (i = 0; i < pad; i++)
					OUT(flags&ZEROPADFLAG?'0':' ');

			if (!(flags & ZEROPADFLAG)) /* print sign if not zero padded */
				for (i = 0; i < size1; i++)
					OUT(buffer1[i]);

			for (i = size2; i < preci; i++) /* extend to precision */
				OUT('0');

			for (i = 0; i < size2; i++) /* print body */
				OUT(buffer2[i]);

			if (flags & LALIGNFLAG) /* Pad right */
				for (i = 0; i < pad; i++)
					OUT(' ');

			format = ptr;
		} else
			OUT(*format++);
	}
	__STDIO_UNLOCK(stream);

	return outcount;
}

#ifdef TESTME
int main(int argc, char ** argv) {
	double d;
	printf("%-20.0f|\n", 0.0);
	printf("%-20.0e\n", 0.0);
	printf("%-20.1g\n", 0.0);
	printf("%#20.0f\n", 0.0);
	printf("%#20.0e\n", 0.0);
	printf("%#20.1g\n", 0.0);

	d = 1.2345678902468e-13;
	for (int i = 0; i < 24; ++i) {
		d *= 10;
		printf("%20.7f\n", d);
	}

	d = 1.2345678902468e-13;
	for (int i = 0; i < 24; ++i) {
		d *= 10;
		printf("%20.7g\n", d);
	}

	d = 1.2345678902468e-13;
	for (int i = 0; i < 24; ++i) {
		d *= 10;
		printf("%20.7e\n", d);
	}

	return 0;
}
#endif
