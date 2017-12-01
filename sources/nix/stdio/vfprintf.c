#include <math.h>
#include <float.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

/* a little macro to make life easier */

#define OUT(c)  do                           \
                { if(fputc((c),stream)==EOF) \
                    return outcount;         \
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
 * No idea what's this...
 */
#define BLANKFLAG     8  /* ' ' is set */

/**
 * '+'
 * Forces to preceed the result with a plus or minus sign (+ or -) even for positive numbers.
 * By default, only negative numbers are preceded with a - sign.
 */
#define SIGNFLAG      16 /* '+' is set */

extern unsigned char *__decimalpoint;

static int __vfprintf(FILE *stream,const char *format,va_list args)
{ unsigned char buf[64];
  FILE fp;
  int ret;

  fp.outcount    = 0;
  fp.flags       = stream->flags&~(__SWO|__SWR|__SNBF);
  fp.file        = stream->file;
  fp.buffer      = buf;
  fp.bufsize     = sizeof(buf);
  fp.linebufsize = 0;
  if(((ret=vfprintf(&fp,format,args))>=0) && __fflush(&fp))
    ret = -1;
  if(fp.flags&__SERR)
    stream->flags|=__SERR;
  return ret;
}


static unsigned __ulldivus(unsigned long long * llp, unsigned short n)
{
  struct LL {
    unsigned long hi;
    union {
      unsigned long lo;
      struct { unsigned short exponent; unsigned short y; };
    };
  } * hl = (struct LL *) llp;

  unsigned long h = hl->hi;
  if (h) {
    unsigned l = hl->exponent;
    unsigned k = hl->y;
    unsigned c = h % n;
    h = h / n;
    l = l + (c << 16);
    c = l % n;
    l = l / n;
    k = k + (c << 16);
    unsigned r = k % n;
    k = k / n;
    hl->lo = (l << 16) + k;
    hl->hi = h + (l >> 16);
    return r;
  }

  unsigned r = hl->lo % n;
  hl->lo /= n;
  return r;
}


int vfprintf(FILE *stream,const char *format,va_list args)
{ 
  size_t outcount=0;

  /* optimize unbuffered write-only files */
  if((stream->flags&(__SWO|__SNBF))==(__SWO|__SNBF))
    return __vfprintf(stream,format,args);

//  puts(format);
  while(*format)
  {
//putchar(*format);
    if(*format=='%')
    { 
      static const char flagc[]=
      { '#','0','-',' ','+' };
      static const char lowertabel[]=
      { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };
      static const char uppertabel[]=
      { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
      short width=0;
      short preci=0x7fff;
      short flags=0; /* Specifications */
      char type,subtype='i';
      char buffer1[2];             /* Signs and that like */
      char buffer[REQUIREDBUFFER]; /* The body */
      char *buffer2=buffer;        /* So we can set this to any other strings */
      size_t size1=0,size2=0;      /* How many chars in buffer? */
      const char *ptr=format+1;    /* pointer to format string */
      short i,pad;                /* Some temporary variables */

      do /* read flags */
        for(i=0;i<sizeof(flagc);i++)
          if(flagc[i]==*ptr)
          { flags|=1<<i;
            ptr++;
            break; }
      while(i<sizeof(flagc));

      if(*ptr=='*') /* read width from arguments */
      { signed int a;
        ptr++;
        a=va_arg(args,signed int);
        if(a<0)
        { flags|=LALIGNFLAG;
          width=-a; }
        else
          width=a;
      }else
        while(isdigit(*ptr))
          width=width*10+(*ptr++-'0');

      if(*ptr=='.')
      { ptr++;
        if(*ptr=='*') /* read precision from arguments */
        { signed int a;
          ptr++;
          a=va_arg(args,signed int);
          if(a>=0)
            preci=a;
        }else
        { preci=0;
          while(isdigit(*ptr))
            preci=preci*10+(*ptr++-'0');
        }
      }

      if(*ptr=='h'||*ptr=='l'||*ptr=='L'||*ptr=='j'||*ptr=='z'||*ptr=='t')
	{
	  subtype=*ptr++;
	  if(*ptr=='h'||*ptr=='l')
	    ++ptr, ++subtype;
	}else
	  subtype=0;

      type=*ptr++;

      switch(type)
      { case 'd':
        case 'i':
        case 'o':
        case 'p':
        case 'u':
        case 'x':
        case 'X':
        {
          unsigned long long v;
          const char *tabel;
          int base;

          if(type=='p')
          { subtype='l'; /* This is written as %#lx */
            type='x';
            flags|=ALTERNATEFLAG; }

          if(type=='d'||type=='i') /* These are signed */
          {
          signed long long v2;
            if(subtype=='l')
              v2=va_arg(args,signed long);
            else if (subtype == 'm' || subtype == 'j')
              v2=va_arg(args,signed long long);
            else
              v2=va_arg(args,signed int);
            if(v2<0)
            { buffer1[size1++]='-';
              v=-v2;
            }else
            { if(flags&SIGNFLAG)
                buffer1[size1++]='+';
//              else if(flags&BLANKFLAG)
//                buffer1[size1++]=' ';
              v=v2; }
          }else                    /* These are unsigned */
          { if(subtype=='l')
              v=va_arg(args,unsigned long);
            else if (subtype == 'm' || subtype == 'j')
              v=va_arg(args,unsigned long long);
            else
              v=va_arg(args,unsigned int);
            if(flags&ALTERNATEFLAG)
            { if(type=='o'&&(preci||v))
                buffer1[size1++]='0';
              if((type=='x'||type=='X')&&v)
              { buffer1[size1++]='0';
                buffer1[size1++]=type; }
            }
          }

          buffer2=&buffer[sizeof(buffer)]; /* Calculate body string */
          base=type=='x'||type=='X'?16:(type=='o'?8:10);
          tabel=type!='X'?lowertabel:uppertabel;
          do
          { *--buffer2=tabel[__ulldivus(&v, base)];
            size2++;
          }while(v);
          if(preci==0x7fff) /* default */
            preci=0;
          else
            flags&=~ZEROPADFLAG;
          break;
        }
        case 'c':
          if(subtype=='l')
            *buffer2=va_arg(args,long);
          else
            *buffer2=va_arg(args,int);
          size2=1;
          preci=0;
          break;
        case 's':
          buffer2=va_arg(args,char *);
          size2=strlen(buffer2);
          size2=size2<=preci?size2:preci;
          preci=0;
          break;

#ifdef FULL_SPECIFIERS
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        {
#if 1
        	double d;
        	short exponent = 0;
        	char sign = 0;
        	char const * infnan = 0;
        	char pad = (flags & ZEROPADFLAG) ? '0' : ' ';

        	if (type == 'f' || type == 'F')
        		type = 0;

        	d=va_arg(args,double);

        	// check for negative number and set the sign char if necessary
        	if (*(char *)&d < 0) {
        		*(char *)&d &= 0x7f;
        		sign = '-';
        	} else if (flags & SIGNFLAG)
        		sign = '+';

        	// check for inf/nan
        	if ((*(short *)&d & 0x7ff0) == 0x7ff0) {
        		if ((0[(long*)&d] & 0xfffff) || 1[(long *)&d]) {
        			infnan = "NaN";
        			sign = 0;
        		} else {
        			infnan = "inf";
        		}
        		width -= 3;
        	}

        	if(preci==0x7fff) /* old default */
        		preci=6; 	  /* new default */

    		// count of digts:
    		// f, F : all digits before dot, preci digits behind. = 1 + preci, add exponent if > 0
    		// e, E : one digit before dot, preci digits behind dot = 1 + preci
    		// g, G : preci digits total
    		int startPos = 1; // first digit
    		short stopPos = preci + 1; // behind last digit
    		short leading = 1; // digits until dot is inserted
    		short dotZero = 0; // insert zeroes after dot
    		short postZero = 0; // append zeroes at end
    		short killZero = 0; // kill trailing zeroes

    		// real number
        	if (!infnan) {
        		// compute exponent - a tad slow but ok
        		if (0[(long*)&d] || 1[(long*)&d]) {
					if (d >= 1) {
						while (d >= 10000000000) {
							d *= 0.0000000001;
							exponent+=10;
						}
						while (d >= 10) {
							d *= 0.1;
							++exponent;
						}
					} else  {
						while (d < 0.0000000001) {
							d *= 10000000000;
							exponent -= 10;
						}
						while (d < 1) {
							d *= 10;
							--exponent;
						}
					}
        		}

        		// convert g into e or f
        		if (type == 'g' || type == 'G') {
        			int limit = preci + 3;
        			--preci;
	    			if (preci >= exponent && exponent >= 0) {
	        			type = 0;
	    				preci -= exponent;
        			} else if (exponent < 0 && limit + exponent + 1 > preci) {
	        			type = 0;
	        			preci -= exponent;
	        		} else {
	        			type = 'e';
	        		}
	    			stopPos = preci + 1;
	    			killZero = 1;
        		}

        		// fill it with digits
        		buffer[0] = '0';
        		short pos = 1;
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
					int z = (int)d;
					d = (d - z) * 10;
					buffer[pos] = (char)('0' + z);
				}

        		// round up
        		if ( d >= 5.) {
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
						} else
    					if (type == 0 && exponent < 0) {
    						if (dotZero > 0)
    							--dotZero;
            				buffer[1] = '1'; // overflow
    					}
        			}
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
        				if (stop + 1 != stopPos && stop - startPos == exponent)
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
        			} else if (exponent > 99) {
        				--width;
        			}
        		} else {
        			// 123.456  -> exponent = 2, preci = 3
        			if (leading > stopPos - startPos)
    					width -= leading + dotZero + postZero;
        			else
        				width -= stopPos - startPos + dotZero + postZero;
        		}

        		// dot?
        		if (preci > 0 || (flags &ALTERNATEFLAG) != 0)
        			--width;
        	}

        	if (sign != 0)
        		--width;

        	// pad on left side
        	if ((flags&LALIGNFLAG) == 0)
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
    			while (leading-- > 0)
    				OUT('0');

    			// output dot
        		if (startPos < stopPos || dotZero != 0 || postZero != 0 || (flags &ALTERNATEFLAG) != 0)
        			OUT(__decimalpoint[0]);

        		// output zeroes behind dot not in buffer
        		while (dotZero-- > 0)
        			OUT('0');

        		// digits somewhere behind dot
        		for(; startPos < stopPos; ++startPos)
        			OUT(buffer[startPos]);

        		// output trailing zeroes not in buffer
        		while (postZero-- > 0)
        			OUT('0');

        		if (type != 0) {
        			OUT(type);
        			if (exponent < 0) {
        				OUT('-');
        				exponent = -exponent;
        			} else
        			OUT('+');
        			--width;
        			if (exponent > 99) {
        				int z = exponent/100;
        				OUT('0' + z);
        				exponent -= z * 100;
        				--width;
        			}
        			int z = exponent/10;
        			OUT('0' + z);
        			exponent -= z * 10;
        			--width;
        			OUT('0' + exponent);
        			--width;
        		}
        	}

        	// pad on right side
        	if ((flags&LALIGNFLAG) != 0)
        		while (--width >= 0)
        			OUT(' ');
#else
          double v;
          char killzeros=0,sign=0; /* some flags */
          int ex1,ex2; /* Some temporary variables */
          size_t size,dnum,dreq;
          char *udstr=NULL;

          v=va_arg(args,double);

          if(isinf(v))
          { if(v>0)
              udstr="+inf";
            else
              udstr="-inf";
          }else if(isnan(v))
            udstr="NaN";

          if(udstr!=NULL)
          { size2=strlen(udstr);
            preci=0;
            buffer2=udstr;
            break; }

          if(preci==0xffff) /* old default */
            preci=6; /* new default */
          else if (preci > 17)
            preci = 17;

          if(v<0.0)
          { sign='-';
            v=-v;
          }else
          { if(flags&SIGNFLAG)
              sign='+';
            else if(flags&BLANKFLAG)
              sign=' ';
          }

          ex1=0;
          if(v!=0.0)
          { ex1=log10(v);
            if(v<1.0)
              v=v*pow(10,- --ex1); /* Caution: (int)log10(.5)!=-1 */
            else
              v=v/pow(10,ex1);
            if(v<1.0) /* adjust if we are too low (log10(.1)=-.999999999) */
            { v*=10.0; /* luckily this cannot happen with FLT_MAX and FLT_MIN */
              ex1--; } /* The case too high (log(10.)=.999999999) is done later */
          }

          ex2=preci;
          if(type=='f')
            ex2+=ex1;
          if(tolower(type)=='g')
            ex2--;
          v+=.5/pow(10,ex2<MINFLOATSIZE?ex2:MINFLOATSIZE); /* Round up */

          if(v>=10.0) /* Adjusts log10(10.)=.999999999 too */
          { v/=10.0;
            ex1++; }

          if(tolower(type)=='g') /* This changes to one of the other types */
          { if(ex1<(signed long)preci&&ex1>=-4)
            { type='f';
              preci-=ex1;
            }else
              type=type=='g'?'e':'E';
            preci--;
            if(!(flags&ALTERNATEFLAG))
              killzeros=1; /* set flags to kill trailing zeros */
          }

          dreq=preci+1; /* Calculate number of decimal places required */
          if(type=='f')
            dreq+=ex1;   /* even more before the decimal point */

          dnum=0;
          while(dnum<dreq&&dnum<MINFLOATSIZE) /* Calculate all decimal places needed */
//          while(dnum<dreq) /* Calculate all decimal places needed */
          { buffer[dnum++]=(char)v+'0';
            v=(v-(double)(char)v)*10.0; }

          if(killzeros) /* Kill trailing zeros if possible */
            while(preci&&(dreq-->dnum||buffer[dreq]=='0'))
              preci--;

          if(type=='f')/* Calculate actual size of string (without sign) */
          { size=preci+1; /* numbers after decimal point + 1 before */
            if(ex1>0)
              size+=ex1; /* numbers >= 10 */
            if(preci||flags&ALTERNATEFLAG)
              size++; /* 1 for decimal point */
          }else
          { size=preci+5; /* 1 for the number before the decimal point, and 4 for the exponent */
            if(preci||flags&ALTERNATEFLAG)
              size++;
            if(ex1>99||ex1<-99)
              size++; /* exponent needs an extra decimal place */
          }

          pad=size+(sign!=0);
          pad=pad>=width?0:width-pad;

          if(sign&&flags&ZEROPADFLAG)
            OUT(sign);

          if(!(flags&LALIGNFLAG))
            for(i=0;i<pad;i++)
              OUT(flags&ZEROPADFLAG?'0':' ');

          if(sign&&!(flags&ZEROPADFLAG))
            OUT(sign);

          dreq=0;
          if(type=='f')
          { if(ex1<0)
              OUT('0');
            else
              while(ex1>=0)
              { OUT(dreq<dnum?buffer[dreq++]:'0');
                ex1--; }
            if(preci||flags&ALTERNATEFLAG)
            { OUT(__decimalpoint[0]);
              while(preci--)
                if(++ex1<0)
                  OUT('0');
                else
                  OUT(dreq<dnum?buffer[dreq++]:'0');
            }
          }else
          { OUT(buffer[dreq++]);
            if(preci||flags&ALTERNATEFLAG)
            { OUT(__decimalpoint[0]);
              while(preci--)
                OUT(dreq<dnum?buffer[dreq++]:'0');
            }
            OUT(type);
            if(ex1<0)
            { OUT('-');
              ex1=-ex1; }
            else
              OUT('+');
            if(ex1>99)
              OUT(ex1/100+'0');
            OUT(ex1/10%10+'0');
            OUT(ex1%10+'0');
          }

          if(flags&LALIGNFLAG)
            for(i=0;i<pad;i++)
              OUT(' ');
#endif // 0
          width=preci=0; /* Everything already done */
          break;
        }
#endif
        case '%':
          buffer2="%";
          size2=1;
          preci=0;
          break;
        case 'n':
          *va_arg(args,int *)=outcount;
          width=preci=0;
          break;
        default:
          if(!type)
            ptr--; /* We've gone too far - step one back */
          buffer2=(char *)format;
          size2=ptr-format;
          width=preci=0;
          break;
      }
      pad=size1+(size2>=preci?size2:preci); /* Calculate the number of characters */
      pad=pad>=width?0:width-pad; /* and the number of resulting pad bytes */

      if(flags&ZEROPADFLAG) /* print sign and that like */
        for(i=0;i<size1;i++)
          OUT(buffer1[i]);

      if(!(flags&LALIGNFLAG)) /* Pad left */
        for(i=0;i<pad;i++)
          OUT(flags&ZEROPADFLAG?'0':' ');

      if(!(flags&ZEROPADFLAG)) /* print sign if not zero padded */
        for(i=0;i<size1;i++)
          OUT(buffer1[i]);

      for(i=size2;i<preci;i++) /* extend to precision */
        OUT('0');

      for(i=0;i<size2;i++) /* print body */
        OUT(buffer2[i]);

      if(flags&LALIGNFLAG) /* Pad right */
        for(i=0;i<pad;i++)
          OUT(' ');

      format=ptr;
    }
    else
      OUT(*format++);
  }
  return outcount;
}

#ifdef TESTME
int main(int argc, char ** argv) {
  double d;
	printf("%-20.0f|\n", 0.0d);
	printf("%-20.0e\n", 0.0d);
	printf("%-20.1g\n", 0.0d);
	printf("%#20.0f\n", 0.0d);
	printf("%#20.0e\n", 0.0d);
	printf("%#20.1g\n", 0.0d);

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
