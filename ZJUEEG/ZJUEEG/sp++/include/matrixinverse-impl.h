/*****************************************************************************
 *                                matrixinverse.h
 *
 * Implementation for matrix Inverse
 *
 * Zhang Ming, 2010-08, Xi'an Jiaotong University.
 *****************************************************************************/


/**
 * Cpmpute the inverse of square matrix.
 */
template <typename Real>
Matrix<Real> inv( const Matrix<Real> &A, const string &type )
{
    int n = A.rows();
    assert( n == A.cols() );

    Matrix<Real> E = eye( n, Real(1) );

    if( type == "sym" )
    {
        Cholesky<Real> cho;
        cho.dec(A);
        if( cho.isSpd() )
            return cho.solve(E);
        else
        {
            cerr << "The matrix is not symmetric!" << endl;
            return A;
        }

    }
    else
    {
        LUD<Real> lu;
        lu.dec(A);
        return lu.solve(E);
    }
}


/**
 * Compute the pseudoinverse of matrix.
 */
template <typename Real>
Matrix<Real> pinv( const Matrix<Real> &A, Real tol )
{
    int m = A.rows(),
        n = A.cols();

    SVD<Real> svd;
    svd.dec( A );
    Matrix<Real> U = svd.getU();
    Matrix<Real> V = svd.getV();
    Vector<Real> s = svd.getSV();

    int r = 0;
    if( tol <= 0 )
        tol = max( m, n ) * s[0] * EPS;
    for( int i=0; i<s.size(); ++i )
        if( s[i] >= tol )
            r++;

    for( int i=0; i<n; ++i )
        for( int k=0; k<r; ++k )
                V[i][k] /= s[k];

    Matrix<Real> invA( n, m );
    for( int i=0; i<n; ++i )
        for( int j=0; j<m; ++j )
        {
            Real sum = 0;
            for( int k=0; k<r; ++k )
                sum += V[i][k]*U[j][k];
            invA[i][j] = sum;
        }

    return invA;
}


/**
 * Gauss-jordan column pivot elimination for computing matrix's inverse.
 */
template <typename Real>
Matrix<Real> colPivInv( const Matrix<Real> &A )
{
    int rows = A.rows();
    int clumns = A.cols();

    assert( rows == clumns );

    Matrix<Real> invA(A);
    Vector<int> index( rows );
    int i, j, k;
    Real tmp = 0;

    for( k=0; k<rows; ++k )
    {
        //Findint pivot and exchange if necessary.
        index[k] = k;
        Real mvl = invA[k][k];
        for( i=k+1; i<rows; ++i )
        {
            tmp = abs(invA[i][k]);
            if( tmp > mvl )
            {
                mvl = tmp;
                index[k] = i;
            }
        }
        if( abs(mvl) < EPS )
        {
            cerr << "\n" << "A is a singular matrix." << "\n";
            return Matrix<Real>(0,0);
        }

        if( index[k] != k )
        {
            tmp = 0;
            for( j=0; j<rows; ++j )
            {
                tmp = invA[k][j];
                invA[k][j] = invA[index[k]][j];
                invA[index[k]][j] = tmp;
            }
        }

        // Calculating the kth column.
        invA[k][k] = 1/invA[k][k];
        for( i=0; i<rows; ++i )
            if( i != k )
                invA[i][k] = - invA[k][k]*invA[i][k];

        // Calculating all elements excptint the kth row and column.
        for( i=0; i<rows; ++i )
            if( i != k )
                for( j=0; j<rows; ++j )
                    if( j != k )
                        invA[i][j] += invA[i][k] * invA[k][j];

        // Calculating the kth row.
        for( j=0; j<rows; ++j )
            if( j != k )
                invA[k][j] *= invA[k][k];
    }

    //Exchanging back.
    for( k=rows-1; k>=0; --k )
        if( index[k] != k )
        {
            tmp = 0;
            for( i=0; i<rows; ++i )
            {
                tmp = invA[i][k];
                invA[i][k] = invA[i][index[k]];
                invA[i][index[k]] = tmp;
            }
        }

    return invA;
}


/**
 * Gauss-jordan complete pivot elimination for computing matrix's inverse.
 */
template <typename Real>
Matrix<Real> cmpPivInv( const Matrix<Real> &A )
{
    int n = A.rows();
    assert( n == A.cols() );
    Matrix<Real> invA(A);

    int k;
    Real tmp = 0,
         mvl = 0;
    Vector<int> rowIndex(n),
                colIndex(n);

    for( k=0; k<n; ++k )
    {
        //findint pivot
        mvl = 0;
        for( int i=k; i<n; ++i )
            for( int j=k; j<n; ++j )
            {
                tmp = abs(invA[i][j]);
                if( abs(invA[i][j]) > mvl )
                {
                    mvl = tmp;
                    rowIndex[k] = i;
                    colIndex[k] = j;
                }
            }

        if( abs(mvl) < EPS )
        {
           cerr << endl << "A is a singular matrix." << endl;
            return invA;
        }

        // row exchange
        if( rowIndex[k] != k )
            for( int i=0; i<n; ++i )
                swap( invA[k][i], invA[rowIndex[k]][i] );

        // column exchange
        if( colIndex[k] != k )
            for( int j=0; j<n; ++j )
                swap( invA[j][k], invA[j][rowIndex[k]] );

        // Calculating the kth column.
        invA[k][k] = 1 / invA[k][k];
        for( int j=0; j<n; ++j )
            if( j != k )
                invA[k][j] = invA[k][j]*invA[k][k];

        // Calculating all elements excptint the kth row and column.
        for( int i=0; i<n; ++i )
            if( i != k )
                for( int j=0; j<n; ++j )
                    if( j != k )
                        invA[i][j] -= invA[i][k]*invA[k][j];

        for( int i=0; i<n; ++i )
            if( i != k )
                invA[i][k] = -invA[i][k]*invA[k][k];
    }

    //Exchanging back.
    for( k=n-1; k>=0; --k )
    {
        if( colIndex[k] != k )
            for( int j=0; j<n; ++j )
                swap( invA[k][j], invA[colIndex[k]][j] );
        if( rowIndex[k] != k )
            for( int i=0; i<n; ++i )
                swap( invA[i][k], invA[i][rowIndex[k]] );
    }

    return invA;
}
