#include <libintl.h>
__stdargs char * gettext (const char * msgid) {
	return msgid;
}
__stdargs char * dgettext (const char * domainname,const char * msgid) {
	return msgid;
}
__stdargs char * dcgettext (const char * domainname, const char* msgid, int category) {
	return msgid;
}
