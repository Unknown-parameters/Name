//
// File: svd.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//
#ifndef SVD_H
#define SVD_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "lightpro_types.h"

// Function Declarations
extern void c_svd(const double A[6561], double U[6561], double S[6561], double
                  V[6561]);
extern void e_svd(const double A[231361], double U[231361], double S[231361],
                  double V[231361]);
extern void svd(const double A[441], double U[441], double S[441], double V[441]);

#endif

//
// File trailer for svd.h
//
// [EOF]
//
