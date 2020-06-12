//
// File: xaxpy.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "xaxpy.h"
#include "lightpro.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : int n
//                double a
//                const double x[441]
//                int ix0
//                double y[21]
//                int iy0
// Return Type  : void
//
void b_xaxpy(int n, double a, const double x[441], int ix0, double y[21], int
             iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                const double x[21]
//                int ix0
//                double y[441]
//                int iy0
// Return Type  : void
//
void c_xaxpy(int n, double a, const double x[21], int ix0, double y[441], int
             iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                int ix0
//                double y[6561]
//                int iy0
// Return Type  : void
//
void d_xaxpy(int n, double a, int ix0, double y[6561], int iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                const double x[6561]
//                int ix0
//                double y[81]
//                int iy0
// Return Type  : void
//
void e_xaxpy(int n, double a, const double x[6561], int ix0, double y[81], int
             iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                const double x[81]
//                int ix0
//                double y[6561]
//                int iy0
// Return Type  : void
//
void f_xaxpy(int n, double a, const double x[81], int ix0, double y[6561], int
             iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                int ix0
//                double y[231361]
//                int iy0
// Return Type  : void
//
void g_xaxpy(int n, double a, int ix0, double y[231361], int iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                const double x[231361]
//                int ix0
//                double y[481]
//                int iy0
// Return Type  : void
//
void h_xaxpy(int n, double a, const double x[231361], int ix0, double y[481],
             int iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                const double x[481]
//                int ix0
//                double y[231361]
//                int iy0
// Return Type  : void
//
void i_xaxpy(int n, double a, const double x[481], int ix0, double y[231361],
             int iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * x[ix];
      ix++;
      iy++;
    }
  }
}

//
// Arguments    : int n
//                double a
//                int ix0
//                double y[441]
//                int iy0
// Return Type  : void
//
void xaxpy(int n, double a, int ix0, double y[441], int iy0)
{
  if (!(a == 0.0)) {
    int ix;
    int iy;
    int i;
    ix = ix0 - 1;
    iy = iy0 - 1;
    i = n - 1;
    for (int k = 0; k <= i; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

//
// File trailer for xaxpy.cpp
//
// [EOF]
//
