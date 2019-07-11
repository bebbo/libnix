/*
~/opt/m68k-amigaos_08Jul19/bin/m68k-amigaos-gcc cpu_test.c -m68020 -m68881 -noixemul -Wl,-Map=name.map,--trace
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
        printf("Hello world, Pi=%f\n",M_PI);

#ifdef __HAVE_68881__ 
	printf("___HAVE_68881____defined...\n");
#endif

	return 0;
}
