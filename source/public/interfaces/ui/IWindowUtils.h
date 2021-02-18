//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IWindowUtils.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IWindowUtils__
#define __IWindowUtils__

#include "widgetid.h"
#include "IPMUnknown.h"
#include "Utils.h"

class IWindow;
class IDataBase;
class AcquireModalDialogState;
class IDialog;
class IDocumentPresentation;

/**	Utility interface for doing a few useful things with windows.
	use like so:
	<pre>
	Utils<IWindowUtils>()->QueryWindowUnderPoint( ... );
	</pre>
*/
class IWindowUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IWINDOWUTILS };

	/**	Returns window under given point, or nil if no IWindow is under it (ignores if bSkipIgnoreables 
		is kTrue and the window's boss has an IID_IIGNOREABLEWINDOW interface containing a kTrue value)
		@param point the mouse point
		@param appFrameOK Whether or not it's ok to return the app frame window on Windows.
		@param bSkipIgnoreables Whether or not to skip windows which implement IID_IIGNOREABLEWINDOW and have the value set to kTrue
	*/
	virtual IWindow* QueryWindowUnderPoint(GSysPoint point,bool16 appFrameOK, bool16 bSkipIgnoreables = kFalse) = 0;
	
	// Obsoleted for CS6...
	// With all the palette changes that have taken place in OWL1 and OWL2, this method no longer makes sense.
	/**	Return snap value in delta if rt can snap to any palette window (except excludeWindow if it's not nil) by CORNERS.
		 If the passed-in delta is not (0,0) (meaning there's a previous snap value), the new delta will not be constrained by the previous delta.
	*/
	//virtual void SnapRectToNearestPalette(const SysRect& rt, uint32 snapDistance, SysPoint& delta, PaletteRef excludeWindow) = 0;

	// With the document wrapper that have taken place in OWL1 and OWL2, this method shouldnt be called any more.
	/** 	Return snap value in delta if rt can snap to any doc window (except excludeWindow if it's not nil) by EDGES.
		If the passed-in delta is not (0,0) (meaning there's a previous snap value), the new delta will not be constrained by the previous delta (in each DIRECTION).
	*/
	virtual void SnapRectToNearestDocWindow(const SysRect& rt, uint32 snapDistance, SysPoint& delta, IDocumentPresentation* excludeWindow = nil) = 0;
	
	/**	Return snap value in delta if rt can snap to any monitor by EDGES.  If the passed-in delta is not (0,0) (meaning there's a previous snap value), 
		the new delta will not be constrained by the previous delta (in each DIRECTION).
	*/
	virtual void SnapRectToNearestMonitor(const SysRect& rt, uint32 snapDistance, SysPoint& delta) = 0;

	/** Dynamically allocate an AcquireModalDialogState
	*/
	virtual AcquireModalDialogState *CreateModalDialogState() = 0;

	/** Free an AcquireModalDialogState returned by a previous call to CreateModalDialogState
	*/
	virtual void ReleaseModalDialogState(AcquireModalDialogState *modalDialogState) = 0;
	
	/** Adds filename to titlebar of dialog. Used for import filter prefs dialogs */
	virtual void AddFilenameToDialogTitle(IDialog* dialog, const PMString& importFileName) = 0;

	/** 
	Flags the window's IID_IFOCUS_EH_GETTING_REMOVED interface to indicate that the event handler is getting removed, then delegates to IKeyboard::RemoveEventHandlersForWindow(). 
	@see IKeyboard::RemoveEventHandlersForWindow
	*/
	virtual void RemoveEventHandlersForWindow(IWindow *window) = 0;
};


#endif	// __IWindowUtils__
