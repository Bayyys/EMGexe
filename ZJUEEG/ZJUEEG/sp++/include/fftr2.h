/*****************************************************************************
 *                                fftr2.h
 *
 * Fast Fourier Transform with Radix 2 Algorithm
 *
 * This class is designed for calculating discrete Fourier transform and
 * inverse discrete Fourier transform of 1D signals by using Split-Radix
 * Algorithms. The length of signals should equal to powers of 2.
 *
 * The algorithm is modified from "kube-gustavson-fft.c". Which is a pretty
 * fast FFT algorithm. Not super-optimized lightning-fast, but very good
 * considering its age and relative simplicity.
 *
 * Zhang Ming, 2010-04, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef FFTR2_H
#define FFTR2_H


#include <complex>
#include "vector.h"
#include "utilities.h"


namespace itlab
{

    /**
     * complex node converted from "C" version for this algorithm
     */
    template<typename Type>
    struct Complex
    {
        Type re;
        Type im;
    };


    /**
     * Radix based FFT class
     */
	template<typename Type>
	class FFTR2
	{

	public:

		FFTR2();
		~FFTR2();

        void fft( Vector< complex<Type> > &xn );
		void fft( Vector<Type> &xn, Vector< complex<Type> > &Xk );
        void ifft( Vector< complex<Type> > &Xk );
        void ifft( Vector< complex<Type> > &Xk, Vector<Type> &xn );

	private:

        void bitReverse( Vector<int> &bitrev );
		void radix2( int nthpo, Complex<Type> *c0, Complex<Type> *c1 );
		void radix4( int nthpo, Complex<Type> *c0, Complex<Type> *c1,
                           Complex<Type> *c2, Complex<Type> *c3 );
		void radix8( int nxtlt, int nthpo, int length,
                     Complex<Type> *cc0, Complex<Type> *cc1, Complex<Type> *cc2, Complex<Type> *cc3,
                     Complex<Type> *cc4, Complex<Type> *cc5, Complex<Type> *cc6, Complex<Type> *cc7 );
		void dft( int direction, int n, Complex<Type> *b );
	};
	//	class FFTR2


    #include "fftr2-impl.h"

}
// namespace itlab


#endif
// FFTR2_H
