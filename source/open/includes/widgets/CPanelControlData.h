//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/CPanelControlData.h $
//  
//  Owner: Frits Habermann
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
#ifndef __CPanelControlData__
#define __CPanelControlData__

#include "AbstractPanelControlData.h"
#include "K2Vector.h"
#include "HelperInterface.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL CPanelControlData : public AbstractPanelControlData
{
public:
	// ----- Initialization -----
	
	CPanelControlData(IPMUnknown *boss);
	virtual ~CPanelControlData();
	
	virtual void			ReadWrite(IPMStream *s, ImplementationID prop);

	// ----- Maintenance -----
	
	virtual void			AddWidget(IControlView *w, int32 at = -1, bool16 invalidate = kTrue); 
	virtual void			RemoveWidget(IControlView *w, bool16 invalidate, bool16 deleteUID); 
	virtual void			RemoveWidget(int32	index, bool16 invalidate, bool16 deleteUID);
	virtual void			MoveWidget(IControlView *w, int32 at, bool16 invalidate = kTrue);
	virtual void			ReleaseAll(bool16 deleteUID);

	// ----- Inquisition -----
	
	virtual IControlView*	GetWidget(int32 index) const;
	virtual bool16			GetWidgetVisibleState(int32 index) const;
	virtual bool16			IsWidgetInstantiated(int32 index) const;
	virtual int32			GetIndex(const IControlView *w) const;
	virtual int32			Length() const;
	
	// ----- Notification -----
	
	virtual void			WidgetAttributeChanged(IControlView* view, const WidgetAttributeID& id);

protected:
	void					AddToWidgetList(IControlView* view, int32 at = -1, bool16 invalidateTransform = kTrue);

protected:
	// ----- Persistent data -----
	
	K2Vector<IControlView *>	fWidgetList;
};

#pragma export off

#endif
