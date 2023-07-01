/*****************************************************************************
 *                                    amgraph.h
 *
 * Adjacency Matrix Based Directed Graph.
 *
 * This is a C++ template class for undirected graph with an adjacency matrix
 * representation. It provedes the general operations for graph, such as
 * insertVertex, removeVertex, insertEdge, removeEdge, getVertexNumber,
 * getEdgeNumber, getData, getWeight, getNextDst, and so on.
 *
 * It also includes the  Dijkstra algorithm for Single-Source Shortest Path
 * and Floyd algorithm for All-Pairs Shortest Paths.
 *
 * When debugging, use #define BOUNDS_CHECK above your "#include amgraph.h"
 * line. When done debugging, comment out #define BOUNDS_CHECK for better
 * performance.
 *
 * Zhang Ming, 2010-07, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef AMGRAPH_H
#define AMGRAPH_H


#include <iostream>
#include <cstdlib>
#include <cassert>
#include "constants.h"
#include "matrixallocate.h"


using namespace std;


namespace itlab
{

    /**
     * adjacency matrix based graph
     */
    template<typename Object, typename Weight>
    class AMGraph
    {

    public:

        static const Weight MAXWEIGHT = Weight(32767);
        static const Weight MINWEIGHT = Weight(-32768);

        explicit AMGraph( int n=INITSIZE );
        ~AMGraph();

        int getVertexNumber() const;
        int getEdgeNumber() const;

        Object getData( int i ) const;
        int getIndex( const Object &x ) const;
        Weight getWeight( int row, int col ) const;
        Weight getWeight( const Object &x1, const Object &x2 ) const;

        int getNextDst( const Object &x ) const;
        int getNextDst( const Object &x1, const Object &x2 ) const;

        void insertVertex( const Object &x );
        void removeVertex( const Object &x );
        void insertEdge( const Object &x1, const Object &x2, Weight c );
        void removeEdge( const Object &x1, const Object &x2 );

        void dijkstra( int start, Weight *dist, int *path );
        void floyd( Weight **dist, int **path );

    private:

        int curSize;
        int maxSize;
        int edgeNum;
        Object *vertexArray;
        Weight **edgeMatrix;

    };


    #include "amgraph-impl.h"

}
// namespace itlab


#endif
// AMGRAPH_H

