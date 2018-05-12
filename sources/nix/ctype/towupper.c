extern char *_ctype_;

int towupper(int c)
{ return _ctype_[1+c]&2?c+L'A'-L'a':c; }
