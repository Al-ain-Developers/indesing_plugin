//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IKit.h $
//  
//  Owner: Matt Ramme
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
//  Purpose of interface:
//  Provide a mechanism for plugins to define what kind of views they have.  
//  This interface and the default implementation should be put onto the 
//  the current boss for the panel's control view.  It will read information
//  from the resources on creation.
//  
//========================================================================================

#pragma once
#ifndef __IKit__
#define __IKit__

#include "IPMUnknown.h"
#include "widgetid.h"

class PMRect;
class IControlView;

class IKit : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IKIT };

	/** Gets the KitViewID of the currently active view
		@return KitViewID of active view
	*/
	virtual KitViewID		GetActiveViewID() const = 0;

	/** Gets the currently active view
		@return IControlView associated with active view
	*/
	virtual IControlView*	QueryActiveView() const = 0;

	/** Make this kit activate 'viewType'
		@param viewType	identifier associated with the view
		@return kTrue if view successfully activated
	*/
	virtual bool16			ActivateView(KitViewID viewType) = 0;

	/** Ask the kit if it can display 'viewType'
		@param viewType	identifier associated with the view
		@return kTrue if kit can display 'viewType'
	*/
	virtual bool16			HasView(KitViewID viewType) const = 0;

	/** Return the bounds (0,0 based) of the 'viewType'.  Should call HasView first
		@param viewType	identifier associated with the view
		@return bounds of view
	*/
	virtual PMRect			GetBounds(KitViewID viewType) const = 0;

	/** Return whether the 'viewType' is resizeable.  Should call HasView first
		@param viewType	identifier associated with the view
		@return kTrue if view is resizeable
	*/
	virtual bool16			IsViewResizeable(KitViewID viewType) const = 0;

	/** iterating kit views
	*/
	virtual int32			GetNumViews() const = 0;
	virtual KitViewID		GetNthView(int32 n) const = 0;	
};


#endif


