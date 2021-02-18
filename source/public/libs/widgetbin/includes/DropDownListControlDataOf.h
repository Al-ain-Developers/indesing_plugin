//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/DropDownListControlDataOf.h $
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

#pragma once
#ifndef __DropDownListControlDataOf_h__
#define __DropDownListControlDataOf_h__

#include "IListControlDataOf.h"
#include "CPMUnknown.h"

template <class T>
class DropDownListControlDataOf : public CPMUnknown< IListControlDataOf<T> >
{
public:
	DropDownListControlDataOf(IPMUnknown* boss);
	virtual ~DropDownListControlDataOf();
	
  	virtual void		Add(const T& item, int32 at, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Add(const K2Vector<T>& items, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Remove(int32 index, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Replace(const T& item, int32 index, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Clear(bool16 invalidate, bool16 notifyOfChange);

	virtual T			operator[](int32 index) const;
	virtual int32		Length() const;

	virtual void		Refresh() const;
	virtual void		Synchronize(SysControl sysControl) const;

private:
	PMString			GetString(const T& item) const;
	
private:
	K2Vector<T>			fElements;
};

#ifdef _INCLUDE_TPP_IN_H_
	#include "DropDownListControlDataOf.tpp"
#endif //_INCLUDE_TPP_IN_H_

#endif // __DropDownListControlDataOf_h__