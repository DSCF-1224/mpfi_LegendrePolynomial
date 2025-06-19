#include <stdio.h>
#include "mpfi_legendre_polynomial.h"


/**
 * @note
 * How to compile:
 * ```
 * gcc example.c -Wall -Wextra -lgmp -lmpfr -lmpfi
 * ```
 * @version Experimental
 */
int main(void)
{
    printf( "GMP  VERSION; %s\n", gmp_version        );
    printf( "MPFR VERSION; %s\n", mpfr_get_version() );
    printf( "MPFI VERSION; %s\n", mpfi_get_version() );

    printf("The example completed successfully.\n");
}
