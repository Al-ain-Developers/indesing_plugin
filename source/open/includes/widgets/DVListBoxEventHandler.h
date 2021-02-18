//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/widgets/DVListBoxEventHandler.h $
//  
//  Owner: Vadim Tkachev
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 2010 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __DVListBoxEventHandler__
#define __DVListBoxEventHandler__
	
#include "DVHostedWidgetEH.h"

class IEvent;

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

class DV_WIDGET_DECL DVListBoxEventHandler : public DVHostedWidgetEH
{
	typedef DVHostedWidgetEH inherited;
public:
	public:
	DVListBoxEventHandler(IPMUnknown *boss);
	virtual ~DVListBoxEventHandler();

	static	bool16	OnlyModifierKeys(IEvent* e, int32 modifierKeys);
	virtual bool16	LButtonDn(IEvent* e);

	virtual bool16 CanHaveKeyFocus() const {	return kTrue;	} 
	virtual void PostGetKeyFocus(); 
	virtual void PostGiveUpKeyFocus(); 
	virtual bool16 KeyDown(IEvent* e);
	virtual bool16 MouseWheel(IEvent* e);
	
protected:	
	enum ListBoxEventType 
	{
		lbNothing = 0,
		lbScroll,
		lbSingleClick,
		lbDoubleClick,
		lbKeyboardFocus
	};

	virtual	bool16	HandleLButtonDn(IEvent* e, int16 whichPartClicked, int32 itemClicked); 
	virtual void	ComputeDragExitRect(int32 itemClicked, SysRect& exitGRect); 
	void InvalidateFocusTrim();

};

#pragma export off

#endif //__DVListBoxEventHandler__
