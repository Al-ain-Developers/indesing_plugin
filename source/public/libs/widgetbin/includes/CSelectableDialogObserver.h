//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/CSelectableDialogObserver.h $
//  
//  Owner: Tom Taylor
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
#ifndef __CSelectableDialogObserver__
#define __CSelectableDialogObserver__

#include "CDialogObserver.h"

#ifdef WIDGET_BUILD
#pragma export on
#endif

class IPanelControlData;

/** Implementation (base) class for selectable dialog observers.
		Subclasses should derive from CSelectableDialogObserver, and call the inherited behavior.

		@see CDialogObserver, IObserver
*/
class WIDGET_DECL CSelectableDialogObserver : public CDialogObserver
{
public:
	// ----- Initialization -----
	
						CSelectableDialogObserver(IPMUnknown *boss);
	virtual				~CSelectableDialogObserver();
	
	/** Override to respond to a change in an observed subject. 
			This implementation calls the inherited dialog behavior and handles the selectable dialog's list box
	*/
	virtual void		Update(const ClassID& theChange, ISubject* theSubject, const PMIID &protocol, void* changedBy);

	/**
		Override to attach to the appropriate subject(s).
		This implementation calls the inherited dialog behavior and attaches the selectable dialog's selection list widget.
	*/
	virtual void		AutoAttach();

	/**
		Override to detach from the appropriate subject(s).
		This implementation calls the inherited dialog behavior and detaches the selectable dialog's selection list widget.
	*/
	virtual void		AutoDetach();

protected:
	/** Utility method for getting the index of the selected panel in the dialog. */
	virtual int32		GetSelectedPanelIndex();
};

#pragma export off

#endif
