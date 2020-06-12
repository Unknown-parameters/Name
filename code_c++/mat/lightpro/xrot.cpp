//
// File: xrot.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "xrot.h"
#include "lightpro.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : double x[6561]
//                int ix0
//                int iy0
//                double c
//                double s
// Return Type  : void
//
void b_xrot(double x[6561], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (int k = 0; k < 81; k++) {
    double temp;
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

//
// Arguments    : double x[231361]
//                int ix0
//                int iy0
//                double c
//                double s
// Return Type  : void
//
void c_xrot(double x[231361], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (int k = 0; k < 481; k++) {
    double temp;
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

//
// Arguments    : double x[441]
//                int ix0
//                int iy0
//                double c
//                double s
// Return Type  : void
//
void xrot(double x[441], int ix0, int iy0, double c, double s)
{
  int ix;
  int iy;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (int k = 0; k < 21; k++) {
    double temp;
    temp = c * x[ix] + s * x[iy];
    x[iy] = c * x[iy] - s * x[ix];
    x[ix] = temp;
    iy++;
    ix++;
  }
}

//
// File trailer for xrot.cpp
//
// [EOF]
//
