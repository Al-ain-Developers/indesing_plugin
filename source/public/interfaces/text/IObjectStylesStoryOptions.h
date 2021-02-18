//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IObjectStylesStoryOptions.h $
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
#ifndef __IObjectStylesStoryOptions__
#define __IObjectStylesStoryOptions__

#include "IPMUnknown.h"
#include "TextID.h"

/** Used to set various options for InDesign stories.
	@ingroup text_story
*/
class IObjectStylesStoryOptions : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IOBJECTSTYLESSTORYOPTIONS };

	typedef enum { kUnknownDirection, kHorizontal, kVertical } ObjectStyleDirection;
	typedef enum { kUnknownWDirection, kLTRDirection = 1, kRTLDirection } ObjectStyleWritingDirection;
	typedef enum { kUnknownFrameType, kTextFrame, kFrameGrid } ObjectStyleFrameType;

	// Formerly Frame List attributes
	/**	Set whether this story should be vertical or not (J-Text)
		@param direction - Should this story be vertical (kVertical) or horizontal (kHorizontal) or unknown.
	*/
	virtual void SetFrameDirection(IObjectStylesStoryOptions::ObjectStyleDirection direction) = 0;

	/**	Find out whether this story is vertical or not (J-Text)
		@return - direction
	*/
	virtual IObjectStylesStoryOptions::ObjectStyleDirection GetFrameDirection() const = 0;

	/**	Set whether this story should be right-to-left or not (ME-Text)
		@param direction - Should this story be vertical (kVertical) or horizontal (kHorizontal) or unknown.
	*/
	virtual void SetWritingDirection(IObjectStylesStoryOptions::ObjectStyleWritingDirection direction) = 0;

	/**	Find out whether this story is right-to-left or not (ME-Text)
		@return - direction
	*/
	virtual IObjectStylesStoryOptions::ObjectStyleWritingDirection GetWritingDirection() const = 0;

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
		@return - Is frame grid or text frame or unknown?
	*/
	virtual IObjectStylesStoryOptions::ObjectStyleFrameType GetFrameType() const = 0;

	/**	Set whether this story should show the CJK Grid (J-Text)
		@param frameType - Set as kTextFrame or kFrameGrid?
	*/
	virtual void SetFrameType(IObjectStylesStoryOptions::ObjectStyleFrameType frameType) = 0;

	/** Copy these values TO the passed in interface.
		@param pCopyTo is filled out with the current interface's values.
	*/
	virtual void CopyData(IObjectStylesStoryOptions *pCopyTo ) const = 0;
};

#endif
