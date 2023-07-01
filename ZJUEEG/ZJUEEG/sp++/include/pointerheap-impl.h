/*****************************************************************************
 *                               binaryheap-impl.h
 *
 * Implementation for PointerHeap class.
 *
 * Zhang Ming, 2009-10, Xi'an Jiaotong University.
 *****************************************************************************/


/**
 * constructors and destructor
 */
template <typename Type>
PointerHeap<Type>::PointerHeap( int maxSize )
{
    capacity = maxSize;

    elements = new Type[capacity+1];
    if( elements == NULL )
        cerr << "Out of memory!" << endl;

    currentSize = 0;
}

template <typename Type>
PointerHeap<Type>::PointerHeap( Type *array, int length )
{
    capacity = ( INITSIZE > length ) ? INITSIZE : length;

    elements = new Type[capacity+1];
    if( elements == NULL )
        cerr << "Out of memory!" << endl;

    for( int i=0; i<length; ++i )
        elements[i+1] = array[i];

    currentSize = length;
    for( int i=currentSize/2; i>0; --i )
        filterDown( i );
}

template <typename Type>
PointerHeap<Type>::PointerHeap( const PointerHeap<Type> &rhs )
{
    currentSize = rhs.currentSize;
    capacity = rhs.capacity;

    elements = new Type[capacity];
    for( int i=1; i<=currentSize; ++i )
        elements[i] = rhs.elements[i];
}

template <typename Type>
PointerHeap<Type>::~PointerHeap()
{
    currentSize = 0;
    capacity = INITSIZE;
    delete []elements;
}


/**
 * Overload copy assignment operation.
 */
template <typename Type>
PointerHeap<Type>& PointerHeap<Type>::operator=( const PointerHeap<Type> &rhs )
{
    currentSize = rhs.currentSize;
    capacity = rhs.capacity;

    delete []elements;
    elements = new Type[capacity];
    for( int i=1; i<=currentSize; ++i )
        elements[i] = rhs.elements[i];

    return *this;
}


/**
 * If the heap is empty, return true.
 */
template <typename Type>
inline bool PointerHeap<Type>::isEmpty() const
{
    return currentSize == 0;
}


/**
 * Make the heap empty.
 */
template <typename Type>
inline void PointerHeap<Type>::makeEmpty()
{
    currentSize = 0;
}


/**
 * Return size of the heap.
 */
template <typename Type>
inline int PointerHeap<Type>::size() const
{
    return currentSize;
}


/**
 * Insert item x, allowing duplicates.
 */
template <typename Type>
inline void PointerHeap<Type>::insert( const Type &x )
{
    if( currentSize == capacity )
        handleOverflow();

    elements[++currentSize] = x;
    filterUp( currentSize );
}


/**
 * Find the smallest item in the heap.
 */
template <typename Type>
inline void PointerHeap<Type>::findMin( Type &x )
{
    if( !isEmpty() )
        x = elements[1];
    else
        handleUnderflow();
}


/**
 * Remove the minimum item.
 */
template <typename Type>
inline void PointerHeap<Type>::deleteMin()
{
    if( !isEmpty() )
    {
        elements[1] = elements[currentSize--];
        filterDown( 1 );
    }
    else
        handleUnderflow();
}


/**
 * Remove the minimum item and place it in minItem.
 */
template <typename Type>
inline void PointerHeap<Type>::deleteMin( Type &minItem )
{
    if( !isEmpty() )
    {
        minItem = elements[1];
        elements[1] = elements[currentSize--];
        filterDown( 1 );
    }
    else
        handleUnderflow();
}


/**
 * Percolate down the heap, begin at "hole".
 */
template <typename Type>
void PointerHeap<Type>::filterDown( int hole )
{
    int child;
    Type tmp = elements[hole];

    for( ; 2*hole<=currentSize; hole=child )
    {
        child = 2*hole;

        if( child != currentSize && *(elements[child+1]) < *(elements[child]) )
            child++;

        if( *(elements[child]) < *tmp )
            elements[hole] = elements[child];
        else
            break;
    }

    elements[hole] = tmp;
}


/**
 * Percolate up the heap, begin at "hole".
 */
template <typename Type>
void PointerHeap<Type>::filterUp( int hole )
{
    Type tmp = elements[hole];

    for( ; hole>1 && *tmp<*(elements[hole/2]); hole/=2 )
        elements[hole] = elements[hole/2];

    elements[hole] = tmp;
}


/**
 * If the capability of the heap exceeds the initial size, make it double.
 */
template <typename Type>
void PointerHeap<Type>::handleOverflow()
{
    capacity = EXTFACTOR * capacity;

    Type *newArray = new Type[capacity+1];
    if( newArray == NULL )
    {
        cerr << "Out of memory!" << endl;
        exit(1);
    }

    for( int i=1; i<=currentSize; ++i )
        newArray[i] = elements[i];

    delete []elements;
    elements = newArray;
};


/**
 * Handle the error of get element from an empty heap.
 */
template <typename Type>
inline void PointerHeap<Type>::handleUnderflow()
{
    cerr << "The heap is empty!" << endl << endl;
    exit( 1 );
};
