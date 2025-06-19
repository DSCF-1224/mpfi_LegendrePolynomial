#include <stdio.h>
#include "mpfi_legendre_polynomial.h"


/**
 * @brief
 * <ol>
 *   <li>
 *     Open the file to save the results.<br>
 *     If opening fails, terminate the execution of this function at that point.
 *   </li>
 *   <li>
 *     Close the file containing the results.
 *   </li>
 * </ol>
 * 
 * @version Experimental
 */
int example_mpfi_LegendrePolynomial_Recursive(const unsigned long degree)
{
    char output_filename[FILENAME_MAX];

    snprintf(output_filename, sizeof(output_filename), "degree_%3.3ld.dat", degree);

    FILE *output_filestream = fopen(output_filename, "w");

    if (output_filestream == NULL)
    {
        fprintf(stderr, "Failed to open `%s`", output_filename);
        return EXIT_FAILURE;
    }

    fclose(output_filestream);

    return EXIT_SUCCESS;
}



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

    example_mpfi_LegendrePolynomial_Recursive(  24UL );
    example_mpfi_LegendrePolynomial_Recursive(  53UL );
    example_mpfi_LegendrePolynomial_Recursive( 113UL );

    printf("The example completed successfully.\n");
}
