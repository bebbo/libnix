#include <wctype.h>
#include <errno.h>
#include <string.h>

/* valid values for wctype_t */
#define WC_ALNUM	1
#define WC_ALPHA	2
#define WC_BLANK	3
#define WC_CNTRL	4
#define WC_DIGIT	5
#define WC_GRAPH	6
#define WC_LOWER	7
#define WC_PRINT	8
#define WC_PUNCT	9
#define WC_SPACE	10
#define WC_UPPER	11
#define WC_XDIGIT	12
wctype_t
wctype (const char *c)
{
  switch (*c)
    {
    case 'a':
      if (!strcmp (c, "alnum"))
        return WC_ALNUM; 
      else if (!strcmp (c, "alpha"))
        return WC_ALPHA;
      break;
    case 'b':
      if (!strcmp (c, "blank"))
        return WC_BLANK;
      break;
    case 'c':
      if (!strcmp (c, "cntrl"))
        return WC_CNTRL;
      break;
    case 'd':
      if (!strcmp (c, "digit"))
        return WC_DIGIT;
      break;
    case 'g':
      if (!strcmp (c, "graph"))
        return WC_GRAPH;
      break;
    case 'l':
      if (!strcmp (c, "lower"))
        return WC_LOWER;
      break;
    case 'p':
      if (!strcmp (c, "print"))
        return WC_PRINT;
      else if (!strcmp (c, "punct"))
        return WC_PUNCT;
      break;
    case 's':
      if (!strcmp (c, "space"))
        return WC_SPACE;
      break;
    case 'u':
      if (!strcmp (c, "upper"))
        return WC_UPPER;
      break;
    case 'x':
      if (!strcmp (c, "xdigit"))
        return WC_XDIGIT;
      break;
    }

  /* otherwise invalid */
  errno = EINVAL;
  return 0;
}
