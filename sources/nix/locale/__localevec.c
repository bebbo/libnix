#ifndef __KICK13__
#include <libraries/locale.h>

/* This is the vector of Locales for the different locale types.
 * Since the default locale is not NULL, NULL means "C" locale.
 * This is the default if locale.library could not be opened
 * or setlocale is never referenced.
 */

struct Locale *__localevec[5] = { 0, 0, 0, 0, 0 };

#endif
