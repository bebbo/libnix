/**
 * written by nonarkitten - enhanced by bebbo
 */

extern char* utoa(int value, char *str, int base);

ALIAS( ltoa, itoa);

char* itoa(int value, char *str, int base) {
	if (!str)
		return str;
	if (value < 0 && base == 10) {
		*str = '-';
		utoa(-value, str + 1, base);
		return str;
	}
	return utoa(value, str, base);
}
