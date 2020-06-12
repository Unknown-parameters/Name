//
// File: svd1.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//
#ifndef SVD1_H
#define SVD1_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "lightpro_types.h"

// Function Declarations
extern void b_svd(const double A[441], double U[441], double s[21], double V[441]);
extern void d_svd(const double A[6561], double U[6561], double s[81], double V
                  [6561]);
extern void f_svd(const double A[231361], double U[231361], double s[481],
                  double V[231361]);

#endif

//
// File trailer for svd1.h
//
// [EOF]
//
