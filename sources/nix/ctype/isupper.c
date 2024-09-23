extern const unsigned char * _ctype_ptr;

int isupper(int c)
{ return _ctype_ptr[1+c]&1; }
