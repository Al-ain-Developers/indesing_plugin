//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CListControlDataOf.h $
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

#pragma once
#ifndef __CListControlDataOf_h__
#define __CListControlDataOf_h__

#include "IListControlDataOf.h"
#include "K2Vector.h"
#include "CPMUnknown.h"

//========================================================================================
// TEMPLATE CListControlDataOf
//========================================================================================

template <class T>
class CListControlDataOf : public CPMUnknown< IListControlDataOf<T> >
{
public:
	CListControlDataOf(IPMUnknown *boss);
	virtual ~CListControlDataOf() {}
	
	void ReadWrite(IPMStream *s, ImplementationID prop);

	// ----- List maintainence -----

  	virtual void		Add(const T& item, int32 at, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Add(const K2Vector<T>& items, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Remove(int32 index, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Replace(const T& item, int32 index, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Clear(bool16 invalidate, bool16 notifyOfChange);
	
	// ----- List query -----
	
	virtual T			operator[](int32 index) const;
	virtual int32		Length() const;
	virtual void		Refresh() const;

protected:
	virtual void		ItemAdded(const T& item, int32 at, bool16 invalidate);
	virtual void		ItemRemoved(int32 index, bool16 invalidate);
	virtual void		ItemReplaced(const T& item, int32 index, bool16 invalidate);
	virtual void		ItemsCleared(bool16 invalidate, bool16 notifyOfChange);

	virtual void		NotifyOfChange(bool16 invalidate, bool16 notifyOfChange, int32 changeMessage);
	
private:
	mutable K2Vector<T>			fItemList;
};
#ifdef _INCLUDE_TPP_IN_H_
	#include "CListControlDataOf.tpp"
#endif //_INCLUDE_TPP_IN_H_

#endif // __CListControlDataOf_h__
