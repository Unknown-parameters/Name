//
// File: xswap.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "xswap.h"
#include "lightpro.h"
#include "rt_nonfinite.h"

// Function Definitions

//
// Arguments    : double x[6561]
//                int ix0
//                int iy0
// Return Type  : void
//
void b_xswap(double x[6561], int ix0, int iy0)
{
  int ix;
  int iy;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (int k = 0; k < 81; k++) {
    double temp;
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

//
// Arguments    : double x[231361]
//                int ix0
//                int iy0
// Return Type  : void
//
void c_xswap(double x[231361], int ix0, int iy0)
{
  int ix;
  int iy;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (int k = 0; k < 481; k++) {
    double temp;
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

//
// Arguments    : double x[441]
//                int ix0
//                int iy0
// Return Type  : void
//
void xswap(double x[441], int ix0, int iy0)
{
  int ix;
  int iy;
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (int k = 0; k < 21; k++) {
    double temp;
    temp = x[ix];
    x[ix] = x[iy];
    x[iy] = temp;
    ix++;
    iy++;
  }
}

//
// File trailer for xswap.cpp
//
// [EOF]
//
