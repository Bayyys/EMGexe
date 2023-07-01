/*****************************************************************************
 *                                  fastconv.h
 *
 * Compute linear convolution by using FFT, which is very efficiently for
 * large scale vectors.
 *
 * And also, we can use FFT computing the auto-corelation and cross-corelation
 * functions based on fallowing facts:
 * for real functions,
 * R1[x(t),y(t)] = sum{ x(u)*y(u+t) } = Conv[x(-t),y(t)]
 * R2[x(t),y(t)] = sum{ x(u)*y(u-t) } = Conv[x(t),y(-t)]
 *
 * Zhang Ming, 2010-01, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef FASTCONV_H
#define FASTCONV_H


#include <complex>
#include "vector.h"
#include "fft.h"
#include "utilities.h"


namespace itlab
{

    template<typename Type> Vector<Type> fastConv( const Vector<Type>&, const Vector<Type>& );

    template<typename Type> Vector<Type> fastAcor( Vector<Type>& );
    template<typename Type> Vector<Type> fastCcor( Vector<Type>&, Vector<Type>& );


    #include "fastconv-impl.h"

}
// namespace itlab


#endif
// FASTCONV_H
