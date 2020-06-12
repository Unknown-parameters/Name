//
// File: xdotc.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "xdotc.h"
#include "lightpro.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : int n
//                const double x[6561]
//                int ix0
//                const double y[6561]
//                int iy0
// Return Type  : double
//
double b_xdotc(int n, const double x[6561], int ix0, const double y[6561], int
               iy0)
{
  double d;
  int ix;
  int iy;
  ix = ix0;
  iy = iy0;
  d = 0.0;
  for (int k = 0; k < n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

//
// Arguments    : int n
//                const double x[231361]
//                int ix0
//                const double y[231361]
//                int iy0
// Return Type  : double
//
double c_xdotc(int n, const double x[231361], int ix0, const double y[231361],
               int iy0)
{
  double d;
  int ix;
  int iy;
  ix = ix0;
  iy = iy0;
  d = 0.0;
  for (int k = 0; k < n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

//
// Arguments    : int n
//                const double x[441]
//                int ix0
//                const double y[441]
//                int iy0
// Return Type  : double
//
double xdotc(int n, const double x[441], int ix0, const double y[441], int iy0)
{
  double d;
  int ix;
  int iy;
  ix = ix0;
  iy = iy0;
  d = 0.0;
  for (int k = 0; k < n; k++) {
    d += x[ix - 1] * y[iy - 1];
    ix++;
    iy++;
  }

  return d;
}

//
// File trailer for xdotc.cpp
//
// [EOF]
//
