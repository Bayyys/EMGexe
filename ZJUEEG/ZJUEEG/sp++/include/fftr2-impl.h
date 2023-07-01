/*****************************************************************************
 *                               fftr2-impl.h
 *
 * Implementation for FFTR2 class.
 *
 * Zhang Ming, 2010-04, Xi'an Jiaotong University.
 *****************************************************************************/


/**
 * constructors and destructor
 */
template<typename Type>
FFTR2<Type>::FFTR2()
{
}

template<typename Type>
FFTR2<Type>::~FFTR2()
{
}


/**
 * Generate the bit reversed array.
 */
template<typename Type>
void FFTR2<Type>::bitReverse( Vector<int> &bitrev )
{
    int i, j;
	bitrev[0] = 0;

	for( j=1; j<bitrev.size(); j<<=1 )
		for( i=0; i<j; ++i )
		{
			bitrev[i] <<= 1;
			bitrev[i+j] = bitrev[i]+1;
		}
}


/**
 * Radix-2 iteration subroutine.
 */
template<typename Type>
void FFTR2<Type>::radix2( int nthpo, Complex<Type> *c0, Complex<Type> *c1 )
{
    int     k, kk;
    Type    *cr0, *ci0, *cr1, *ci1, r1, fi1;

    cr0 = &(c0[0].re);
    ci0 = &(c0[0].im);
    cr1 = &(c1[0].re);
    ci1 = &(c1[0].im);

    for( k=0; k<nthpo; k+=2 )
    {
        kk = k*2;

        r1 = cr0[kk] + cr1[kk];
        cr1[kk] = cr0[kk] - cr1[kk];
        cr0[kk] = r1;
        fi1 = ci0[kk] + ci1[kk];
        ci1[kk] = ci0[kk] - ci1[kk];
        ci0[kk] = fi1;
    }
}


/**
 * Radix-4 iteration subroutine.
 */
template<typename Type>
void FFTR2<Type>::radix4( int nthpo, Complex<Type> *c0, Complex<Type> *c1,
                          Complex<Type> *c2, Complex<Type> *c3 )
{
    int     k, kk;
    Type    *cr0, *ci0, *cr1, *ci1, *cr2, *ci2, *cr3, *ci3;
    Type    r1, r2, r3, r4, i1, i2, i3, i4;

    cr0 = &(c0[0].re);
    cr1 = &(c1[0].re);
    cr2 = &(c2[0].re);
    cr3 = &(c3[0].re);
    ci0 = &(c0[0].im);
    ci1 = &(c1[0].im);
    ci2 = &(c2[0].im);
    ci3 = &(c3[0].im);

    for( k=1; k<=nthpo; k+=4 )
    {
        kk = (k-1)*2;

        r1 = cr0[kk] + cr2[kk];
        r2 = cr0[kk] - cr2[kk];
        r3 = cr1[kk] + cr3[kk];
        r4 = cr1[kk] - cr3[kk];
        i1 = ci0[kk] + ci2[kk];
        i2 = ci0[kk] - ci2[kk];
        i3 = ci1[kk] + ci3[kk];
        i4 = ci1[kk] - ci3[kk];
        cr0[kk] = r1 + r3;
        ci0[kk] = i1 + i3;
        cr1[kk] = r1 - r3;
        ci1[kk] = i1 - i3;
        cr2[kk] = r2 - i4;
        ci2[kk] = i2 + r4;
        cr3[kk] = r2 + i4;
        ci3[kk] = i2 - r4;
    }
}


/**
 * Radix-8 iteration subroutine.
 */
template<typename Type>
void FFTR2<Type>::radix8( int nxtlt, int nthpo, int length,
                          Complex<Type> *cc0, Complex<Type> *cc1, Complex<Type> *cc2, Complex<Type> *cc3,
                          Complex<Type> *cc4, Complex<Type> *cc5, Complex<Type> *cc6, Complex<Type> *cc7 )
{
    int     j, k, kk;
    Type    scale, arg, tr, ti;

    Type    c1, c2, c3, c4, c5, c6, c7,
            s1, s2, s3, s4, s5, s6, s7;
    Type    ar0, ar1, ar2, ar3, ar4, ar5, ar6, ar7,
            ai0, ai1, ai2, ai3, ai4, ai5, ai6, ai7;
    Type    br0, br1, br2, br3, br4, br5, br6, br7,
            bi0, bi1, bi2, bi3, bi4, bi5, bi6, bi7;

    Type    *cr0, *cr1, *cr2, *cr3, *cr4, *cr5, *cr6, *cr7;
    Type    *ci0, *ci1, *ci2, *ci3, *ci4, *ci5, *ci6, *ci7;

    cr0 = &(cc0[0].re);
    cr1 = &(cc1[0].re);
    cr2 = &(cc2[0].re);
    cr3 = &(cc3[0].re);
    cr4 = &(cc4[0].re);
    cr5 = &(cc5[0].re);
    cr6 = &(cc6[0].re);
    cr7 = &(cc7[0].re);

    ci0 = &(cc0[0].im);
    ci1 = &(cc1[0].im);
    ci2 = &(cc2[0].im);
    ci3 = &(cc3[0].im);
    ci4 = &(cc4[0].im);
    ci5 = &(cc5[0].im);
    ci6 = &(cc6[0].im);
    ci7 = &(cc7[0].im);

    scale = TWOPI / length;

    for( j=1; j<=nxtlt; j++ )
    {
        arg = (j-1)*scale;
        c1 = cos(arg);
        s1 = sin(arg);
        c2 = c1*c1 - s1*s1;
        s2 = c1*s1 + c1*s1;
        c3 = c1*c2 - s1*s2;
        s3 = c2*s1 + s2*c1;
        c4 = c2*c2 - s2*s2;
        s4 = c2*s2 + c2*s2;
        c5 = c2*c3 - s2*s3;
        s5 = c3*s2 + s3*c2;
        c6 = c3*c3 - s3*s3;
        s6 = c3*s3 + c3*s3;
        c7 = c3*c4 - s3*s4;
        s7 = c4*s3 + s4*c3;

        for( k=j; k<=nthpo; k+=length )
      	{
            kk = (k-1)*2; /* index by twos; re & im alternate */

            ar0 = cr0[kk] + cr4[kk];
            ar1 = cr1[kk] + cr5[kk];
            ar2 = cr2[kk] + cr6[kk];
            ar3 = cr3[kk] + cr7[kk];
            ar4 = cr0[kk] - cr4[kk];
            ar5 = cr1[kk] - cr5[kk];
            ar6 = cr2[kk] - cr6[kk];
            ar7 = cr3[kk] - cr7[kk];
            ai0 = ci0[kk] + ci4[kk];
            ai1 = ci1[kk] + ci5[kk];
            ai2 = ci2[kk] + ci6[kk];
            ai3 = ci3[kk] + ci7[kk];
            ai4 = ci0[kk] - ci4[kk];
            ai5 = ci1[kk] - ci5[kk];
            ai6 = ci2[kk] - ci6[kk];
            ai7 = ci3[kk] - ci7[kk];
            br0 = ar0 + ar2;
            br1 = ar1 + ar3;
            br2 = ar0 - ar2;
            br3 = ar1 - ar3;
            br4 = ar4 - ai6;
            br5 = ar5 - ai7;
            br6 = ar4 + ai6;
            br7 = ar5 + ai7;
            bi0 = ai0 + ai2;
            bi1 = ai1 + ai3;
            bi2 = ai0 - ai2;
            bi3 = ai1 - ai3;
            bi4 = ai4 + ar6;
            bi5 = ai5 + ar7;
            bi6 = ai4 - ar6;
            bi7 = ai5 - ar7;
            cr0[kk] = br0 + br1;
            ci0[kk] = bi0 + bi1;

            if( j > 1 )
      	    {
                cr1[kk] = c4*(br0-br1) - s4*(bi0-bi1);
                cr2[kk] = c2*(br2-bi3) - s2*(bi2+br3);
                cr3[kk] = c6*(br2+bi3) - s6*(bi2-br3);
                ci1[kk] = c4*(bi0-bi1) + s4*(br0-br1);
                ci2[kk] = c2*(bi2+br3) + s2*(br2-bi3);
                ci3[kk] = c6*(bi2-br3) + s6*(br2+bi3);
                tr = IRT2*(br5-bi5);
                ti = IRT2*(br5+bi5);
                cr4[kk] = c1*(br4+tr) - s1*(bi4+ti);
                ci4[kk] = c1*(bi4+ti) + s1*(br4+tr);
                cr5[kk] = c5*(br4-tr) - s5*(bi4-ti);
                ci5[kk] = c5*(bi4-ti) + s5*(br4-tr);
                tr = -IRT2*(br7+bi7);
                ti = IRT2*(br7-bi7);
                cr6[kk] = c3*(br6+tr) - s3*(bi6+ti);
                ci6[kk] = c3*(bi6+ti) + s3*(br6+tr);
                cr7[kk] = c7*(br6-tr) - s7*(bi6-ti);
                ci7[kk] = c7*(bi6-ti) + s7*(br6-tr);
      	    }
            else
      	    {
                cr1[kk] = br0 - br1;
                cr2[kk] = br2 - bi3;
                cr3[kk] = br2 + bi3;
                ci1[kk] = bi0 - bi1;
                ci2[kk] = bi2 + br3;
                ci3[kk] = bi2 - br3;
                tr = IRT2*(br5-bi5);
                ti = IRT2*(br5+bi5);
                cr4[kk] = br4 + tr;
                ci4[kk] = bi4 + ti;
                cr5[kk] = br4 - tr;
                ci5[kk] = bi4 - ti;
                tr = -IRT2*(br7+bi7);
                ti = IRT2*(br7-bi7);
                cr6[kk] = br6 + tr;
                ci6[kk] = bi6 + ti;
                cr7[kk] = br6 - tr;
                ci7[kk] = bi6 - ti;
      	    }
      	}
    }
}


/**
 * This routine replaces the input Complex<Type> vector by its
 * finite discrete Fourier transform if direction == FORWARD.
 * It replaces the input Complex<Type> vector by its finite discrete
 * inverse Fourier transform if direction == INVERSE.
 */
template<typename Type>
void FFTR2<Type>::dft( int direction, int n, Complex<Type> *b )
{
    int     i, j;
    int     n2pow, n8pow, nthpo, ipass, nxtlt, length;
    Complex<Type> tmp;

    n2pow = fastLog2(n);
    nthpo = n;

    // Conjugate the input
    if( direction == FORWARD )
        for( i=0; i<n; i++ )
            b[i].im = -b[i].im;

    n8pow = n2pow/3;
    if( n8pow )
    {
        // radix 8 iterations
        for( ipass=1; ipass<=n8pow; ipass++ )
      	{
            nxtlt = 0x1 << ( n2pow - 3*ipass );
            length = 8*nxtlt;
            radix8( nxtlt, nthpo, length,
                    b, b+nxtlt, b+2*nxtlt, b+3*nxtlt,
                    b+4*nxtlt, b+5*nxtlt, b+6*nxtlt, b+7*nxtlt );
      	}
    }

    // A final radix 2 or radix 4 iteration is needed.
    if( n2pow%3 == 1 )
    	radix2( nthpo, b, b+1 );
    if( n2pow%3 == 2 )
        radix4( nthpo, b, b+1, b+2, b+3 );

     // scale outputs
    if( direction == FORWARD )
        for( i=0; i<n; i++ )
            b[i].im *= -1;

    if( direction == INVERSE )
    {
        for( i=0; i<nthpo; i++ )
        {
            b[i].re /= n;
            b[i].im /= n;
        }
    }

    // bit reverse
    Vector<int> bitrev(n);
    bitReverse( bitrev );
	for( i=0; i<n; ++i )
	{
		j = bitrev[i];
		if( i < j )
		{
            tmp = b[i];
            b[i] = b[j];
            b[j] = tmp;
		}
	}
}


/**
 * Forward Transform
 */
template<typename Type>
void FFTR2<Type>::fft( Vector<complex<Type> > &xn )
{
    int nFFT = xn.size();
    if( isPower2(nFFT)  )
        dft( FORWARD, nFFT, reinterpret_cast<Complex<Type>*>(xn.begin()) );
    else
        cerr << "The length of signal must abe power of 2!" ;
}

template<typename Type>
void FFTR2<Type>::fft( Vector<Type> &xn, Vector< complex<Type> > &Xk )
{
    int nFFT = xn.size();
    if( isPower2(nFFT)  )
    {
        Xk.resize(nFFT);
        for( int i=0; i<nFFT; i++ )
            Xk[i] = xn[i];

        dft( FORWARD, nFFT, reinterpret_cast<Complex<Type>*>(Xk.begin()) );
    }
    else
        cerr << "The length of signal must abe power of 2!" ;
}


/**
 * Inverse Transform
 */
template<typename Type>
void FFTR2<Type>::ifft( Vector<complex<Type> > &Xk )
{
    int nFFT = Xk.size();
    if( isPower2(nFFT)  )
        dft( INVERSE, nFFT, reinterpret_cast<Complex<Type>*>(Xk.begin()) );
    else
        cerr << "The length of signal must abe power of 2!" ;
}

template<typename Type>
void FFTR2<Type>::ifft( Vector< complex<Type> > &Xk, Vector<Type> &xn )
{
    int nFFT = Xk.size();
    if( isPower2(nFFT)  )
    {
        dft( INVERSE, nFFT, reinterpret_cast<Complex<Type>*>(Xk.begin()) );

        xn.resize(nFFT);
        for( int i=0; i<nFFT; i++ )
            xn[i] = Xk[i].real();
    }
    else
        cerr << "The length of signal must abe power of 2!" ;
}
