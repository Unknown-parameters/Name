//
// File: histcounts.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "histcounts.h"
#include "lightpro.h"
#include "lightpro_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *x
//                double n_data[]
//                int n_size[2]
// Return Type  : void
//
void histcounts(const coder::array<double, 2U> &x, double n_data[], int n_size[2])
{
  int nx;
  int k;
  double LowLimit;
  int low_i;
  double HighLimit;
  int i;
  int low_ip1;
  double binWidth;
  double leftEdge;
  double epsxScale;
  double edges_data[251];
  int ni_data[250];
  double xScale;
  int high_i;
  int mid_i;
  nx = x.size(0) * x.size(1);
  k = 0;
  while ((k + 1 <= nx) && (rtIsInf(x[k]) || rtIsNaN(x[k]))) {
    k++;
  }

  if (k + 1 > nx) {
    LowLimit = 0.0;
    low_i = 0;
  } else {
    LowLimit = x[k];
    low_i = 1;
  }

  HighLimit = LowLimit;
  i = k + 2;
  for (low_ip1 = i; low_ip1 <= nx; low_ip1++) {
    if ((!rtIsInf(x[low_ip1 - 1])) && (!rtIsNaN(x[low_ip1 - 1]))) {
      if (x[low_ip1 - 1] < LowLimit) {
        LowLimit = x[low_ip1 - 1];
      } else {
        if (x[low_ip1 - 1] > HighLimit) {
          HighLimit = x[low_ip1 - 1];
        }
      }

      low_i++;
    }
  }

  binWidth = HighLimit - LowLimit;
  leftEdge = binWidth / 250.0;
  if (low_i > 0) {
    double u0;
    boolean_T b;
    boolean_T b1;
    u0 = std::abs(LowLimit);
    epsxScale = std::abs(HighLimit);
    if ((u0 > epsxScale) || rtIsNaN(epsxScale)) {
      xScale = u0;
    } else {
      xScale = epsxScale;
    }

    b = !rtIsInf(xScale);
    b1 = !rtIsNaN(xScale);
    if (b && b1) {
      if (xScale <= 2.2250738585072014E-308) {
        epsxScale = 4.94065645841247E-324;
      } else {
        frexp(xScale, &high_i);
        epsxScale = std::ldexp(1.0, high_i - 53);
      }
    } else {
      epsxScale = rtNaN;
    }

    if ((!(leftEdge > epsxScale)) && (!rtIsNaN(epsxScale))) {
      leftEdge = epsxScale;
    }

    u0 = std::sqrt(epsxScale);
    if (!(u0 > 2.2250738585072014E-308)) {
      u0 = 2.2250738585072014E-308;
    }

    if (binWidth > u0) {
      epsxScale = rt_powd_snf(10.0, std::floor(std::log10(leftEdge)));
      binWidth = epsxScale * std::floor(leftEdge / epsxScale);
      u0 = binWidth * std::floor(LowLimit / binWidth);
      if ((u0 < LowLimit) || rtIsNaN(LowLimit)) {
        leftEdge = u0;
      } else {
        leftEdge = LowLimit;
      }

      if (!(leftEdge > -1.7976931348623157E+308)) {
        leftEdge = -1.7976931348623157E+308;
      }

      epsxScale = HighLimit - leftEdge;
      xScale = epsxScale / 250.0;
      epsxScale = rt_powd_snf(10.0, std::floor(std::log10(epsxScale / 249.0 -
        xScale)));
      binWidth = epsxScale * std::ceil(xScale / epsxScale);
      u0 = leftEdge + 250.0 * binWidth;
      if ((u0 > HighLimit) || rtIsNaN(HighLimit)) {
        xScale = u0;
      } else {
        xScale = HighLimit;
      }

      if (!(xScale < 1.7976931348623157E+308)) {
        xScale = 1.7976931348623157E+308;
      }
    } else {
      if (b && b1) {
        if (xScale <= 2.2250738585072014E-308) {
          epsxScale = 4.94065645841247E-324;
        } else {
          frexp(xScale, &mid_i);
          epsxScale = std::ldexp(1.0, mid_i - 53);
        }
      } else {
        epsxScale = rtNaN;
      }

      epsxScale = std::ceil(250.0 * epsxScale);
      if ((1.0 > epsxScale) || rtIsNaN(epsxScale)) {
        epsxScale = 1.0;
      }

      leftEdge = std::floor(2.0 * (LowLimit - epsxScale / 4.0)) / 2.0;
      xScale = std::ceil(2.0 * (HighLimit + epsxScale / 4.0)) / 2.0;
      binWidth = (xScale - leftEdge) / 250.0;
    }

    if ((!rtIsInf(binWidth)) && (!rtIsNaN(binWidth))) {
      std::memset(&edges_data[0], 0, 251U * sizeof(double));
      edges_data[0] = leftEdge;
      for (low_i = 0; low_i < 249; low_i++) {
        edges_data[low_i + 1] = leftEdge + (static_cast<double>(low_i) + 1.0) *
          binWidth;
      }

      edges_data[250] = xScale;
    } else {
      edges_data[250] = xScale;
      edges_data[0] = leftEdge;
      if (leftEdge == -xScale) {
        for (k = 0; k < 249; k++) {
          edges_data[k + 1] = xScale * ((2.0 * (static_cast<double>(k) + 2.0) -
            252.0) / 250.0);
        }

        edges_data[125] = 0.0;
      } else if (((leftEdge < 0.0) != (xScale < 0.0)) && ((std::abs(leftEdge) >
                   8.9884656743115785E+307) || (std::abs(xScale) >
                   8.9884656743115785E+307))) {
        binWidth = leftEdge / 250.0;
        epsxScale = xScale / 250.0;
        for (k = 0; k < 249; k++) {
          edges_data[k + 1] = (leftEdge + epsxScale * (static_cast<double>(k) +
            1.0)) - binWidth * (static_cast<double>(k) + 1.0);
        }
      } else {
        binWidth = (xScale - leftEdge) / 250.0;
        for (k = 0; k < 249; k++) {
          edges_data[k + 1] = leftEdge + (static_cast<double>(k) + 1.0) *
            binWidth;
        }
      }
    }
  } else {
    for (k = 0; k < 251; k++) {
      edges_data[k] = k;
    }
  }

  std::memset(&ni_data[0], 0, 250U * sizeof(int));
  nx = x.size(0) * x.size(1);
  leftEdge = edges_data[0];
  epsxScale = edges_data[1] - edges_data[0];
  for (k = 0; k < nx; k++) {
    if ((x[k] >= leftEdge) && (x[k] <= edges_data[250])) {
      boolean_T guard1 = false;
      xScale = std::ceil((x[k] - leftEdge) / epsxScale);
      guard1 = false;
      if ((xScale >= 1.0) && (xScale < 251.0)) {
        i = static_cast<int>(xScale) - 1;
        if ((x[k] >= edges_data[i]) && (x[k] < edges_data[static_cast<int>
             (xScale)])) {
          ni_data[i]++;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        low_i = 1;
        low_ip1 = 2;
        high_i = 251;
        while (high_i > low_ip1) {
          mid_i = (low_i >> 1) + (high_i >> 1);
          if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
            mid_i++;
          }

          if (x[k] >= edges_data[mid_i - 1]) {
            low_i = mid_i;
            low_ip1 = mid_i + 1;
          } else {
            high_i = mid_i;
          }
        }

        ni_data[low_i - 1]++;
      }
    }
  }

  n_size[0] = 1;
  n_size[1] = 250;
  for (i = 0; i < 250; i++) {
    n_data[i] = ni_data[i];
  }
}

//
// File trailer for histcounts.cpp
//
// [EOF]
//
