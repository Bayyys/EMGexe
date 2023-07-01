/*****************************************************************************
 *                                matrixinverse.h
 *
 * Matrix Inverse
 *
 * Matrix's inverse is a very important algorithm. If 'A' is an n-by-n full
 * rank square matrix, then it's inverse 'invA' is also an n-by-n full rank
 * square matrix. The general method to compute such matrix's inverse is
 * use LU decomposition to solve A*invA=I, if 'A' is symmetric, then Cholesky
 * decomposition will be more efficiency.
 *
 * If 'A' is an m-by-n (where m != n) matrix, or n-by-n but nor full rank,
 * then we can't compute the ordinary inverse. In these cases, we should
 * compute the pseudoinverse. And here we use SVD to compute the pseudoinverse,
 * which is consistent with Matlab's "pinv".
 *
 * Zhang Ming, 2010-08, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef MATRIXINVERSE_H
#define MATRIXINVERSE_H


#include <string>
#include "matrix.h"
#include "cholesky.h"
#include "lud.h"
#include "svd.h"


namespace itlab
{

	template<typename Real> Matrix<Real> inv( const Matrix<Real>&, const string &type="nonsym" );
	template<typename Real>	Matrix<Real> pinv( const Matrix<Real>&, Real tol=-1 );
	template<typename Real> Matrix<Real> colPivInv( const Matrix<Real>& );
    template<typename Real> Matrix<Real> cmpPivInv( const Matrix<Real>& );


    #include "matrixinverse-impl.h"
}
// namespace itlab


#endif
// MATRIXINVERSE_H
