/*****************************************************************************
 *                               doublelist-impl.h
 *
 * Implementation for ListItr and DList class.
 *
 * Zhang Ming, 2009-10, Xi'an Jiaotong University.
 *****************************************************************************/


/**
 * constructors and destructor
 */
template <typename Type>
ListItr<Type>::ListItr()
{
}

template <typename Type>
ListItr<Type>::ListItr( Node<Type> *p ) : current(p)
{
}

template <typename Type>
ListItr<Type>::~ListItr()
{
}


/**
 * Overload operations of pointer.
 */
template <typename Type>
inline Type& ListItr<Type>::operator*()
{
    return current->data;
}

template <typename Type>
inline const Type& ListItr<Type>::operator*() const
{
    return current->data;
}


/**
 * Overload operations of "++" and "--".
 */
template <typename Type>
inline ListItr<Type>& ListItr<Type>::operator++()
{
    current = current->next;
    return *this;
}

template <typename Type>
inline ListItr<Type> ListItr<Type>::operator++( int )
{
    ListItr old = *this;
    ++( *this );
    return old;
}

template <typename Type>
inline ListItr<Type>& ListItr<Type>::operator--()
{
    current = current->prev;
    return *this;
}

template <typename Type>
inline ListItr<Type> ListItr<Type>::operator--( int )
{
    ListItr old = *this;
    --( *this );
    return old;
}


/**
 * Overload comparison operations.
 */
template <typename Type>
inline bool ListItr<Type>::operator==( const ListItr &rhs ) const
{
    return current == rhs.current;
}


template <typename Type>
inline bool ListItr<Type>::operator!=( const ListItr &rhs ) const
{
    return !( *this == rhs );
}



/**
 * constructors and destructor
 */
template< typename Type >
inline void DList<Type>::init()
{
    listSize = 0;
    head = new Node<Type>;
    tail = new Node<Type>;
    head->next = tail;
    tail->prev = head;
}

template< typename Type >
DList<Type>::DList()
{
    init();
}

template< typename Type >
DList<Type>::DList( const DList &rhs )
{
    init();
    *this = rhs;
}

template< typename Type >
DList<Type>::~DList()
{
    clear();
    delete head;
    delete tail;
}


/**
 * assigning operator
 */
template< typename Type >
DList<Type>& DList<Type>::operator=( const DList &rhs )
{
    if( this == &rhs )
        return *this;

    clear();
    for( Iterator itr=rhs.begin(); itr!=rhs.end(); ++itr )
        pushBack( *itr );

    return *this;
}


/**
 * Make the list empty.
 */
template< typename Type >
inline void DList<Type>::clear()
{
    while( !isEmpty() )
        popFront();
}


/**
 * If the list is empty, return true.
 */
template< typename Type >
inline bool DList<Type>::isEmpty() const
{
    return size() == 0;
}


/**
 * Return the size of list.
 */
template< typename Type >
inline int DList<Type>::size() const
{
    return listSize;
}


/**
 * Get the beginning iterator of the list.
 */
template< typename Type >
inline typename DList<Type>::Iterator DList<Type>::begin()
{
    return Iterator( head->next );
}

template< typename Type >
inline typename DList<Type>::Const_Iterator DList<Type>::begin() const
{
    return Iterator( head->next );
}


/**
 * Get the ending iterator of the list.
 */
template< typename Type >
inline typename DList<Type>::Iterator DList<Type>::end()
{
    return Iterator( tail );
}

template< typename Type >
inline typename DList<Type>::Const_Iterator DList<Type>::end() const
{
    return Iterator( tail );
}


/**
 * Get the front element of the list.
 */
template< typename Type >
inline Type& DList<Type>::front()
{
    return *begin();
}


template< typename Type >
inline const Type& DList<Type>::front() const
{
    return *begin();
}


/**
 * Get the back element of the list.
 */
template< typename Type >
inline Type& DList<Type>::back()
{
    return *--end();
}

template< typename Type >
inline const Type& DList<Type>::back() const
{
    return *--end();
}


/**
 * Push an element from the front of the list.
 */
template< typename Type >
inline void DList<Type>::pushFront( const Type &x )
{
    insert( begin(), x );
}


/**
 * Push an element from the back of the list.
 */
template< typename Type >
inline void DList<Type>::pushBack( const Type &x )
{
    insert( end(), x );
}


/**
 * Pop an element from the front of the list.
 */
template< typename Type >
inline void DList<Type>::popFront()
{
    erase( begin() );
}


/**
 * Push an element from the back of the list.
 */
template< typename Type >
inline void DList<Type>::popBack()
{
    erase( --end() );
}


/**
 * Insert an element into list at the position pointed by "itr".
 */
template< typename Type >
typename DList<Type>::Iterator DList<Type>::insert( Iterator itr,
                                                    const Type &x )
{
    Node<Type> *p = itr.current;
    p->prev = p->prev->next = new Node<Type>( x, p->prev, p );
    listSize++;

    return Iterator( p->prev );
}


/**
 * Erase an element pointed by "itr".
 */
template< typename Type >
typename DList<Type>::Iterator DList<Type>::erase( Iterator itr )
{
    Node<Type> *p = itr.current;
    Iterator tmp( p->next );
    p->prev->next = p->next;
    p->next->prev = p->prev;
    listSize--;
    delete p;

    return tmp;
}


/**
 * Erase elements from "start" to "end" of the list .
 */
template< typename Type >
typename DList<Type>::Iterator DList<Type>::erase( Iterator start,
                                                   Iterator end )
{
    for( Iterator itr = start; itr != end; )
        itr = erase( itr );

    return end;
}
