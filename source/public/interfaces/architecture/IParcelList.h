//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IParcelList.h $
//  
//  Owner: dwaterfa
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
#ifndef __IParcelList__
#define __IParcelList__

#include "IPMUnknown.h"
#include "UIDRef.h"
#include "ParcelKey.h"
#include "IParcel.h"

class ITextFrameColumn;


class PUBLIC_DECL IParcelList : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPARCELLIST };

		//
		// ParcelLists are associated with a single FrameList because each
		// Parcel is associated with a single TextFrame.
		//
		virtual UIDRef		GetFrameListRef() const = 0;

		//
		// Returns the number of Parcels in this ParcelList.
		//
		virtual int32		GetParcelCount() const = 0;

		//
		// GetParcelIndex()		Returns the index of the specified Parcel in
		//						the ParcelList or -1 if the Parcel is not part
		//						of the ParcelList.
		//
		// QueryParcel()		Returns the specified Parcel or nil if the
		//
		virtual int32		GetParcelIndex(ParcelKey key) const = 0;
		virtual IParcel*	QueryParcel(ParcelKey key) const = 0;

		//
		// The GetNext...() methods return the Parcel which is the FIRST Parcel
		// at the desired location relative to the specified Parcel. If the
		// specified Parcel is already at the specified location then it will
		// be returned.
		//
		// Note: A Multi-Column Frame is a type of "Box".
		//
		virtual ParcelKey	GetNthParcelKey(int32 index) const = 0;
		virtual ParcelKey	GetFirstParcelKey() const = 0;
		virtual ParcelKey	GetLastParcelKey() const = 0;
		virtual ParcelKey	GetPreviousParcelKey(ParcelKey key) const = 0;
		virtual ParcelKey	GetNextParcelKey(ParcelKey key) const = 0;
		virtual ParcelKey	GetNextBoxParcelKey(ParcelKey key) const = 0;
		virtual ParcelKey	GetNextPageParcelKey(ParcelKey key) const = 0;
		virtual ParcelKey	GetNextEvenPageParcelKey(ParcelKey key) const = 0;
		virtual ParcelKey	GetNextOddPageParcelKey(ParcelKey key) const = 0;

		//
		// Bounds are expressed in an unspecified coordinate system. To place
		// the Parcel in Text Frame coordinates use the matrix returned in
		// GetParcelToFrameMatrix().
		//
		// The actual shape within the Parcel is not available through this
		// interface.
		//
		virtual PMRect		GetParcelBounds(ParcelKey key) const = 0;

		//
		// The UID of the page item boss through which the Parcel is flowing.
		//
		virtual UID			GetParcelFrameUID(ParcelKey key) const = 0;
		virtual ITextFrameColumn*	QueryParcelFrame(ParcelKey key) const = 0;

		//
		// Returns the innerToFrame Matrix.
		//
		virtual PMMatrix	GetParcelToFrameMatrix(ParcelKey key) const = 0;

		//
		// Although invalidation is handled by the IPendingInvals interface
		// on the TextFrame, the Parcel may have information that allows the
		// client to avoid doing the invalidation in the first place. For
		// example:
		//
		//	ParcelKey	key;
		//	PMRect		invalRect;
		//	if (pl->GetParcelAcceptingInvals(key))
		//	{
		//		InterfacePtr<ITextFrameColumn> tfc(pl->QueryParcelFrame(key));
		//		InterfacePtr<IPendingInvals> pi(tfc, UseDefaultIID());
		//		pl->GetParcelToFrameMatrix(key).Transform(&invalRect);
		//		pi->RecordPendingInval(invalRect);
		//	}
		//
		virtual bool16		GetParcelAcceptingPendingInvals(ParcelKey key) const = 0;

		//
		// Iterators
		//
		// It is acceptable to pass in an invalid ParcelKey to begin()/end()/
		// rbegin()/rend(). The resulting iterator will be the same as if the
		// caller had called the end()/rend() methods with no key argument.
		//
		// Iterators do NOT obtain a reference to the underlying ParcelList.
		// It is the responsibility of the caller to maintain that reference
		// over the life of the iterator.
		//
		class const_iterator_helper;
		class const_iterator
		{
		public:
			typedef ParcelKey						value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const ParcelKey*				pointer;
			typedef const ParcelKey&				reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			const_iterator(const_iterator_helper* helper) :
				fHelper(helper)
				{ fKey = fHelper->dereference(); }

			const_iterator(const const_iterator& copy)
				{
				fHelper = copy.fHelper->copy();
				fKey = copy.fKey;
				}

			~const_iterator()
				{ delete fHelper; }

			const ParcelKey&		operator*() const
				{ return fKey; }

			const ParcelKey*		operator->() const
				{ return &fKey; }

			const_iterator&			operator=(const const_iterator& rhs)
				{
				if (this != &rhs)
				{
					delete fHelper;
					fHelper = rhs.fHelper->copy();
					fKey = rhs.fKey;
				}
				return *this;
				}

			const_iterator&			operator++()
				{
				fHelper->increment();
				fKey = fHelper->dereference();
				return *this;
				}

			const_iterator			operator++(int)
				{
				const_iterator tmp = *this;
				fHelper->increment();
				fKey = fHelper->dereference();
				return tmp;
				}

			const_iterator&			operator--()
				{
				fHelper->decrement();
				fKey = fHelper->dereference();
				return *this;
				}

			const_iterator			operator--(int)
				{
				const_iterator tmp = *this;
				fHelper->decrement();
				fKey = fHelper->dereference();
				return tmp;
				}

			bool16					operator==(const const_iterator& rhs) const
				{ return fHelper->equal(rhs.fHelper); }

			bool16					operator!=(const const_iterator& rhs) const
				{ return !(*this == rhs); }

		protected:
			const_iterator_helper*	fHelper;
			ParcelKey				fKey;
		};

		class const_reverse_iterator
		{
		public:
			typedef ParcelKey						value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef const ParcelKey*				pointer;
			typedef const ParcelKey&				reference;
			typedef std::bidirectional_iterator_tag	iterator_category;

			const_reverse_iterator(const_iterator_helper* helper) :
				fIter(helper)
				{ }

			const_reverse_iterator(const const_reverse_iterator& copy) :
				fIter(copy.fIter)
				{ }

			const ParcelKey&		operator*() const
				{ return fIter.operator*(); }

			const ParcelKey*		operator->() const
				{ return fIter.operator->(); }

			const_reverse_iterator&	operator=(const const_reverse_iterator& rhs)
				{ this->fIter = rhs.fIter; return *this; }

			const_reverse_iterator&	operator++()
				{ --fIter; return *this; }

			const_reverse_iterator	operator++(int)
				{
				const_reverse_iterator tmp = *this;
				++fIter;
				return tmp;
				}

			const_reverse_iterator&	operator--()
				{ ++fIter; return *this; }

			const_reverse_iterator	operator--(int)
				{
				const_reverse_iterator tmp = *this;
				--fIter;
				return tmp;
				}

			bool16					operator==(const const_reverse_iterator& rhs) const
				{ return (this->fIter == rhs.fIter); }

			bool16					operator!=(const const_reverse_iterator& rhs)
				{ return !(*this == rhs); }

		private:
			const_iterator	fIter;
		};

		virtual const_iterator			begin() const;
		virtual const_iterator			begin(ParcelKey key) const;
		virtual const_iterator			end() const;
		virtual const_iterator			end(ParcelKey key) const;
		virtual const_reverse_iterator	rbegin() const;
		virtual const_reverse_iterator	rbegin(ParcelKey key) const;
		virtual const_reverse_iterator	rend() const;
		virtual const_reverse_iterator	rend(ParcelKey key) const;

		//
		// Implementation must supply a helper to assist the common iterator
		// code above. Note that this method returns a class from the heap
		// that must be deleted by the caller.
		//
		class const_iterator_helper
		{
		public:
			virtual ~const_iterator_helper() { }
			virtual ParcelKey				dereference() const = 0;
			virtual bool16					equal(const const_iterator_helper* rhs) const = 0;
			virtual void					increment() = 0;
			virtual void					decrement() = 0;
			virtual const_iterator_helper*	copy() const = 0;

		protected:
			const_iterator_helper() { }
			const_iterator_helper(const const_iterator_helper&) { }
		};

		virtual const_iterator_helper*	NewIterHelper(int32 parcelIndex) const = 0;

};

#endif
