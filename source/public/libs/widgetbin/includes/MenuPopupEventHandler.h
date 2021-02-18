//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/MenuPopupEventHandler.h $
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
#ifndef __MenuPopupEventHandler__
#define __MenuPopupEventHandler__

#include "DVControlEventHandler.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class WIDGET_DECL MenuPopupEventHandler : public DVControlEventHandler
{
	typedef DVControlEventHandler inherited;
public:
	MenuPopupEventHandler(IPMUnknown *boss);
	~MenuPopupEventHandler();
	
	virtual bool16 LButtonDn(IEvent* e) ; //Override
	
	virtual bool16 LButtonUp(IEvent* e) ; //Override

	virtual bool16 ButtonTrplClk(IEvent* e) ; //Override
	
	virtual bool16 ButtonQuadClk(IEvent* e)	 ; //Override
	
	virtual bool16 ButtonQuintClk(IEvent* e) ; //Override

	virtual bool16 KeyDown(IEvent* e) ; //Override
	
private:
	void	SetWorkingPanelRef ();
	
	bool16	IsInTabbedPalette ();
	UIDRef	GetPanelInTabbedPalette ();
	UIDRef	GetParentPanel ();
};


#pragma export off

#endif
