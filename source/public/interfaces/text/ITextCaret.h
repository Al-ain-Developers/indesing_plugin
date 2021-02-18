//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextCaret.h $
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
#ifndef __ITEXTCARET__
#define __ITEXTCARET__

#include "IPMUnknown.h"

#include "TextEditorID.h"

//========================================================================================
// Forward declarations
//========================================================================================

class PMLineSeg;
class RangeData;
class IControlView;
class IGraphicsContext;

//========================================================================================
// CLASS ITextCaret
//========================================================================================

/** Interface to set and draw the text caret.
	@ingroup text_editor
*/
class ITextCaret : public IPMUnknown
{
// ----- Blinking the caret
public:
	enum { kDefaultIID = IID_ITEXTCARET };


/**	Check if text caret was stroked?
	@param none
	@return bool16 kTrue = text caret was stroked.
 */
	virtual bool16		IsCaretStroked() const = 0; //looks easy

//	virtual bool16		IsCaretBlinking() const = 0; //likely easy

	/** Not used. 
	*/
	enum{ kStopCaretBlinking = 0, kStartCaretBlinking};
	
	/** Not used.
	*/
	enum{ kEraseCaretNow = 0, kStrokeCaretNow};
//	virtual void		SetCaretBlinking( bool16 bOn, bool16 bVisible = kStrokeCaretNow ) = 0;
							// To set a steady TextCaret call SetBlinking( kStopCaretBlinking, kStrokeCaretNow ).


/**	Invalidate the param invalidRgn to redraw the text caret
	@param view 
	@param invalidRgn 
 */
	virtual void		DrawingRegion(IControlView* view, const SysRgn& invalidRgn) = 0;
	
// ----- Activating
//	virtual void		ActivateCaret(bool16 active) = 0;
							// Use to activate the caret when the view the caret is
							// in becomes active.
//	virtual bool16		IsCaretActive() const = 0; 
		//TextCaretSelectionObserver::Update and several incopy callers
		//also TextCaretThread::RunTask (which is silly) and EditorToFrame::ActivateTextEditor



// ----- Position

/** Use to recalculate the TextCaret. Pass in nil to use the current selection.
	It returns whether the position is a valid caret position.
	@param view The control view
	@param newCaretPosition The new caret position
	@return bool16 kTrue = the position is a valid caret position.
 */
	virtual bool16		UpdateCaretPosition(IControlView *view = nil, const RangeData* newCaretPosition = nil) = 0;


/**	Use to get the caret bounds in pasteboard. It returns kFalse on error.
	By convention, the caret is 1.0 units wide, where wide is independent of x or y.
	@param pCaretBounds Return the caret bounds
	@return bool16 
 */
	virtual bool16		GetCaretBounds( PMLineSeg* pCaretBounds ) const = 0; //WritingObserver::DoAutoScroll, ChangesDialogMenuAction::DoAutoScroll --reconcile these


/**	Toggle text caret state to earse or storke
	@param none
 */
	virtual  void		ToggleCaret() = 0;
	
/** Called from the view that the caret belongs to to draw the caret. Normally, this should not need to be called externally.
	@param gc The graphic context to draw the caret with.
	@param updateRect The area of the screen being currently being redrawn. 
*/
	virtual void DrawCaret(IGraphicsContext *gc, PMRect updateRect) = 0;

public:
	/* The state of text caret.
	*/
	enum CaretState {
		kCaretOff, kCaretErased = kCaretOff,
		kCaretParked, kCaretStroked = kCaretParked,
		kCaretOn, kCaretBlinking = kCaretOn
	};
	

/**	Set the new state and new position of text caret.
	@param CaretState The state of text caret
			kCreatOff, kCaretEarsed = earse text caret.
			kCaretParked, kCaretStroked = stroke text caret
			kCaretOn, kCaretBlinking = set the text caret, no stoke the caret
	@param newCaretPosition The new position of text caret
 */
	virtual void SetCaretState(CaretState, const RangeData* newCaretPosition = nil) = 0;

/**	Get the text caret state
	@param none
	@return CaretState The state of text caret
*/
	virtual CaretState GetCaretState() = 0;
};

#endif
