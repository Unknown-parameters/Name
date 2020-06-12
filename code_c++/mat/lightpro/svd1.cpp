//
// File: svd1.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "svd1.h"
#include "lightpro.h"
#include "rt_nonfinite.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"
#include <cmath>
#include <cstring>

// Function Definitions

//
// Arguments    : const double A[441]
//                double U[441]
//                double s[21]
//                double V[441]
// Return Type  : void
//
void b_svd(const double A[441], double U[441], double s[21], double V[441])
{
  double b_A[441];
  double e[21];
  double work[21];
  int q;
  int m;
  int qp1;
  int qq;
  double nrm;
  int k;
  int qjj;
  int qp1jj;
  double snorm;
  double r;
  double sm;
  double sqds;
  std::memcpy(&b_A[0], &A[0], 441U * sizeof(double));
  std::memset(&s[0], 0, 21U * sizeof(double));
  std::memset(&e[0], 0, 21U * sizeof(double));
  std::memset(&work[0], 0, 21U * sizeof(double));
  std::memset(&U[0], 0, 441U * sizeof(double));
  std::memset(&V[0], 0, 441U * sizeof(double));
  for (q = 0; q < 20; q++) {
    boolean_T apply_transform;
    qp1 = q + 2;
    qq = (q + 21 * q) + 1;
    apply_transform = false;
    nrm = xnrm2(21 - q, b_A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0) {
        nrm = -nrm;
      }

      s[q] = nrm;
      if (std::abs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qp1jj = (qq - q) + 20;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qp1jj = (qq - q) + 20;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] /= s[q];
        }
      }

      b_A[qq - 1]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (k = qp1; k < 22; k++) {
      qjj = q + 21 * (k - 1);
      if (apply_transform) {
        xaxpy(21 - q, -(xdotc(21 - q, b_A, qq, b_A, qjj + 1) / b_A[q + 21 * q]),
              qq, b_A, qjj + 1);
      }

      e[k - 1] = b_A[qjj];
    }

    for (k = q + 1; k < 22; k++) {
      qjj = (k + 21 * q) - 1;
      U[qjj] = b_A[qjj];
    }

    if (q + 1 <= 19) {
      nrm = b_xnrm2(20 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }

        nrm = e[q];
        if (std::abs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          for (k = qp1; k < 22; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (k = qp1; k < 22; k++) {
            e[k - 1] /= nrm;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (k = qp1; k < 22; k++) {
          work[k - 1] = 0.0;
        }

        for (k = qp1; k < 22; k++) {
          b_xaxpy(20 - q, e[k - 1], b_A, (q + 21 * (k - 1)) + 2, work, q + 2);
        }

        for (k = qp1; k < 22; k++) {
          c_xaxpy(20 - q, -e[k - 1] / e[q + 1], work, q + 2, b_A, (q + 21 * (k -
                    1)) + 2);
        }
      }

      for (k = qp1; k < 22; k++) {
        V[(k + 21 * q) - 1] = e[k - 1];
      }
    }
  }

  m = 19;
  s[20] = b_A[440];
  e[19] = b_A[439];
  e[20] = 0.0;
  std::memset(&U[420], 0, 21U * sizeof(double));
  U[440] = 1.0;
  for (q = 19; q >= 0; q--) {
    qp1 = q + 2;
    qq = q + 21 * q;
    if (s[q] != 0.0) {
      for (k = qp1; k < 22; k++) {
        qjj = (q + 21 * (k - 1)) + 1;
        xaxpy(21 - q, -(xdotc(21 - q, U, qq + 1, U, qjj) / U[qq]), qq + 1, U,
              qjj);
      }

      for (k = q + 1; k < 22; k++) {
        qjj = (k + 21 * q) - 1;
        U[qjj] = -U[qjj];
      }

      U[qq]++;
      for (k = 0; k < q; k++) {
        U[k + 21 * q] = 0.0;
      }
    } else {
      std::memset(&U[q * 21], 0, 21U * sizeof(double));
      U[qq] = 1.0;
    }
  }

  for (q = 20; q >= 0; q--) {
    if ((q + 1 <= 19) && (e[q] != 0.0)) {
      qp1 = q + 2;
      qjj = (q + 21 * q) + 2;
      for (k = qp1; k < 22; k++) {
        qp1jj = (q + 21 * (k - 1)) + 2;
        xaxpy(20 - q, -(xdotc(20 - q, V, qjj, V, qp1jj) / V[qjj - 1]), qjj, V,
              qp1jj);
      }
    }

    std::memset(&V[q * 21], 0, 21U * sizeof(double));
    V[q + 21 * q] = 1.0;
  }

  qq = 0;
  snorm = 0.0;
  for (q = 0; q < 21; q++) {
    if (s[q] != 0.0) {
      nrm = std::abs(s[q]);
      r = s[q] / nrm;
      s[q] = nrm;
      if (q + 1 < 21) {
        e[q] /= r;
      }

      qjj = 21 * q;
      qp1jj = qjj + 21;
      for (k = qjj + 1; k <= qp1jj; k++) {
        U[k - 1] *= r;
      }
    }

    if ((q + 1 < 21) && (e[q] != 0.0)) {
      nrm = std::abs(e[q]);
      r = nrm / e[q];
      e[q] = nrm;
      s[q + 1] *= r;
      qjj = 21 * (q + 1);
      qp1jj = qjj + 21;
      for (k = qjj + 1; k <= qp1jj; k++) {
        V[k - 1] *= r;
      }
    }

    nrm = std::abs(s[q]);
    r = std::abs(e[q]);
    if ((nrm > r) || rtIsNaN(r)) {
      r = nrm;
    }

    if ((!(snorm > r)) && (!rtIsNaN(r))) {
      snorm = r;
    }
  }

  while ((m + 2 > 0) && (qq < 75)) {
    k = m;
    int exitg1;
    do {
      exitg1 = 0;
      q = k + 1;
      if (k + 1 == 0) {
        exitg1 = 1;
      } else {
        nrm = std::abs(e[k]);
        if ((nrm <= 2.2204460492503131E-16 * (std::abs(s[k]) + std::abs(s[k + 1])))
            || (nrm <= 1.0020841800044864E-292) || ((qq > 20) && (nrm <=
              2.2204460492503131E-16 * snorm))) {
          e[k] = 0.0;
          exitg1 = 1;
        } else {
          k--;
        }
      }
    } while (exitg1 == 0);

    if (k + 1 == m + 1) {
      qjj = 4;
    } else {
      boolean_T exitg2;
      qp1jj = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= k + 1)) {
        qp1jj = qjj;
        if (qjj == k + 1) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (qjj < m + 2) {
            nrm = std::abs(e[qjj - 1]);
          }

          if (qjj > k + 2) {
            nrm += std::abs(e[qjj - 2]);
          }

          r = std::abs(s[qjj - 1]);
          if ((r <= 2.2204460492503131E-16 * nrm) || (r <=
               1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qp1jj == k + 1) {
        qjj = 3;
      } else if (qp1jj == m + 2) {
        qjj = 1;
      } else {
        qjj = 2;
        q = qp1jj;
      }
    }

    switch (qjj) {
     case 1:
      {
        r = e[m];
        e[m] = 0.0;
        qp1jj = m + 1;
        for (k = qp1jj; k >= q + 1; k--) {
          xrotg(&s[k - 1], &r, &sm, &sqds);
          if (k > q + 1) {
            double b;
            b = e[k - 2];
            r = -sqds * b;
            e[k - 2] = b * sm;
          }

          xrot(V, 21 * (k - 1) + 1, 21 * (m + 1) + 1, sm, sqds);
        }
      }
      break;

     case 2:
      {
        r = e[q - 1];
        e[q - 1] = 0.0;
        for (k = q + 1; k <= m + 2; k++) {
          double b;
          xrotg(&s[k - 1], &r, &sm, &sqds);
          b = e[k - 1];
          r = -sqds * b;
          e[k - 1] = b * sm;
          xrot(U, 21 * (k - 1) + 1, 21 * (q - 1) + 1, sm, sqds);
        }
      }
      break;

     case 3:
      {
        double scale;
        double b;
        qjj = m + 1;
        nrm = s[m + 1];
        scale = std::abs(nrm);
        r = std::abs(s[m]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(e[m]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(s[q]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(e[q]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        sm = nrm / scale;
        nrm = s[m] / scale;
        r = e[m] / scale;
        sqds = s[q] / scale;
        b = ((nrm + sm) * (nrm - sm) + r * r) / 2.0;
        nrm = sm * r;
        nrm *= nrm;
        if ((b != 0.0) || (nrm != 0.0)) {
          r = std::sqrt(b * b + nrm);
          if (b < 0.0) {
            r = -r;
          }

          r = nrm / (b + r);
        } else {
          r = 0.0;
        }

        r += (sqds + sm) * (sqds - sm);
        nrm = sqds * (e[q] / scale);
        for (k = q + 1; k <= qjj; k++) {
          xrotg(&r, &nrm, &sm, &sqds);
          if (k > q + 1) {
            e[k - 2] = r;
          }

          nrm = e[k - 1];
          b = s[k - 1];
          e[k - 1] = sm * nrm - sqds * b;
          r = sqds * s[k];
          s[k] *= sm;
          xrot(V, 21 * (k - 1) + 1, 21 * k + 1, sm, sqds);
          s[k - 1] = sm * b + sqds * nrm;
          xrotg(&s[k - 1], &r, &sm, &sqds);
          r = sm * e[k - 1] + sqds * s[k];
          s[k] = -sqds * e[k - 1] + sm * s[k];
          nrm = sqds * e[k];
          e[k] *= sm;
          xrot(U, 21 * (k - 1) + 1, 21 * k + 1, sm, sqds);
        }

        e[m] = r;
        qq++;
      }
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        qjj = 21 * q;
        qp1jj = qjj + 21;
        for (k = qjj + 1; k <= qp1jj; k++) {
          V[k - 1] = -V[k - 1];
        }
      }

      qp1 = q + 1;
      while ((q + 1 < 21) && (s[q] < s[qp1])) {
        nrm = s[q];
        s[q] = s[qp1];
        s[qp1] = nrm;
        xswap(V, 21 * q + 1, 21 * (q + 1) + 1);
        xswap(U, 21 * q + 1, 21 * (q + 1) + 1);
        q = qp1;
        qp1++;
      }

      qq = 0;
      m--;
      break;
    }
  }
}

//
// Arguments    : const double A[6561]
//                double U[6561]
//                double s[81]
//                double V[6561]
// Return Type  : void
//
void d_svd(const double A[6561], double U[6561], double s[81], double V[6561])
{
  double b_A[6561];
  double e[81];
  double work[81];
  int q;
  int m;
  int qp1;
  int qq;
  double nrm;
  int k;
  int qjj;
  int qp1jj;
  double snorm;
  double r;
  double sm;
  double sqds;
  std::memcpy(&b_A[0], &A[0], 6561U * sizeof(double));
  std::memset(&s[0], 0, 81U * sizeof(double));
  std::memset(&e[0], 0, 81U * sizeof(double));
  std::memset(&work[0], 0, 81U * sizeof(double));
  std::memset(&U[0], 0, 6561U * sizeof(double));
  std::memset(&V[0], 0, 6561U * sizeof(double));
  for (q = 0; q < 80; q++) {
    boolean_T apply_transform;
    qp1 = q + 2;
    qq = (q + 81 * q) + 1;
    apply_transform = false;
    nrm = c_xnrm2(81 - q, b_A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0) {
        nrm = -nrm;
      }

      s[q] = nrm;
      if (std::abs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qp1jj = (qq - q) + 80;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qp1jj = (qq - q) + 80;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] /= s[q];
        }
      }

      b_A[qq - 1]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (k = qp1; k < 82; k++) {
      qjj = q + 81 * (k - 1);
      if (apply_transform) {
        d_xaxpy(81 - q, -(b_xdotc(81 - q, b_A, qq, b_A, qjj + 1) / b_A[q + 81 *
                          q]), qq, b_A, qjj + 1);
      }

      e[k - 1] = b_A[qjj];
    }

    for (k = q + 1; k < 82; k++) {
      qjj = (k + 81 * q) - 1;
      U[qjj] = b_A[qjj];
    }

    if (q + 1 <= 79) {
      nrm = d_xnrm2(80 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }

        nrm = e[q];
        if (std::abs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          for (k = qp1; k < 82; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (k = qp1; k < 82; k++) {
            e[k - 1] /= nrm;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (k = qp1; k < 82; k++) {
          work[k - 1] = 0.0;
        }

        for (k = qp1; k < 82; k++) {
          e_xaxpy(80 - q, e[k - 1], b_A, (q + 81 * (k - 1)) + 2, work, q + 2);
        }

        for (k = qp1; k < 82; k++) {
          f_xaxpy(80 - q, -e[k - 1] / e[q + 1], work, q + 2, b_A, (q + 81 * (k -
                    1)) + 2);
        }
      }

      for (k = qp1; k < 82; k++) {
        V[(k + 81 * q) - 1] = e[k - 1];
      }
    }
  }

  m = 79;
  s[80] = b_A[6560];
  e[79] = b_A[6559];
  e[80] = 0.0;
  std::memset(&U[6480], 0, 81U * sizeof(double));
  U[6560] = 1.0;
  for (q = 79; q >= 0; q--) {
    qp1 = q + 2;
    qq = q + 81 * q;
    if (s[q] != 0.0) {
      for (k = qp1; k < 82; k++) {
        qjj = (q + 81 * (k - 1)) + 1;
        d_xaxpy(81 - q, -(b_xdotc(81 - q, U, qq + 1, U, qjj) / U[qq]), qq + 1, U,
                qjj);
      }

      for (k = q + 1; k < 82; k++) {
        qjj = (k + 81 * q) - 1;
        U[qjj] = -U[qjj];
      }

      U[qq]++;
      for (k = 0; k < q; k++) {
        U[k + 81 * q] = 0.0;
      }
    } else {
      std::memset(&U[q * 81], 0, 81U * sizeof(double));
      U[qq] = 1.0;
    }
  }

  for (q = 80; q >= 0; q--) {
    if ((q + 1 <= 79) && (e[q] != 0.0)) {
      qp1 = q + 2;
      qjj = (q + 81 * q) + 2;
      for (k = qp1; k < 82; k++) {
        qp1jj = (q + 81 * (k - 1)) + 2;
        d_xaxpy(80 - q, -(b_xdotc(80 - q, V, qjj, V, qp1jj) / V[qjj - 1]), qjj,
                V, qp1jj);
      }
    }

    std::memset(&V[q * 81], 0, 81U * sizeof(double));
    V[q + 81 * q] = 1.0;
  }

  qq = 0;
  snorm = 0.0;
  for (q = 0; q < 81; q++) {
    if (s[q] != 0.0) {
      nrm = std::abs(s[q]);
      r = s[q] / nrm;
      s[q] = nrm;
      if (q + 1 < 81) {
        e[q] /= r;
      }

      qjj = 81 * q;
      qp1jj = qjj + 81;
      for (k = qjj + 1; k <= qp1jj; k++) {
        U[k - 1] *= r;
      }
    }

    if ((q + 1 < 81) && (e[q] != 0.0)) {
      nrm = std::abs(e[q]);
      r = nrm / e[q];
      e[q] = nrm;
      s[q + 1] *= r;
      qjj = 81 * (q + 1);
      qp1jj = qjj + 81;
      for (k = qjj + 1; k <= qp1jj; k++) {
        V[k - 1] *= r;
      }
    }

    nrm = std::abs(s[q]);
    r = std::abs(e[q]);
    if ((nrm > r) || rtIsNaN(r)) {
      r = nrm;
    }

    if ((!(snorm > r)) && (!rtIsNaN(r))) {
      snorm = r;
    }
  }

  while ((m + 2 > 0) && (qq < 75)) {
    k = m;
    int exitg1;
    do {
      exitg1 = 0;
      q = k + 1;
      if (k + 1 == 0) {
        exitg1 = 1;
      } else {
        nrm = std::abs(e[k]);
        if ((nrm <= 2.2204460492503131E-16 * (std::abs(s[k]) + std::abs(s[k + 1])))
            || (nrm <= 1.0020841800044864E-292) || ((qq > 20) && (nrm <=
              2.2204460492503131E-16 * snorm))) {
          e[k] = 0.0;
          exitg1 = 1;
        } else {
          k--;
        }
      }
    } while (exitg1 == 0);

    if (k + 1 == m + 1) {
      qjj = 4;
    } else {
      boolean_T exitg2;
      qp1jj = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= k + 1)) {
        qp1jj = qjj;
        if (qjj == k + 1) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (qjj < m + 2) {
            nrm = std::abs(e[qjj - 1]);
          }

          if (qjj > k + 2) {
            nrm += std::abs(e[qjj - 2]);
          }

          r = std::abs(s[qjj - 1]);
          if ((r <= 2.2204460492503131E-16 * nrm) || (r <=
               1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qp1jj == k + 1) {
        qjj = 3;
      } else if (qp1jj == m + 2) {
        qjj = 1;
      } else {
        qjj = 2;
        q = qp1jj;
      }
    }

    switch (qjj) {
     case 1:
      {
        r = e[m];
        e[m] = 0.0;
        qp1jj = m + 1;
        for (k = qp1jj; k >= q + 1; k--) {
          xrotg(&s[k - 1], &r, &sm, &sqds);
          if (k > q + 1) {
            double b;
            b = e[k - 2];
            r = -sqds * b;
            e[k - 2] = b * sm;
          }

          b_xrot(V, 81 * (k - 1) + 1, 81 * (m + 1) + 1, sm, sqds);
        }
      }
      break;

     case 2:
      {
        r = e[q - 1];
        e[q - 1] = 0.0;
        for (k = q + 1; k <= m + 2; k++) {
          double b;
          xrotg(&s[k - 1], &r, &sm, &sqds);
          b = e[k - 1];
          r = -sqds * b;
          e[k - 1] = b * sm;
          b_xrot(U, 81 * (k - 1) + 1, 81 * (q - 1) + 1, sm, sqds);
        }
      }
      break;

     case 3:
      {
        double scale;
        double b;
        qjj = m + 1;
        nrm = s[m + 1];
        scale = std::abs(nrm);
        r = std::abs(s[m]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(e[m]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(s[q]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(e[q]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        sm = nrm / scale;
        nrm = s[m] / scale;
        r = e[m] / scale;
        sqds = s[q] / scale;
        b = ((nrm + sm) * (nrm - sm) + r * r) / 2.0;
        nrm = sm * r;
        nrm *= nrm;
        if ((b != 0.0) || (nrm != 0.0)) {
          r = std::sqrt(b * b + nrm);
          if (b < 0.0) {
            r = -r;
          }

          r = nrm / (b + r);
        } else {
          r = 0.0;
        }

        r += (sqds + sm) * (sqds - sm);
        nrm = sqds * (e[q] / scale);
        for (k = q + 1; k <= qjj; k++) {
          xrotg(&r, &nrm, &sm, &sqds);
          if (k > q + 1) {
            e[k - 2] = r;
          }

          nrm = e[k - 1];
          b = s[k - 1];
          e[k - 1] = sm * nrm - sqds * b;
          r = sqds * s[k];
          s[k] *= sm;
          b_xrot(V, 81 * (k - 1) + 1, 81 * k + 1, sm, sqds);
          s[k - 1] = sm * b + sqds * nrm;
          xrotg(&s[k - 1], &r, &sm, &sqds);
          r = sm * e[k - 1] + sqds * s[k];
          s[k] = -sqds * e[k - 1] + sm * s[k];
          nrm = sqds * e[k];
          e[k] *= sm;
          b_xrot(U, 81 * (k - 1) + 1, 81 * k + 1, sm, sqds);
        }

        e[m] = r;
        qq++;
      }
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        qjj = 81 * q;
        qp1jj = qjj + 81;
        for (k = qjj + 1; k <= qp1jj; k++) {
          V[k - 1] = -V[k - 1];
        }
      }

      qp1 = q + 1;
      while ((q + 1 < 81) && (s[q] < s[qp1])) {
        nrm = s[q];
        s[q] = s[qp1];
        s[qp1] = nrm;
        b_xswap(V, 81 * q + 1, 81 * (q + 1) + 1);
        b_xswap(U, 81 * q + 1, 81 * (q + 1) + 1);
        q = qp1;
        qp1++;
      }

      qq = 0;
      m--;
      break;
    }
  }
}

//
// Arguments    : const double A[231361]
//                double U[231361]
//                double s[481]
//                double V[231361]
// Return Type  : void
//
void f_svd(const double A[231361], double U[231361], double s[481], double V
           [231361])
{
  static double b_A[231361];
  double e[481];
  double work[481];
  int q;
  int m;
  int qp1;
  int qq;
  double nrm;
  int k;
  int qjj;
  int qp1jj;
  double snorm;
  double r;
  double sm;
  double sqds;
  std::memcpy(&b_A[0], &A[0], 231361U * sizeof(double));
  std::memset(&s[0], 0, 481U * sizeof(double));
  std::memset(&e[0], 0, 481U * sizeof(double));
  std::memset(&work[0], 0, 481U * sizeof(double));
  std::memset(&U[0], 0, 231361U * sizeof(double));
  std::memset(&V[0], 0, 231361U * sizeof(double));
  for (q = 0; q < 480; q++) {
    boolean_T apply_transform;
    qp1 = q + 2;
    qq = (q + 481 * q) + 1;
    apply_transform = false;
    nrm = e_xnrm2(481 - q, b_A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0) {
        nrm = -nrm;
      }

      s[q] = nrm;
      if (std::abs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qp1jj = (qq - q) + 480;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qp1jj = (qq - q) + 480;
        for (k = qq; k <= qp1jj; k++) {
          b_A[k - 1] /= s[q];
        }
      }

      b_A[qq - 1]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }

    for (k = qp1; k < 482; k++) {
      qjj = q + 481 * (k - 1);
      if (apply_transform) {
        g_xaxpy(481 - q, -(c_xdotc(481 - q, b_A, qq, b_A, qjj + 1) / b_A[q + 481
                           * q]), qq, b_A, qjj + 1);
      }

      e[k - 1] = b_A[qjj];
    }

    for (k = q + 1; k < 482; k++) {
      qjj = (k + 481 * q) - 1;
      U[qjj] = b_A[qjj];
    }

    if (q + 1 <= 479) {
      nrm = f_xnrm2(480 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }

        nrm = e[q];
        if (std::abs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          for (k = qp1; k < 482; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (k = qp1; k < 482; k++) {
            e[k - 1] /= nrm;
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (k = qp1; k < 482; k++) {
          work[k - 1] = 0.0;
        }

        for (k = qp1; k < 482; k++) {
          h_xaxpy(480 - q, e[k - 1], b_A, (q + 481 * (k - 1)) + 2, work, q + 2);
        }

        for (k = qp1; k < 482; k++) {
          i_xaxpy(480 - q, -e[k - 1] / e[q + 1], work, q + 2, b_A, (q + 481 * (k
                    - 1)) + 2);
        }
      }

      for (k = qp1; k < 482; k++) {
        V[(k + 481 * q) - 1] = e[k - 1];
      }
    }
  }

  m = 479;
  s[480] = b_A[231360];
  e[479] = b_A[231359];
  e[480] = 0.0;
  std::memset(&U[230880], 0, 481U * sizeof(double));
  U[231360] = 1.0;
  for (q = 479; q >= 0; q--) {
    qp1 = q + 2;
    qq = q + 481 * q;
    if (s[q] != 0.0) {
      for (k = qp1; k < 482; k++) {
        qjj = (q + 481 * (k - 1)) + 1;
        g_xaxpy(481 - q, -(c_xdotc(481 - q, U, qq + 1, U, qjj) / U[qq]), qq + 1,
                U, qjj);
      }

      for (k = q + 1; k < 482; k++) {
        qjj = (k + 481 * q) - 1;
        U[qjj] = -U[qjj];
      }

      U[qq]++;
      for (k = 0; k < q; k++) {
        U[k + 481 * q] = 0.0;
      }
    } else {
      std::memset(&U[q * 481], 0, 481U * sizeof(double));
      U[qq] = 1.0;
    }
  }

  for (q = 480; q >= 0; q--) {
    if ((q + 1 <= 479) && (e[q] != 0.0)) {
      qp1 = q + 2;
      qjj = (q + 481 * q) + 2;
      for (k = qp1; k < 482; k++) {
        qp1jj = (q + 481 * (k - 1)) + 2;
        g_xaxpy(480 - q, -(c_xdotc(480 - q, V, qjj, V, qp1jj) / V[qjj - 1]), qjj,
                V, qp1jj);
      }
    }

    std::memset(&V[q * 481], 0, 481U * sizeof(double));
    V[q + 481 * q] = 1.0;
  }

  qq = 0;
  snorm = 0.0;
  for (q = 0; q < 481; q++) {
    if (s[q] != 0.0) {
      nrm = std::abs(s[q]);
      r = s[q] / nrm;
      s[q] = nrm;
      if (q + 1 < 481) {
        e[q] /= r;
      }

      qjj = 481 * q;
      qp1jj = qjj + 481;
      for (k = qjj + 1; k <= qp1jj; k++) {
        U[k - 1] *= r;
      }
    }

    if ((q + 1 < 481) && (e[q] != 0.0)) {
      nrm = std::abs(e[q]);
      r = nrm / e[q];
      e[q] = nrm;
      s[q + 1] *= r;
      qjj = 481 * (q + 1);
      qp1jj = qjj + 481;
      for (k = qjj + 1; k <= qp1jj; k++) {
        V[k - 1] *= r;
      }
    }

    nrm = std::abs(s[q]);
    r = std::abs(e[q]);
    if ((nrm > r) || rtIsNaN(r)) {
      r = nrm;
    }

    if ((!(snorm > r)) && (!rtIsNaN(r))) {
      snorm = r;
    }
  }

  while ((m + 2 > 0) && (qq < 75)) {
    k = m;
    int exitg1;
    do {
      exitg1 = 0;
      q = k + 1;
      if (k + 1 == 0) {
        exitg1 = 1;
      } else {
        nrm = std::abs(e[k]);
        if ((nrm <= 2.2204460492503131E-16 * (std::abs(s[k]) + std::abs(s[k + 1])))
            || (nrm <= 1.0020841800044864E-292) || ((qq > 20) && (nrm <=
              2.2204460492503131E-16 * snorm))) {
          e[k] = 0.0;
          exitg1 = 1;
        } else {
          k--;
        }
      }
    } while (exitg1 == 0);

    if (k + 1 == m + 1) {
      qjj = 4;
    } else {
      boolean_T exitg2;
      qp1jj = m + 2;
      qjj = m + 2;
      exitg2 = false;
      while ((!exitg2) && (qjj >= k + 1)) {
        qp1jj = qjj;
        if (qjj == k + 1) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (qjj < m + 2) {
            nrm = std::abs(e[qjj - 1]);
          }

          if (qjj > k + 2) {
            nrm += std::abs(e[qjj - 2]);
          }

          r = std::abs(s[qjj - 1]);
          if ((r <= 2.2204460492503131E-16 * nrm) || (r <=
               1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg2 = true;
          } else {
            qjj--;
          }
        }
      }

      if (qp1jj == k + 1) {
        qjj = 3;
      } else if (qp1jj == m + 2) {
        qjj = 1;
      } else {
        qjj = 2;
        q = qp1jj;
      }
    }

    switch (qjj) {
     case 1:
      {
        r = e[m];
        e[m] = 0.0;
        qp1jj = m + 1;
        for (k = qp1jj; k >= q + 1; k--) {
          xrotg(&s[k - 1], &r, &sm, &sqds);
          if (k > q + 1) {
            double b;
            b = e[k - 2];
            r = -sqds * b;
            e[k - 2] = b * sm;
          }

          c_xrot(V, 481 * (k - 1) + 1, 481 * (m + 1) + 1, sm, sqds);
        }
      }
      break;

     case 2:
      {
        r = e[q - 1];
        e[q - 1] = 0.0;
        for (k = q + 1; k <= m + 2; k++) {
          double b;
          xrotg(&s[k - 1], &r, &sm, &sqds);
          b = e[k - 1];
          r = -sqds * b;
          e[k - 1] = b * sm;
          c_xrot(U, 481 * (k - 1) + 1, 481 * (q - 1) + 1, sm, sqds);
        }
      }
      break;

     case 3:
      {
        double scale;
        double b;
        qjj = m + 1;
        nrm = s[m + 1];
        scale = std::abs(nrm);
        r = std::abs(s[m]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(e[m]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(s[q]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        r = std::abs(e[q]);
        if ((!(scale > r)) && (!rtIsNaN(r))) {
          scale = r;
        }

        sm = nrm / scale;
        nrm = s[m] / scale;
        r = e[m] / scale;
        sqds = s[q] / scale;
        b = ((nrm + sm) * (nrm - sm) + r * r) / 2.0;
        nrm = sm * r;
        nrm *= nrm;
        if ((b != 0.0) || (nrm != 0.0)) {
          r = std::sqrt(b * b + nrm);
          if (b < 0.0) {
            r = -r;
          }

          r = nrm / (b + r);
        } else {
          r = 0.0;
        }

        r += (sqds + sm) * (sqds - sm);
        nrm = sqds * (e[q] / scale);
        for (k = q + 1; k <= qjj; k++) {
          xrotg(&r, &nrm, &sm, &sqds);
          if (k > q + 1) {
            e[k - 2] = r;
          }

          nrm = e[k - 1];
          b = s[k - 1];
          e[k - 1] = sm * nrm - sqds * b;
          r = sqds * s[k];
          s[k] *= sm;
          c_xrot(V, 481 * (k - 1) + 1, 481 * k + 1, sm, sqds);
          s[k - 1] = sm * b + sqds * nrm;
          xrotg(&s[k - 1], &r, &sm, &sqds);
          r = sm * e[k - 1] + sqds * s[k];
          s[k] = -sqds * e[k - 1] + sm * s[k];
          nrm = sqds * e[k];
          e[k] *= sm;
          c_xrot(U, 481 * (k - 1) + 1, 481 * k + 1, sm, sqds);
        }

        e[m] = r;
        qq++;
      }
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        qjj = 481 * q;
        qp1jj = qjj + 481;
        for (k = qjj + 1; k <= qp1jj; k++) {
          V[k - 1] = -V[k - 1];
        }
      }

      qp1 = q + 1;
      while ((q + 1 < 481) && (s[q] < s[qp1])) {
        nrm = s[q];
        s[q] = s[qp1];
        s[qp1] = nrm;
        c_xswap(V, 481 * q + 1, 481 * (q + 1) + 1);
        c_xswap(U, 481 * q + 1, 481 * (q + 1) + 1);
        q = qp1;
        qp1++;
      }

      qq = 0;
      m--;
      break;
    }
  }
}

//
// File trailer for svd1.cpp
//
// [EOF]
//
