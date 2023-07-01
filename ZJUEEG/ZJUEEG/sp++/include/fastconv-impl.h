/*****************************************************************************
 *                              fastconv-impl.h
 *
 * Implementation for linear convolution by using FFT.
 *
 * Zhang Ming, 2010-01, Xi'an Jiaotong University.
 *****************************************************************************/


/**
 * Fast convolution by FFT.
 */
template<typename Type>
Vector<Type> fastConv( const Vector<Type> &xn, const Vector<Type> &yn )
{
    int M = xn.dim(),
        N = yn.dim(),
        L = M + N - 1;

    Vector<Type> zn(L),
                 xnPadded = wextend( xn, N-1, "right", "zpd" ),
                 ynPadded = wextend( yn, M-1, "right", "zpd" );

    Vector< complex<Type> > Xk( L/2+1 ),
                            Yk( L/2+1 ),
                            Zk( L/2+1 );
    fft( xnPadded, Xk );
    fft( ynPadded, Yk );
    Zk = Xk * Yk;
    ifft( Zk, zn );

    return zn;
}


/**
 * Fast auto-correlation by FFT.
 */
template<typename Type>
inline Vector<Type> fastAcor( Vector<Type> &xn )
{
    return fastConv( reverse(xn), xn );
}


/**
 * Fast cross-correlation by FFT.
 */
template<typename Type>
inline Vector<Type> fastCcor( Vector<Type> &xn, Vector<Type> &yn )
{
    return fastConv( reverse(xn), yn );
}


//    void fastConv( const Vector<double> &xn, const Vector<double> &yn,
//                   Vector<double> &zn )
//    {
//        int M = xn.dim(),
//            N = yn.dim(),
//            L = M + N - 1;
//
//        zn.resize( L );
//        Vector<double>  xnPadded( L ),
//                        ynPadded( L );
//
//        for( int i=0; i<M; ++i )
//            xnPadded[i] = xn[i];
//        for( int i=0; i<N; ++i )
//            ynPadded[i] = yn[i];
//
//        Vector< complex<double> >   Xk( L/2+1 ),
//                                    Yk( L/2+1 ),
//                                    Zk( L/2+1 );
//        fftw_plan r2cP,
//                  c2rP;
//        r2cP = fftw_plan_dft_r2c_1d( L, xnPadded.begin(),
//               reinterpret_cast<fftw_complex*>(Xk.begin()),
//               FFTW_ESTIMATE );
//        fftw_execute( r2cP );
//        r2cP = fftw_plan_dft_r2c_1d( L, ynPadded.begin(),
//               reinterpret_cast<fftw_complex*>(Yk.begin()),
//               FFTW_ESTIMATE );
//        fftw_execute( r2cP );
//
//        Zk = Xk * Yk;
//
//        c2rP = fftw_plan_dft_c2r_1d( L,
//               reinterpret_cast<fftw_complex*>(Zk.begin()),
//               zn.begin(), FFTW_ESTIMATE );
//        fftw_execute( c2rP );
//        zn /= double(L);
//
//        fftw_destroy_plan( r2cP );
//        fftw_destroy_plan( c2rP );
//    }
//
//
//    /**
//     * Fast auto-correlation by FFT.
//     */
//    inline void fastAcor( Vector<double> &xn, Vector<double> &zn )
//    {
//        fastConv( xn.reverse(), xn, zn );
//    }
//
//
//    /**
//     * Fast cross-correlation by FFT.
//     */
//    inline void fastCcor( Vector<double> &xn, Vector<double> &yn,
//                          Vector<double> &zn )
//    {
//        fastConv( xn.reverse(), yn, zn );
//    }
