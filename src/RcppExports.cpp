// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// rpg3
List rpg3(int num, double z);
RcppExport SEXP rpg3_rpg3(SEXP nSEXP, SEXP zSEXP) {
BEGIN_RCPP
        Rcpp::traits::input_parameter< int >::type n(nSEXP );
        Rcpp::traits::input_parameter< double >::type z(zSEXP );

        Rcpp::RObject rcpp_result_gen = Rcpp::wrap(rpg3(n, z));
        return rcpp_result_gen;
END_RCPP
}
