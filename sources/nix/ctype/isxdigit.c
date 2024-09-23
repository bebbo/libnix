extern const unsigned char * _ctype_ptr;

int isxdigit(int c)
{ return _ctype_ptr[1+c]&68; }
