extern const unsigned char * _ctype_ptr;

int islower(int c)
{ return _ctype_ptr[1+c]&2; }
