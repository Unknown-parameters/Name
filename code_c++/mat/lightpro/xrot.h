//
// File: xrot.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//
#ifndef XROT_H
#define XROT_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "lightpro_types.h"

// Function Declarations
extern void b_xrot(double x[6561], int ix0, int iy0, double c, double s);
extern void c_xrot(double x[231361], int ix0, int iy0, double c, double s);
extern void xrot(double x[441], int ix0, int iy0, double c, double s);

#endif

//
// File trailer for xrot.h
//
// [EOF]
//
