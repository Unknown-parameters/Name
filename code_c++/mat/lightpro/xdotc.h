//
// File: xdotc.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//
#ifndef XDOTC_H
#define XDOTC_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "lightpro_types.h"

// Function Declarations
extern double b_xdotc(int n, const double x[6561], int ix0, const double y[6561],
                      int iy0);
extern double c_xdotc(int n, const double x[231361], int ix0, const double y
                      [231361], int iy0);
extern double xdotc(int n, const double x[441], int ix0, const double y[441],
                    int iy0);

#endif

//
// File trailer for xdotc.h
//
// [EOF]
//
