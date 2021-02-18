//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/AbstractDialogObserver.h $
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
#ifndef __AbstractDialogObserver__
#define __AbstractDialogObserver__

#include "CObserver.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class IPanelControlData;

/**	InDesign selectable dialogs(e.g. the prefs dialog) are made up of multiple independent 'dialogs', each with their own dialog observer.
	However, CDialogObserver provides some functionality that we don't want in the case of a selectable dialog, so each individual
	selectable dialog panel should inherit their observer from AbstractDialogObserver rather than CDialogObserver.

	@see CObserver.h		@see CDialogObserver.h
*/

class WIDGET_DECL AbstractDialogObserver : public CObserver
{
public:	
				AbstractDialogObserver(IPMUnknown *boss);
	virtual		~AbstractDialogObserver();

protected:	
	/** Helper method to make it easy to attach to widget in the dialog. */
	void AttachToWidget(const WidgetID& widgetId, const PMIID& iidOfDataToObserve, IPanelControlData* panel);

	/** Helper method to make it easy to detach from widget in the dialog. */
	void DetachFromWidget(const WidgetID& widgetId, const PMIID& iidOfDataToUnobserve, IPanelControlData* panel);
};

#pragma export off

#endif
