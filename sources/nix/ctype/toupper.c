const unsigned char * const _ctype_;

int toupper(int c)
{ return _ctype_[1+c]&2?c+'A'-'a':c; }
