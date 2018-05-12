#include <wctype.h>
#include <errno.h>

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

int
iswctype (wint_t c, wctype_t desc)
{
  switch (desc)
    {
    case WC_ALNUM:
      return iswalnum (c);
    case WC_ALPHA:
      return iswalpha (c);
    case WC_BLANK:
      return iswblank (c);
    case WC_CNTRL:
      return iswcntrl (c);
    case WC_DIGIT:
      return iswdigit (c);
    case WC_GRAPH:
      return iswgraph (c);
    case WC_LOWER:
      return iswlower (c);
    case WC_PRINT:
      return iswprint (c);
    case WC_PUNCT:
      return iswpunct (c);
    case WC_SPACE:
      return iswspace (c);
    case WC_UPPER:
      return iswupper (c);
    case WC_XDIGIT:
      return iswxdigit (c);
    default:
      return 0; /* eliminate warning */
    }

  /* otherwise unknown */
  return 0;
}
