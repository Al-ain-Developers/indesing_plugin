//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IControlViewObservers.h $
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
//  
//  ADOBE CONFIDENTIAL
//  
//========================================================================================

#pragma once
#ifndef __IControlViewObservers_h__
#define __IControlViewObservers_h__

#include "IPMUnknown.h"
#include "widgetid.h"

class IControlView;

/** IControlViewObservers can  be called in place of IObserver::AutoAttach() and IObserver::AutoDetach().
	CControlView actually does this.  Of course this interface can be repurposed in any way you see fit.
*/
class IControlViewObservers : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ICONTROLVIEWOBSERVERS };  // for UseDefaultIID()
		
	/** Called when the control is being attached, for example CControlView::DoAutoAttach()
	@param view IN The control
	*/
	virtual void					OnDoAutoAttach(IControlView* view) = 0;
	
	/** Call when the control is being detached, for example CControlView::DoAutoDetach
	@param view IN The Control
	*/
	virtual void					OnDoAutoDetach(IControlView* view) = 0;	

									
};

#endif // __IControlViewObservers_h__
