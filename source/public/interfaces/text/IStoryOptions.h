//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IStoryOptions.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IStoryOptions__
#define __IStoryOptions__

#include "IPMUnknown.h"
#include "TextID.h"


class ICJKGridData;

/** Used to set various options for InDesign stories.
	@ingroup text_story
*/
class IStoryOptions : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_ISTORYOPTIONS };

	// Formerly Frame List attributes
	/**	Set whether this story should be vertical or not (J-Text)
		@param vertical - Should this story be vertical (kTrue) or horizontal (kFalse)
	*/
	virtual void SetVertical(bool16 vertical) = 0;

	/**	Find out whether this story is vertical or not (J-Text)
		@return - Is this story vertical (kTrue) or horizontal (kFalse)
	*/
	virtual bool16 IsVertical() const = 0;

	/**	Set whether this story is primarily right to left (ME - Text)
		@param rtl - Should this story be right-to-left (kTrue) or left-to-right (kFalse)
	*/
	virtual void SetRightToLeft(bool16 rtl) = 0;

	/**	Find out whether this story is right-to-left or not (ME - Text)
		@return - Is this story right-to-left (kTrue) or left-to-right (kFalse)
	*/
	virtual bool16 IsRightToLeft() const = 0;

	/** Used to determine whether or not Optical Margin Alignment is used.
		@return - kKFOpticalSideBearingBoss it is on, kEdgeAlignOffBoss it is off
	*/
	virtual ClassID GetEdgeAlignMethod() const = 0;

	/** Used to set whether or not Optical Margin Alignment is used.
		@param algo - kKFOpticalSideBearingBoss will turn it on, kEdgeAlignOffBoss will turn it off
	*/
	virtual void SetEdgeAlignMethod(ClassID algo) = 0;

	/** Gets the story's optical-margin-alignment size
		@return - The current size (in points)
	*/
	virtual PMReal GetParagraphBodySize() const = 0;

	/** Sets the story's optical-margin-alignment size
		@param b - The new size to use (in points)
	*/
	virtual void SetParagraphBodySize(PMReal b) = 0;

	/**	Find out whether this story show the CJK Grid (J-Text)
		@return - Is the grid be shown?
	*/
	virtual bool16 GetCJKGridActive() const = 0;

	/**	Set whether this story should show the CJK Grid (J-Text)
		@param vertical - Should the grid be shown?
	*/
	virtual void SetCJKGridActive(bool16 active) = 0;

	/**	Same as this->QueryInterface(IID_ICJKGRIDDATA) but
		done to support multi-threading composition.
	*/
	virtual const ICJKGridData* QueryCJKGridData() const = 0;

};

#endif
