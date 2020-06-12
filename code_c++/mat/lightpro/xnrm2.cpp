//
// File: xnrm2.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "xnrm2.h"
#include "lightpro.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : int n
//                const double x[21]
//                int ix0
// Return Type  : double
//
double b_xnrm2(int n, const double x[21], int ix0)
{
  double y;
  double scale;
  int kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (int k = ix0; k <= kend; k++) {
    double absxk;
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// Arguments    : int n
//                const double x[6561]
//                int ix0
// Return Type  : double
//
double c_xnrm2(int n, const double x[6561], int ix0)
{
  double y;
  double scale;
  int kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (int k = ix0; k <= kend; k++) {
    double absxk;
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// Arguments    : int n
//                const double x[81]
//                int ix0
// Return Type  : double
//
double d_xnrm2(int n, const double x[81], int ix0)
{
  double y;
  double scale;
  int kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (int k = ix0; k <= kend; k++) {
    double absxk;
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// Arguments    : int n
//                const double x[231361]
//                int ix0
// Return Type  : double
//
double e_xnrm2(int n, const double x[231361], int ix0)
{
  double y;
  double scale;
  int kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (int k = ix0; k <= kend; k++) {
    double absxk;
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// Arguments    : int n
//                const double x[481]
//                int ix0
// Return Type  : double
//
double f_xnrm2(int n, const double x[481], int ix0)
{
  double y;
  double scale;
  int kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (int k = ix0; k <= kend; k++) {
    double absxk;
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// Arguments    : int n
//                const double x[441]
//                int ix0
// Return Type  : double
//
double xnrm2(int n, const double x[441], int ix0)
{
  double y;
  double scale;
  int kend;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  kend = (ix0 + n) - 1;
  for (int k = ix0; k <= kend; k++) {
    double absxk;
    absxk = std::abs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }

  return scale * std::sqrt(y);
}

//
// File trailer for xnrm2.cpp
//
// [EOF]
//
