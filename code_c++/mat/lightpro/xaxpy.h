//
// File: xaxpy.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//
#ifndef XAXPY_H
#define XAXPY_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "lightpro_types.h"

// Function Declarations
extern void b_xaxpy(int n, double a, const double x[441], int ix0, double y[21],
                    int iy0);
extern void c_xaxpy(int n, double a, const double x[21], int ix0, double y[441],
                    int iy0);
extern void d_xaxpy(int n, double a, int ix0, double y[6561], int iy0);
extern void e_xaxpy(int n, double a, const double x[6561], int ix0, double y[81],
                    int iy0);
extern void f_xaxpy(int n, double a, const double x[81], int ix0, double y[6561],
                    int iy0);
extern void g_xaxpy(int n, double a, int ix0, double y[231361], int iy0);
extern void h_xaxpy(int n, double a, const double x[231361], int ix0, double y
                    [481], int iy0);
extern void i_xaxpy(int n, double a, const double x[481], int ix0, double y
                    [231361], int iy0);
extern void xaxpy(int n, double a, int ix0, double y[441], int iy0);

#endif

//
// File trailer for xaxpy.h
//
// [EOF]
//
