/*****************************************************************************
 *                               funcroot.h
 *
 * Solution for nonlinear equation.
 *
 * This class includes three routines for finding root of nonlinear equation.
 * The bisection method don't need compute the function's gradient, but it
 * has a slow convergence rate, linear convergence. Newton method has a
 * quadratic convergence, however, it has to compute the gradient of function.
 * The secant method don't need compute the gradient, in adition, it has a
 * superlinear convergence rate( the order is 1.618 ), so it's a practical
 * method in many cases.
 *
 * Zhang Ming, 2010-04, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef FUNCTIONROOT_H
#define FUNCTIONROOT_H


#include <cmath>
#include "constants.h"
#include "nlfunction.h"


using namespace std;


namespace itlab
{

    template <typename Type>
    class FuncRoot
    {

    public:

        FuncRoot();
        ~FuncRoot();

        Type bisection( NLFunc<Type> &f, Type a, Type b, Type tol=1.0e-6 );
        Type newton( NLFunc<Type> &f, Type x0, Type tol=1.0e-6, int maxItr=MAXTERM );
        Type secant( NLFunc<Type> &f, Type x1, Type x2, Type tol=1.0e-6, int maxItr=MAXTERM );

    };
    // class FuncRoot


    #include "funcroot-impl.h"

}


#endif
// FUNCTIONROOT_H
