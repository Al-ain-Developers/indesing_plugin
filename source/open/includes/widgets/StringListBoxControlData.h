//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/StringListBoxControlData.h $
//  
//  Owner: Bob Freeman
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __StringListBoxControlData_h__
#define __StringListBoxControlData_h__

#include "IStringListBoxControlData.h"
#include "K2Vector.h"
#include "CPMUnknown.h"

class WIDGET_DECL StringListBoxControlData : public CPMUnknown<IStringListBoxControlData>
{
public:
	StringListBoxControlData(IPMUnknown *boss);
	virtual ~StringListBoxControlData() {}
	
	void ReadWrite(IPMStream *s, ImplementationID prop);

	// ----- List maintainence -----

  	virtual void		Add(const PMString& item, int32 at, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Add(const K2Vector<PMString>& items, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Remove(int32 index, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Replace(const PMString& item, int32 index, bool16 invalidate, bool16 notifyOfChange);
	virtual void		Clear(bool16 invalidate, bool16 notifyOfChange);
	
	// ----- List query -----
	
	virtual PMString	operator[](int32 index) const;
	virtual int32		GetIDAt(int32 index) const;
	virtual int32		Length() const;

protected:
	virtual void		NotifyOfChange(bool16 invalidate, bool16 notifyOfChange, int32 changeMessage);
	virtual void		Refresh() const;
	virtual void		Synchronize(SysControl sysControl) const;

private:
	mutable K2Vector<PMString>			fItemList;
	mutable K2Vector<int32>			fItemIDList;
	int32							fNextID;
};

#endif
