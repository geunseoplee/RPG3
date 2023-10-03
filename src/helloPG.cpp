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

double rpg_single(double scale) {
// C++-only interface to PolyaGamma class
// draws random PG variates from arma::vectors of n's and psi's
  RNG r;
  PolyaGamma pg;
#ifdef USE_R
  GetRNGstate();
#endif
  double result;
  result = pg.draw(1, scale, r);
  
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
  for(int i=0; i<n; i++) {
    pgshape[i] = z;
  }
  colvec out = rpg(pgscale, pgshape);

  return Rcpp::List::create(Rcpp::Named("draws")=out
			    );
}

// [[Rcpp::export]]
List rpg2(int n, double z) {


	colvec pgscale(1, fill::ones);
  	colvec pgshape(1);
	pgshape[0] = z;
	
	vec rpg_vec(n);
	for(int i = 0;i<n;i++)
	{
		  colvec out = rpg(pgscale, pgshape);
	          rpg_vec(i) = out[0];
	}
	
	return Rcpp::List::create(rpg_vec
			    );
}
