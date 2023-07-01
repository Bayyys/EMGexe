/*****************************************************************************
 *                               funcroot-impl.h
 *
 * Implementation for FuncRoot class.
 *
 * Zhang Ming, 2010-04, Xi'an Jiaotong University.
 *****************************************************************************/


/**
 * constructor and destructor
 */
template <typename Type>
FuncRoot<Type>::FuncRoot()
{
}

template <typename Type>
FuncRoot<Type>::~FuncRoot()
{
}


/**
 * Bisection method for finding function root.
 */
template <typename Type>
Type FuncRoot<Type>::bisection( NLFunc<Type> &f, Type a, Type b, Type tol )
{
	Type    c = 0,
            fc = 0,
            fa = f(a),
            fb = f(b);

    if( a > b )
    {
        c = a;
        a = b;
        b = c;
    }
    if( fa*fb > 0 )
    {
        cerr << " Invalid interval!" << endl;
        return Type(0);
    }

    int maxItr = (int) ceil( (log(b-a)-log(tol)) / log(2.0) );
	for( int i=0; i<maxItr; ++i )
	{
	    c = ( a+ b) / 2;
	    fc = f(c);

	    if( abs(fc) < EPS )
            return c;

	    if( fb*fc > 0 )
	    {
	        b = c;
	        fb = fc;
	    }
	    else
	    {
	        a = c;
	        fa = fc;
	    }

	    if( (b-a) < tol )
            return (b+a)/2;
	}

	cout << "No solution for the specified tolerance!" << endl;
	return c;
}


/**
 * Newton method for finding function root.
 */
template <typename Type>
Type FuncRoot<Type>::newton( NLFunc<Type> &f, Type x0, Type tol, int maxItr )
{
	Type    xkOld = x0,
            xkNew,
            fkGrad;

	for( int i=0; i<maxItr; ++i )
	{
	    fkGrad = f.grad(xkOld);
	    while( abs(fkGrad) < EPS )
	    {
	        xkOld *= 1.2;
	        fkGrad = f.grad(xkOld);
	    }
		xkNew = xkOld - f(xkOld)/fkGrad;

		if( abs(f(xkNew)) < tol )
			return xkNew;
		if( abs(xkOld-xkNew) <tol )
			return xkNew;

		xkOld = xkNew;
	}

	cout << "No solution for the specified tolerance!" << endl;
	return xkNew;
}


/**
 * Secant method for finding function root.
 */
template <typename Type>
Type FuncRoot<Type>::secant( NLFunc<Type> &f, Type x1, Type x2, Type tol, int maxItr )
{
	Type    x_k,
            x_k1 = x1,
            x_k2 = x2,
            f_k1 = f(x_k1),
            f_k2;

	for( int i=0; i<maxItr; ++i )
	{
		f_k2 = f(x_k2);
		if( abs(f_k2-f_k1) < EPS )
        {
            x_k2 = (x_k1+x_k2) / 2;
            f_k2 = f(x_k2);
        }

		x_k = x_k2 - (x_k2-x_k1)*f_k2/(f_k2-f_k1);

		if( abs(f(x_k)) < tol )
			return x_k;
		if( abs(x_k2-x_k) < tol )
			return x_k;

		f_k1 = f_k2;
		x_k1 = x_k2;
		x_k2 = x_k;
	}

	cout << "No solution for the specified tolerance!" << endl;
	return x_k;
}
