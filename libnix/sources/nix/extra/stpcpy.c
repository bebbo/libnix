char *stpcpy(char *dest,char *source)
{
  while((*dest++=*source++)); return(dest-1);
}
