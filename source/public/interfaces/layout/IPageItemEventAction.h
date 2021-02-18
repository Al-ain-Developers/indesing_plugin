//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IPageItemEventAction.h $
//  
//  Owner: Shengliu Dai
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
#ifndef __IPAGEITEMEVENTACTION__
#define __IPAGEITEMEVENTACTION__

#include "IPMUnknown.h"
#include "GenericID.h"

class IEvent;

/** Command-Handler Interface for AutoLayout, provides an interface for page-items to 
	respond to certain events. It is similar to
	EventHandler but it sits in special PageItem bosses (instead of widgets) and only
	responds to certain events. (In fact this interface is introduced for double click 
	on pageitems only, define it this way just for extensibility consideration. )
	It does intend to replace or handle these events.

	The event on pageitems is caught by LayoutEventHandler(IEvent *pEvent), 
	which will ask ILayoutControlViewHelper to QueryHitTestPageItemNew and get 
	the pageitem. From the pageitem get this Interface to do any actions.

	See also IEventHandler.h

	@ingroup layout_auto
	@ingroup layout_pgitem 
  */
class IPageItemEventAction : public IPMUnknown {

	public:
		enum { kDefaultIID = IID_IPAGEITEMEVENTACTION };  // for UseDefaultIID()

		/** Double click the page item.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, 
			kFalse otherwise (pass event to next handler), normally we should
			return kFalse unless we called EventHandler and that return kTrue(handled)
		*/
		virtual bool16 ButtonDblClk(IEvent* e) = 0; 
			 
		/** Triple click with any button.
			@param e event of interest
			@return kTrue if event has been handled and should not be further dispatched, 
			kFalse otherwise (pass event to next handler)
		*/
		virtual bool16 ButtonTrplClk(IEvent* e) = 0;

};


#endif	// __IPAGEITEMEVENTACTION__
