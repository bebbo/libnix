extern const unsigned char * _ctype_ptr;

int toupper(int c)
{ return _ctype_ptr[1+c]&2?c+'A'-'a':c; }
