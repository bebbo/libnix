unsigned __ulldivus(unsigned long long * llp, unsigned short n) {
	struct LL {
		unsigned long hi;
		union {
			unsigned long lo;
			struct {
				unsigned short exponent;
				unsigned short y;
			} s;
		} u;
	}* hl = (struct LL *) llp;

	unsigned r;
	unsigned long h = hl->hi;
	if (h) {
		unsigned l = hl->u.s.exponent;
		unsigned k = hl->u.s.y;
		unsigned c = h % n;
		h = h / n;
		l = l + (c << 16);
		c = l % n;
		l = l / n;
		k = k + (c << 16);
		r = k % n;
		k = k / n;
		hl->u.lo = (l << 16) + k;
		hl->hi = h + (l >> 16);
		return r;
	}

	r = hl->u.lo % n;
	hl->u.lo /= n;
	return r;
}
