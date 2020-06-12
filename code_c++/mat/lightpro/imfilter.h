//
// File: imfilter.h
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//
#ifndef IMFILTER_H
#define IMFILTER_H

// Include Files
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "lightpro_types.h"

// Function Declarations
extern void b_imfilter(coder::array<double, 2U> &varargin_1, const double
  varargin_2[231361]);
extern void imfilter(coder::array<double, 2U> &varargin_1, const double
                     varargin_2[6561]);
extern void padImage(const coder::array<double, 2U> &a_tmp, const double pad[2],
                     coder::array<double, 2U> &a);

#endif

//
// File trailer for imfilter.h
//
// [EOF]
//
