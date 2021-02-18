//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/hiddentext/HidTxtParcelList.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IParcelList.h"

// General includes:
#include "CPMUnknown.h"
#include "PMRect.h"
#include "PMMatrix.h"
#include "Trace.h"

// Project includes:
#include "HidTxtID.h"

/** Stub IParcelList implementation, display of composed hidden text is not supported.

	
	@ingroup hiddentext
	@see IParcelList
 */
class HidTxtParcelList : public CPMUnknown<IParcelList>
{
	public:
		/** Constructor
			@param boss
		 */
						HidTxtParcelList(IPMUnknown* boss);
		/** Destructor.
		 */
		virtual				~HidTxtParcelList();

		// This is a stub, no documentation comments are provided.
		// See IParcelList for all further information.
	public:
		virtual int32		GetParcelIndex(ParcelKey key) const;
		virtual ParcelKey	GetNthParcelKey(int32 index) const;
		virtual ParcelKey	GetFirstParcelKey() const;
		virtual ParcelKey	GetLastParcelKey() const;
		virtual ParcelKey	GetPreviousParcelKey(ParcelKey key) const;
		virtual ParcelKey	GetNextParcelKey(ParcelKey key) const;
		virtual UIDRef		GetFrameListRef() const;
		virtual int32		GetParcelCount() const;
		virtual IParcel*	QueryParcel(ParcelKey key) const;
		virtual ParcelKey	GetNextBoxParcelKey(ParcelKey key) const;
		virtual ParcelKey	GetNextPageParcelKey(ParcelKey key) const;
		virtual ParcelKey	GetNextEvenPageParcelKey(ParcelKey key) const;
		virtual ParcelKey	GetNextOddPageParcelKey(ParcelKey key) const;			
		virtual PMRect		GetParcelBounds(ParcelKey key) const;
		virtual UID			GetParcelFrameUID(ParcelKey key) const;
		virtual ITextFrameColumn*	QueryParcelFrame(ParcelKey key) const;
		virtual PMMatrix	GetParcelToFrameMatrix(ParcelKey key) const;
		virtual bool16		GetParcelAcceptingPendingInvals(ParcelKey key) const;
		// begin, rbegin, end, rend all create dummy iterator helper
		virtual const_iterator			begin() const;
		virtual const_iterator			begin(ParcelKey key) const;
		virtual const_iterator			end() const;
		virtual const_iterator			end(ParcelKey key) const;
		virtual const_reverse_iterator	rbegin() const;
		virtual const_reverse_iterator	rbegin(ParcelKey key) const;
		virtual const_reverse_iterator	rend() const;
		virtual const_reverse_iterator	rend(ParcelKey key) const;
		virtual const_iterator_helper*	NewIterHelper(int32 parcelIndex) const;

		/** Stub iterator helper class.
		 */
		class dummyHelper : public IParcelList::const_iterator_helper
		{
		public:
			dummyHelper(const IParcelList* pl, int32 parcelCount, int32 index) :
				fPL(pl), fParcelCount(parcelCount), fIndex(index)
				{
				}

			virtual ParcelKey				dereference() const
				{
				return ParcelKey();
				}

			/** A key method to force begin and end (rbegin and rend) iterators
				to be the same objects so no iteration will occur for this 
				parcel-less owned item.  Return kTrue always.
			 */
			virtual bool16					equal(const const_iterator_helper* rhs) const
				{
				return kTrue;
				}

			virtual void					increment()
				{
				return;
				}

			virtual void					decrement()
				{
				return;
				}

			virtual const_iterator_helper*	copy() const
				{
				return new dummyHelper(fPL, fParcelCount, fIndex);
				}

			const IParcelList*	fPL;
			int32				fParcelCount;
			int32				fIndex;
		};
};

/* Make implementation available to the application.
*/
CREATE_PMINTERFACE(HidTxtParcelList, kHidTxtParcelListImpl)

/*
*/
HidTxtParcelList::HidTxtParcelList(IPMUnknown* boss) : CPMUnknown<IParcelList>(boss)
{
	TRACEFLOW("HiddenText", "HidTxtParcelList::Constructor()-->In/Out\n");
}

/*
*/
HidTxtParcelList::~HidTxtParcelList()
{
	TRACEFLOW("HiddenText", "HidTxtParcelList::Destructor()-->In/Out\n");
}

/*
*/
int32		HidTxtParcelList::GetParcelIndex(ParcelKey key) const
{
	return 0;
}

/*
*/
ParcelKey	HidTxtParcelList::GetNthParcelKey(int32 index) const 
{
	return ParcelKey();
}

/*
*/
ParcelKey	HidTxtParcelList::GetFirstParcelKey() const 
{
	return ParcelKey();
}

/*
*/
ParcelKey	HidTxtParcelList::GetLastParcelKey() const 
{
	return ParcelKey();
}

/*
*/
ParcelKey	HidTxtParcelList::GetPreviousParcelKey(ParcelKey key) const 
{
	return ParcelKey();
}

/*
*/
ParcelKey	HidTxtParcelList::GetNextParcelKey(ParcelKey key) const 
{
	return ParcelKey();
}

/*
*/
UIDRef			HidTxtParcelList::GetFrameListRef() const
{
	return UIDRef(nil, kInvalidUID);
}

/*
*/
int32			HidTxtParcelList::GetParcelCount() const
{
	return 0;
}

/*
*/
IParcel*		HidTxtParcelList::QueryParcel(ParcelKey key) const
{
	return nil;
}

/*
*/
ParcelKey			HidTxtParcelList::GetNextBoxParcelKey(ParcelKey key) const
{
	return ParcelKey();
}

/*
*/
ParcelKey			HidTxtParcelList::GetNextPageParcelKey(ParcelKey key) const
{
	return ParcelKey();
}

/*
*/
ParcelKey			HidTxtParcelList::GetNextEvenPageParcelKey(ParcelKey key) const
{
	return ParcelKey();
}

/*
*/
ParcelKey			HidTxtParcelList::GetNextOddPageParcelKey(ParcelKey key) const
{
	return ParcelKey();
}

/*
*/
PMRect		HidTxtParcelList::GetParcelBounds(ParcelKey key) const
{
	return PMRect();
}

/*
*/
UID			HidTxtParcelList::GetParcelFrameUID(ParcelKey key) const
{
	return kInvalidUID;
}

/*
*/
ITextFrameColumn*	HidTxtParcelList::QueryParcelFrame(ParcelKey key) const
{
	return nil;
}

/*
*/
PMMatrix	HidTxtParcelList::GetParcelToFrameMatrix(ParcelKey key) const
{
	return PMMatrix();	// identity
}

/*
*/
bool16		HidTxtParcelList::GetParcelAcceptingPendingInvals(ParcelKey key) const
{
	return kFalse;
}

/*
*/
IParcelList::const_iterator			HidTxtParcelList::begin() const
{
	return IParcelList::const_iterator(this->NewIterHelper(0));
}

/*
*/
IParcelList::const_iterator			HidTxtParcelList::begin(ParcelKey key) const
{
	return IParcelList::const_iterator(this->NewIterHelper(0));
}

/*
*/
IParcelList::const_iterator			HidTxtParcelList::end() const
{
	return IParcelList::const_iterator(this->NewIterHelper(0));
}

/*
*/
IParcelList::const_iterator			HidTxtParcelList::end(ParcelKey key) const
{
	return IParcelList::const_iterator(this->NewIterHelper(0));
}

/*
*/
IParcelList::const_reverse_iterator	HidTxtParcelList::rbegin() const
{
	return IParcelList::const_reverse_iterator(this->NewIterHelper(0));
}

/*
*/
IParcelList::const_reverse_iterator HidTxtParcelList::rbegin(ParcelKey key) const
{
	return IParcelList::const_reverse_iterator(this->NewIterHelper(0));
}

/*
*/
IParcelList::const_reverse_iterator HidTxtParcelList::rend() const
{
	return IParcelList::const_reverse_iterator(this->NewIterHelper(0));
}

/*
*/
IParcelList::const_reverse_iterator HidTxtParcelList::rend(ParcelKey key) const
{
	return IParcelList::const_reverse_iterator(this->NewIterHelper(0));
}

/*
*/
IParcelList::const_iterator_helper*	HidTxtParcelList::NewIterHelper(int32 parcelIndex) const
{
	return new dummyHelper(this, this->GetParcelCount(), parcelIndex);
}

// End, HidTxtParcelList.cpp
