//
// File: imgaussfilt.cpp
//
// MATLAB Coder version            : 5.0
// C/C++ source code generated on  : 12-Jun-2020 10:33:50
//

// Include Files
#include "imgaussfilt.h"
#include "imfilter.h"
#include "libmwimfilter.h"
#include "libmwippfilter.h"
#include "lightpro.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include <cmath>

// Function Definitions

//
// Arguments    : const coder::array<double, 2U> *A
//                coder::array<double, 2U> *B
// Return Type  : void
//
void b_imgaussfilt(const coder::array<double, 2U> &A, coder::array<double, 2U>
                   &B)
{
  int j;
  int h_tmp;
  int i;
  double sumH;
  static double h[231361];
  static short Y[231361];
  double d;
  coder::array<int, 1U> r;
  static boolean_T bv[231361];
  for (j = 0; j < 481; j++) {
    for (i = 0; i < 481; i++) {
      h_tmp = i + 481 * j;
      h[h_tmp] = ((static_cast<double>(j) + 1.0) - 1.0) + -240.0;
      Y[h_tmp] = static_cast<short>(i - 240);
    }
  }

  for (h_tmp = 0; h_tmp < 231361; h_tmp++) {
    h[h_tmp] = std::exp(-(h[h_tmp] * h[h_tmp] / 14400.0 + static_cast<double>
                          (Y[h_tmp] * Y[h_tmp]) / 14400.0) / 2.0);
  }

  sumH = h[0];
  for (h_tmp = 0; h_tmp < 231360; h_tmp++) {
    d = h[h_tmp + 1];
    if (sumH < d) {
      sumH = d;
    }
  }

  d = 2.2204460492503131E-16 * sumH;
  h_tmp = 0;
  for (i = 0; i < 231361; i++) {
    boolean_T b;
    b = (h[i] < d);
    bv[i] = b;
    if (b) {
      h_tmp++;
    }
  }

  r.set_size(h_tmp);
  h_tmp = 0;
  for (i = 0; i < 231361; i++) {
    if (bv[i]) {
      r[h_tmp] = i + 1;
      h_tmp++;
    }
  }

  h_tmp = r.size(0);
  for (j = 0; j < h_tmp; j++) {
    h[r[j] - 1] = 0.0;
  }

  sumH = h[0];
  for (h_tmp = 0; h_tmp < 231360; h_tmp++) {
    sumH += h[h_tmp + 1];
  }

  if (sumH != 0.0) {
    for (j = 0; j < 231361; j++) {
      h[j] /= sumH;
    }
  }

  B.set_size(A.size(0), A.size(1));
  h_tmp = A.size(0) * A.size(1);
  for (j = 0; j < h_tmp; j++) {
    B[j] = A[j];
  }

  b_imfilter(B, h);
}

//
// Arguments    : coder::array<double, 2U> *A
// Return Type  : void
//
void c_imgaussfilt(coder::array<double, 2U> &A)
{
  double outSizeT[2];
  double startT[2];
  static const double h[441] = { 0.00012532191133954771, 0.0001832562996702628,
    0.00025746549667733556, 0.00034754206833683169, 0.00045073776480808881,
    0.000561653840324327, 0.000672421729700329, 0.00077346909745654494,
    0.00085481555253919233, 0.00090767439424147944, 0.00092601063331313133,
    0.00090767439424147944, 0.00085481555253919233, 0.00077346909745654494,
    0.000672421729700329, 0.000561653840324327, 0.00045073776480808881,
    0.00034754206833683169, 0.00025746549667733556, 0.0001832562996702628,
    0.00012532191133954771, 0.0001832562996702628, 0.00026797286292456541,
    0.00037648782810229632, 0.00050820541070904508, 0.00065910688735489617,
    0.00082129775530281391, 0.00098327193294149638, 0.0011310319416143041,
    0.0012499836092867626, 0.0013272782789233602, 0.0013540910787460181,
    0.0013272782789233602, 0.0012499836092867626, 0.0011310319416143041,
    0.00098327193294149638, 0.00082129775530281391, 0.00065910688735489617,
    0.00050820541070904508, 0.00037648782810229632, 0.00026797286292456541,
    0.0001832562996702628, 0.00025746549667733556, 0.00037648782810229632,
    0.00052894566696884188, 0.00071400196728705462, 0.00092601063331313133,
    0.0011538803024479763, 0.001381445533054963, 0.0015890406012214798,
    0.0017561614601114221, 0.0018647564199807684, 0.001902426998487876,
    0.0018647564199807684, 0.0017561614601114221, 0.0015890406012214798,
    0.001381445533054963, 0.0011538803024479763, 0.00092601063331313133,
    0.00071400196728705462, 0.00052894566696884188, 0.00037648782810229632,
    0.00025746549667733556, 0.00034754206833683169, 0.00050820541070904508,
    0.00071400196728705462, 0.00096380184416902388, 0.0012499836092867628,
    0.0015575754891478633, 0.0018647564199807684, 0.0021449804511546821,
    0.0023705700144569367, 0.0025171578774949369, 0.0025680078396792391,
    0.0025171578774949369, 0.0023705700144569367, 0.0021449804511546821,
    0.0018647564199807684, 0.0015575754891478633, 0.0012499836092867628,
    0.00096380184416902388, 0.00071400196728705462, 0.00050820541070904508,
    0.00034754206833683169, 0.00045073776480808881, 0.00065910688735489617,
    0.00092601063331313133, 0.0012499836092867628, 0.0016211413507230756,
    0.0020200665141290202, 0.0024184587053762128, 0.0027818896824124283,
    0.0030744635742969146, 0.0032645777842109387, 0.003330526630073577,
    0.0032645777842109387, 0.0030744635742969146, 0.0027818896824124283,
    0.0024184587053762128, 0.0020200665141290202, 0.0016211413507230756,
    0.0012499836092867628, 0.00092601063331313133, 0.00065910688735489617,
    0.00045073776480808881, 0.000561653840324327, 0.00082129775530281391,
    0.0011538803024479763, 0.0015575754891478633, 0.0020200665141290202,
    0.0025171578774949369, 0.0030135851166557806, 0.0034664480003152457,
    0.0038310175189698926, 0.0040679144120977619, 0.0041500917343362895,
    0.0040679144120977619, 0.0038310175189698926, 0.0034664480003152457,
    0.0030135851166557806, 0.0025171578774949369, 0.0020200665141290202,
    0.0015575754891478633, 0.0011538803024479763, 0.00082129775530281391,
    0.000561653840324327, 0.000672421729700329, 0.00098327193294149638,
    0.001381445533054963, 0.0018647564199807684, 0.0024184587053762128,
    0.0030135851166557806, 0.0036079164269057665, 0.0041500917343362895,
    0.0045865606921345944, 0.0048701777658568916, 0.0049685618828957129,
    0.0048701777658568916, 0.0045865606921345944, 0.0041500917343362895,
    0.0036079164269057665, 0.0030135851166557806, 0.0024184587053762128,
    0.0018647564199807684, 0.001381445533054963, 0.00098327193294149638,
    0.000672421729700329, 0.00077346909745654494, 0.0011310319416143041,
    0.0015890406012214798, 0.0021449804511546821, 0.0027818896824124283,
    0.0034664480003152457, 0.0041500917343362895, 0.0047737417848609824,
    0.0052758005910308924, 0.0056020378798422111, 0.0057152065518956694,
    0.0056020378798422111, 0.0052758005910308924, 0.0047737417848609824,
    0.0041500917343362895, 0.0034664480003152457, 0.0027818896824124283,
    0.0021449804511546821, 0.0015890406012214798, 0.0011310319416143041,
    0.00077346909745654494, 0.00085481555253919233, 0.0012499836092867626,
    0.0017561614601114221, 0.0023705700144569367, 0.0030744635742969146,
    0.0038310175189698926, 0.0045865606921345944, 0.0052758005910308924,
    0.0058306613827736565, 0.00619120934675977, 0.0063162800719504929,
    0.00619120934675977, 0.0058306613827736565, 0.0052758005910308924,
    0.0045865606921345944, 0.0038310175189698926, 0.0030744635742969146,
    0.0023705700144569367, 0.0017561614601114221, 0.0012499836092867626,
    0.00085481555253919233, 0.00090767439424147944, 0.0013272782789233602,
    0.0018647564199807684, 0.0025171578774949369, 0.0032645777842109387,
    0.0040679144120977619, 0.0048701777658568916, 0.0056020378798422111,
    0.00619120934675977, 0.0065740523517027463, 0.0067068570186131875,
    0.0065740523517027463, 0.00619120934675977, 0.0056020378798422111,
    0.0048701777658568916, 0.0040679144120977619, 0.0032645777842109387,
    0.0025171578774949369, 0.0018647564199807684, 0.0013272782789233602,
    0.00090767439424147944, 0.00092601063331313133, 0.0013540910787460181,
    0.001902426998487876, 0.0025680078396792391, 0.003330526630073577,
    0.0041500917343362895, 0.0049685618828957129, 0.0057152065518956694,
    0.0063162800719504929, 0.0067068570186131875, 0.0068423445177570258,
    0.0067068570186131875, 0.0063162800719504929, 0.0057152065518956694,
    0.0049685618828957129, 0.0041500917343362895, 0.003330526630073577,
    0.0025680078396792391, 0.001902426998487876, 0.0013540910787460181,
    0.00092601063331313133, 0.00090767439424147944, 0.0013272782789233602,
    0.0018647564199807684, 0.0025171578774949369, 0.0032645777842109387,
    0.0040679144120977619, 0.0048701777658568916, 0.0056020378798422111,
    0.00619120934675977, 0.0065740523517027463, 0.0067068570186131875,
    0.0065740523517027463, 0.00619120934675977, 0.0056020378798422111,
    0.0048701777658568916, 0.0040679144120977619, 0.0032645777842109387,
    0.0025171578774949369, 0.0018647564199807684, 0.0013272782789233602,
    0.00090767439424147944, 0.00085481555253919233, 0.0012499836092867626,
    0.0017561614601114221, 0.0023705700144569367, 0.0030744635742969146,
    0.0038310175189698926, 0.0045865606921345944, 0.0052758005910308924,
    0.0058306613827736565, 0.00619120934675977, 0.0063162800719504929,
    0.00619120934675977, 0.0058306613827736565, 0.0052758005910308924,
    0.0045865606921345944, 0.0038310175189698926, 0.0030744635742969146,
    0.0023705700144569367, 0.0017561614601114221, 0.0012499836092867626,
    0.00085481555253919233, 0.00077346909745654494, 0.0011310319416143041,
    0.0015890406012214798, 0.0021449804511546821, 0.0027818896824124283,
    0.0034664480003152457, 0.0041500917343362895, 0.0047737417848609824,
    0.0052758005910308924, 0.0056020378798422111, 0.0057152065518956694,
    0.0056020378798422111, 0.0052758005910308924, 0.0047737417848609824,
    0.0041500917343362895, 0.0034664480003152457, 0.0027818896824124283,
    0.0021449804511546821, 0.0015890406012214798, 0.0011310319416143041,
    0.00077346909745654494, 0.000672421729700329, 0.00098327193294149638,
    0.001381445533054963, 0.0018647564199807684, 0.0024184587053762128,
    0.0030135851166557806, 0.0036079164269057665, 0.0041500917343362895,
    0.0045865606921345944, 0.0048701777658568916, 0.0049685618828957129,
    0.0048701777658568916, 0.0045865606921345944, 0.0041500917343362895,
    0.0036079164269057665, 0.0030135851166557806, 0.0024184587053762128,
    0.0018647564199807684, 0.001381445533054963, 0.00098327193294149638,
    0.000672421729700329, 0.000561653840324327, 0.00082129775530281391,
    0.0011538803024479763, 0.0015575754891478633, 0.0020200665141290202,
    0.0025171578774949369, 0.0030135851166557806, 0.0034664480003152457,
    0.0038310175189698926, 0.0040679144120977619, 0.0041500917343362895,
    0.0040679144120977619, 0.0038310175189698926, 0.0034664480003152457,
    0.0030135851166557806, 0.0025171578774949369, 0.0020200665141290202,
    0.0015575754891478633, 0.0011538803024479763, 0.00082129775530281391,
    0.000561653840324327, 0.00045073776480808881, 0.00065910688735489617,
    0.00092601063331313133, 0.0012499836092867628, 0.0016211413507230756,
    0.0020200665141290202, 0.0024184587053762128, 0.0027818896824124283,
    0.0030744635742969146, 0.0032645777842109387, 0.003330526630073577,
    0.0032645777842109387, 0.0030744635742969146, 0.0027818896824124283,
    0.0024184587053762128, 0.0020200665141290202, 0.0016211413507230756,
    0.0012499836092867628, 0.00092601063331313133, 0.00065910688735489617,
    0.00045073776480808881, 0.00034754206833683169, 0.00050820541070904508,
    0.00071400196728705462, 0.00096380184416902388, 0.0012499836092867628,
    0.0015575754891478633, 0.0018647564199807684, 0.0021449804511546821,
    0.0023705700144569367, 0.0025171578774949369, 0.0025680078396792391,
    0.0025171578774949369, 0.0023705700144569367, 0.0021449804511546821,
    0.0018647564199807684, 0.0015575754891478633, 0.0012499836092867628,
    0.00096380184416902388, 0.00071400196728705462, 0.00050820541070904508,
    0.00034754206833683169, 0.00025746549667733556, 0.00037648782810229632,
    0.00052894566696884188, 0.00071400196728705462, 0.00092601063331313133,
    0.0011538803024479763, 0.001381445533054963, 0.0015890406012214798,
    0.0017561614601114221, 0.0018647564199807684, 0.001902426998487876,
    0.0018647564199807684, 0.0017561614601114221, 0.0015890406012214798,
    0.001381445533054963, 0.0011538803024479763, 0.00092601063331313133,
    0.00071400196728705462, 0.00052894566696884188, 0.00037648782810229632,
    0.00025746549667733556, 0.0001832562996702628, 0.00026797286292456541,
    0.00037648782810229632, 0.00050820541070904508, 0.00065910688735489617,
    0.00082129775530281391, 0.00098327193294149638, 0.0011310319416143041,
    0.0012499836092867626, 0.0013272782789233602, 0.0013540910787460181,
    0.0013272782789233602, 0.0012499836092867626, 0.0011310319416143041,
    0.00098327193294149638, 0.00082129775530281391, 0.00065910688735489617,
    0.00050820541070904508, 0.00037648782810229632, 0.00026797286292456541,
    0.0001832562996702628, 0.00012532191133954771, 0.0001832562996702628,
    0.00025746549667733556, 0.00034754206833683169, 0.00045073776480808881,
    0.000561653840324327, 0.000672421729700329, 0.00077346909745654494,
    0.00085481555253919233, 0.00090767439424147944, 0.00092601063331313133,
    0.00090767439424147944, 0.00085481555253919233, 0.00077346909745654494,
    0.000672421729700329, 0.000561653840324327, 0.00045073776480808881,
    0.00034754206833683169, 0.00025746549667733556, 0.0001832562996702628,
    0.00012532191133954771 };

  double unusedU0[441];
  double s[441];
  double unusedU1[441];
  double b_s[21];
  int idx;
  boolean_T x[21];
  coder::array<double, 2U> a;
  double out_size_row[2];
  double padSizeT[2];
  double connDimsT[2];
  boolean_T conn[441];
  double hcol[21];
  static const double nonZeroKernel[441] = { 0.00012532191133954771,
    0.0001832562996702628, 0.00025746549667733556, 0.00034754206833683169,
    0.00045073776480808881, 0.000561653840324327, 0.000672421729700329,
    0.00077346909745654494, 0.00085481555253919233, 0.00090767439424147944,
    0.00092601063331313133, 0.00090767439424147944, 0.00085481555253919233,
    0.00077346909745654494, 0.000672421729700329, 0.000561653840324327,
    0.00045073776480808881, 0.00034754206833683169, 0.00025746549667733556,
    0.0001832562996702628, 0.00012532191133954771, 0.0001832562996702628,
    0.00026797286292456541, 0.00037648782810229632, 0.00050820541070904508,
    0.00065910688735489617, 0.00082129775530281391, 0.00098327193294149638,
    0.0011310319416143041, 0.0012499836092867626, 0.0013272782789233602,
    0.0013540910787460181, 0.0013272782789233602, 0.0012499836092867626,
    0.0011310319416143041, 0.00098327193294149638, 0.00082129775530281391,
    0.00065910688735489617, 0.00050820541070904508, 0.00037648782810229632,
    0.00026797286292456541, 0.0001832562996702628, 0.00025746549667733556,
    0.00037648782810229632, 0.00052894566696884188, 0.00071400196728705462,
    0.00092601063331313133, 0.0011538803024479763, 0.001381445533054963,
    0.0015890406012214798, 0.0017561614601114221, 0.0018647564199807684,
    0.001902426998487876, 0.0018647564199807684, 0.0017561614601114221,
    0.0015890406012214798, 0.001381445533054963, 0.0011538803024479763,
    0.00092601063331313133, 0.00071400196728705462, 0.00052894566696884188,
    0.00037648782810229632, 0.00025746549667733556, 0.00034754206833683169,
    0.00050820541070904508, 0.00071400196728705462, 0.00096380184416902388,
    0.0012499836092867628, 0.0015575754891478633, 0.0018647564199807684,
    0.0021449804511546821, 0.0023705700144569367, 0.0025171578774949369,
    0.0025680078396792391, 0.0025171578774949369, 0.0023705700144569367,
    0.0021449804511546821, 0.0018647564199807684, 0.0015575754891478633,
    0.0012499836092867628, 0.00096380184416902388, 0.00071400196728705462,
    0.00050820541070904508, 0.00034754206833683169, 0.00045073776480808881,
    0.00065910688735489617, 0.00092601063331313133, 0.0012499836092867628,
    0.0016211413507230756, 0.0020200665141290202, 0.0024184587053762128,
    0.0027818896824124283, 0.0030744635742969146, 0.0032645777842109387,
    0.003330526630073577, 0.0032645777842109387, 0.0030744635742969146,
    0.0027818896824124283, 0.0024184587053762128, 0.0020200665141290202,
    0.0016211413507230756, 0.0012499836092867628, 0.00092601063331313133,
    0.00065910688735489617, 0.00045073776480808881, 0.000561653840324327,
    0.00082129775530281391, 0.0011538803024479763, 0.0015575754891478633,
    0.0020200665141290202, 0.0025171578774949369, 0.0030135851166557806,
    0.0034664480003152457, 0.0038310175189698926, 0.0040679144120977619,
    0.0041500917343362895, 0.0040679144120977619, 0.0038310175189698926,
    0.0034664480003152457, 0.0030135851166557806, 0.0025171578774949369,
    0.0020200665141290202, 0.0015575754891478633, 0.0011538803024479763,
    0.00082129775530281391, 0.000561653840324327, 0.000672421729700329,
    0.00098327193294149638, 0.001381445533054963, 0.0018647564199807684,
    0.0024184587053762128, 0.0030135851166557806, 0.0036079164269057665,
    0.0041500917343362895, 0.0045865606921345944, 0.0048701777658568916,
    0.0049685618828957129, 0.0048701777658568916, 0.0045865606921345944,
    0.0041500917343362895, 0.0036079164269057665, 0.0030135851166557806,
    0.0024184587053762128, 0.0018647564199807684, 0.001381445533054963,
    0.00098327193294149638, 0.000672421729700329, 0.00077346909745654494,
    0.0011310319416143041, 0.0015890406012214798, 0.0021449804511546821,
    0.0027818896824124283, 0.0034664480003152457, 0.0041500917343362895,
    0.0047737417848609824, 0.0052758005910308924, 0.0056020378798422111,
    0.0057152065518956694, 0.0056020378798422111, 0.0052758005910308924,
    0.0047737417848609824, 0.0041500917343362895, 0.0034664480003152457,
    0.0027818896824124283, 0.0021449804511546821, 0.0015890406012214798,
    0.0011310319416143041, 0.00077346909745654494, 0.00085481555253919233,
    0.0012499836092867626, 0.0017561614601114221, 0.0023705700144569367,
    0.0030744635742969146, 0.0038310175189698926, 0.0045865606921345944,
    0.0052758005910308924, 0.0058306613827736565, 0.00619120934675977,
    0.0063162800719504929, 0.00619120934675977, 0.0058306613827736565,
    0.0052758005910308924, 0.0045865606921345944, 0.0038310175189698926,
    0.0030744635742969146, 0.0023705700144569367, 0.0017561614601114221,
    0.0012499836092867626, 0.00085481555253919233, 0.00090767439424147944,
    0.0013272782789233602, 0.0018647564199807684, 0.0025171578774949369,
    0.0032645777842109387, 0.0040679144120977619, 0.0048701777658568916,
    0.0056020378798422111, 0.00619120934675977, 0.0065740523517027463,
    0.0067068570186131875, 0.0065740523517027463, 0.00619120934675977,
    0.0056020378798422111, 0.0048701777658568916, 0.0040679144120977619,
    0.0032645777842109387, 0.0025171578774949369, 0.0018647564199807684,
    0.0013272782789233602, 0.00090767439424147944, 0.00092601063331313133,
    0.0013540910787460181, 0.001902426998487876, 0.0025680078396792391,
    0.003330526630073577, 0.0041500917343362895, 0.0049685618828957129,
    0.0057152065518956694, 0.0063162800719504929, 0.0067068570186131875,
    0.0068423445177570258, 0.0067068570186131875, 0.0063162800719504929,
    0.0057152065518956694, 0.0049685618828957129, 0.0041500917343362895,
    0.003330526630073577, 0.0025680078396792391, 0.001902426998487876,
    0.0013540910787460181, 0.00092601063331313133, 0.00090767439424147944,
    0.0013272782789233602, 0.0018647564199807684, 0.0025171578774949369,
    0.0032645777842109387, 0.0040679144120977619, 0.0048701777658568916,
    0.0056020378798422111, 0.00619120934675977, 0.0065740523517027463,
    0.0067068570186131875, 0.0065740523517027463, 0.00619120934675977,
    0.0056020378798422111, 0.0048701777658568916, 0.0040679144120977619,
    0.0032645777842109387, 0.0025171578774949369, 0.0018647564199807684,
    0.0013272782789233602, 0.00090767439424147944, 0.00085481555253919233,
    0.0012499836092867626, 0.0017561614601114221, 0.0023705700144569367,
    0.0030744635742969146, 0.0038310175189698926, 0.0045865606921345944,
    0.0052758005910308924, 0.0058306613827736565, 0.00619120934675977,
    0.0063162800719504929, 0.00619120934675977, 0.0058306613827736565,
    0.0052758005910308924, 0.0045865606921345944, 0.0038310175189698926,
    0.0030744635742969146, 0.0023705700144569367, 0.0017561614601114221,
    0.0012499836092867626, 0.00085481555253919233, 0.00077346909745654494,
    0.0011310319416143041, 0.0015890406012214798, 0.0021449804511546821,
    0.0027818896824124283, 0.0034664480003152457, 0.0041500917343362895,
    0.0047737417848609824, 0.0052758005910308924, 0.0056020378798422111,
    0.0057152065518956694, 0.0056020378798422111, 0.0052758005910308924,
    0.0047737417848609824, 0.0041500917343362895, 0.0034664480003152457,
    0.0027818896824124283, 0.0021449804511546821, 0.0015890406012214798,
    0.0011310319416143041, 0.00077346909745654494, 0.000672421729700329,
    0.00098327193294149638, 0.001381445533054963, 0.0018647564199807684,
    0.0024184587053762128, 0.0030135851166557806, 0.0036079164269057665,
    0.0041500917343362895, 0.0045865606921345944, 0.0048701777658568916,
    0.0049685618828957129, 0.0048701777658568916, 0.0045865606921345944,
    0.0041500917343362895, 0.0036079164269057665, 0.0030135851166557806,
    0.0024184587053762128, 0.0018647564199807684, 0.001381445533054963,
    0.00098327193294149638, 0.000672421729700329, 0.000561653840324327,
    0.00082129775530281391, 0.0011538803024479763, 0.0015575754891478633,
    0.0020200665141290202, 0.0025171578774949369, 0.0030135851166557806,
    0.0034664480003152457, 0.0038310175189698926, 0.0040679144120977619,
    0.0041500917343362895, 0.0040679144120977619, 0.0038310175189698926,
    0.0034664480003152457, 0.0030135851166557806, 0.0025171578774949369,
    0.0020200665141290202, 0.0015575754891478633, 0.0011538803024479763,
    0.00082129775530281391, 0.000561653840324327, 0.00045073776480808881,
    0.00065910688735489617, 0.00092601063331313133, 0.0012499836092867628,
    0.0016211413507230756, 0.0020200665141290202, 0.0024184587053762128,
    0.0027818896824124283, 0.0030744635742969146, 0.0032645777842109387,
    0.003330526630073577, 0.0032645777842109387, 0.0030744635742969146,
    0.0027818896824124283, 0.0024184587053762128, 0.0020200665141290202,
    0.0016211413507230756, 0.0012499836092867628, 0.00092601063331313133,
    0.00065910688735489617, 0.00045073776480808881, 0.00034754206833683169,
    0.00050820541070904508, 0.00071400196728705462, 0.00096380184416902388,
    0.0012499836092867628, 0.0015575754891478633, 0.0018647564199807684,
    0.0021449804511546821, 0.0023705700144569367, 0.0025171578774949369,
    0.0025680078396792391, 0.0025171578774949369, 0.0023705700144569367,
    0.0021449804511546821, 0.0018647564199807684, 0.0015575754891478633,
    0.0012499836092867628, 0.00096380184416902388, 0.00071400196728705462,
    0.00050820541070904508, 0.00034754206833683169, 0.00025746549667733556,
    0.00037648782810229632, 0.00052894566696884188, 0.00071400196728705462,
    0.00092601063331313133, 0.0011538803024479763, 0.001381445533054963,
    0.0015890406012214798, 0.0017561614601114221, 0.0018647564199807684,
    0.001902426998487876, 0.0018647564199807684, 0.0017561614601114221,
    0.0015890406012214798, 0.001381445533054963, 0.0011538803024479763,
    0.00092601063331313133, 0.00071400196728705462, 0.00052894566696884188,
    0.00037648782810229632, 0.00025746549667733556, 0.0001832562996702628,
    0.00026797286292456541, 0.00037648782810229632, 0.00050820541070904508,
    0.00065910688735489617, 0.00082129775530281391, 0.00098327193294149638,
    0.0011310319416143041, 0.0012499836092867626, 0.0013272782789233602,
    0.0013540910787460181, 0.0013272782789233602, 0.0012499836092867626,
    0.0011310319416143041, 0.00098327193294149638, 0.00082129775530281391,
    0.00065910688735489617, 0.00050820541070904508, 0.00037648782810229632,
    0.00026797286292456541, 0.0001832562996702628, 0.00012532191133954771,
    0.0001832562996702628, 0.00025746549667733556, 0.00034754206833683169,
    0.00045073776480808881, 0.000561653840324327, 0.000672421729700329,
    0.00077346909745654494, 0.00085481555253919233, 0.00090767439424147944,
    0.00092601063331313133, 0.00090767439424147944, 0.00085481555253919233,
    0.00077346909745654494, 0.000672421729700329, 0.000561653840324327,
    0.00045073776480808881, 0.00034754206833683169, 0.00025746549667733556,
    0.0001832562996702628, 0.00012532191133954771 };

  double nonzero_h_data[21];
  signed char tmp_data[21];
  signed char b_tmp_data[21];
  outSizeT[0] = A.size(0);
  startT[0] = 10.0;
  outSizeT[1] = A.size(1);
  startT[1] = 10.0;
  if ((A.size(0) != 0) && (A.size(1) != 0)) {
    int i;
    double tol;
    int b_i;
    double d;
    svd(h, unusedU0, s, unusedU1);
    for (i = 0; i < 21; i++) {
      b_s[i] = s[i + 21 * i];
    }

    if (!rtIsNaN(b_s[0])) {
      idx = 1;
    } else {
      boolean_T exitg1;
      idx = 0;
      i = 2;
      exitg1 = false;
      while ((!exitg1) && (i <= 21)) {
        if (!rtIsNaN(b_s[i - 1])) {
          idx = i;
          exitg1 = true;
        } else {
          i++;
        }
      }
    }

    if (idx == 0) {
      tol = b_s[0];
    } else {
      tol = b_s[idx - 1];
      b_i = idx + 1;
      for (i = b_i; i < 22; i++) {
        d = b_s[i - 1];
        if (tol < d) {
          tol = d;
        }
      }
    }

    tol = 21.0 * tol * 2.2204460492503131E-16;
    for (i = 0; i < 21; i++) {
      x[i] = (b_s[i] > tol);
    }

    idx = x[0];
    for (i = 0; i < 20; i++) {
      idx += x[i + 1];
    }

    if (idx == 1) {
      boolean_T tooBig;
      int trueCount;
      padImage(A, startT, a);
      svd(h, unusedU0, s, unusedU1);
      for (i = 0; i < 21; i++) {
        b_s[i] = s[i + 21 * i];
      }

      tol = std::sqrt(b_s[0]);
      out_size_row[0] = a.size(0);
      out_size_row[1] = A.size(1);
      trueCount = 0;
      idx = 0;
      for (i = 0; i < 21; i++) {
        hcol[i] = unusedU0[i] * tol;
        d = unusedU1[i] * tol;
        b_s[i] = d;
        if (d != 0.0) {
          trueCount++;
          tmp_data[idx] = static_cast<signed char>(i + 1);
          idx++;
        }
      }

      for (b_i = 0; b_i < trueCount; b_i++) {
        nonzero_h_data[b_i] = b_s[tmp_data[b_i] - 1];
      }

      for (i = 0; i < 21; i++) {
        x[i] = (b_s[i] != 0.0);
      }

      tooBig = (a.size(0) > 65500);
      if ((!tooBig) || (!(out_size_row[1] > 65500.0))) {
        tooBig = false;
      }

      if ((static_cast<double>(trueCount) / 21.0 > 0.05) && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      A.set_size(a.size(0), (static_cast<int>(out_size_row[1])));
      if (tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 1.0;
        padSizeT[1] = a.size(1);
        startT[1] = 21.0;
        ippfilter_real64(&a[0], &A[0], out_size_row, 2.0, padSizeT, b_s, startT,
                         false);
      } else {
        padSizeT[0] = a.size(0);
        connDimsT[0] = 1.0;
        startT[0] = 0.0;
        padSizeT[1] = a.size(1);
        connDimsT[1] = 21.0;
        startT[1] = 10.0;
        imfilter_real64(&a[0], &A[0], 2.0, out_size_row, 2.0, padSizeT,
                        &nonzero_h_data[0], static_cast<double>(trueCount), x,
                        2.0, connDimsT, startT, 2.0, true, false);
      }

      trueCount = 0;
      idx = 0;
      for (i = 0; i < 21; i++) {
        if (hcol[i] != 0.0) {
          trueCount++;
          b_tmp_data[idx] = static_cast<signed char>(i + 1);
          idx++;
        }
      }

      for (b_i = 0; b_i < trueCount; b_i++) {
        nonzero_h_data[b_i] = hcol[b_tmp_data[b_i] - 1];
      }

      for (i = 0; i < 21; i++) {
        x[i] = (hcol[i] != 0.0);
      }

      tooBig = (outSizeT[0] > 65500.0);
      if ((!tooBig) || (!(outSizeT[1] > 65500.0))) {
        tooBig = false;
      }

      if ((static_cast<double>(trueCount) / 21.0 > 0.05) && (!tooBig)) {
        tooBig = true;
      } else {
        tooBig = false;
      }

      a.set_size(A.size(0), A.size(1));
      idx = A.size(0) * A.size(1);
      for (b_i = 0; b_i < idx; b_i++) {
        a[b_i] = A[b_i];
      }

      A.set_size((static_cast<int>(outSizeT[0])), (static_cast<int>(outSizeT[1])));
      if (tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 21.0;
        padSizeT[1] = a.size(1);
        startT[1] = 1.0;
        ippfilter_real64(&a[0], &A[0], outSizeT, 2.0, padSizeT, hcol, startT,
                         false);
      } else {
        padSizeT[0] = a.size(0);
        connDimsT[0] = 21.0;
        startT[0] = 10.0;
        padSizeT[1] = a.size(1);
        connDimsT[1] = 1.0;
        startT[1] = 0.0;
        imfilter_real64(&a[0], &A[0], 2.0, outSizeT, 2.0, padSizeT,
                        &nonzero_h_data[0], static_cast<double>(trueCount), x,
                        2.0, connDimsT, startT, 2.0, true, false);
      }
    } else {
      boolean_T tooBig;
      padImage(A, startT, a);
      tooBig = (outSizeT[0] > 65500.0);
      if ((!tooBig) || (!(outSizeT[1] > 65500.0))) {
        tooBig = false;
      }

      A.set_size((static_cast<int>(outSizeT[0])), (static_cast<int>(outSizeT[1])));
      if (!tooBig) {
        padSizeT[0] = a.size(0);
        startT[0] = 21.0;
        padSizeT[1] = a.size(1);
        startT[1] = 21.0;
        ippfilter_real64(&a[0], &A[0], outSizeT, 2.0, padSizeT, h, startT, false);
      } else {
        padSizeT[0] = a.size(0);
        padSizeT[1] = a.size(1);
        for (b_i = 0; b_i < 441; b_i++) {
          conn[b_i] = true;
        }

        connDimsT[0] = 21.0;
        connDimsT[1] = 21.0;
        imfilter_real64(&a[0], &A[0], 2.0, outSizeT, 2.0, padSizeT,
                        nonZeroKernel, 441.0, conn, 2.0, connDimsT, startT, 2.0,
                        true, false);
      }
    }
  }
}

//
// Arguments    : const coder::array<double, 2U> *A
//                coder::array<double, 2U> *B
// Return Type  : void
//
void imgaussfilt(const coder::array<double, 2U> &A, coder::array<double, 2U> &B)
{
  int j;
  int h_tmp;
  int i;
  double sumH;
  static double h[6561];
  signed char Y[6561];
  double d;
  short tmp_data[6561];
  for (j = 0; j < 81; j++) {
    for (i = 0; i < 81; i++) {
      h_tmp = i + 81 * j;
      h[h_tmp] = ((static_cast<double>(j) + 1.0) - 1.0) + -40.0;
      Y[h_tmp] = static_cast<signed char>(i - 40);
    }
  }

  for (h_tmp = 0; h_tmp < 6561; h_tmp++) {
    h[h_tmp] = std::exp(-(h[h_tmp] * h[h_tmp] / 400.0 + static_cast<double>
                          (Y[h_tmp] * Y[h_tmp]) / 400.0) / 2.0);
  }

  sumH = h[0];
  for (h_tmp = 0; h_tmp < 6560; h_tmp++) {
    d = h[h_tmp + 1];
    if (sumH < d) {
      sumH = d;
    }
  }

  d = 2.2204460492503131E-16 * sumH;
  j = 0;
  h_tmp = 0;
  for (i = 0; i < 6561; i++) {
    boolean_T b;
    b = (h[i] < d);
    if (b) {
      j++;
      tmp_data[h_tmp] = static_cast<short>(i + 1);
      h_tmp++;
    }
  }

  for (i = 0; i < j; i++) {
    h[tmp_data[i] - 1] = 0.0;
  }

  sumH = h[0];
  for (h_tmp = 0; h_tmp < 6560; h_tmp++) {
    sumH += h[h_tmp + 1];
  }

  if (sumH != 0.0) {
    for (i = 0; i < 6561; i++) {
      h[i] /= sumH;
    }
  }

  B.set_size(A.size(0), A.size(1));
  h_tmp = A.size(0) * A.size(1);
  for (i = 0; i < h_tmp; i++) {
    B[i] = A[i];
  }

  imfilter(B, h);
}

//
// File trailer for imgaussfilt.cpp
//
// [EOF]
//
