/*****************************************************************************
 *                                    algraph.h
 *
 * Adjacency List Based Undirected Graph.
 *
 * This is a C++ template class for undirected graph with an adjacency list
 * representation. It provedes the general operations for graph, such as
 * insertVertex, removeVertex, insertEdge, removeEdge, getVertexNumber,
 * getEdgeNumber, getData, getWeight, getNextDst, and so on.
 *
 * It also includes the Depth First Search (nonrecursion version), Breadth
 * First Search and Minimum Span Tree algorithms.
 *
 * When debugging, use #define BOUNDS_CHECK above your "#include algraph.h"
 * line. When done debugging, comment out #define BOUNDS_CHECK for better
 * performance.
 *
 * Zhang Ming, 2009-10, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef ALGRAPH_H
#define ALGRAPH_H


#include <iostream>
#include <cstdlib>
#include <cassert>
#include "constants.h"
#include "stack.h"
#include "queue.h"


using namespace std;


namespace itlab
{

    /**
     * graph's edge
     */
    template<typename Weight>
    struct Edge
    {
        int             dst;
        Weight          cost;
        Edge<Weight>    *next;

        Edge( int d, Weight c, Edge<Weight> *p=NULL )
          : dst(d), cost(c), next(p)
        { }
    };


    /**
     * graph's vertex
     */
    template<typename Object, typename Weight>
    struct Vertex
    {
        Object          data;
        Edge<Weight>    *adj;

        Vertex( Object x=Object(), Edge<Weight> *p=NULL )
          : data(x), adj(p)
        { }
    };


    /**
     * adjacency list based graph
     */
    template<typename Object, typename Weight>
    class ALGraph
    {

    public:

        static const Weight MAXWEIGHT = Weight(32767);
        static const Weight MINWEIGHT = Weight(-32768);

        explicit ALGraph( int n=INITSIZE );
        ~ALGraph();

        int getVertexNumber() const;
        int getEdgeNumber() const;

        Object getData( int i ) const;
        int getIndex( const Object &x ) const;
        Weight getWeight( const Object &x1, const Object &x2 ) const;

        int getNextDst( const Object &x ) const;
        int getNextDst( const Object &x1, const Object &x2 ) const;

        void insertVertex( const Object &x );
        void removeVertex( const Object &x );
        void insertEdge( const Object &x1, const Object &x2, Weight c );
        void removeEdge( const Object &x1, const Object &x2 );

        void dfs();
        void dfs( int start, bool *visited );
        void bfs();
        void bfs( int start, bool *visited );

        void minSpanTree( int start, int *addedVertex, int *conectedVertex, Weight *lowCost );

    private:

        int curSize;
        int maxSize;
        int edgeNum;
        Vertex<Object, Weight> *vertexArray;

    };


    #include "algraph-impl.h"

}
// namespace itlab


#endif
// ALGRAPH_H
