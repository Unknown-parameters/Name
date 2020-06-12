//
// File: imfilter.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "imfilter.h"
#include "libmwimfilter.h"
#include "libmwippfilter.h"
#include "lightpro.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include <cmath>

// Function Declarations
static double rt_roundd_snf(double u);

// Function Definitions

//
// Arguments    : double u
// Return Type  : double
//
static double rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

//
// Arguments    : coder::array<double, 2U> *varargin_1
//                const double varargin_2[231361]
// Return Type  : void
//
void b_imfilter(coder::array<double, 2U> &varargin_1, const double varargin_2
                [231361])
{
  double outSizeT[2];
  double startT[2];
  static boolean_T x[231361];
  static double unusedU0[231361];
  static double s[231361];
  static double unusedU1[231361];
  coder::array<double, 2U> a;
  double b_s[481];
  int idx;
  coder::array<int, 1U> r;
  double out_size_row[2];
  coder::array<double, 1U> nonzero_h;
  boolean_T b_x[481];
  double hcol[481];
  double nonzero_h_data[481];
  short tmp_data[481];
  double padSizeT[2];
  double connDimsT[2];
  short b_tmp_data[481];
  outSizeT[0] = varargin_1.size(0);
  startT[0] = 240.0;
  outSizeT[1] = varargin_1.size(1);
  startT[1] = 240.0;
  if ((varargin_1.size(0) != 0) && (varargin_1.size(1) != 0)) {
    int i;
    boolean_T tooBig;
    int k;
    boolean_T exitg1;
    double tol;
    double d;
    for (i = 0; i < 231361; i++) {
      x[i] = ((!rtIsInf(varargin_2[i])) && (!rtIsNaN(varargin_2[i])));
    }

    tooBig = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= 231360)) {
      if (!x[k]) {
        tooBig = false;
        exitg1 = true;
      } else {
        k++;
      }
    }

    if (tooBig) {
      e_svd(varargin_2, unusedU0, s, unusedU1);
      for (k = 0; k < 481; k++) {
        b_s[k] = s[k + 481 * k];
      }

      if (!rtIsNaN(b_s[0])) {
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= 481)) {
          if (!rtIsNaN(b_s[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        tol = b_s[0];
      } else {
        tol = b_s[idx - 1];
        i = idx + 1;
        for (k = i; k < 482; k++) {
          d = b_s[k - 1];
          if (tol < d) {
            tol = d;
          }
        }
      }

      tol = 481.0 * tol * 2.2204460492503131E-16;
      for (i = 0; i < 481; i++) {
        b_x[i] = (b_s[i] > tol);
      }

      idx = b_x[0];
      for (k = 0; k < 480; k++) {
        idx += b_x[k + 1];
      }

      tooBig = (idx == 1);
    } else {
      tooBig = false;
    }

    if (tooBig) {
      padImage(varargin_1, startT, a);
      e_svd(varargin_2, unusedU0, s, unusedU1);
      for (k = 0; k < 481; k++) {
        b_s[k] = s[k + 481 * k];
      }

      tol = std::sqrt(b_s[0]);
      out_size_row[0] = a.size(0);
      out_size_row[1] = varargin_1.size(1);
      k = 0;
      idx = 0;
      for (i = 0; i < 481; i++) {
        hcol[i] = unusedU0[i] * tol;
        d = unusedU1[i] * tol;
        b_s[i] = d;
        if (d != 0.0) {
          k++;
          tmp_data[idx] = static_cast<short>(i + 1);
          idx++;
        }
      }

      for (i = 0; i < k; i++) {
        nonzero_h_data[i] = b_s[tmp_data[i] - 1];
      }

      for (i = 0; i < 481; i++) {
        b_x[i] = (b_s[i] != 0.0);
      }

      tooBig = (a.size(0) > 65500);
      if ((!tooBig) || (!(out_size_row[1] > 65500.0))) {
        tooBig = false;
      }

      if ((static_cast<double>(k) / 481.0 > 0.05) && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      varargin_1.set_size(a.size(0), (static_cast<int>(out_size_row[1])));
      if (tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 1.0;
        padSizeT[1] = a.size(1);
        startT[1] = 481.0;
        ippfilter_real64(&a[0], &varargin_1[0], out_size_row, 2.0, padSizeT, b_s,
                         startT, false);
      } else {
        padSizeT[0] = a.size(0);
        connDimsT[0] = 1.0;
        startT[0] = 0.0;
        padSizeT[1] = a.size(1);
        connDimsT[1] = 481.0;
        startT[1] = 240.0;
        imfilter_real64(&a[0], &varargin_1[0], 2.0, out_size_row, 2.0, padSizeT,
                        &nonzero_h_data[0], static_cast<double>(k), b_x, 2.0,
                        connDimsT, startT, 2.0, true, false);
      }

      k = 0;
      idx = 0;
      for (i = 0; i < 481; i++) {
        if (hcol[i] != 0.0) {
          k++;
          b_tmp_data[idx] = static_cast<short>(i + 1);
          idx++;
        }
      }

      for (i = 0; i < k; i++) {
        nonzero_h_data[i] = hcol[b_tmp_data[i] - 1];
      }

      for (i = 0; i < 481; i++) {
        b_x[i] = (hcol[i] != 0.0);
      }

      tooBig = (outSizeT[0] > 65500.0);
      if ((!tooBig) || (!(outSizeT[1] > 65500.0))) {
        tooBig = false;
      }

      if ((static_cast<double>(k) / 481.0 > 0.05) && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      a.set_size(varargin_1.size(0), varargin_1.size(1));
      idx = varargin_1.size(0) * varargin_1.size(1);
      for (i = 0; i < idx; i++) {
        a[i] = varargin_1[i];
      }

      varargin_1.set_size((static_cast<int>(outSizeT[0])), (static_cast<int>
        (outSizeT[1])));
      if (tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 481.0;
        padSizeT[1] = a.size(1);
        startT[1] = 1.0;
        ippfilter_real64(&a[0], &varargin_1[0], outSizeT, 2.0, padSizeT, hcol,
                         startT, false);
      } else {
        padSizeT[0] = a.size(0);
        connDimsT[0] = 481.0;
        startT[0] = 240.0;
        padSizeT[1] = a.size(1);
        connDimsT[1] = 1.0;
        startT[1] = 0.0;
        imfilter_real64(&a[0], &varargin_1[0], 2.0, outSizeT, 2.0, padSizeT,
                        &nonzero_h_data[0], static_cast<double>(k), b_x, 2.0,
                        connDimsT, startT, 2.0, true, false);
      }
    } else {
      padImage(varargin_1, startT, a);
      k = 0;
      for (i = 0; i < 231361; i++) {
        if (varargin_2[i] != 0.0) {
          k++;
        }
      }

      r.set_size(k);
      idx = 0;
      for (i = 0; i < 231361; i++) {
        if (varargin_2[i] != 0.0) {
          r[idx] = i + 1;
          idx++;
        }
      }

      nonzero_h.set_size(r.size(0));
      idx = r.size(0);
      for (i = 0; i < idx; i++) {
        nonzero_h[i] = varargin_2[r[i] - 1];
      }

      for (i = 0; i < 231361; i++) {
        x[i] = (varargin_2[i] != 0.0);
      }

      tooBig = (outSizeT[0] > 65500.0);
      if ((!tooBig) || (!(outSizeT[1] > 65500.0))) {
        tooBig = false;
      }

      if ((static_cast<double>(r.size(0)) / 231361.0 > 0.05) && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      varargin_1.set_size((static_cast<int>(outSizeT[0])), (static_cast<int>
        (outSizeT[1])));
      if (tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 481.0;
        padSizeT[1] = a.size(1);
        startT[1] = 481.0;
        ippfilter_real64(&a[0], &varargin_1[0], outSizeT, 2.0, padSizeT,
                         varargin_2, startT, false);
      } else {
        padSizeT[0] = a.size(0);
        connDimsT[0] = 481.0;
        padSizeT[1] = a.size(1);
        connDimsT[1] = 481.0;
        imfilter_real64(&a[0], &varargin_1[0], 2.0, outSizeT, 2.0, padSizeT,
                        &(nonzero_h.data())[0], static_cast<double>(r.size(0)),
                        x, 2.0, connDimsT, startT, 2.0, true, false);
      }
    }
  }
}

//
// Arguments    : coder::array<double, 2U> *varargin_1
//                const double varargin_2[6561]
// Return Type  : void
//
void imfilter(coder::array<double, 2U> &varargin_1, const double varargin_2[6561])
{
  double outSizeT[2];
  double startT[2];
  boolean_T x[6561];
  static double unusedU0[6561];
  static double s[6561];
  double unusedU1[6561];
  coder::array<double, 2U> a;
  double b_s[81];
  int idx;
  double out_size_row[2];
  short tmp_data[6561];
  boolean_T b_x[81];
  double hcol[81];
  double nonzero_h_data[81];
  signed char b_tmp_data[81];
  double padSizeT[2];
  double connDimsT[2];
  signed char c_tmp_data[81];
  outSizeT[0] = varargin_1.size(0);
  startT[0] = 40.0;
  outSizeT[1] = varargin_1.size(1);
  startT[1] = 40.0;
  if ((varargin_1.size(0) != 0) && (varargin_1.size(1) != 0)) {
    int i;
    boolean_T tooBig;
    int k;
    boolean_T exitg1;
    double tol;
    double d;
    for (i = 0; i < 6561; i++) {
      x[i] = ((!rtIsInf(varargin_2[i])) && (!rtIsNaN(varargin_2[i])));
    }

    tooBig = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= 6560)) {
      if (!x[k]) {
        tooBig = false;
        exitg1 = true;
      } else {
        k++;
      }
    }

    if (tooBig) {
      c_svd(varargin_2, unusedU0, s, unusedU1);
      for (k = 0; k < 81; k++) {
        b_s[k] = s[k + 81 * k];
      }

      if (!rtIsNaN(b_s[0])) {
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= 81)) {
          if (!rtIsNaN(b_s[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        tol = b_s[0];
      } else {
        tol = b_s[idx - 1];
        i = idx + 1;
        for (k = i; k < 82; k++) {
          d = b_s[k - 1];
          if (tol < d) {
            tol = d;
          }
        }
      }

      tol = 81.0 * tol * 2.2204460492503131E-16;
      for (i = 0; i < 81; i++) {
        b_x[i] = (b_s[i] > tol);
      }

      idx = b_x[0];
      for (k = 0; k < 80; k++) {
        idx += b_x[k + 1];
      }

      tooBig = (idx == 1);
    } else {
      tooBig = false;
    }

    if (tooBig) {
      padImage(varargin_1, startT, a);
      c_svd(varargin_2, unusedU0, s, unusedU1);
      for (k = 0; k < 81; k++) {
        b_s[k] = s[k + 81 * k];
      }

      tol = std::sqrt(b_s[0]);
      out_size_row[0] = a.size(0);
      out_size_row[1] = varargin_1.size(1);
      k = 0;
      idx = 0;
      for (i = 0; i < 81; i++) {
        hcol[i] = unusedU0[i] * tol;
        d = unusedU1[i] * tol;
        b_s[i] = d;
        if (d != 0.0) {
          k++;
          b_tmp_data[idx] = static_cast<signed char>(i + 1);
          idx++;
        }
      }

      for (i = 0; i < k; i++) {
        nonzero_h_data[i] = b_s[b_tmp_data[i] - 1];
      }

      for (i = 0; i < 81; i++) {
        b_x[i] = (b_s[i] != 0.0);
      }

      tooBig = (a.size(0) > 65500);
      if ((!tooBig) || (!(out_size_row[1] > 65500.0))) {
        tooBig = false;
      }

      if ((static_cast<double>(k) / 81.0 > 0.05) && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      varargin_1.set_size(a.size(0), (static_cast<int>(out_size_row[1])));
      if (tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 1.0;
        padSizeT[1] = a.size(1);
        startT[1] = 81.0;
        ippfilter_real64(&a[0], &varargin_1[0], out_size_row, 2.0, padSizeT, b_s,
                         startT, false);
      } else {
        padSizeT[0] = a.size(0);
        connDimsT[0] = 1.0;
        startT[0] = 0.0;
        padSizeT[1] = a.size(1);
        connDimsT[1] = 81.0;
        startT[1] = 40.0;
        imfilter_real64(&a[0], &varargin_1[0], 2.0, out_size_row, 2.0, padSizeT,
                        &nonzero_h_data[0], static_cast<double>(k), b_x, 2.0,
                        connDimsT, startT, 2.0, true, false);
      }

      k = 0;
      idx = 0;
      for (i = 0; i < 81; i++) {
        if (hcol[i] != 0.0) {
          k++;
          c_tmp_data[idx] = static_cast<signed char>(i + 1);
          idx++;
        }
      }

      for (i = 0; i < k; i++) {
        nonzero_h_data[i] = hcol[c_tmp_data[i] - 1];
      }

      for (i = 0; i < 81; i++) {
        b_x[i] = (hcol[i] != 0.0);
      }

      tooBig = (outSizeT[0] > 65500.0);
      if ((!tooBig) || (!(outSizeT[1] > 65500.0))) {
        tooBig = false;
      }

      if ((static_cast<double>(k) / 81.0 > 0.05) && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      a.set_size(varargin_1.size(0), varargin_1.size(1));
      idx = varargin_1.size(0) * varargin_1.size(1);
      for (i = 0; i < idx; i++) {
        a[i] = varargin_1[i];
      }

      varargin_1.set_size((static_cast<int>(outSizeT[0])), (static_cast<int>
        (outSizeT[1])));
      if (tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 81.0;
        padSizeT[1] = a.size(1);
        startT[1] = 1.0;
        ippfilter_real64(&a[0], &varargin_1[0], outSizeT, 2.0, padSizeT, hcol,
                         startT, false);
      } else {
        padSizeT[0] = a.size(0);
        connDimsT[0] = 81.0;
        startT[0] = 40.0;
        padSizeT[1] = a.size(1);
        connDimsT[1] = 1.0;
        startT[1] = 0.0;
        imfilter_real64(&a[0], &varargin_1[0], 2.0, outSizeT, 2.0, padSizeT,
                        &nonzero_h_data[0], static_cast<double>(k), b_x, 2.0,
                        connDimsT, startT, 2.0, true, false);
      }
    } else {
      padImage(varargin_1, startT, a);
      k = 0;
      idx = 0;
      for (i = 0; i < 6561; i++) {
        if (varargin_2[i] != 0.0) {
          k++;
          tmp_data[idx] = static_cast<short>(i + 1);
          idx++;
        }
      }

      for (i = 0; i < k; i++) {
        unusedU0[i] = varargin_2[tmp_data[i] - 1];
      }

      for (i = 0; i < 6561; i++) {
        x[i] = (varargin_2[i] != 0.0);
      }

      tooBig = (outSizeT[0] > 65500.0);
      if ((!tooBig) || (!(outSizeT[1] > 65500.0))) {
        tooBig = false;
      }

      if ((static_cast<double>(k) / 6561.0 > 0.05) && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      varargin_1.set_size((static_cast<int>(outSizeT[0])), (static_cast<int>
        (outSizeT[1])));
      if (tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 81.0;
        padSizeT[1] = a.size(1);
        startT[1] = 81.0;
        ippfilter_real64(&a[0], &varargin_1[0], outSizeT, 2.0, padSizeT,
                         varargin_2, startT, false);
      } else {
        padSizeT[0] = a.size(0);
        connDimsT[0] = 81.0;
        padSizeT[1] = a.size(1);
        connDimsT[1] = 81.0;
        imfilter_real64(&a[0], &varargin_1[0], 2.0, outSizeT, 2.0, padSizeT,
                        &unusedU0[0], static_cast<double>(k), x, 2.0, connDimsT,
                        startT, 2.0, true, false);
      }
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *a_tmp
//                const double pad[2]
//                coder::array<double, 2U> *a
// Return Type  : void
//
void padImage(const coder::array<double, 2U> &a_tmp, const double pad[2], coder::
              array<double, 2U> &a)
{
  int loop_ub;
  coder::array<int, 2U> idxA;
  coder::array<double, 2U> y;
  coder::array<unsigned int, 2U> idxDir;
  if ((a_tmp.size(0) == 0) || (a_tmp.size(1) == 0)) {
    double sizeA_idx_0;
    double sizeA_idx_1;
    int i;
    sizeA_idx_0 = static_cast<double>(a_tmp.size(0)) + 2.0 * pad[0];
    sizeA_idx_1 = static_cast<double>(a_tmp.size(1)) + 2.0 * pad[1];
    i = static_cast<int>(sizeA_idx_0);
    loop_ub = static_cast<int>(sizeA_idx_1);
    a.set_size(i, loop_ub);
    loop_ub *= i;
    for (i = 0; i < loop_ub; i++) {
      a[i] = 0.0;
    }
  } else {
    unsigned int varargin_1_idx_0_tmp_tmp;
    double sizeA_idx_0;
    double sizeA_idx_1;
    unsigned int varargin_1_idx_1_tmp_tmp;
    int i;
    int b_loop_ub;
    unsigned int u;
    varargin_1_idx_0_tmp_tmp = static_cast<unsigned int>(a_tmp.size(0));
    sizeA_idx_0 = 2.0 * pad[0] + static_cast<double>(varargin_1_idx_0_tmp_tmp);
    varargin_1_idx_1_tmp_tmp = static_cast<unsigned int>(a_tmp.size(1));
    sizeA_idx_1 = 2.0 * pad[1] + static_cast<double>(varargin_1_idx_1_tmp_tmp);
    if ((sizeA_idx_0 < sizeA_idx_1) || (rtIsNaN(sizeA_idx_0) && (!rtIsNaN
          (sizeA_idx_1)))) {
      sizeA_idx_0 = sizeA_idx_1;
    }

    idxA.set_size((static_cast<int>(sizeA_idx_0)), 2);
    loop_ub = static_cast<int>(pad[0]);
    b_loop_ub = static_cast<int>(static_cast<double>(varargin_1_idx_0_tmp_tmp) -
      1.0);
    y.set_size(1, (b_loop_ub + 1));
    for (i = 0; i <= b_loop_ub; i++) {
      y[i] = static_cast<double>(i) + 1.0;
    }

    idxDir.set_size(1, ((loop_ub + y.size(1)) + loop_ub));
    for (i = 0; i < loop_ub; i++) {
      idxDir[i] = 1U;
    }

    b_loop_ub = y.size(1);
    for (i = 0; i < b_loop_ub; i++) {
      sizeA_idx_0 = rt_roundd_snf(y[i]);
      if (sizeA_idx_0 < 4.294967296E+9) {
        if (sizeA_idx_0 >= 0.0) {
          u = static_cast<unsigned int>(sizeA_idx_0);
        } else {
          u = 0U;
        }
      } else if (sizeA_idx_0 >= 4.294967296E+9) {
        u = MAX_uint32_T;
      } else {
        u = 0U;
      }

      idxDir[i + loop_ub] = u;
    }

    for (i = 0; i < loop_ub; i++) {
      idxDir[(i + loop_ub) + y.size(1)] = varargin_1_idx_0_tmp_tmp;
    }

    loop_ub = idxDir.size(1);
    for (i = 0; i < loop_ub; i++) {
      idxA[i] = static_cast<int>(idxDir[i]);
    }

    loop_ub = static_cast<int>(pad[1]);
    b_loop_ub = static_cast<int>(static_cast<double>(varargin_1_idx_1_tmp_tmp) -
      1.0);
    y.set_size(1, (b_loop_ub + 1));
    for (i = 0; i <= b_loop_ub; i++) {
      y[i] = static_cast<double>(i) + 1.0;
    }

    idxDir.set_size(1, ((loop_ub + y.size(1)) + loop_ub));
    for (i = 0; i < loop_ub; i++) {
      idxDir[i] = 1U;
    }

    b_loop_ub = y.size(1);
    for (i = 0; i < b_loop_ub; i++) {
      sizeA_idx_0 = rt_roundd_snf(y[i]);
      if (sizeA_idx_0 < 4.294967296E+9) {
        if (sizeA_idx_0 >= 0.0) {
          u = static_cast<unsigned int>(sizeA_idx_0);
        } else {
          u = 0U;
        }
      } else if (sizeA_idx_0 >= 4.294967296E+9) {
        u = MAX_uint32_T;
      } else {
        u = 0U;
      }

      idxDir[i + loop_ub] = u;
    }

    for (i = 0; i < loop_ub; i++) {
      idxDir[(i + loop_ub) + y.size(1)] = varargin_1_idx_1_tmp_tmp;
    }

    loop_ub = idxDir.size(1);
    for (i = 0; i < loop_ub; i++) {
      idxA[i + idxA.size(0)] = static_cast<int>(idxDir[i]);
    }

    i = static_cast<int>(static_cast<double>(a_tmp.size(1)) + 2.0 * pad[1]);
    a.set_size((static_cast<int>(static_cast<double>(a_tmp.size(0)) + 2.0 * pad
      [0])), i);
    for (b_loop_ub = 0; b_loop_ub < i; b_loop_ub++) {
      loop_ub = a.size(0);
      for (int b_i = 0; b_i < loop_ub; b_i++) {
        a[b_i + a.size(0) * b_loop_ub] = a_tmp[(idxA[b_i] + a_tmp.size(0) *
          (idxA[b_loop_ub + idxA.size(0)] - 1)) - 1];
      }
    }
  }
}

//
// File trailer for imfilter.cpp
//
// [EOF]
//
