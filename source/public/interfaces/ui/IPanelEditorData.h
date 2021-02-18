//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanelEditorData.h $
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
#ifndef __IPanelEditorData_h__
#define __IPanelEditorData_h__

#include "IPMUnknown.h"
#include "K2Vector.h"

class IEventHandler;
class IControlView;

class IPanelEditorData : public IPMUnknown
{
public:
	virtual IEventHandler*	GetEventHandler() const = 0;
	
	// ----- Selection methods -----
	
	virtual void			ClearSelection() = 0;
	virtual void			AddToSelection(IControlView* selectedView) = 0;
	virtual void			RemoveFromSelection(IControlView* selectedView) = 0;
	virtual int32			SelectionSize() const = 0;
	virtual IControlView*	GetNthSelectedView(int32 i) const = 0;
	virtual int32			GetSelectionSerialNumber() const = 0;
	virtual bool16			IsViewSelected(IControlView* view) const = 0;
	virtual void			InvalidateSelection() = 0;
	virtual const K2Vector<IControlView*>& GetSelectedViews() const = 0;

	// ----- Editor state -----
	
	virtual void			SetEditorOn(bool16 on = kTrue) = 0;
	virtual bool16			IsEditorOn() const = 0;
	
	virtual int32			GetActionCount() const = 0;
	virtual void			IncrementActionCount() = 0;
};

#endif // __IPanelEditorData_h__

