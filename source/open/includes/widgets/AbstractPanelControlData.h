//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/AbstractPanelControlData.h $
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
#ifndef __AbstractPanelControlData_h__
#define __AbstractPanelControlData_h__

#include "IPanelControlData.h"
#include "HelperInterface.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

//========================================================================================
// CLASS AbstractPanelControlData
//========================================================================================

class DV_WIDGET_DECL AbstractPanelControlData : public IPanelControlData
{
public:
	// ----- Initialization -----
	
	AbstractPanelControlData(IPMUnknown *boss);
	virtual ~AbstractPanelControlData();
	
	// ----- Inquisition -----
	
	virtual IControlView*	FindWidget(const WidgetID& widgetId, int16 searchLevels = 9999) const;
	virtual IControlView*	FindWidget(const SysPoint& windowPt, int16 searchLevels = 9999) const;

	// ----- Keyboard Focus ----
	virtual void			SetKeyboardFocus(const WidgetID& widgetId);
	virtual void			SetKeyboardFocus(const IControlView* widgetId);

protected:
	virtual IControlView*	QueryWidget(IDataBase* dataBase, const UID& uid);
	virtual void 			WidgetInstantiated(IControlView *w);
	virtual void 			WidgetReleased(IControlView *w);

protected:
	void					ChangeWidgetParent(IPMUnknown* newParent, IControlView *widget, bool16 invalidateTransform = kTrue);
	void					NormalizeBBox(PMRect &bbox);

protected:	
	// ----- Nonpersistent data -----
	
	IDataBase*						fDataBase;

DECLARE_HELPER_METHODS()
};

#pragma export off

#endif
