/*****************************************************************************
 *                                 doublelist.h
 *
 * Double List.
 *
 * This class template includes a smart pointer supporting "*", "++", "--",
 * "==" and "!=" operations,  which makes it easy to implement the frequently
 * used operations, such as "is empty", "make empty", "begin", "end", "fornt",
 * "back", "push front", "push back", "pop front", "pop back", "insert",
 * "erase" and so on.
 *
 * Zhang Ming, 2009-10, Xi'an Jiaotong University.
 *****************************************************************************/


#ifndef DOUBLELIST_H
#define DOUBLELIST_H


#include <iostream>


namespace itlab
{

    /**
     * List Node
     */
    template <typename Type>
    struct Node
    {
        Type        data;
        Node<Type>  *prev;
        Node<Type>  *next;

        Node( const Type &d=Type(), Node<Type> *p=NULL, Node<Type> *n=NULL )
          : data(d), prev(p), next(n)
        { }
    };
    // class Node


    /**
     * List Iterator
     */
    template <typename Type> class DList;

    template <typename Type>
    class ListItr
    {

        friend class DList<Type>;

    public:

        ListItr();
        ListItr( Node<Type> *p );
        ~ListItr();

        Type& operator*();
        const Type& operator*() const;

        ListItr& operator++();
        ListItr operator++( int );

        ListItr& operator--();
        ListItr operator--( int );

        bool operator==( const ListItr &rhs ) const;
        bool operator!=( const ListItr &rhs ) const;

    private:

        Node<Type> *current;

    };
    // class ListItr


    /**
     * Double List
     */
    template <typename Type>
    class DList
    {

    public:

        DList();
        DList( const DList<Type> &rhs );
        ~DList();

        DList<Type>& operator=( const DList<Type> &rhs );

        typedef ListItr<Type>   Iterator;
        typedef const Iterator  Const_Iterator;

        void clear();
        bool isEmpty() const;
        int size() const;

        Iterator begin();
        Const_Iterator begin() const;

        Iterator end();
        Const_Iterator end() const;

        Type& front();
        const Type& front() const;

        Type& back();
        const Type& back() const;

        void pushFront( const Type &x );
        void pushBack( const Type &x );

        void popFront();
        void popBack();

        Iterator insert( Iterator itr, const Type &x );
        Iterator erase( Iterator itr );
        Iterator erase( Iterator start, Iterator end );

    private:

        int         listSize;
        Node<Type>  *head;
        Node<Type>  *tail;

        void init();

    };
    // class DList


    #include "doublelist-impl.h"

}
// namespace itlab


#endif
// DOUBLELIST_H
