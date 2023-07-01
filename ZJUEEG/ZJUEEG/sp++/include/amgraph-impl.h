/*****************************************************************************
 *                               AMGraph-impl.h
 *
 * Implementation for AMGraph class.
 *
 * Zhang Ming, 2010-07, Xi'an Jiaotong University.
 *****************************************************************************/


/**
 * constructors and destructor
 */
template<typename Object, typename Weight>
AMGraph<Object,Weight>::AMGraph( int n )
{
    maxSize = n;
    curSize = 0;
    edgeNum = 0;

    vertexArray = new Object[maxSize];
    makeMatrix( edgeMatrix, maxSize, maxSize );
    if( vertexArray == NULL || edgeMatrix == NULL )
    {
        cerr << "Out of memory!";
        exit(1);
    }

    for( int i=0; i<maxSize; ++i )
        for( int j=0; j<maxSize; ++j )
            edgeMatrix[i][j] = MAXWEIGHT;
    for( int i=0; i<maxSize; ++i )
            edgeMatrix[i][i] = MINWEIGHT;
}

template<typename Object, typename Weight>
AMGraph<Object,Weight>::~AMGraph()
{
    delete []vertexArray;
    deleteMatrix( edgeMatrix, maxSize );
}


/**
 * Get the vertex number of the graph.
 */
template<typename Object, typename Weight>
inline int AMGraph<Object,Weight>::getVertexNumber() const
{
    return curSize;
}


/**
 * Get the edge number of the graph.
 */
template<typename Object, typename Weight>
inline int AMGraph<Object,Weight>::getEdgeNumber() const
{
    return edgeNum;
}


/**
 * Return the content of vertex "i".
 */
template<typename Object, typename Weight>
inline Object AMGraph<Object,Weight>::getData( int i ) const
{
#ifdef BOUNDS_CHECK
    assert( 0 <= i );
    assert( i < curSize );
#endif

    return vertexArray[i];
}


/**
 * Return the index of vertex "x", if there is no shuch vertex, return -1.
 */
template<typename Object, typename Weight>
inline int AMGraph<Object,Weight>::getIndex( const Object &x ) const
{
    for( int i=0; i<curSize; ++i )
        if( vertexArray[i] == x )
            return i;

    return -1;
}


/**
 * Return weight on the edge between vertex "x1" and "x2".
 */
template<typename Object, typename Weight>
Weight AMGraph<Object,Weight>::getWeight( int row, int col ) const
{
#ifdef BOUNDS_CHECK
    assert( 0 <= row );
    assert( row < curSize );
    assert( 0 <= col );
    assert( col < curSize );
#endif

    return edgeMatrix[row][col];
}

template<typename Object, typename Weight>
Weight AMGraph<Object,Weight>::getWeight( const Object &x1, const Object &x2 ) const
{
    int v1 = getIndex(x1),
        v2 = getIndex(x2);

    if( v1 == -1 )
    {
        cerr << "There is no vertex: " << x1 << endl;
        return Weight(0);
    }
    else if( v2 == -1 )
    {
        cerr << "There is no vertex: " << x2 << endl;
        return Weight(0);
    }
    else
        return edgeMatrix[v1][v2];
}


/**
 * Get the position of the next adjacency point of vertex "x",
 * if there is no next adjacendy vertex, return -1;
 */
template<typename Object, typename Weight>
int AMGraph<Object,Weight>::getNextDst( const Object &x ) const
{
    int i = getIndex(x);

    if( i == -1 )
    {
        cerr << "There is no vertex: " << x << endl;
        return -1;
    }
    else
    {
        for( int j=0; j<curSize; ++j )
            if( MINWEIGHT < edgeMatrix[i][j] && edgeMatrix[i][j] < MAXWEIGHT )
                return j;
        return -1;
    }
}

template<typename Object, typename Weight>
int AMGraph<Object,Weight>::getNextDst( const Object &x1, const Object &x2 ) const
{
    int v1 = getIndex(x1),
        v2 = getIndex(x2);

    if( v1 == -1 )
    {
        cerr << "There is no vertex: " << x1 << endl;
        return -1;
    }
    else if( v2 == -1 )
    {
        cerr << "There is no vertex: " << x2 << endl;
        return -1;
    }
    else
    {
        for( int col=v2+1; col<curSize; ++col )
            if( MINWEIGHT < edgeMatrix[v1][col] && edgeMatrix[v1][col] < MAXWEIGHT )
                return col;
        return -1;
    }
}


/**
 * Insert a new vertex "x". If the vertex array is full, output
 * the FULL warning.
 */
template<typename Object, typename Weight>
void AMGraph<Object,Weight>::insertVertex( const Object &x )
{
    if( curSize < maxSize )
        vertexArray[curSize++] = x;
    else
        cerr << "The vertex table is full!" << endl;
}


/**
 * Remove the vertex "x".
 */
template<typename Object, typename Weight>
void AMGraph<Object,Weight>::removeVertex( const Object &x )
{
    int v = getIndex(x);

    if( v == -1 )
        cerr << "There is no vertex: " << x << endl;
    else
    {
        vertexArray[v] = vertexArray[curSize-1];

        for( int i=0; i<curSize; ++i )
            if( MINWEIGHT < edgeMatrix[i][v] && edgeMatrix[i][v] < MAXWEIGHT )
                edgeNum--;
        for( int j=0; j<curSize; ++j )
            if( MINWEIGHT < edgeMatrix[v][j] && edgeMatrix[v][j] < MAXWEIGHT )
                edgeNum--;

        for( int j=0; j<curSize; ++j )
            edgeMatrix[v][j] = edgeMatrix[curSize-1][j];
        for( int i=0; i<curSize; ++i )
            edgeMatrix[i][v] = edgeMatrix[i][curSize-1];

        curSize--;
    }
}


/**
 * Insert an edge (x1,x2) with weight "c". If the edge already exist then
 * return false, else return true.
 */
template<typename Object, typename Weight>
void AMGraph<Object,Weight>::insertEdge( const Object &x1, const Object &x2, Weight c )
{
    int v1 = getIndex(x1),
        v2 = getIndex(x2);

    if( v1 == -1 )
        cerr << "There is no vertex: " << x1 << endl;
    else if( v2 == -1 )
        cerr << "There is no vertex: " << x2 << endl;
    else
        if( v1 != v2 )
        {
            edgeMatrix[v1][v2] = c;
            edgeNum++;
        }
}


/**
 * Remove the edge (x1,x2).
 */
template<typename Object, typename Weight>
void AMGraph<Object,Weight>::removeEdge( const Object &x1, const Object &x2 )
{
    int v1 = getIndex(x1),
        v2 = getIndex(x2);

    if( v1 == -1 )
        cerr << "There is no vertex: " << x1 << endl;
    else if( v2 == -1 )
        cerr << "There is no vertex: " << x2 << endl;
    else
        if( v1 != v2 )
        {
            if( edgeMatrix[v1][v2] == MAXWEIGHT )
            {
                cerr << "There is no such edge between " << x1 << " and " << x2 << endl;
                return;
            }
            else
            {
                edgeMatrix[v1][v2] = MAXWEIGHT;
                edgeNum--;
            }
        }
}


/**
 * Dijkstra algorithm for Single-Source Shortest Path
 */
template<typename Object, typename Weight>
void AMGraph<Object,Weight>::dijkstra( int start, Weight *dist, int *path )
{
#ifdef BOUNDS_CHECK
    assert( 0 <= start );
    assert( start < curSize );
#endif

    bool *visited = new bool[curSize];
    for( int i=0; i<curSize; ++i )
    {
        visited[i] = false;
        dist[i] = edgeMatrix[start][i];
        if( dist[i] < MAXWEIGHT )
            path[i] = start;
        else
            path[i] = -1;
    }

    visited[start] = true;
    dist[start] = 0;

    for( int i=1; i<curSize; ++i )
    {
        Weight minDIst = MAXWEIGHT;
        for( int j=0; j<curSize; ++j )
            if( !visited[j] && dist[j] < minDIst )
            {
                minDIst = dist[j];
                start = j;
            }

        visited[start] = true;
        for( int j=0; j<curSize; ++j )
            if( !visited[j] && dist[start]+edgeMatrix[start][j] < dist[j] )
            {
                dist[j] = dist[start]+edgeMatrix[start][j];
                path[j] = start;
            }
    }

    /* output the result...
    for( int i=0; i<verNum; ++i )
    {
        if( dist[i] < g.MAXWEIGHT )
        {
            cout << i << ":\t" << dist[i] << "\t" << i << " <-- ";
            for( int j=path[i]; j!=start; j=path[j] )
                cout << j << " <-- ";
            cout << start << endl;
        }
        else
            cout << i << ":\tMAX\tNo Path!" <<endl;
    }
    */
}


/**
 * Floyd algorithm for All-Pairs Shortest Path
 */
template<typename Object, typename Weight>
void AMGraph<Object,Weight>::floyd( Weight **dist, int **path )
{
    for( int i=0; i<curSize; ++i )
    {
        for( int j=0; j<curSize; ++j )
        {
            dist[i][j] = edgeMatrix[i][j];

            if( dist[i][j] < MAXWEIGHT )
                path[i][j] = i;
            else
                path[i][j] = -1;
        }
        dist[i][i] = Weight(0);
    }

    for( int v=0; v<curSize; ++v )
        for( int i=0; i<curSize; ++i )
            for( int j=0; j<curSize; ++j )
                if( dist[i][j] > dist[i][v]+dist[v][j] )
                {
                    dist[i][j] = dist[i][v]+dist[v][j];
                    path[i][j] = path[v][j];
                }

    /* output the result...
    for( int v=0; v<verNum; ++v )
    {
        cout << "The " << v << "th vertex's shortest path: " << endl;
        for( int i=0; i<verNum; ++i )
        {
            if( dist2D[v][i] < g.MAXWEIGHT )
            {
                cout << i << ":\t" << dist2D[v][i] << "\t" << i << " <-- ";
                for( int j=path2D[v][i]; j!=v; j=path2D[v][j] )
                    cout << j << " <-- ";
                cout << v << endl;
            }
            else
                cout << i << ":\tMAX\tNo Path!" <<endl;
        }
        cout << endl;
    }
    */
}


/**
 * Reload the "<<" operator.
 */
template<typename Object, typename Weight>
ostream& operator<<( ostream &out, const AMGraph<Object,Weight> &g )
{
    int verNum = g.getVertexNumber(),
        edgeNum = g.getEdgeNumber();

    out << "This graph has " << verNum << " vertexes and " << edgeNum << " edges." << endl;
	for( int i=0; i<verNum; ++i )
	{
		for( int j=0; j<verNum; ++j )
		{
		    Weight tmp = g.getWeight( i, j );
		    if( tmp == g.MINWEIGHT )
                out << "MIN" << "\t";
            else if( tmp == g.MAXWEIGHT )
                out << "MAX" << "\t";
            else
                out << g.getWeight( i, j ) << "\t";
		}
		out << "\n";
	}

	return out;
}
