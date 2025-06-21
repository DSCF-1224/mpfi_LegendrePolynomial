#include <stdio.h>
#include "mpfi_legendre_polynomial.h"



/// @brief Parameter to set `step_x`
#define NUM_INTERVALS 255UL

/// @brief Specify the range to compute legendre polynomial
#define MINVAL_X -1L

/// @brief Specify the range to compute legendre polynomial
#define MAXVAL_X  1L



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

    snprintf(output_filename, sizeof(output_filename), "precision_%3.3ld_degree_%3.3ld.dat", precision, degree);

    FILE *output_filestream = fopen(output_filename, "w");

    if (output_filestream == NULL)
    {
        fprintf(stderr, "Failed to open `%s`", output_filename);
        return EXIT_FAILURE;
    }



    mpfi_t step_x, minval_x;

    mpfi_init2( step_x   , precision );
    mpfi_init2( minval_x , precision );

    struct mpfi_LegendrePolynomial_t          legendre_polynomial;
    struct mpfi_LegendrePolynomialWorkspace_t workspace;

    mpfi_init2_LegendrePolynomial          ( &legendre_polynomial , precision );
    mpfi_init2_LegendrePolynomialWorkspace ( &workspace           , precision );



    mpfi_set_si( minval_x, MINVAL_X );

    mpfi_set_si( workspace.temp1 , (MAXVAL_X - MINVAL_X)                 );
    mpfi_div_ui( step_x          , workspace.temp1       , NUM_INTERVALS );



    for (unsigned long i = 0; i < NUM_INTERVALS; i++)
    {
        mpfi_mul_ui( workspace.temp1       , step_x   , i               );
        mpfi_add   ( legendre_polynomial.x , minval_x , workspace.temp1 );

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

        mpfr_fprintf( output_filestream, "%Ra " , &legendre_polynomial.x                ->left  );
        mpfr_fprintf( output_filestream, "%Ra " , &legendre_polynomial.x                ->right );
        mpfr_fprintf( output_filestream, "%Ra " , &legendre_polynomial.polynomial_target->left  );
        mpfr_fprintf( output_filestream, "%Ra " , &legendre_polynomial.polynomial_target->right );
        mpfr_fprintf( output_filestream, "%d\n" ,  status                                       );
    }



    fclose(output_filestream);

    mpfi_clear( step_x   );
    mpfi_clear( minval_x );

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
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision,  1UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision,  2UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision,  3UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision,  4UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision,  5UL) ) return EXIT_FAILURE;

    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision,  9UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 19UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 20UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 29UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 30UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 39UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 40UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 49UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 50UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 59UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 60UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 69UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 70UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 79UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 80UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 89UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 90UL) ) return EXIT_FAILURE;
    if ( example_mpfi_LegendrePolynomial_Recursive_unit(precision, 99UL) ) return EXIT_FAILURE;

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
