//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CData.tpp $
//  
//  Owner: Mat Marcus
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

#ifndef __CDatatpp__
#define __CDatatpp__

#include "CommandID.h"
#include "IData.h"
#include "CPMUnknown.h"

template <class T>
class CData : public CPMUnknown<IData<T> >
{
	typedef CPMUnknown<IData<T> > Inherited;
public:
	CData(IPMUnknown*);
	virtual const T& Get() const;
	virtual void Set(const T&);
private:
	T fData;
};


template <class T>
CData<T>::CData(IPMUnknown *boss) : Inherited(boss), fData()
{
}


template <class T>
const T& CData<T>::Get() const
{
	return fData;
}


template <class T>
void CData<T>::Set(const T& data) 
{
	fData = data;
}





#endif // __CDatatpp__
