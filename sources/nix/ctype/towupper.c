extern const unsigned char * _ctype_ptr;

int towupper(int c)
{ return _ctype_ptr[1+c]&2?c+L'A'-L'a':c; }
