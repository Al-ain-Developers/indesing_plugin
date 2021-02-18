//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DropDownListControlDataOf.tpp $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#ifndef __DropDownListControlDataOf_tpp__
#define __DropDownListControlDataOf_tpp__

#include "IStringListControlData.h"
#include "DropDownListControlDataOf.h"

template <class T>
DropDownListControlDataOf<T>::DropDownListControlDataOf(IPMUnknown* boss) :
	CPMUnknown< IListControlDataOf<T> >(boss)
{
}

template <class T>
DropDownListControlDataOf<T>::~DropDownListControlDataOf()
{
}

template <class T>
void DropDownListControlDataOf<T>::Add(const T& item, int32 at, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IStringListControlData> stringData(this, UseDefaultIID());
	stringData->AddString(GetString(item), at, invalidate, notifyOfChange);
	
	if (at == IListControlDataOf<T>::kEnd)
		fElements.push_back(item);
	else
		fElements.insert(fElements.begin() + at, item);
}

template <class T>
void DropDownListControlDataOf<T>::Add(const K2Vector<T>& items, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IStringListControlData> stringData(this, UseDefaultIID());
	
	for (typename K2Vector<T>::const_iterator i = items.begin(); i != items.end(); i++)
		Add(*i, IListControlDataOf<T>::kEnd, invalidate, notifyOfChange);
}

template <class T>
void DropDownListControlDataOf<T>::Remove(int32 index, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IStringListControlData> stringData(this, UseDefaultIID());
	stringData->RemoveString(index, invalidate, notifyOfChange);
	
	fElements.erase(fElements.begin() + index);
}

template <class T>
void DropDownListControlDataOf<T>::Replace(const T& item, int32 index, bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IStringListControlData> stringData(this, UseDefaultIID());
	stringData->SetString(index, GetString(item), invalidate, notifyOfChange);
	
	fElements[index] = item;
}

template <class T>
void DropDownListControlDataOf<T>::Clear(bool16 invalidate, bool16 notifyOfChange)
{
	InterfacePtr<IStringListControlData> stringData(this, UseDefaultIID());
	stringData->Clear(invalidate, notifyOfChange);
	
	fElements.clear();
}

template <class T>
T DropDownListControlDataOf<T>::operator[](int32 index) const
{
	InterfacePtr<IStringListControlData> stringData(this, UseDefaultIID());
	return fElements[index];
}

template <class T>
int32 DropDownListControlDataOf<T>::Length() const
{
	return fElements.size();
}

template <class T>
void DropDownListControlDataOf<T>::Refresh() const
{
}

template <class T>
void DropDownListControlDataOf<T>::Synchronize(SysControl sysControl) const
{
}

#endif // __DropDownListControlDataOf_tpp__