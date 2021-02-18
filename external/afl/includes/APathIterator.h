//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/APathIterator.h $
//  
//  Owner: Michael Easter
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __APathIterator__
#define __APathIterator__

// ----- Includes -----
#include "AFLDecl.h"
#include "APathComponent.h"
#include "ATypes.h"

namespace adobe {
namespace afl {

class APathIteratorImpl;

/**
 Random-access iterator used to iterate over the components of a path.
 @see APath
 @see APathComponent
 */
class AFL_DECL APathIterator
{
public:
	typedef std::random_access_iterator_tag iterator_category;
	typedef APathComponent	value_type;
	typedef APathComponent*	pointer;
	typedef APathComponent&	reference;
	typedef int32			difference_type;
	typedef uint32			size_type;

	/**
	 Copy constructor.
	 Constructs an APathIterator object that is a copy of the given path iterator.
	 @param iter	IN Path iterator to copy.
	 */
	APathIterator(const APathIterator& iter);

	/**
	Destructor.
	Destroys the APathIterator object. */
	virtual ~APathIterator();

	/**
	 Assignment operator.
	 Assigns the given path iterator to this path iterator.
	 @param rhs	IN Iterator to assign to this iterator.
	 @return Reference to this path iterator.
	 */
	APathIterator& operator=(const APathIterator& rhs);

	/**
	 Equality operator.
	 Test whether this iterator and the given iterator are positioned on the same path component.
	 @param rhs	IN Iterator to test for position equality against this iterator.
	 @return True if the iterators are positioned on the same component, else false.
	 */
	bool operator==(const APathIterator& rhs) const;

 	/**
	 Non-equality operator.
	 Test whether this iterator and the given iterator are positioned on different path components.
	 @param rhs	IN Iterator to test for position non-equality against this iterator.
	 @return True if the iterators are positioned on different components, else false.
	 */
	bool operator!=(const APathIterator& rhs) const;

	/**
	 Greater than operator.
	 Tests whether the position of this iterator succeeds the position of the given iterator.
	 @param rhs	IN Path iterator to test against this iterator.
	 @return True if this iterator's position succeeds the given iterator's position, else false.
	 */
	bool operator>(const APathIterator& rhs) const;

	/**
	 Greater than or equal to operator.
	 Tests whether the position of this iterator succeeds or is equal to the position of the given iterator.
	 @param rhs	IN Path iterator to test against this iterator.
	 @return True if this iterator's position succeeds or is equal to the given iterator's position,
			 else false.
	 */
	bool operator>=(const APathIterator& rhs) const;

	/**
	 Less than operator.
	 Tests whether the position of this iterator precedes the position of the given iterator.
	 @param rhs	IN Path iterator to test against this iterator.
	 @return True if this iterator's position precedes the given iterator's position, else false.
	 */
	bool operator<(const APathIterator& rhs) const;

	/**
	 Less than or equal to operator.
	 Tests whether the position of this iterator precedes or is equal to the position of the given iterator.
	 @param rhs	IN Path iterator to test against this iterator.
	 @return True if this iterator's position precedes or is equal to the given iterator's position,
			 else false.
	 */
	bool operator<=(const APathIterator& rhs) const;

	/**
	 Difference operator.
	 Returns the difference between the position of this iterator and the given iterator.
	 @param rhs	IN Path iterator to get the difference in position from.
	 @return Difference between this iterator's position and the given iterator's position.
	 */
	int32 operator-(const APathIterator& rhs) const;

	/**
	 Element access operator.
	 Gets the path component at the given position.
	 @param position	IN Position of the path component to retrieve.
	 @return Const reference to the path component at the given position.
	 */
	const APathComponent& operator[](uint32 position) const;

	/**
	 Dereference operator.
	 Returns a reference to the path component the iterator is positioned on.
	 @return Const reference to the path component the iterator is positioned on.
	 */
	const APathComponent& operator*() const;

	/**
	 Pointer operator.
	 Returns a pointer to the path component the iterator is positioned on.
	 @return Const pointer to the path component the iterator is positioned on.
	 */
	const APathComponent* operator->() const;

	/**
	 Preincrement operator.
	 Positions the iterator on the next component in the path.
	 @return Reference to this path iterator.
	 */
	APathIterator& operator++();

	/**
	 Postincrement operator.
	 Positions the iterator on the next component in the path.
	 @return Copy of this path iterator positioned before the increment.
	 */
	APathIterator operator++(int);

	/**
	 Addition operator.
	 Increments a copy of the iterator by the given number of positions.
	 @param nPositions	IN Number of positions to increment the iterator copy.
	 @return Copy of this path iterator.
	 */
	APathIterator operator+(int32 nPositions) const;

	/**
	 Addition operator.
	 Increments the iterator by the given number of positions.
	 @param rhs	IN Number of positions to increment the iterator.
	 @return Reference to this path iterator.
	 */
	APathIterator& operator+=(int32 nPositions);

	/**
	 Predecrement operator.
	 Positions the iterator on the previous component in the path.
	 @return Reference to this path iterator.
	 */
	APathIterator& operator--();

	/**
	 Postdecrement operator.
	 Positions the iterator on the previous component in the path.
	 @return Copy of this path iterator positioned before the decrement.
	 */
	APathIterator operator--(int);

	/**
	 Subtraction operator.
	 Decrements a copy of the iterator by the given number of positions.
	 @param nPositions	IN Number of positions to decrement the iterator copy.
	 @return Copy of this path iterator.
	 */
	APathIterator operator-(int32 nPositions) const;

	/**
	 Subtraction operator.
	 Decrements the iterator by the given number of positions.
	 @param nPositions	IN Number of positions to decrement the iterator.
	 @return Reference to this path iterator.
	 */
	APathIterator& operator-=(int32 nPositions);

	// Override new and delete operators
	void* operator new(size_t size);
	void operator delete(void* p);
	void* operator new[](size_t size);
	void operator delete[](void* p);
	void* operator new(size_t, void* p) { return p; }
	void operator delete (void*, void*) {} 

private:
	friend class APath;
	APathIterator(APathIteratorImpl* pImpl);

	APathIteratorImpl* fpImpl;
};

}	// namespace afl
}	// namespace adobe

#endif	// __APathIterator__
