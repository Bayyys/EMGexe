/*****************************************************************************
 *                                    pointerheap.h
 *
 * Minimum binary heap (For Pointer) implemented by C++ template class.
 *
 * This class provides the following operatins of a minimum binary heap:
 *      build a heap
 *      insert an element into the heap
 *      find the minimum element in the heap
 *      delete the minimum element in the heap
 *
 * The defualt initial size of the heap is set to 20. If the elements number
 * exceed initial size, then it will be extended by a factor of 2.
 *
 * Zhang Ming, 2009-10, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef POINTERHEAP_H
#define POINTERHEAP_H


#include <iostream>
#include <cstdlib>
#include "constants.h"


using namespace std;


namespace itlab
{

    template <typename Type>
    class PointerHeap
    {

    public:

        PointerHeap( int maxSize = INITSIZE );
        PointerHeap( Type *array, int length );
        PointerHeap( const PointerHeap<Type> &rhs );
        ~PointerHeap();
        PointerHeap<Type>& operator=( const PointerHeap<Type> &rhs );

        bool isEmpty() const;
        void makeEmpty();
        int size() const;

        void insert( const Type &x );
        void findMin( Type &x );
        void deleteMin();
        void deleteMin( Type &minItem );

    private:

        Type *elements;
        int currentSize;
        int capacity;

        void filterDown( int hole );
        void filterUp( int hole );

        void handleOverflow();
        void handleUnderflow();

    };
    // class PointerHeap


    #include "pointerheap-impl.h"

}
// namespace itlab


#endif
// POINTERHEAP_H

