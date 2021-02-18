//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CListControlDataOf.tpp $
//  
//  Owner: Michael Burbidge
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

#ifndef __CListControlDataOf_tpp__
#define __CListControlDataOf_tpp__

// ----- Interface Includes -----

#include "IControlView.h"
#include "ISubject.h"
#include "IListBoxController.h"
#include "IListBoxAttributes.h"

// ----- Implementation Includes -----

#include "widgetid.h"
#include "CListControlDataOf.h"

//========================================================================================
// METHODS CListControlDataOf
//========================================================================================

//----------------------------------------------------------------------------------------
// CListControlDataOf::CListControlDataOf
//----------------------------------------------------------------------------------------

template <class T>
CListControlDataOf<T>::CListControlDataOf(IPMUnknown *boss) :
	CPMUnknown< IListControlDataOf<T> >(boss),
	fItemList()
{
	fItemList.reserve(10);
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::ReadWrite
//----------------------------------------------------------------------------------------
/*
	I wanted to make CListControlDataOf::ReadWrite actually do something useful, but it's hard(i.e. if a PMString changes that affects the readwrite...)
	I've given up for now and proposed a workaround for bug #612830 instead. Something we could try to fix in the future.
	
void SpecializedReadWriteListItem(IDataBase* db, IPMStream *s, void* & thing);
void SpecializedReadWriteListItem(IDataBase* db, IPMStream *s, void* & thing)
{
	ASSERT_FAIL("Dunno how to read/write a void*");
}

void SpecializedReadWriteListItem(IDataBase* db, IPMStream *s, PMString& strRef);
void SpecializedReadWriteListItem(IDataBase* db, IPMStream *s, PMString& strRef)
{
	strRef.ReadPlatformWriteUnicode(s, PMString::kUTF8Encoding);
}

void SpecializedReadWriteListItem(IDataBase* db, IPMStream *s, IControlView* & view);
void SpecializedReadWriteListItem(IDataBase* db, IPMStream *s, IControlView* & view)
{
	if(s->IsWriting())
	{
		UID theUID = ::GetUID(view);
		s->XferReference(theUID);
	}
	else
	{
		UID uid;
		s->XferReference(uid);
		view = (IControlView*)db->Instantiate(uid,IID_ICONTROLVIEW);
	}

}

template <class T>
void CListControlDataOf<T>::ReadWrite(IPMStream *s, ImplementationID prop)
{
	int32 numItems = fItemList.Length();
	s->XferInt32(numItems);
	
	if(s->IsWriting())
	{
		for(int32 i = 0; i < numItems; ++i)
			SpecializedReadWriteListItem(nil,s,fItemList[i]);
	}
	else
	{
		fItemList.Clear();
		for(int32 i = 0; i < numItems; ++i)
		{
			T item;
			SpecializedReadWriteListItem(::GetDataBase(this),s,item);
			ItemAdded(item, IListControlDataOf<T>::kEnd, kFalse);
		}
	}

}*/

template <class T>
void CListControlDataOf<T>::ReadWrite(IPMStream *s, ImplementationID prop)
{
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::Add
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::Add(const T& item, int32 at, bool16 invalidate, bool16 notifyOfChange)
{
	// We have to call ItemAdded() before adding the item to fItemList because
	// ItemAdded() may call CreateSysControl() (via GetSysControl), which in turn 
	// calls IListControlData->Synchronize. Then we will sync the ListControlData
	// (stored in fItemList) with the new system control. 
	// In this case, if we add the item to fItemList first, we will add it to the
	// system control twice (one in ItemAdded and one in Synchronize).
	//	[lxia]		01/26/01 
	ItemAdded(item, at, invalidate);

	if (at == IListControlDataOf<T>::kEnd)
		fItemList.push_back(item);
	else
		fItemList.insert(fItemList.begin() + at, item);
	
	NotifyOfChange(invalidate, notifyOfChange, kListItemAddedMessage);
	//Dirty(this);
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::Add
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::Add(const K2Vector<T>& items, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IListBoxAttributes> attrs(this, IID_ILISTBOXATTRIBUTES);
	
	if (attrs)
		attrs->MuteDrawing(kTrue);
	
	for (typename K2Vector<T>::const_iterator i = items.begin(); i != items.end(); ++i)
		Add(*i, IListControlDataOf<T>::kEnd, invalidate, notifyOfChange);
		
	if (attrs)
		attrs->MuteDrawing(kFalse);

	NotifyOfChange(invalidate, notifyOfChange, kListItemAddedMessage);
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::Remove
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::Remove(int32 index, bool16 invalidate, bool16 notifyOfChange)
{
	fItemList.erase(fItemList.begin() + index);

	ItemRemoved(index, invalidate);
	NotifyOfChange(invalidate, notifyOfChange, kListItemRemovedMessage);
	//Dirty(this);
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::Replace
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::Replace(const T& item, int32 index, bool16 invalidate, bool16 notifyOfChange)
{
	fItemList[index] = item;
	
	ItemReplaced(item, index, invalidate);
	NotifyOfChange(invalidate, notifyOfChange, kListItemContentsChangedMessage);
	//Dirty(this);
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::Clear
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::Clear(bool16 invalidate, bool16 notifyOfChange)
{
	fItemList.clear();
	
	ItemsCleared(invalidate, notifyOfChange);
	NotifyOfChange(invalidate, notifyOfChange, kListItemRemovedMessage);
	//Dirty(this);
}
	
//----------------------------------------------------------------------------------------
// CListControlDataOf::operator[]
//----------------------------------------------------------------------------------------

template <class T>
T CListControlDataOf<T>::operator[](int32 index) const
{
	return fItemList[index];
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::Length
//----------------------------------------------------------------------------------------

template <class T>
int32 CListControlDataOf<T>::Length() const
{
	return static_cast<int32>(fItemList.size());
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::ItemAdded
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::ItemAdded(const T& item, int32 at, bool16 invalidate)
{
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::ItemRemoved
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::ItemRemoved(int32 index, bool16 invalidate)
{
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::ItemReplaced
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::ItemReplaced(const T& item, int32 index, bool16 invalidate)
{
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::ItemsCleared
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::ItemsCleared(bool16 invalidate, bool16 notifyOfChange)
{
}

//----------------------------------------------------------------------------------------
// CListControlDataOf::NotifyOfChange
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::NotifyOfChange(bool16 invalidate, bool16 notifyOfChange, int32 changeMessage)
{
	InterfacePtr<IListBoxAttributes> attrs(this, IID_ILISTBOXATTRIBUTES);
	
	if (attrs && attrs->IsDrawingMuted())
		return;
		
	InterfacePtr<IControlView> view(this, IID_ICONTROLVIEW);
	if (invalidate)
	{	
		if (view)
			view->Invalidate();
	}
	
	if (notifyOfChange)
	{
		InterfacePtr<ISubject> subject(view, IID_ISUBJECT);
		if (subject) 
			subject->Change(changeMessage, IID_ILISTCONTROLDATA);
	}
}
//----------------------------------------------------------------------------------------
// CListControlDataOf::Refresh
//----------------------------------------------------------------------------------------

template <class T>
void CListControlDataOf<T>::Refresh()const
{
}

#endif // __CListControlDataOf_tpp__
