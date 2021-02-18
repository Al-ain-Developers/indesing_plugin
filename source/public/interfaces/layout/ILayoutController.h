//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/ILayoutController.h $
//  
//  Owner: jargast
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
//  This interface provides hints to the layoutwidget on what has been invalidated.
//  This interface tells the layout widget whether or not selection is the only
//  thing that has changed.  If that is the case, the layout widget can make some
//  optimizations for screen refreshing.
//  
//  All page items should use this interface instead of IControlView for invalidates
//  of the layout widget.
//  All objects that change the content (such as panorama for scrolling) should use
//  this interface instead of IControlView for invalidates of the layout widget.
//  
//========================================================================================

#pragma once
#ifndef __ILayoutController__
#define __ILayoutController__

#include "IPMUnknown.h"
#include "LayoutUIID.h"

class PMRect;

class ILayoutController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ILAYOUTCONTROLLER };

	/**
	@Deprecated This API is deprecated. Please Use UpdateEnableWithAsyncInval() instead.
	// Enable/Disable view updating.  If false, all invalidate calls are logged but the window
	// should not update.
	*/
	virtual void 	UpdateEnable (bool16 bEnable) = 0;

	virtual bool16	IsUpdateEnabled() const = 0;
	
	// Enable/Disable offscreen drawing.  
	virtual void 	OffscreenEnable (bool16 bEnable) = 0;
	virtual bool16	IsOffscreenEnabled() const = 0;
	
	// Invalidate the content.  This tells the layout widget to regenerate the background
	// bitmap (if it is using offscreen updating).  If invalidRect is nil it invalidates the
	// entire view. If systemInvalOK is true and updates are enabled,then a System inval will
	// occur.
	virtual void 	InvalidateContent(const PMRect* invalidRect = nil, bool8 systemInvalOK = kTrue) = 0;
	virtual void 	InvalidateContent(const SysRgn invalidRgn, bool8 systemInvalOK = kTrue) = 0;
	virtual SysRgn 	GetInvalidContentRgn() const = 0; // client must dispose of result
	virtual void	ValidateContent() = 0;
	
	// Invalidates the selection only.  This tells the layout widget that the background widget
	// is ok to reuse and only the selection has changed.
	virtual void 	InvalidateSelection(const PMRect* invalidRect = nil, bool8 systemInvalOK = kTrue) = 0;
	virtual void 	InvalidateSelection(const SysRgn invalidRgn, bool8 systemInvalOK = kTrue) = 0;
	virtual SysRgn 	GetInvalidSelectionRgn() const = 0;	// client must dispose of result
	virtual void	ValidateSelection() = 0;

	// Returns the union of selection and content.  
	virtual PMRect 	GetInvalidBounds() const = 0;
	virtual SysRgn 	GetInvalidRgn() const = 0;	// client must dispose of result
	virtual void	DocumentChanged() = 0;

	// Enable/Disable view updating.  If false, all invalidate calls are logged but the window
	// should not update.
	// Note: invals during drawing are dropped on Cocoa, so when re-enabling updates,
	//	set doAsynchInvalOnMac to schedule any pending invals.
	virtual void 	UpdateEnableWithAsyncInval (bool16 bEnable, bool16 doAsynchInvalOnMac = kFalse) = 0;
};

#endif
