//
// File: lightpro.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "lightpro.h"
#include "histcounts.h"
#include "imgaussfilt.h"
#include "libmwrgb2hsv_tbb.h"
#include "lightpro_rtwutil.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<unsigned char, 3U> *a
//                coder::array<double, 3U> *iml
// Return Type  : void
//
void lightpro(const coder::array<unsigned char, 3U> &a, coder::array<double, 3U>
              &iml)
{
  double CDF;
  coder::array<double, 3U> b;
  int wh;
  int nx;
  int dims3;
  coder::array<double, 2U> v1;
  int j;
  double counts_data[250];
  int counts_size[2];
  int sj_tmp;
  double xbar;
  double dev;
  double t;
  boolean_T exitg1;
  coder::array<double, 2U> GV1;
  coder::array<double, 2U> GV2;
  coder::array<double, 2U> GV3;
  coder::array<double, 2U> y;
  unsigned int unnamed_idx_0;
  unsigned int unnamed_idx_1;
  coder::array<double, 2U> b_y;
  CDF = 0.0;

  // 通道转换
  b.set_size(a.size(0), a.size(1), 3);
  rgb2hsv_tbb_uint8(&a[0], static_cast<double>(a.size(0)) * static_cast<double>
                    (a.size(1)), &b[0], true);

  // 分离通道
  // 相关长常量和变量
  wh = b.size(0) * b.size(1);

  // 直方图的相关统计
  nx = b.size(0);
  dims3 = b.size(1);
  v1.set_size(b.size(0), b.size(1));
  for (j = 0; j < dims3; j++) {
    for (sj_tmp = 0; sj_tmp < nx; sj_tmp++) {
      v1[sj_tmp + v1.size(0) * j] = b[(sj_tmp + b.size(0) * j) + b.size(0) *
        b.size(1) * 2];
    }
  }

  histcounts(v1, counts_data, counts_size);

  // 方差
  xbar = counts_data[0];
  for (dims3 = 0; dims3 < 249; dims3++) {
    xbar += counts_data[dims3 + 1];
  }

  xbar /= 250.0;
  dev = 0.0;
  for (dims3 = 0; dims3 < 250; dims3++) {
    t = counts_data[dims3] - xbar;
    dev += t * t;
  }

  dev /= 249.0;

  // 计算P和Z
  nx = 1;
  dims3 = 0;
  exitg1 = false;
  while ((!exitg1) && (dims3 < 250)) {
    nx = dims3 + 1;
    CDF += counts_data[dims3];
    if (CDF >= static_cast<double>(wh) * 0.1) {
      exitg1 = true;
    } else {
      dims3++;
    }
  }

  if (nx <= 50) {
    t = 0.0;
  } else if (nx <= 150) {
    t = (static_cast<double>(nx) - 50.0) / 100.0;
  } else {
    t = 1.0;
  }

  if (dev <= 3.0) {
    xbar = 3.0;
  } else if (dev <= 10.0) {
    xbar = (27.0 - 2.0 * dev) / 7.0;
  } else {
    xbar = 1.0;
  }

  // gauss blur
  nx = b.size(0);
  dims3 = b.size(1);
  GV1.set_size(b.size(0), b.size(1));
  for (j = 0; j < dims3; j++) {
    for (sj_tmp = 0; sj_tmp < nx; sj_tmp++) {
      GV1[sj_tmp + GV1.size(0) * j] = b[(sj_tmp + b.size(0) * j) + b.size(0) *
        b.size(1) * 2];
    }
  }

  c_imgaussfilt(GV1);
  nx = b.size(0);
  dims3 = b.size(1);
  v1.set_size(b.size(0), b.size(1));
  for (j = 0; j < dims3; j++) {
    for (sj_tmp = 0; sj_tmp < nx; sj_tmp++) {
      v1[sj_tmp + v1.size(0) * j] = b[(sj_tmp + b.size(0) * j) + b.size(0) *
        b.size(1) * 2];
    }
  }

  imgaussfilt(v1, GV2);
  nx = b.size(0);
  dims3 = b.size(1);
  v1.set_size(b.size(0), b.size(1));
  for (j = 0; j < dims3; j++) {
    for (sj_tmp = 0; sj_tmp < nx; sj_tmp++) {
      v1[sj_tmp + v1.size(0) * j] = b[(sj_tmp + b.size(0) * j) + b.size(0) *
        b.size(1) * 2];
    }
  }

  b_imgaussfilt(v1, GV3);

  
  // 相关增强参数的映射
  // 亮度的线性增强
  CDF = 0.75 * t + 0.25;
  v1.set_size(b.size(0), b.size(1));
  nx = b.size(0) * b.size(1);
  for (dims3 = 0; dims3 < nx; dims3++) {
    v1[dims3] = rt_powd_snf(b[(dims3 % b.size(0) + b.size(0) * (dims3 / b.size(0)))
      + b.size(0) * b.size(1) * 2], CDF);
  }

  y.set_size(b.size(0), b.size(1));
  nx = b.size(0) * b.size(1);
  for (dims3 = 0; dims3 < nx; dims3++) {
    y[dims3] = rt_powd_snf(b[(dims3 % b.size(0) + b.size(0) * (dims3 / b.size(0)))
      + b.size(0) * b.size(1) * 2], 2.0 - t);
  }

  nx = v1.size(1);
  for (j = 0; j < nx; j++) {
    dims3 = v1.size(0);
    for (sj_tmp = 0; sj_tmp < dims3; sj_tmp++) {
      v1[sj_tmp + v1.size(0) * j] = ((v1[sj_tmp + v1.size(0) * j] + (1.0 - b
        [(sj_tmp + b.size(0) * j) + b.size(0) * b.size(1) * 2]) * 0.4 * (1.0 - t))
        + y[sj_tmp + y.size(0) * j]) * 0.5;
    }
  }

  // 对比度的增强
  // 图像还原
  // 通道合并
  nx = GV1.size(1);
  for (j = 0; j < nx; j++) {
    dims3 = GV1.size(0);
    for (sj_tmp = 0; sj_tmp < dims3; sj_tmp++) {
      GV1[sj_tmp + GV1.size(0) * j] = GV1[sj_tmp + GV1.size(0) * j] / b[(sj_tmp
        + b.size(0) * j) + b.size(0) * b.size(1) * 2];
    }
  }

  unnamed_idx_0 = static_cast<unsigned int>(GV1.size(0));
  unnamed_idx_1 = static_cast<unsigned int>(GV1.size(1));
  y.set_size((static_cast<int>(unnamed_idx_0)), (static_cast<int>(unnamed_idx_1)));
  nx = static_cast<int>(unnamed_idx_0) * static_cast<int>(unnamed_idx_1);
  for (dims3 = 0; dims3 < nx; dims3++) {
    y[dims3] = rt_powd_snf(GV1[dims3], xbar);
  }

  if (v1.size(0) <= y.size(0)) {
    wh = v1.size(0);
  } else {
    wh = y.size(0);
  }

  if (v1.size(1) <= y.size(1)) {
    nx = v1.size(1);
  } else {
    nx = y.size(1);
  }

  b_y.set_size(wh, nx);
  if (v1.size(0) <= y.size(0)) {
    wh = v1.size(0);
  } else {
    wh = y.size(0);
  }

  if (v1.size(1) <= y.size(1)) {
    nx = v1.size(1);
  } else {
    nx = y.size(1);
  }

  nx *= wh;
  for (dims3 = 0; dims3 < nx; dims3++) {
    b_y[dims3] = rt_powd_snf(v1[dims3], y[dims3]);
  }

  nx = GV2.size(1);
  for (j = 0; j < nx; j++) {
    dims3 = GV2.size(0);
    for (sj_tmp = 0; sj_tmp < dims3; sj_tmp++) {
      GV2[sj_tmp + GV2.size(0) * j] = GV2[sj_tmp + GV2.size(0) * j] / b[(sj_tmp
        + b.size(0) * j) + b.size(0) * b.size(1) * 2];
    }
  }

  unnamed_idx_0 = static_cast<unsigned int>(GV2.size(0));
  unnamed_idx_1 = static_cast<unsigned int>(GV2.size(1));
  y.set_size((static_cast<int>(unnamed_idx_0)), (static_cast<int>(unnamed_idx_1)));
  nx = static_cast<int>(unnamed_idx_0) * static_cast<int>(unnamed_idx_1);
  for (dims3 = 0; dims3 < nx; dims3++) {
    y[dims3] = rt_powd_snf(GV2[dims3], xbar);
  }

  if (v1.size(0) <= y.size(0)) {
    wh = v1.size(0);
  } else {
    wh = y.size(0);
  }

  if (v1.size(1) <= y.size(1)) {
    nx = v1.size(1);
  } else {
    nx = y.size(1);
  }

  GV2.set_size(wh, nx);
  if (v1.size(0) <= y.size(0)) {
    wh = v1.size(0);
  } else {
    wh = y.size(0);
  }

  if (v1.size(1) <= y.size(1)) {
    nx = v1.size(1);
  } else {
    nx = y.size(1);
  }

  nx *= wh;
  for (dims3 = 0; dims3 < nx; dims3++) {
    GV2[dims3] = rt_powd_snf(v1[dims3], y[dims3]);
  }

  nx = GV3.size(1);
  for (j = 0; j < nx; j++) {
    dims3 = GV3.size(0);
    for (sj_tmp = 0; sj_tmp < dims3; sj_tmp++) {
      GV3[sj_tmp + GV3.size(0) * j] = GV3[sj_tmp + GV3.size(0) * j] / b[(sj_tmp
        + b.size(0) * j) + b.size(0) * b.size(1) * 2];
    }
  }

  unnamed_idx_0 = static_cast<unsigned int>(GV3.size(0));
  unnamed_idx_1 = static_cast<unsigned int>(GV3.size(1));
  y.set_size((static_cast<int>(unnamed_idx_0)), (static_cast<int>(unnamed_idx_1)));
  nx = static_cast<int>(unnamed_idx_0) * static_cast<int>(unnamed_idx_1);
  for (dims3 = 0; dims3 < nx; dims3++) {
    y[dims3] = rt_powd_snf(GV3[dims3], xbar);
  }

  if (v1.size(0) <= y.size(0)) {
    wh = v1.size(0);
  } else {
    wh = y.size(0);
  }

  if (v1.size(1) <= y.size(1)) {
    nx = v1.size(1);
  } else {
    nx = y.size(1);
  }

  GV1.set_size(wh, nx);
  if (v1.size(0) <= y.size(0)) {
    wh = v1.size(0);
  } else {
    wh = y.size(0);
  }

  if (v1.size(1) <= y.size(1)) {
    nx = v1.size(1);
  } else {
    nx = y.size(1);
  }

  nx *= wh;
  for (dims3 = 0; dims3 < nx; dims3++) {
    GV1[dims3] = rt_powd_snf(v1[dims3], y[dims3]);
  }

  nx = b_y.size(1);
  for (j = 0; j < nx; j++) {
    dims3 = b_y.size(0);
    for (sj_tmp = 0; sj_tmp < dims3; sj_tmp++) {
      b[(sj_tmp + b.size(0) * j) + b.size(0) * b.size(1) * 2] = ((b_y[sj_tmp +
        b_y.size(0) * j] + GV2[sj_tmp + GV2.size(0) * j]) + GV1[sj_tmp +
        GV1.size(0) * j]) / 3.0;
    }
  }

  // 通道转换
  nx = b.size(0) * b.size(1) - 1;
  dims3 = ((nx + 1) << 1) - 1;
  iml.set_size(b.size(0), b.size(1), b.size(2));
  for (int b_j = 0; b_j <= nx; b_j++) {
    j = b_j + 1;
    xbar = 6.0 * b[j - 1];
    CDF = std::floor(xbar);
    xbar -= CDF;
    sj_tmp = nx + j;
    wh = dims3 + j;
    if ((CDF == 0.0) || (CDF == 6.0)) {
      iml[j - 1] = b[wh];
      iml[sj_tmp] = (1.0 - b[sj_tmp] * (1.0 - xbar)) * b[wh];
      iml[wh] = (1.0 - b[sj_tmp]) * b[wh];
    } else if (CDF == 1.0) {
      iml[j - 1] = (1.0 - b[sj_tmp] * xbar) * b[wh];
      iml[sj_tmp] = b[wh];
      iml[wh] = (1.0 - b[sj_tmp]) * b[wh];
    } else if (CDF == 2.0) {
      iml[j - 1] = (1.0 - b[sj_tmp]) * b[wh];
      iml[sj_tmp] = b[wh];
      iml[wh] = (1.0 - b[sj_tmp] * (1.0 - xbar)) * b[wh];
    } else if (CDF == 3.0) {
      iml[j - 1] = (1.0 - b[sj_tmp]) * b[wh];
      iml[sj_tmp] = (1.0 - b[sj_tmp] * xbar) * b[wh];
      iml[wh] = b[wh];
    } else if (CDF == 4.0) {
      iml[j - 1] = (1.0 - b[sj_tmp] * (1.0 - xbar)) * b[wh];
      iml[sj_tmp] = (1.0 - b[sj_tmp]) * b[wh];
      iml[wh] = b[wh];
    } else if (CDF == 5.0) {
      iml[j - 1] = b[wh];
      iml[sj_tmp] = (1.0 - b[sj_tmp]) * b[wh];
      iml[wh] = (1.0 - b[sj_tmp] * xbar) * b[wh];
    } else {
      iml[j - 1] = rtNaN;
      iml[sj_tmp] = rtNaN;
      iml[wh] = rtNaN;
    }
  }

  // imshow(a);
}

//
// File trailer for lightpro.cpp
//
// [EOF]
//
