//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ICursorProvider.h $
//  
//  Owner: Dave Burnard
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
#ifndef __ICursorProvider__
#define __ICursorProvider__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "CursorDefs.h"
#include "CursorID.h"
#include "ICursorMgr.h"

class IWindow;

/** Provides an interface for obtaining cursors while tracking the mouse.
	Used by the application, to figure out how to set the mouse cursor, 
	and used by the windows, views, and tools to provide the cursors that
	should be used for different areas of the screen.
	
	@see also ICursorMgr, ICursorRegion
*/ 
class ICursorProvider : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICURSORPROVIDER };

	/** Called when mouse enters a region assigned to this provider,
		returns the CursorSpec describing the cursor to be displayed. 
		This method is also called periodically if the provider requests
		additional control by returning kTrue from either of the methods below.
		@param viewUnderMouse IN view the cursor is currently over
		@param globalLocation IN current location of mouse
		@param modifiers IN state of keyboard modifiers
		@return CursorSpec describing the cursor to be displayed
	*/
	virtual CursorSpec	GetCursor(  IControlView* viewUnderMouse, const SysPoint globalLocation, ICursorMgr::eCursorModifierState modifiers) const =0;
	

	/** Called to determine if cursor can be affected by mouse location
		when in the given region.
		If true, GetCursor will be called whenever the mouse
		moves while inside the region assigned to this provider.
		@param cursorRgn IN
		@return kTrue if cursor can be affected by mouse location, kFalse otherwise
	*/
	virtual bool16	LocationAffectsCursor(SysRgn cursorRgn) const =0;
		

	/** Called to determine if cursor can be affected by modifier keys
		when in the given region.
		If true, GetCursor will be called periodically whenever the modifiers
		change while the mouse is inside the region assigned to this provider.
		@param cursorRgn IN
		@return kTrue if cursor can be affected by modifier keys
		when in the given region, kFalse otherwise
	*/
	virtual bool16	ModifiersAffectCursor(SysRgn cursorRgn) const =0;
		
		
	/** Called to determine if this provider can be affected by the tool lock state,
		used for read-only or locked pubs. 
		Most tools can be locked, however, some like the zoom tool cannot.
		@return kTrue if this provider can be affected by the tool lock state, kFalse otherwise
	*/
	virtual bool16	HasLockedState() const =0;
		
		
	/** Called to set the single cursor that the simplest type of cursor providers return
		This call will assert if used on non-simple providers, know your provider!
		@param cursor IN the sursor spec to be used
	*/
	virtual void SetSingleCursor(const CursorSpec&) = 0;
	
};

#endif // __ICursorProvider__
