const unsigned char * const _ctype_;

int towlower(int c)
{ return _ctype_[1+c]&1?c+L'a'-L'A':c; }
