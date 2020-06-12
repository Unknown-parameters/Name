//
// File: svd.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "svd.h"
#include "lightpro.h"
#include "rt_nonfinite.h"
#include "svd1.h"
#include <cstring>

// Function Definitions

//
// Arguments    : const double A[6561]
//                double U[6561]
//                double S[6561]
//                double V[6561]
// Return Type  : void
//
void c_svd(const double A[6561], double U[6561], double S[6561], double V[6561])
{
  boolean_T p;
  int i;
  double s[81];
  p = true;
  for (i = 0; i < 6561; i++) {
    if ((!p) || (rtIsInf(A[i]) || rtIsNaN(A[i]))) {
      p = false;
    }
  }

  if (p) {
    d_svd(A, U, s, V);
  } else {
    for (i = 0; i < 6561; i++) {
      U[i] = rtNaN;
    }

    for (i = 0; i < 81; i++) {
      s[i] = rtNaN;
    }

    for (i = 0; i < 6561; i++) {
      V[i] = rtNaN;
    }
  }

  std::memset(&S[0], 0, 6561U * sizeof(double));
  for (i = 0; i < 81; i++) {
    S[i + 81 * i] = s[i];
  }
}

//
// Arguments    : const double A[231361]
//                double U[231361]
//                double S[231361]
//                double V[231361]
// Return Type  : void
//
void e_svd(const double A[231361], double U[231361], double S[231361], double V
           [231361])
{
  boolean_T p;
  int i;
  double s[481];
  p = true;
  for (i = 0; i < 231361; i++) {
    if ((!p) || (rtIsInf(A[i]) || rtIsNaN(A[i]))) {
      p = false;
    }
  }

  if (p) {
    f_svd(A, U, s, V);
  } else {
    for (i = 0; i < 231361; i++) {
      U[i] = rtNaN;
    }

    for (i = 0; i < 481; i++) {
      s[i] = rtNaN;
    }

    for (i = 0; i < 231361; i++) {
      V[i] = rtNaN;
    }
  }

  std::memset(&S[0], 0, 231361U * sizeof(double));
  for (i = 0; i < 481; i++) {
    S[i + 481 * i] = s[i];
  }
}

//
// Arguments    : const double A[441]
//                double U[441]
//                double S[441]
//                double V[441]
// Return Type  : void
//
void svd(const double A[441], double U[441], double S[441], double V[441])
{
  boolean_T p;
  int i;
  double s[21];
  p = true;
  for (i = 0; i < 441; i++) {
    if ((!p) || (rtIsInf(A[i]) || rtIsNaN(A[i]))) {
      p = false;
    }
  }

  if (p) {
    b_svd(A, U, s, V);
  } else {
    for (i = 0; i < 441; i++) {
      U[i] = rtNaN;
    }

    for (i = 0; i < 21; i++) {
      s[i] = rtNaN;
    }

    for (i = 0; i < 441; i++) {
      V[i] = rtNaN;
    }
  }

  std::memset(&S[0], 0, 441U * sizeof(double));
  for (i = 0; i < 21; i++) {
    S[i + 21 * i] = s[i];
  }
}

//
// File trailer for svd.cpp
//
// [EOF]
//
