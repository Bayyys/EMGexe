/*****************************************************************************
 *                               function.h
 *
 * Function Object.
 *
 * We can use this functor computing the value of objective function and it's
 * gradient vector. The objective function is supposed to be multidimensional,
 * one dimention is the special case of "vector.dim()=1".
 *
 * Zhang Ming, 2010-03, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef FUNCTION_H
#define FUNCTION_H


#include "vector.h"


namespace itlab
{

    template <typename Type>
    class ObjFunc
    {

    public:

        /**
         * Initialize the parameters
         */
        ObjFunc( Type aa, Type bb, Type cc ) : a(aa), b(bb), c(cc)
        { }

        /**
         * Compute the value of objective function at point x.
         */
        Type operator()( Vector<Type> &x )
        {
            return ( a*x(1) * exp(b*x(1)*x(1)+c*x(2)*x(2)) );
        }

        /**
         * Compute the gradient of objective function at point x.
         */
        Vector<Type> grad( Vector<Type> &x )
        {
            Type expTerm = exp(a*x(1)*x(1)+b*x(2)*x(2));
            Vector<Type> df(x.dim());
            df(1) = (a+2*a*b*x(1)*x(1)) * expTerm;
            df(2) = 2*a*c*x(1)*x(2) * expTerm;

            return df;
        }

    private:

        // parameters
        Type a,
             b,
             c;

    };
    // class ObjFunc

}
// namespace itlab


#endif
// FUNCTION_H
