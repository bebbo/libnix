extern const unsigned char * _ctype_ptr;

int tolower(int c)
{ return _ctype_ptr[1+c]&1?c+'a'-'A':c; }
