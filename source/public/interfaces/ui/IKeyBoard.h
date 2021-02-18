//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IKeyBoard.h $
//  
//  Owner: Robin_Briggs
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
//  The keyboard is the keeper of the key focus. An event handler must
//  aquire the key focus in order to get key events.
//  
//========================================================================================

#pragma once
#ifndef __IKEYBOARD__
#define __IKEYBOARD__

#include "IPMUnknown.h"

class IEventHandler;
class IWindow;

class IKeyBoard : public IPMUnknown	
{
public:
	enum { kDefaultIID = IID_IKEYBOARD };

	/** Set a new key focus. newKeyFocus will get all subsequent keyboard events
		until RelinquishKeyFocus is called. If the focus can't be acquired because the current focus
		handler won't let go, this function returns kFalse. If you pass kFalse for the "validate"
		parameter, validation of the current handler won't occur.
	*/
	virtual bool16			AcquireKeyFocus(IEventHandler *newKeyFocus, bool16 validate = kTrue) = 0;
		
	/** Remove the key focus. Restores key focus to the previous holder of the key focus.
		Returns kFalse if the current focus event handler won't let go of the focus.
		If you pass kFalse for the "validate" parameter, validation of the current handler won't occur.
		If you pass kTrue for the "rememberFocus" parameter, a keyboard shortcut will restore the
		keyboard focus to the focus that is being relinquished.
	*/
	virtual bool16			RelinquishKeyFocus(bool16 validate = kTrue) = 0;
		
	/** If any event handler belonging to "window" has the key focus, give it up.
		If you pass kFalse for the "validate" parameter, validation of the current handler won't occur.
	*/
	virtual bool16			RelinquishKeyFocusForWindow(IWindow* window, bool16 validate = kTrue) = 0;
		
	/** Call RemoveEventHandlersForWindow before closing a window. This function makes sure that
		any event handlers on the event handler stack belonging to the referenced window are
		removed.
	*/
	virtual void			RemoveEventHandlersForWindow(IWindow* window) = 0;

	/** Return the event handler that has key focus.
	*/
	virtual IEventHandler*	GetKeyFocus() const = 0;

	/** Remember the last editbox in palette with key focus so we can restore it with
		shortcut. This is specified in Adobe Common UI for palette (Ctrl+~).
		Note: Ctrl+~ is defualt one in window but on onger available after OS X 10.2.x
		@return none
	*/
	virtual void RememberLastEditboxKeyFocusInPalette(IEventHandler* eh) = 0;

	/** This function attempts to restore the last editbox with key focus in palette
		@return kTrue if keyboard focus (if there was one) was successfully restored.
	*/
	virtual bool16 RestoreLastEditboxKeyFocusInPalette() = 0;

	/** Handle necessary key focus job after application has been suspended
		@return none
	*/
	virtual void AppSuspend() = 0;

	/** Handle necessary key focus job after application has been resumed
		@return none
	*/
	virtual void AppResume() = 0;

	/** Try to validate widget which hold key focus. Right now, only editbox link its 
		validation to loss of key focus
		@return kTrue if widget hold keyboard focus (if there was one) was successfully validated.
	*/
	virtual bool16 ValidateCurrentKeyFocus() = 0;

	/** Handle necessary key focus job before open external modal window such as 
		Open/Save dialog, alert box et al.
		@Param isDVAOwnedWindow:Internal Use only, is this window external(false) or dvaowned(true)
	*/
	virtual void OpenExternalModalWindow(bool isDVAOwnedWindow = false) = 0;

	/** Handle necessary key focus job after external modal window such as 
		Open/Save dialog, alert box et al. closed
		@return none
	*/
	virtual void ExternalModalWindowClosed() = 0;

#ifdef WINDOWS 
	/** Returns the CoolType font writing script and codepage implied by the current keyboard 
		language/layout. Returns kCTDontKnowScript if unable to determine writing script and
		-1 for codepage if unable to determine code page. The codepage value is specific to CoolType.
	*/
	virtual void			GetScriptAndCodePage(int32& outWritingScript, int32& outCodePage) const = 0;
#endif

};

#endif // __IKEYBOARD__
