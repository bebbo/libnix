/*
 * Get the AmigaDOS FileHandle from the filedescriptor.
 * Be careful when mixing both kinds of I/O (flush() between changing).
 *
 * DICE has such a function SAS has not.
 * It's not ANSI but it's encapsulated and may be useful - so why not :-).
 * 
 */
unsigned long *__stdfiledes;

unsigned long fdtofh(int filedescriptor)
{
  return __stdfiledes[filedescriptor];
}
