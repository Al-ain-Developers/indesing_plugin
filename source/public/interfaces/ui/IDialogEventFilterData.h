//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IDialogEventFilterData.h $
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
#ifndef __IDialogEventFilterData__
#define __IDialogEventFilterData__

#include "IPMUnknown.h"
#include "widgetid.h"

class IWindow;

/** Data interface for Dialog event filters (retains the dialog state for the event filter).
		Found on dialog event filter bosses (see kDialogEventFilterBoss).
*/
class IDialogEventFilterData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDIALOGEVENTFILTERDATA };

	/** Set the dialog window */
	virtual void		SetWindow(IWindow* window) = 0;
	/** Get the dialog window */
	virtual IWindow*	GetWindow() const = 0;
	
	/** Set the dialog window's modality */
	virtual void		SetModal(bool16 modal) = 0;
	/** Get the dialog window's modality */
	virtual bool16		IsModal() const = 0;
};

#endif
