//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAppTextOptions.h $
//  
//  Owner: Zak_Williamson
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
#ifndef __IAppTextOptions__
#define __IAppTextOptions__

#include "IPMUnknown.h"
#include "TextID.h"


/** 
	@ingroup text_layout
*/
class IAppTextOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IAPPTEXTOPTIONS };

	/**  GetPreferStyledTextWhenPasting returns whether or not styled text should be pasted
		from the external clipboard if available.
		@return kTrue if styled text should be pasted when available.
	*/
	virtual bool16 GetPreferStyledTextWhenPasting() const = 0;
	
	/**  SetPreferStyledTextWhenPasting is used to set whether or not styled text should be
		pasted from the external clipboard if available.
		@param preferStyledText IN kTrue if pasting styled text from the external clipboard is preferred.
	*/
	virtual void SetPreferStyledTextWhenPasting(bool16 preferStyledText) = 0;

	/**  GetDragDropTextInLayout returns whether or not selected text can be dragged and dropped in layout view.
		@return kTrue if selected text can be dragged, kFalse otherwise.
	*/
	virtual bool16 GetDragDropTextInLayout() const = 0;
	
	/**  SetDragDropTextInLayout is used to set whether or not selected text can be dragged and dropped in layout view.
		@param bDragDropText IN kTrue to allow drag and drop of selected text, kFalse to disallow.
	*/
	virtual void SetDragDropTextInLayout(bool16 bDragDropText) = 0;

	/**  GetDragDropTextInStory returns whether or not selected text can be dragged and dropped in layout view.
		@return kTrue if selected text can be dragged, kFalse otherwise.
	*/
	virtual bool16 GetDragDropTextInStory() const = 0;
	
	/**  SetDragDropTextInStory is used to set whether or not selected text can be dragged and dropped in story/galley view.
		@param bool16 bDragDropText IN kTrue to allow drag and drop of selected text, kFalse to disallow.
	*/
	virtual void SetDragDropTextInStory(bool16 bDragDropText) = 0;

	/**  GetTextToolConvertsFrames() returns kTrue if the text tool can be used to convert an empty graphic frame or "Unknown"
		frame to a text frame, kFalse otherwise.  Default is kTrue.
	*/
	virtual bool16 GetTextToolConvertsFrames() const = 0;
	
	/**  SetTextToolConvertsFrames is used to set whether or not the text tool can convert an empty frame to a text frame.
		@param bool16 bDoesConvert IN kTrue to allow the text tool to convert frames to text frames, kFalse to disallow.
	*/
	virtual void SetTextToolConvertsFrames(bool16 bDoesConvert) = 0;

};

#endif
