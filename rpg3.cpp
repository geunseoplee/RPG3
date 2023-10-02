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

