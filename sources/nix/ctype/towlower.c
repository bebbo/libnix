extern const unsigned char * _ctype_ptr;

int towlower(int c)
{ return _ctype_ptr[1+c]&1?c+L'a'-L'A':c; }
