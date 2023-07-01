/*****************************************************************************
 *                               functions.h
 *
 * Fitted functions for least square fitting.
 *
 * Zhang Ming, 2010-04, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <iostream>
#include "constants.h"


namespace itlab
{

    template <typename Type>
    class Funcs
    {

    public:

        const static int dim = 4;

        // Compute the value of functions at point x.
        Type operator()( int i, const Type &x )
        {
            switch( i )
            {
                case 1:
                {
                    return 1;
                    break;
                }
                case 2:
                {
                    return log(max(x,EPS));
                    break;
                }
                case 3:
                {
                    return x;
                    break;
                }
                case 4:
                {
                    return x*x;
                    break;
                }
                default:
                {
                    std::cerr << "The dimension 'i' exceed the bound!" << std::endl;
                    return 0;
                    break;
                }
            }
        }

    };
    // class ObjFunc

}
// namespace itlab


#endif
// FUNCTIONS_H
