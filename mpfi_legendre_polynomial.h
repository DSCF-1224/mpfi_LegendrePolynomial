#ifndef MPFI_LEGENDRE_POLYNOMIAL_H
#define MPFI_LEGENDRE_POLYNOMIAL_H



#include <stdlib.h>
#include <string.h>
#include <mpfr.h>
#include <mpfi.h>



/**
 * @brief Computes the Legendre polynomial of degree 0: P_0(x) = 1.
 * 
 * @param[out] result Legendre polynomial of degree 0
 * 
 * @see 
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/set_ui.c
 */
static void mpfi_LegendrePolynomial_ComputeDegree0(mpfi_ptr result) {

    mpfi_set_ui(result, 1UL);

}



/**
 * @brief Computes the Legendre polynomial of degree 1: P_1(x) = x.
 * 
 * @param[out] result Legendre polynomial of degree 1
 * @param[in ] x      Evaluation argument of the Legendre polynomial
 * 
 * @see 
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/set.c
 */
static void mpfi_LegendrePolynomial_ComputeDegree1(mpfi_ptr result, mpfi_srcptr x) {

    mpfi_set(result, x);

}



struct mpfi_LegendrePolynomial_t{

    mpfi_t derivative;        /**< First derivative of the Legendre polynomial */
    mpfi_t polynomial_target; /**< Legendre polynomial of the target degree (n) */
    mpfi_t polynomial_ref1;   /**< Legendre polynomial of the degree (n - 1) */
    mpfi_t polynomial_ref2;   /**< Legendre polynomial of the degree (n - 2) */
    mpfi_t range;             /**< Interval [-1, 1] */
    mpfi_t x;                 /**< Evaluation argument of the Legendre polynomial */
    mpfi_t x_copy;            /**< Copy of the evaluation argument */
    mpfi_t x_diff;            /**< Difference of the evaluation argument */

};



/**
 * @brief Clears the memory allocated for a Legendre polynomial structure.
 * 
 * @param[in] legendre_polynomial_ptr Pointer to the Legendre polynomial structure
 * 
 * @see 
 * - https://gitlab.inria.fr/mpfr/mpfr/-/blob/master/src/clear.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/clear.c
 */
void mpfi_clear_LegendrePolynomial(struct mpfi_LegendrePolynomial_t *const legendre_polynomial_ptr) {

    if (legendre_polynomial_ptr) {

        mpfi_clear( legendre_polynomial_ptr->derivative        );
        mpfi_clear( legendre_polynomial_ptr->polynomial_target );
        mpfi_clear( legendre_polynomial_ptr->polynomial_ref1   );
        mpfi_clear( legendre_polynomial_ptr->polynomial_ref2   );
        mpfi_clear( legendre_polynomial_ptr->range             );
        mpfi_clear( legendre_polynomial_ptr->x                 );
        mpfi_clear( legendre_polynomial_ptr->x_copy            );
        mpfi_clear( legendre_polynomial_ptr->x_diff            );

    }

}



/**
 * @brief Initializes a Legendre polynomial structure with the given precision.
 * 
 * @param[in] legendre_polynomial_ptr Pointer to the Legendre polynomial structure.
 * @param[in] precision Precision for the floating-point computations.
 * 
 * @see
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/interv_d.c
 * - https://gitlab.inria.fr/mpfr/mpfr/-/blob/master/src/init2.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/init2.c
 */
void mpfi_init2_LegendrePolynomial(
    /***/ struct mpfi_LegendrePolynomial_t *const legendre_polynomial_ptr , //
    const /****/ mpfr_prec_t                      precision               ) {

    if (legendre_polynomial_ptr) {

        memset( legendre_polynomial_ptr, 0, sizeof(*legendre_polynomial_ptr) );

        mpfi_init2( legendre_polynomial_ptr->derivative        , precision );
        mpfi_init2( legendre_polynomial_ptr->polynomial_target , precision );
        mpfi_init2( legendre_polynomial_ptr->polynomial_ref1   , precision );
        mpfi_init2( legendre_polynomial_ptr->polynomial_ref2   , precision );
        mpfi_init2( legendre_polynomial_ptr->range             , precision );
        mpfi_init2( legendre_polynomial_ptr->x                 , precision );
        mpfi_init2( legendre_polynomial_ptr->x_copy            , precision );
        mpfi_init2( legendre_polynomial_ptr->x_diff            , precision );
        
        mpfi_interv_d( legendre_polynomial_ptr->range, -1.0, 1.0 );

    }

}



/**
 * @brief Checks whether the evaluation argument is bounded and lies within the domain.
 * 
 * @param[in] x     Evaluation argument of the Legendre polynomial
 * @param[in] range Interval [-1,1]
 * 
 * @return Nonzero if x is bounded and inside range; zero otherwise.
 * 
 * @see
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/is_inside.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/predicates.c
 */
static int mpfi_is_valid_LegendrePolynomial(
    mpfi_srcptr x     , //
    mpfi_srcptr range ) {

    return mpfi_bounded_p(x) && mpfi_is_inside(x, range);

}



/**
 * @struct mpfi_LegendrePolynomialWorkspace_t
 * @brief Structure for temporary storage used during polynomial computations.
 */
struct mpfi_LegendrePolynomialWorkspace_t {

    mpfi_t denominator; /**< Stores the denominator during computations */
    mpfi_t numerator;   /**< Stores the numerator during computations */
    mpfi_t temp1;       /**< Temporary variable for calculations */
    mpfi_t temp2;       /**< Temporary variable for calculations */
    mpfi_t temp3;       /**< Temporary variable for calculations */
    mpfi_t temp4;       /**< Temporary variable for calculations */

};



/**
 * @brief Clears the memory allocated for a Legendre polynomial workspace.
 * 
 * @param[in] legendre_polynomial_Workspace_ptr Pointer to the workspace structure.
 * 
 * @see 
 * - https://gitlab.inria.fr/mpfr/mpfr/-/blob/master/src/clear.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/clear.c
 */
void mpfi_clear_LegendrePolynomialWorkspace(struct mpfi_LegendrePolynomialWorkspace_t *const legendre_polynomial_Workspace_ptr) {

    if (legendre_polynomial_Workspace_ptr) {

        mpfi_clear( legendre_polynomial_Workspace_ptr->denominator );
        mpfi_clear( legendre_polynomial_Workspace_ptr->numerator   );
        mpfi_clear( legendre_polynomial_Workspace_ptr->temp1       );
        mpfi_clear( legendre_polynomial_Workspace_ptr->temp2       );
        mpfi_clear( legendre_polynomial_Workspace_ptr->temp3       );
        mpfi_clear( legendre_polynomial_Workspace_ptr->temp4       );

    }

}



/**
 * @brief Initializes a Legendre polynomial workspace with the given precision.
 * 
 * @param[in] legendre_polynomial_Workspace_ptr Pointer to the workspace structure.
 * @param[in] precision Precision for the floating-point computations.
 * 
 * @see
 * - https://gitlab.inria.fr/mpfr/mpfr/-/blob/master/src/init2.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/init2.c
 */
void mpfi_init2_LegendrePolynomialWorkspace(
    /***/ struct mpfi_LegendrePolynomialWorkspace_t *const legendre_polynomial_Workspace_ptr , //
    const /****/ mpfr_prec_t                               precision                         ) {

    if (legendre_polynomial_Workspace_ptr) {

        memset( legendre_polynomial_Workspace_ptr, 0, sizeof(*legendre_polynomial_Workspace_ptr) );

        mpfi_init2( legendre_polynomial_Workspace_ptr->denominator , precision );
        mpfi_init2( legendre_polynomial_Workspace_ptr->numerator   , precision );
        mpfi_init2( legendre_polynomial_Workspace_ptr->temp1       , precision );
        mpfi_init2( legendre_polynomial_Workspace_ptr->temp2       , precision );
        mpfi_init2( legendre_polynomial_Workspace_ptr->temp3       , precision );
        mpfi_init2( legendre_polynomial_Workspace_ptr->temp4       , precision );

    }

}



/**
 * @param[  out] result    Legendre polynomial of the target degree
 * @param[in   ] degree    The target degree of Legendre polynomial
 * @param[in   ] range     Interval [-1, 1]
 * @param[in   ] x         Evaluation point
 * @param[in   ] ref1      Legendre polynomial of the degree (n - 1)
 * @param[in   ] ref2      Legendre polynomial of the degree (n - 2)
 * @param[inout] workspace Temporary storage used during polynomial computations
 * 
 * @see
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/div.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/intersect.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/is_inside.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/mul.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/predicates.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/set_ui.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/sub.c
 */
static int mpfi_LegendrePolynomial_RecursiveSingleStep(
    /***/ /****/ mpfi_ptr                                  result    , //
    const /****/ unsigned long                             degree    , //
    /***/ /****/ mpfi_srcptr                               range     , //
    /***/ /****/ mpfi_srcptr                               x         , //
    /***/ /****/ mpfi_srcptr                               ref1      , //
    /***/ /****/ mpfi_srcptr                               ref2      , //
    /***/ struct mpfi_LegendrePolynomialWorkspace_t *const workspace ) {

    // temp1 <- n
    mpfi_set_ui( workspace->temp1 , degree );

    // temp2 <- n - 1
    mpfi_set_ui( workspace->temp2 , (degree - 1UL) ); 

    // temp3 <- 2n - 1
    mpfi_set_ui( workspace->temp3 , (degree + degree - 1UL) );

    // temp4 <- temp3 * x
    //       <- ( 2n - 1 ) * x
    mpfi_mul( workspace->temp4 , workspace->temp3 , x );

    // temp3 <- temp4          * lp[ n - 1 ]
    //       <- ( 2n - 1 ) * x * lp[ n - 1 ]
    mpfi_mul( workspace->temp3 , workspace->temp4 , ref1 );

    // temp4 <- temp2     * lp[ n - 2 ]
    //       <- ( n - 1 ) * lp[ n - 2 ]
    mpfi_mul( workspace->temp4 , workspace->temp2 , ref2 );

    // temp2 <- temp3 - temp4
    //       <- ( 2n - 1 ) * x * lp[ n - 1 ] - ( n - 1 ) * lp[ n - 2 ]
    mpfi_sub( workspace->temp2 , workspace->temp3 , workspace->temp4 );

    // result <- temp2 / temp1
    //        <- { ( 2n - 1 ) * x * lp[ n - 1 ] - ( n - 1 ) * lp[ n - 2 ] } / n
    mpfi_div( result , workspace->temp2 , workspace->temp1 );

    // validation: result (before clipping)
    if ( mpfi_nan_p(result) || mpfi_inf_p(result) ) return EXIT_FAILURE;

    // result <- result \cap range
    mpfi_intersect(result, result, range);

    // validation: result (after clipping)
    if ( mpfi_is_empty(result) ) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}



/**
 * @param[in] result    Legendre polynomial of the target degree (n)
 * @param[in] ref1      Legendre polynomial of the degree (n - 1)
 * @param[in] ref2      Legendre polynomial of the degree (n - 2)
 * @param[in] degree    The target degree of Legendre polynomial
 * @param[in] range     Interval [-1, 1]
 * @param[in] x         Evaluation point
 * @param[in] workspace Temporary storage used during polynomial computations
 */
int mpfi_LegendrePolynomial_Recursive(
    /***/ /****/ mpfi_ptr                                  result    , //
    /***/ /****/ mpfi_ptr                                  ref1      , //
    /***/ /****/ mpfi_ptr                                  ref2      , //
    const /****/ unsigned long                             degree    , //
    /***/ /****/ mpfi_srcptr                               range     , //
    const /****/ mpfi_srcptr                               x         , //
    /***/ struct mpfi_LegendrePolynomialWorkspace_t *const workspace ) {


    if ( 
        (degree < 2UL) ||
        !workspace     ||
        !range         ||
        !x             ||
        !ref1          ||
        !ref2          ||
        !mpfi_is_valid_LegendrePolynomial(x, range) ) {

        mpfr_set_nan( &result->left  );
        mpfr_set_nan( &result->right );

        return EXIT_FAILURE;

    }


    mpfi_LegendrePolynomial_ComputeDegree0(ref2);
    mpfi_LegendrePolynomial_ComputeDegree1(ref1, x);

    for (unsigned long i = 2UL; i <= degree; i++) {

        const int status =
            mpfi_LegendrePolynomial_RecursiveSingleStep(
                result    , //
                i         , //
                range     , //
                x         , //
                ref1      , //
                ref2      , //
                workspace   //
            );

        if ( status != EXIT_SUCCESS ) return EXIT_FAILURE;

        if ( i == degree ) break;

        mpfi_set( ref2, ref1   );
        mpfi_set( ref1, result );

    }

    return EXIT_SUCCESS;
}



/**
 * @brief Computes the Legendre polynomial for any degree, dispatching
 *        to the degree 0/1 computation or to the recursive
 *        computation depending on the requested degree.
 * 
 * @param[in] result    Legendre polynomial of the target degree (n)
 * @param[in] ref1      Legendre polynomial of the degree (n - 1); set to NaN if undefined for the given degree
 * @param[in] ref2      Legendre polynomial of the degree (n - 2); set to NaN if undefined for the given degree
 * @param[in] degree    The target degree of Legendre polynomial
 * @param[in] range     Interval [-1, 1]
 * @param[in] x         Evaluation argument of the Legendre polynomial
 * @param[in] workspace Temporary storage used during polynomial computations; unused if degree < 2
 */
int mpfi_LegendrePolynomial(
    /***/ /****/ mpfi_ptr                                  result    , //
    /***/ /****/ mpfi_ptr                                  ref1      , //
    /***/ /****/ mpfi_ptr                                  ref2      , //
    const /****/ unsigned long                             degree    , //
    /***/ /****/ mpfi_srcptr                               range     , //
    const /****/ mpfi_srcptr                               x         , //
    /***/ struct mpfi_LegendrePolynomialWorkspace_t *const workspace ) {

    if ( degree >= 2UL ) {
        return mpfi_LegendrePolynomial_Recursive(result, ref1, ref2, degree, range, x, workspace);
    }

    if ( !ref1 || !ref2 || !range || !x || !mpfi_is_valid_LegendrePolynomial(x, range) ) {
        mpfr_set_nan(&result->left);
        mpfr_set_nan(&result->right);
        return EXIT_FAILURE;
    }

    if (degree == 0UL) {

        // P_0
        mpfi_LegendrePolynomial_ComputeDegree0(result);

        // P_{-1}: undefined
        mpfr_set_nan(&ref1->left);
        mpfr_set_nan(&ref1->right); 

        // P_{-2}: undefined
        mpfr_set_nan(&ref2->left);
        mpfr_set_nan(&ref2->right);

    } else { // degree == 1UL

        // P_1
        mpfi_LegendrePolynomial_ComputeDegree1(result, x);

        // P_0
        mpfi_LegendrePolynomial_ComputeDegree0(ref1);

        // P_{-1}: undefined
        mpfr_set_nan(&ref2->left);
        mpfr_set_nan(&ref2->right);

    }

    return EXIT_SUCCESS;
}



/**
 * @param[in] derivative          First derivative of the Legendre polynomial of the target degree (n)
 * @param[in] degree              The target degree of Legendre polynomial
 * @param[in] x                   Evaluation point
 * @param[in] legendre_polynomial Legendre polynomial at the evaluation point
 * @param[in] workspace           Temporary storage used during polynomial computations.
 * 
 * @see
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/div.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/mul.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/mul_ui.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/set_ui.c
 * - https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/sub.c
 */
int mpfi_LegendrePolynomial_Derivative(
    /***/ /****/ mpfi_ptr                                  derivative          , //
    const /****/ unsigned long                             degree              , //
    const struct mpfi_LegendrePolynomial_t          *const legendre_polynomial , //
    /***/ struct mpfi_LegendrePolynomialWorkspace_t *const workspace           ) {

    // validation: x
    if ( !mpfi_is_valid_LegendrePolynomial(legendre_polynomial->x, legendre_polynomial->range) ) {

        mpfr_set_nan( &(derivative->left  ) );
        mpfr_set_nan( &(derivative->right ) );

        return EXIT_FAILURE;

    }

    // temp1 <- 1
    mpfi_set_ui( workspace->temp1 , 1UL ); 

    // temp2 <- x * x
    mpfi_mul( workspace->temp2       , //
    /*******/ legendre_polynomial->x , //
    /*******/ legendre_polynomial->x   );

    // denominator <- 1 - x * x
    mpfi_sub( workspace->denominator , //
    /*******/ workspace->temp1       , //
    /*******/ workspace->temp2         );

    // temp1 <- x * lp[ n ]
    mpfi_mul( workspace->temp1                       , //
    /*******/ legendre_polynomial->x                 , //
    /*******/ legendre_polynomial->polynomial_target   );

    // temp2 <- lp[ n - 1 ] - x * lp[ n ]
    mpfi_sub( workspace->temp2                     , //
    /*******/ legendre_polynomial->polynomial_ref1 , //
    /*******/ workspace->temp1                       );

    // numerator <- ( lp[ n - 1 ] - x * lp[ n ] ) * n
    mpfi_mul_ui( workspace->numerator   , //
    /**********/ workspace->temp2       , //
    /**********/ degree                   );

    mpfi_div( derivative           , //
    /*******/ workspace->numerator , //
    /*******/ workspace->denominator );

    return EXIT_SUCCESS;

}



/**
 * @param[  out] initial_zero inital value of the zero point of the Legendre polynomial
 * @param[in   ] mpfi_pi      Mathematical constant: pi; `mpfi_const_pi` must be applied before using this function
 * @param[in   ] degree       The target degree of Legendre polynomial
 * @param[in   ] node_id      selector of zero point
 * @param[inout] workspace    Temporary storage used during polynomial computations
 * 
 * @see
 * https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/add_d.c
 * https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/cos.c
 * https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/div.c
 * https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/mul.c
 * https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/set_ui.c
 * https://gitlab.inria.fr/mpfi/mpfi/-/blob/master/src/sub_d.c
 */
int mpfi_LegendrePolynomial_InitializeZero(
    /***/ /****/ mpfi_ptr                                  initial_zero , //
    const /****/ mpfi_srcptr                               mpfi_pi      , //
    const /****/ unsigned long                             degree       , //
    const /****/ unsigned long                             node_id      , //
    /***/ struct mpfi_LegendrePolynomialWorkspace_t *const workspace    ) {

    // temp1 <- k
    mpfi_set_ui( workspace->temp1 , node_id );

    // temp2 <- k + 0.25
    mpfi_sub_d( workspace->numerator ,      //
    /*********/ workspace->temp1     , 0.25 );

    // temp1 <- n
    mpfi_set_ui( workspace->temp1 , degree );

    // denominator <- n + 0.5
    mpfi_add_d( workspace->denominator ,     //
    /*********/ workspace->temp1       , 0.5 );

    mpfi_div( workspace->temp1       , //
    /*******/ workspace->numerator   , //
    /*******/ workspace->denominator   );

    mpfi_mul( workspace->temp2 ,         //
    /*******/ workspace->temp1 , mpfi_pi );

    mpfi_cos( initial_zero , workspace->temp2 );

    return EXIT_SUCCESS;

}



#endif /* MPFI_LEGENDRE_POLYNOMIAL_H */
