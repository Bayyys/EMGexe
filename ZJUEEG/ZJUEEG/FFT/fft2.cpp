/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fft2.cpp
 *
 * Code generation for function 'fft2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "FFT.h"
#include "fft2.h"
#include "FFT_emxutil.h"

/* Function Declarations */
static void dobluesteinfft(const emxArray_real_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y);
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y);

/* Function Definitions */
static void dobluesteinfft(const emxArray_real_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int nInt2m1;
  int nInt2;
  int idx;
  int rt;
  int j;
  int ihi;
  double twid_im;
  double r;
  emxArray_creal_T *fy;
  int nRowsD2;
  int nRowsD4;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  emxArray_creal_T *fv;
  double fv_re;
  double fv_im;
  double wwc_im;
  double b_fv_re;
  emxInit_creal_T(&wwc, 1);
  nInt2m1 = (n1 + n1) - 1;
  nInt2 = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, nInt2);
  idx = n1;
  rt = 0;
  wwc->data[n1 - 1].re = 1.0;
  wwc->data[n1 - 1].im = 0.0;
  nInt2 = n1 << 1;
  for (j = 1; j < n1; j++) {
    ihi = (j << 1) - 1;
    if (nInt2 - rt <= ihi) {
      rt += ihi - nInt2;
    } else {
      rt += ihi;
    }

    twid_im = -3.1415926535897931 * (double)rt / (double)n1;
    if (twid_im == 0.0) {
      r = 1.0;
      twid_im = 0.0;
    } else {
      r = std::cos(twid_im);
      twid_im = std::sin(twid_im);
    }

    wwc->data[idx - 2].re = r;
    wwc->data[idx - 2].im = -twid_im;
    idx--;
  }

  idx = 0;
  for (j = nInt2m1 - 1; j >= n1; j--) {
    wwc->data[j] = wwc->data[idx];
    idx++;
  }

  rt = x->size[0];
  if (n1 < rt) {
    rt = n1;
  }

  nInt2 = y->size[0];
  y->size[0] = n1;
  emxEnsureCapacity_creal_T(y, nInt2);
  if (n1 > x->size[0]) {
    ihi = y->size[0];
    nInt2 = y->size[0];
    y->size[0] = ihi;
    emxEnsureCapacity_creal_T(y, nInt2);
    for (nInt2 = 0; nInt2 < ihi; nInt2++) {
      y->data[nInt2].re = 0.0;
      y->data[nInt2].im = 0.0;
    }
  }

  idx = 0;
  for (j = 0; j + 1 <= rt; j++) {
    r = wwc->data[(n1 + j) - 1].re;
    twid_im = wwc->data[(n1 + j) - 1].im;
    y->data[j].re = r * x->data[idx];
    y->data[j].im = twid_im * -x->data[idx];
    idx++;
  }

  while (rt + 1 <= n1) {
    y->data[rt].re = 0.0;
    y->data[rt].im = 0.0;
    rt++;
  }

  nInt2m1 = y->size[0];
  if (!(nInt2m1 < N2)) {
    nInt2m1 = N2;
  }

  emxInit_creal_T(&fy, 1);
  nRowsD2 = N2 / 2;
  nRowsD4 = nRowsD2 / 2;
  nInt2 = fy->size[0];
  fy->size[0] = N2;
  emxEnsureCapacity_creal_T(fy, nInt2);
  if (N2 > y->size[0]) {
    idx = fy->size[0];
    nInt2 = fy->size[0];
    fy->size[0] = idx;
    emxEnsureCapacity_creal_T(fy, nInt2);
    for (nInt2 = 0; nInt2 < idx; nInt2++) {
      fy->data[nInt2].re = 0.0;
      fy->data[nInt2].im = 0.0;
    }
  }

  rt = 0;
  nInt2 = 0;
  idx = 0;
  for (i = 1; i < nInt2m1; i++) {
    fy->data[idx] = y->data[rt];
    idx = N2;
    tst = true;
    while (tst) {
      idx >>= 1;
      nInt2 ^= idx;
      tst = ((nInt2 & idx) == 0);
    }

    idx = nInt2;
    rt++;
  }

  fy->data[idx] = y->data[rt];
  if (N2 > 1) {
    for (i = 0; i <= N2 - 2; i += 2) {
      temp_re = fy->data[i + 1].re;
      temp_im = fy->data[i + 1].im;
      fy->data[i + 1].re = fy->data[i].re - fy->data[i + 1].re;
      fy->data[i + 1].im = fy->data[i].im - fy->data[i + 1].im;
      fy->data[i].re += temp_re;
      fy->data[i].im += temp_im;
    }
  }

  idx = 2;
  rt = 4;
  nInt2 = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < nInt2; i += rt) {
      temp_re = fy->data[i + idx].re;
      temp_im = fy->data[i + idx].im;
      fy->data[i + idx].re = fy->data[i].re - temp_re;
      fy->data[i + idx].im = fy->data[i].im - temp_im;
      fy->data[i].re += temp_re;
      fy->data[i].im += temp_im;
    }

    nInt2m1 = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      r = costab->data[j];
      twid_im = sintab->data[j];
      i = nInt2m1;
      ihi = nInt2m1 + nInt2;
      while (i < ihi) {
        temp_re = r * fy->data[i + idx].re - twid_im * fy->data[i + idx].im;
        temp_im = r * fy->data[i + idx].im + twid_im * fy->data[i + idx].re;
        fy->data[i + idx].re = fy->data[i].re - temp_re;
        fy->data[i + idx].im = fy->data[i].im - temp_im;
        fy->data[i].re += temp_re;
        fy->data[i].im += temp_im;
        i += rt;
      }

      nInt2m1++;
    }

    nRowsD4 /= 2;
    idx = rt;
    rt += rt;
    nInt2 -= idx;
  }

  emxInit_creal_T(&fv, 1);
  r2br_r2dit_trig_impl(wwc, N2, costab, sintab, fv);
  nInt2 = fy->size[0];
  emxEnsureCapacity_creal_T(fy, nInt2);
  idx = fy->size[0];
  for (nInt2 = 0; nInt2 < idx; nInt2++) {
    r = fy->data[nInt2].re;
    twid_im = fy->data[nInt2].im;
    fv_re = fv->data[nInt2].re;
    fv_im = fv->data[nInt2].im;
    fy->data[nInt2].re = r * fv_re - twid_im * fv_im;
    fy->data[nInt2].im = r * fv_im + twid_im * fv_re;
  }

  r2br_r2dit_trig_impl(fy, N2, costab, sintabinv, fv);
  emxFree_creal_T(&fy);
  if (fv->size[0] > 1) {
    r = 1.0 / (double)fv->size[0];
    nInt2 = fv->size[0];
    emxEnsureCapacity_creal_T(fv, nInt2);
    idx = fv->size[0];
    for (nInt2 = 0; nInt2 < idx; nInt2++) {
      fv->data[nInt2].re *= r;
      fv->data[nInt2].im *= r;
    }
  }

  idx = 0;
  for (j = n1 - 1; j + 1 <= wwc->size[0]; j++) {
    r = wwc->data[j].re;
    fv_re = fv->data[j].re;
    twid_im = wwc->data[j].im;
    fv_im = fv->data[j].im;
    temp_re = wwc->data[j].re;
    temp_im = fv->data[j].im;
    wwc_im = wwc->data[j].im;
    b_fv_re = fv->data[j].re;
    y->data[idx].re = r * fv_re + twid_im * fv_im;
    y->data[idx].im = temp_re * temp_im - wwc_im * b_fv_re;
    idx++;
  }

  emxFree_creal_T(&fv);
  emxFree_creal_T(&wwc);
}

static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y)
{
  int j;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int iDelta;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int ihi;
  j = x->size[0];
  if (!(j < unsigned_nRows)) {
    j = unsigned_nRows;
  }

  nRowsD2 = unsigned_nRows / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  if (unsigned_nRows > x->size[0]) {
    iDelta = y->size[0];
    iy = y->size[0];
    y->size[0] = iDelta;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < iDelta; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 1; i < j; i++) {
    y->data[iy] = x->data[ix];
    iDelta = unsigned_nRows;
    tst = true;
    while (tst) {
      iDelta >>= 1;
      ju ^= iDelta;
      tst = ((ju & iDelta) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= unsigned_nRows - 2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }
  }

  iDelta = 2;
  iy = 4;
  ix = 1 + ((nRowsD4 - 1) << 2);
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iy) {
      temp_re = y->data[i + iDelta].re;
      temp_im = y->data[i + iDelta].im;
      y->data[i + iDelta].re = y->data[i].re - temp_re;
      y->data[i + iDelta].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      ihi = ju + ix;
      while (i < ihi) {
        temp_re = twid_re * y->data[i + iDelta].re - twid_im * y->data[i +
          iDelta].im;
        temp_im = twid_re * y->data[i + iDelta].im + twid_im * y->data[i +
          iDelta].re;
        y->data[i + iDelta].re = y->data[i].re - temp_re;
        y->data[i + iDelta].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iy;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iDelta = iy;
    iy += iy;
    ix -= iDelta;
  }
}

void fft(const emxArray_real_T *x, int n, emxArray_creal_T *y)
{
  emxArray_real_T *costab1q;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T useRadix2;
  int pmax;
  int pmin;
  int nn1m1;
  double e;
  int nRowsD4;
  boolean_T exitg1;
  int b_n;
  int pow2p;
  int nRowsD2;
  int i;
  double temp_re;
  double temp_im;
  double twid_im;
  int ihi;
  emxInit_real_T(&costab1q, 2);
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  if ((x->size[0] == 0) || (n == 0)) {
    pmax = y->size[0];
    y->size[0] = n;
    emxEnsureCapacity_creal_T(y, pmax);
    if (n > x->size[0]) {
      nn1m1 = y->size[0];
      pmax = y->size[0];
      y->size[0] = nn1m1;
      emxEnsureCapacity_creal_T(y, pmax);
      for (pmax = 0; pmax < nn1m1; pmax++) {
        y->data[pmax].re = 0.0;
        y->data[pmax].im = 0.0;
      }
    }
  } else {
    useRadix2 = ((n & (n - 1)) == 0);
    pmin = 1;
    if (useRadix2) {
      nn1m1 = n;
    } else {
      nn1m1 = (n + n) - 1;
      pmax = 31;
      if (nn1m1 <= 1) {
        pmax = 0;
      } else {
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          b_n = (pmin + pmax) >> 1;
          pow2p = 1 << b_n;
          if (pow2p == nn1m1) {
            pmax = b_n;
            exitg1 = true;
          } else if (pow2p > nn1m1) {
            pmax = b_n;
          } else {
            pmin = b_n;
          }
        }
      }

      pmin = 1 << pmax;
      nn1m1 = pmin;
    }

    e = 6.2831853071795862 / (double)nn1m1;
    nRowsD4 = nn1m1 / 2 / 2;
    pmax = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = nRowsD4 + 1;
    emxEnsureCapacity_real_T(costab1q, pmax);
    costab1q->data[0] = 1.0;
    nn1m1 = nRowsD4 / 2;
    for (pmax = 1; pmax <= nn1m1; pmax++) {
      costab1q->data[pmax] = std::cos(e * (double)pmax);
    }

    for (pmax = nn1m1 + 1; pmax < nRowsD4; pmax++) {
      costab1q->data[pmax] = std::sin(e * (double)(nRowsD4 - pmax));
    }

    costab1q->data[nRowsD4] = 0.0;
    if (!useRadix2) {
      b_n = costab1q->size[1] - 1;
      nn1m1 = (costab1q->size[1] - 1) << 1;
      pmax = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = nn1m1 + 1;
      emxEnsureCapacity_real_T(costab, pmax);
      pmax = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = nn1m1 + 1;
      emxEnsureCapacity_real_T(sintab, pmax);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      pmax = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = nn1m1 + 1;
      emxEnsureCapacity_real_T(sintabinv, pmax);
      for (pmax = 1; pmax <= b_n; pmax++) {
        sintabinv->data[pmax] = costab1q->data[b_n - pmax];
      }

      for (pmax = costab1q->size[1]; pmax <= nn1m1; pmax++) {
        sintabinv->data[pmax] = costab1q->data[pmax - b_n];
      }

      for (pmax = 1; pmax <= b_n; pmax++) {
        costab->data[pmax] = costab1q->data[pmax];
        sintab->data[pmax] = -costab1q->data[b_n - pmax];
      }

      for (pmax = costab1q->size[1]; pmax <= nn1m1; pmax++) {
        costab->data[pmax] = -costab1q->data[nn1m1 - pmax];
        sintab->data[pmax] = -costab1q->data[pmax - b_n];
      }
    } else {
      b_n = costab1q->size[1] - 1;
      nn1m1 = (costab1q->size[1] - 1) << 1;
      pmax = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = nn1m1 + 1;
      emxEnsureCapacity_real_T(costab, pmax);
      pmax = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = nn1m1 + 1;
      emxEnsureCapacity_real_T(sintab, pmax);
      costab->data[0] = 1.0;
      sintab->data[0] = 0.0;
      for (pmax = 1; pmax <= b_n; pmax++) {
        costab->data[pmax] = costab1q->data[pmax];
        sintab->data[pmax] = -costab1q->data[b_n - pmax];
      }

      for (pmax = costab1q->size[1]; pmax <= nn1m1; pmax++) {
        costab->data[pmax] = -costab1q->data[nn1m1 - pmax];
        sintab->data[pmax] = -costab1q->data[pmax - b_n];
      }

      pmax = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = 0;
      emxEnsureCapacity_real_T(sintabinv, pmax);
    }

    if (useRadix2) {
      pow2p = x->size[0];
      if (!(pow2p < n)) {
        pow2p = n;
      }

      nRowsD2 = n / 2;
      nRowsD4 = nRowsD2 / 2;
      pmax = y->size[0];
      y->size[0] = n;
      emxEnsureCapacity_creal_T(y, pmax);
      if (n > x->size[0]) {
        nn1m1 = y->size[0];
        pmax = y->size[0];
        y->size[0] = nn1m1;
        emxEnsureCapacity_creal_T(y, pmax);
        for (pmax = 0; pmax < nn1m1; pmax++) {
          y->data[pmax].re = 0.0;
          y->data[pmax].im = 0.0;
        }
      }

      pmax = 0;
      pmin = 0;
      nn1m1 = 0;
      for (i = 1; i < pow2p; i++) {
        y->data[nn1m1].re = x->data[pmax];
        y->data[nn1m1].im = 0.0;
        b_n = n;
        useRadix2 = true;
        while (useRadix2) {
          b_n >>= 1;
          pmin ^= b_n;
          useRadix2 = ((pmin & b_n) == 0);
        }

        nn1m1 = pmin;
        pmax++;
      }

      y->data[nn1m1].re = x->data[pmax];
      y->data[nn1m1].im = 0.0;
      if (n > 1) {
        for (i = 0; i <= n - 2; i += 2) {
          temp_re = y->data[i + 1].re;
          temp_im = y->data[i + 1].im;
          y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
          y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
        }
      }

      nn1m1 = 2;
      pmax = 4;
      pmin = 1 + ((nRowsD4 - 1) << 2);
      while (nRowsD4 > 0) {
        for (i = 0; i < pmin; i += pmax) {
          temp_re = y->data[i + nn1m1].re;
          temp_im = y->data[i + nn1m1].im;
          y->data[i + nn1m1].re = y->data[i].re - temp_re;
          y->data[i + nn1m1].im = y->data[i].im - temp_im;
          y->data[i].re += temp_re;
          y->data[i].im += temp_im;
        }

        b_n = 1;
        for (pow2p = nRowsD4; pow2p < nRowsD2; pow2p += nRowsD4) {
          e = costab->data[pow2p];
          twid_im = sintab->data[pow2p];
          i = b_n;
          ihi = b_n + pmin;
          while (i < ihi) {
            temp_re = e * y->data[i + nn1m1].re - twid_im * y->data[i + nn1m1].
              im;
            temp_im = e * y->data[i + nn1m1].im + twid_im * y->data[i + nn1m1].
              re;
            y->data[i + nn1m1].re = y->data[i].re - temp_re;
            y->data[i + nn1m1].im = y->data[i].im - temp_im;
            y->data[i].re += temp_re;
            y->data[i].im += temp_im;
            i += pmax;
          }

          b_n++;
        }

        nRowsD4 /= 2;
        nn1m1 = pmax;
        pmax += pmax;
        pmin -= nn1m1;
      }
    } else {
      dobluesteinfft(x, pmin, n, costab, sintab, sintabinv, y);
    }
  }

  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
  emxFree_real_T(&costab1q);
}

/* End of code generation (fft2.cpp) */
