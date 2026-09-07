#include <stddef.h>
#include <stdio.h>
#include "mpfi_legendre_polynomial.h"



/// @brief Parameter to set `step_x`
#define NUM_INTERVALS 2048UL



static void fprintf_result_LegendrePolynomial(
    /***/ /****/ FILE                      *const output_filestream   , //
    const struct mpfi_LegendrePolynomial_t *const legendre_polynomial , //
    /***/ /****/ mpfr_srcptr               /****/ diam                , //
    const /****/ int                       /****/ status              ) {

    mpfr_fprintf( output_filestream, "%Ra " , &legendre_polynomial -> x                 -> left  );
    mpfr_fprintf( output_filestream, "%Ra " , &legendre_polynomial -> x                 -> right );
    mpfr_fprintf( output_filestream, "%Ra " , &legendre_polynomial -> polynomial_target -> left  );
    mpfr_fprintf( output_filestream, "%Ra " , &legendre_polynomial -> polynomial_target -> right );
    mpfr_fprintf( output_filestream, "%Ra " ,  diam                                              );
    mpfr_fprintf( output_filestream, "%d\n" ,  status                                            );

}



/**
 * @brief Run example how to use mpfi_LegendrePolynomial_Recursive
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
 * @param precision Precision for the floating-point computations.
 * @param degree    The target degree of Legendre polynomial.
 * 
 * @version Experimental
 */
int example_mpfi_LegendrePolynomial_Recursive_unit(const mpfr_prec_t precision, const unsigned long degree)
{
    char output_filename[FILENAME_MAX];

    snprintf(output_filename, sizeof(output_filename), "examples/precision_%3.3ld_degree_%3.3lu.dat", precision, degree);

    FILE *output_filestream = fopen(output_filename, "w");

    if (output_filestream == NULL)
    {
        fprintf(stderr, "Failed to open `%s`\n", output_filename);
        return EXIT_FAILURE;
    }



    mpfr_t diam;

    mpfr_init2(diam, precision);

    mpfi_t step_x;

    mpfi_init2(step_x, precision);

    struct mpfi_LegendrePolynomial_t          legendre_polynomial;
    struct mpfi_LegendrePolynomialWorkspace_t workspace;

    mpfi_init2_LegendrePolynomial          ( &legendre_polynomial , precision );
    mpfi_init2_LegendrePolynomialWorkspace ( &workspace           , precision );



    // diam is reused here to compute the range width
    mpfi_diam_abs(diam, legendre_polynomial.range);

    mpfi_set_fr(step_x, diam);

    mpfi_div_ui(step_x, step_x, NUM_INTERVALS);



    // -1 <= x < +1
    for (unsigned long i = 0; i < NUM_INTERVALS; i++)
    {
        mpfi_mul_ui( workspace.temp1 , //
        /**********/ step_x          , //
        /**********/ i                 );

        mpfi_add_fr(  legendre_polynomial.x           , //
        /**********/  workspace.temp1                 , //
        /**********/ &legendre_polynomial.range->left   );

        const int status =
            mpfi_LegendrePolynomial_Recursive(
                /**/  legendre_polynomial.polynomial_target , //
                /**/  legendre_polynomial.polynomial_ref1   , //
                /**/  legendre_polynomial.polynomial_ref2   , //
                /**/  degree                                , //
                /**/  legendre_polynomial.range             , //
                /**/  legendre_polynomial.x                 , //
                /**/ &workspace                               //
            );

        mpfi_diam( diam , legendre_polynomial.polynomial_target );

        fprintf_result_LegendrePolynomial(output_filestream, &legendre_polynomial, diam, status);
    }

    // x = +1
    mpfi_set_fr(legendre_polynomial.x, &legendre_polynomial.range->right);

    const int status =
        mpfi_LegendrePolynomial_Recursive(
            /**/  legendre_polynomial.polynomial_target , //
            /**/  legendre_polynomial.polynomial_ref1   , //
            /**/  legendre_polynomial.polynomial_ref2   , //
            /**/  degree                                , //
            /**/  legendre_polynomial.range             , //
            /**/  legendre_polynomial.x                 , //
            /**/ &workspace                               //
        );

    mpfi_diam( diam , legendre_polynomial.polynomial_target );

    fprintf_result_LegendrePolynomial(output_filestream, &legendre_polynomial, diam, status);




    fclose(output_filestream);



    mpfr_clear(diam);

    mpfi_clear(step_x);

    mpfi_clear_LegendrePolynomial          ( &legendre_polynomial );
    mpfi_clear_LegendrePolynomialWorkspace ( &workspace           );



    return EXIT_SUCCESS;
}


/**
 * @brief Run example how to use mpfi_LegendrePolynomial_Recursive
 * 
 * @param precision Precision for the floating-point computations.
 * 
 * @version Experimental
 */
int example_mpfi_LegendrePolynomial_Recursive(const mpfr_prec_t precision)
{
    static const unsigned long degrees[] = {
        // Low-degree cases (1-10): covers every degree in the 1-digit range
         1UL,  2UL,  3UL,  4UL,  5UL,  6UL,  7UL,  8UL,  9UL, 10UL,
        // Multiples of 11 (2-digit range): even/odd degrees balanced
        11UL, 22UL, 33UL, 44UL, 55UL, 66UL, 77UL, 88UL, 99UL,
    };

    for (size_t i = 0; i < ( sizeof(degrees) / sizeof(degrees[0]) ); i++)
    {
        if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, degrees[i]) )
        {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}



/**
 * @note
 * How to compile (from the repository root):
 * ```
 * gcc examples/example.c -I. -Wall -Wextra -Werror -lgmp -lmpfr -lmpfi
 * ```
 * @version Experimental
 */
int main(void)
{
    printf( "GMP  VERSION; %s\n", gmp_version        );
    printf( "MPFR VERSION; %s\n", mpfr_get_version() );
    printf( "MPFI VERSION; %s\n", mpfi_get_version() );

    if ( example_mpfi_LegendrePolynomial_Recursive(  24UL ) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive(  53UL ) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive( 113UL ) ) return EXIT_FAILURE;

    printf("The example completed successfully.\n");

    return EXIT_SUCCESS;
}
