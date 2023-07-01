/*****************************************************************************
 *                               nlfunction.h
 *
 * Nolinear function.
 *
 * Zhang Ming, 2010-04, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef NLFUNCTION_H
#define NLFUNCTION_H


namespace itlab
{

    template <typename Type>
    class NLFunc
    {

    public:

        /**
         * Initialize the parameters
         */
        NLFunc( Type aa, Type bb, Type cc ) : a(aa), b(bb), c(cc)
        { }

        /**
         * Compute the value of objective function at point x.
         */
        Type operator()( Type &x )
        {
            return ( a*x*x + b*x + c );
        }

        /**
         * Compute the gradient of objective function at point x.
         */
        Type grad( Type &x )
        {
            return ( 2*a*x + b );
        }

    private:

        // parameters
        Type a,
             b,
             c;

    };
    // class NLFunc

}
// namespace itlab


#endif
// NLFUNCTION_H
