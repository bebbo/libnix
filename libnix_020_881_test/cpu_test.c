/*
~/opt/m68k-amigaos_08Jul19/bin/m68k-amigaos-gcc cpu_test.c -m68020 -m68881 -noixemul -Wl,-Map=name.map,--trace
*/

#include <stdio.h>

// taken from https://stackoverflow.com/questions/32672693/calculating-pi-with-taylor-method-c


double pi(int n) {
    double sum = 0.0;
    int sign = 1;
    int i;
    for (i = 0; i < n; ++i) {
        sum += sign/(2.0*i+1.0);
        sign *= -1;
    }
    return 4.0*sum;
}


int main(void)
{
        printf("Hello world, Pi=%1.2f\n",pi(1000));

#ifdef __HAVE_68881__ 
	printf("___HAVE_68881____defined...\n");
#endif

	return 0;
}
