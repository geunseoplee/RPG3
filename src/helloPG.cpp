#include "RcppArmadillo.h"
#include <R_ext/Utils.h>
#include <iostream>
#include <exception>
#include "RNG.h"
#include "PolyaGamma.h"
// Rcpp::depends(RcppArmadillo)

using namespace Rcpp;
using namespace arma;

colvec rpg(colvec shape, colvec scale) {
// C++-only interface to PolyaGamma class
// draws random PG variates from arma::vectors of n's and psi's
  RNG r;
  PolyaGamma pg;
#ifdef USE_R
  GetRNGstate();
#endif
  int d = shape.n_elem;
  colvec result(d);
  for(int i=0; i<d; i++) {
    result[i] = pg.draw(shape(i), scale(i), r);
  }
#ifdef USE_R
  PutRNGstate();
#endif
  return result;
}

// [[Rcpp::export]]
SEXP helloPG(int n, double z) {
  // returns n draws from PG(1,z)
  colvec pgscale(n, fill::ones);
  colvec pgshape(n);
  for(int i=0; i<2; i++) {
    pgshape[i] = z;
  }
  colvec out = rpg(pgscale, pgshape);

  return Rcpp::List::create(Rcpp::Named("draws")=out
			    );
}

/*
#include "RcppArmadillo.h"
#include <R_ext/Utils.h>
#include <iostream>
#include <exception>
#include "RNG.h"
#include "PolyaGamma.h"
// Rcpp::depends(RcppArmadillo)

using namespace Rcpp;
using namespace arma;

double rpg2(double scale)
{
  RNG r;
  PolyaGamma pg;
  #ifdef USE_R
    GetRNGstate();
  #endif
  double result = pg.draw(1, scale, r);
 #ifdef USE_R
    PutRNGstate();
  #endif
  return result;
}

// [[Rcpp::export]]
List rpg3(int num, double z) {

  vec rpg_vec(num);
  for(int i = 0;i<num;i++)
  {
	rpg_vec(i) = rpg2(z);	
  }

  return Rcpp::List::create(rpg_vec);
}
*/
