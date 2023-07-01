/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FFT.cpp
 *
 * Code generation for function 'FFT'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "FFT.h"
#include "FFT_emxutil.h"
#include "fft2.h"


/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

void FFT(const emxArray_real_T *datain, double N, emxArray_real_T *out)
{
  emxArray_real_T *y_f;
  emxArray_creal_T *b_y1;
  int b_datain[1];
  emxArray_real_T c_datain;
  unsigned int unnamed_idx_1;
  int k;
  int exitg1;
  int b_unnamed_idx_1;
  double y;
  double x_im;
  emxInit_real_T(&y_f, 2);
  emxInit_creal_T(&b_y1, 1);
  b_datain[0] = datain->size[1];
  c_datain = *datain;
  c_datain.size = (int *)&b_datain;
  c_datain.numDimensions = 1;

  fft(&c_datain, datain->size[1], b_y1);

  unnamed_idx_1 = (unsigned int)datain->size[1];
  k = y_f->size[0] * y_f->size[1];
  y_f->size[0] = 1;
  y_f->size[1] = (int)unnamed_idx_1;
  emxEnsureCapacity_real_T(y_f, k);
  k = 0;

  do {
    exitg1 = 0;
    b_unnamed_idx_1 = datain->size[1];
    if (k + 1 <= b_unnamed_idx_1) {
      y = b_y1->data[k].re;
      x_im = b_y1->data[k].im;
      y_f->data[k] = rt_hypotd_snf(y, x_im);
      k++;
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  emxFree_creal_T(&b_y1);
  y = N / 2.0;
  k = y_f->size[0] * y_f->size[1];
  y_f->size[0] = 1;
  emxEnsureCapacity_real_T(y_f, k);
  k = y_f->size[0];
  b_unnamed_idx_1 = y_f->size[1];
  b_unnamed_idx_1 *= k;
  for (k = 0; k < b_unnamed_idx_1; k++) {
    y_f->data[k] /= y;
  }

  y_f->data[0] /= 2.0;
  y = N / 2.0;
  if (1.0 > y) {
    b_unnamed_idx_1 = 0;
  } else {
    b_unnamed_idx_1 = (int)y;
  }

  k = out->size[0] * out->size[1];
  out->size[0] = 1;
  out->size[1] = b_unnamed_idx_1;
  // we find following line cause some error ,due to out.numDimensions is too large
  //emxEnsureCapacity_real_T(out, k);

  for (k = 0; k < b_unnamed_idx_1; k++) {
    out->data[out->size[0] * k] = y_f->data[k];
  }

  emxFree_real_T(&y_f);
}

/* End of code generation (FFT.cpp) */
