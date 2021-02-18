//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextOffscreen.h $
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
#ifndef __ITextOffscreen__
#define __ITextOffscreen__

#include "IPMUnknown.h"
#include "DVAForwardDeclarations.h"

class IGraphicsContext;
class PMRect;

//----------------------------------------------------------------------------------------
// Interface ITextOffscreen
//----------------------------------------------------------------------------------------

/**
	ITextOffscreen is a class which is used to quickly process IPendingInvals on the text model.
	The idea is that when a text frame has focus and the user is typing, we want to draw
	the text frontmost and quickly update the view without going through the typical OS level
	invalidation followed by the processing of a paint/update message from the OS.
	@ingroup text_editor
*/
class ITextOffscreen : public IPMUnknown
{
public:
	/** Initializes the text offscreen for the given text frame (kFrameItemBoss).
		@param pShape - IN: Pointer to the text frame with focus (kFrameItemBoss).
		@param gc - IN: Pointer to the graphics context (the view/window that we are drawing to).
		@return kFalse if it was not possible to create the offscreen or if the pShape
			does not have typing focus. If CreateOffscreen is successful, kTrue is returned.
			If the textoffscreen has already been initialized with the given pShape, 
			then this method is a no-op and kTrue is returned.
	*/
	virtual	bool16		CreateOffscreen( IPMUnknown *pShape,  IGraphicsContext* gc ) = 0;

	/** Draw causes an update to occur for the text frame to the provided graphics context.
		@param pShape - IN: the text frame (kFrameItemBoss).
		@param gc - IN: Pointer to the graphics context (the view/window that we are drawing to).
		@return kTrue if the draw occurred successfully, kFalse otherwise.
	*/
	virtual	bool16		Draw( IPMUnknown *pShape,  IGraphicsContext* gc ) = 0;

	/** IsSupported is used to determine if the text offscreen is active for the given pShape.
		@param pShape - IN: the text frame (kFrameItemBoss).
		@return kTrue if the textoffscreen is active for the given pShape.
	*/
	virtual	bool16		IsSupported( const IPMUnknown *pShape ) const = 0;

	/** Called by the TextEditor and the TextOffscreenObserver if the offscreen needs to be recalculated.
		@param pShape - IN: the text frame (kFrameItemBoss).
		@return kTrue if this shape is currently supported. If pShape is nil it will clear all sprites.
	*/
	virtual	bool16		Clear( const IPMUnknown *pShape = 0 ) = 0;
	
	/** Enables/Disables the text offscreen.
		@param bOn - IN: if kTrue, then enable text offscreening, otherwise disable.
	*/
	virtual	void			Enable( bool16 bOn = kTrue ) = 0;

	/** @return Returns the current Enabled state of the text offscreen.
	*/
	virtual	bool16		IsEnabled() const = 0;

	/** Set by the TextOffscreenSprite if it was not able to create a sprite.  Low memory mode
		for sprites typically means that the drawing will be in XOr mode instead of using offscreens.
		@param bOn - IN: kTrue if in low memory mode.
	*/
	virtual	void			SetLowMemory( bool16 bOn = kTrue ) = 0;

	/** @return Returns the low memory state.
	*/
	virtual	bool16		IsLowMemory() const = 0;

	/** Set the typing mode. Set by the TextEditor on GetFocus/LoseFocus()
		@param bOn - IN: kTrue if we are in typing mode.
	*/
	virtual	void			SetTypingMode( bool16 bOn = kTrue ) = 0;

	/** @return Returns the current typing mode state.
	*/
	virtual	bool16		IsInTypingMode() const = 0;

	/** @return Returns whether it is currently drawing
	*/
	virtual	bool16		IsInDrawingMode() const = 0;

	/** @return Returns true if we are typing, this offscreen is active for the frame that has focus and the frame has invals pending.
	*/
	virtual bool16		HasPendingInvals() const = 0;

	/** @return Returns a pointer to the text frame for which this offscreen is setup. Nil if the offscreen is not set up.
		You should be able to query for the ITextFrameColumn using the returned pointer.
	*/
	virtual IPMUnknown *GetTargetTextFrame() const = 0;
	
	/** INTERNAL USE ONLY
	 
	 Draw causes an update to occur for the text frame to the provided graphics context.
	 @param pShape - IN: the text frame (kFrameItemBoss).
	 @param gc - IN: Pointer to the graphics context (the view/window that we are drawing to).
	 @param drawbotP - IN: The destination drawbot to draw to. Used when drawing from the view's DV_Draw.
	 @return kTrue if the draw occurred successfully, kFalse otherwise.
	 */
	virtual	bool16		Draw( IPMUnknown *pShape, IGraphicsContext* gc, dvaui::drawbot::Drawbot* drawbotP ) = 0;
};

#endif
