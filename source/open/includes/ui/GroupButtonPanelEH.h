//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/ui/GroupButtonPanelEH.h $
//  
//  Owner: 
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
//  Copyright 2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this
//  file in accordance with the terms of the Adobe license agreement
//  accompanying it. If you have received this file from a source
//  other than Adobe, then your use, modification, or distribution of
//  it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __GroupButtonPanelEH__
#define __GroupButtonPanelEH__

#include "DVControlEventHandler.h"
#ifdef WIDGET_BUILD 
#pragma export on 
#endif 

class WIDGET_DECL GroupButtonPanelEH : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
public:
	typedef enum { 
		kNextWidget = 0,		// next widget in the group
		kPreviousWidget = 1,	// previous widget in the group
		kUpWidget = 2,			// up a row in the group
		kDownWidget = 3,		// down a row in the group
		kDisabledWidget = 4 }	// usually next widget, previous widget if at end
	FocusDirection;

	typedef enum { kFocusOn = 0, kFocusOff = 1 } FocusAction;

				GroupButtonPanelEH(IPMUnknown *boss);
	virtual		~GroupButtonPanelEH();

	virtual bool16		CanHaveKeyFocus() const;
	virtual bool16		KeyDown(IEvent* e); 

	virtual bool16		WantsTabKeyFocus() const { return CanHaveKeyFocus(); }
protected:
	virtual void		PostGetKeyFocus();
	virtual void		PostGiveUpKeyFocus();

protected:
	virtual void		SetFocusToNextWidget(FocusDirection);
	virtual void		GetNextFocusWidgetIndex(FocusDirection direction, int32& currentFocusIndex);
	virtual void		InvalidateFocus(FocusAction);
	virtual void		SendEventToFocusWidget();

	virtual void		ReleaseKeyBoardFocus();
	virtual void		AcquireKeyBoardFocus();

	virtual void		CountRowsAndColumns();

	virtual IControlView*	GetFocusWidget()	{ return fCurrentFocusWidget; }
	virtual void		SetFocusWidget(IControlView* focusView)	{ fCurrentFocusWidget = focusView; }

protected:
	IControlView*		fCurrentFocusWidget;
	int32				fNumRows, fNumColumns;
};

// This class would not be necessary if all the users of it had cluster controllers.
// Not sure if this would work though for all Object Styles users since they may have an "unknown" state.
class WIDGET_DECL GroupASSButtonFocusPanelEH : public GroupButtonPanelEH 
{
public:
	GroupASSButtonFocusPanelEH(IPMUnknown *boss);
	virtual ~GroupASSButtonFocusPanelEH();
	virtual bool16		CanHaveKeyFocus() const;
protected:
	virtual void		GetNextFocusWidgetIndex(FocusDirection direction, int32& currentFocusIndex);
};

#endif
