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
 * Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X
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

puts("__vfprintf");
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
      struct { unsigned short x; unsigned short y; };
    };
  } * hl = (struct LL *) llp;

  unsigned long h = hl->hi;
  if (h) {
    unsigned l = hl->x;
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
      short width=0,preci=0x7fff,flags=0; /* Specifications */
      char type,subtype='i';
      char buffer1[2];             /* Signs and that like */
      char buffer[REQUIREDBUFFER]; /* The body */
      char *buffer2=buffer;        /* So we can set this to any other strings */
      size_t size1=0,size2=0;      /* How many chars in buffer? */
      const char *ptr=format+1;    /* pointer to format string */
      size_t i,pad;                /* Some temporary variables */

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
        	short x = 0;
        	short y = 0;
        	char sign = 0;
        	char const * infnan = 0;
        	char pad = (flags & ZEROPADFLAG) ? '0' : ' ';
    		short j = 1; // position in buffer after dot

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
        	else if (preci > 17)
        		preci = 17;

        	short num = preci;

        	// real number
        	if (!infnan) {
        		// compute exponent
        		if (d >= 1) {
        			while (d >= 10000000000) {
        				d *= 0.0000000001;
        				x+=10;
        			}
        			while (d >= 10) {
        				d *= 0.1;
        				++x;
        			}
        		} else if (d > 0) {
        			while (d < 0.0000000001) {
        				d *= 10000000000;
        				x -= 10;
        			}
        			while (d < 1) {
        				d *= 10;
        				--x;
        			}
        		}

        		// count of digts:
        		// f, F : all digits before dot, preci digits behind.
        		// e, E : one digit before dot, preci digits behind dot
        		// g, G : preci digits total

        		// count of digits
        		// f : x + preci
        		// e : 1 + preci
        		// g : preci
        		if (!type) {
        			num += x;
        			if (num >= REQUIREDBUFFER)
        				num = REQUIREDBUFFER;
        		} else if (type == 'E' || type == 'e') {
        			++num;
        		}
    			if (num <= 0)
    				num = 1;

//        		printf("num=%d|", num);

        		// compute the digits
        		for (short i = 0; i < num; ++i) {
        			short z = d;
        			d = (d - z) * 10;
        			buffer[i] = '0' + z;
        		}

        		// round up
        		if ( d >= 5.) {
        			short i = num - 1;
        			for (; i >= 0; --i) {
        				if (++buffer[i] <= '9')
        					break;
        				buffer[i] = '0';
        			}
        			// overflow: start behind .  at 0 and first digit is '1'
        			if (i < 0) {
        				++x;
        				--num;
        				j = 0;
        			}
        		}

        		// kill trailing zeroes
        		if (type == 'g' || type == 'G') {
        			short i = num - 1;
        			for (; i > 0; --i) {
        				if (buffer[i] != '0')
        					break;
        			}
        			// i == count - 1 of digits without trailing zero
//        			printf("num=%d, preci=%d, i=%d\n", num, preci, i);
        			if (x >= 0 && x < preci) {
        				preci = i - x;
        				if (preci < 0) preci = 0;
        				num = x + 1 + preci;
        				type = 0;
        			} else {
        				preci = i;
        				num = i + 1;
        				type = type == 'g' ? 'e' : 'E';
        			}
//        			printf("num=%d, preci=%d, i=%d\n", num, preci, i);
        		}

        		// calculate width
        		if (type) {
        			// 1e+00
        			width -= 5 + preci;

        			if (x < -99) {
        				--width;
        			} else if (x > 99) {
        				--width;
        			}
        		} else {
        			// 123.456  -> x = 2, preci = 3
        			width -= x + 1 + preci ;
        		}

        		// dot?
        		if (preci > 0 || (flags &ALTERNATEFLAG))
        			--width;
        	}

        	if (sign)
        		--width;

        	//if (width < 0) width = 0;

        //	printf("width=%d\n", width);

        	// pad on left side
        	if (!(flags&LALIGNFLAG))
        		while (--width >= 0)
        			OUT(pad);

        	// output sign if set
        	if (sign)
        		OUT(sign);

        	if (infnan) {
        		// output inf/nan
        		OUT(infnan[0]);
        		OUT(infnan[1]);
        		OUT(infnan[2]);
        	} else {
//    			printf("num=%d, preci=%d, i=%d, j=%d\n", num, preci, i, j);
        		// output the number
        		OUT(j ? buffer[0] : '1');

        		if (!type) {
        			for(;j <= x && j < num; ++j)
        				OUT(buffer[j]);
        			for (;j <= x; ++j)
        				OUT('0');
        		}

        		if (preci || (flags &ALTERNATEFLAG))
        			OUT(__decimalpoint[0]);

        		for(; j < num; ++j) {
        			OUT(buffer[j]);
        			--preci;
        		}
        		if (!type)
        			for (;preci > 0; --preci)
        				OUT('0');

        		if (type) {
        			OUT(type);
        			if (x < 0) {
        				OUT('-');
        				x = -x;
        			} else
        			OUT('+');
        			--width;
        			if (x > 99) {
        				short z = x/100;
        				OUT('0' + z);
        				x -= z * 100;
        				--width;
        			}
        			short z = x/10;
        			OUT('0' + z);
        			x -= z * 10;
        			--width;
        			OUT('0' + x);
        			--width;
        		}
        	}

        	// pad on right side
        	if (flags&LALIGNFLAG)
        		while (--width >= 0)
        			OUT(' ');
//puts("");

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
