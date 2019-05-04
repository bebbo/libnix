extern void __initlibraries(void);
void *__LIB_LIST__[1] = { __initlibraries
#if defined(___mc68020)
		, __cpucheck
#endif
};
