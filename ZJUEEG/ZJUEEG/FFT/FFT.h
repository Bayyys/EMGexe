/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * FFT.h
 *
 * Code generation for function 'FFT'
 *
 */

#ifndef FFT_H
#define FFT_H

/* Include files */
#include <cmath>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "FFT_types.h"

/* Function Declarations */
extern void FFT(const emxArray_real_T *datain, double N, emxArray_real_T *out);

#endif

/* End of code generation (FFT.h) */
