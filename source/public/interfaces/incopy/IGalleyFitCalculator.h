//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGalleyFitCalculator.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IGalleyFitCalculator__
#define __IGalleyFitCalculator__

#include "IPMUnknown.h"
#include "IGalleyInfoUtils.h"

#include "WritingModeUIID2.h"
#include "GalleyInfoID.h"
#include "UIDRef.h"

/** 
	This interface is a data interface associated with the fit widget. It contains or calculates information
	related to how close a story is to fit. The widget uses this information to display a percentage fit bar.
*/
class IGalleyFitCalculator : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGALLEYFITCALCULATOR };
	
	/**
		Set a document reference that the fit calculations will be performed on
		@param docRef the document reference to perform the calculations on
	*/
	virtual void SetDocRef(const UIDRef &docRef) = 0;
	
	/**
		Get a document reference that the fit calculations are performed on
		@return a document reference.
	*/
	virtual UIDRef GetDocRef() = 0;

	/**
		Set a story to perform fit calculations on.
		@param storyRef the story to set the interface to look at
	*/
	virtual void SetStoryRef(const UIDRef &storyRef) = 0;
	
	/**
		Get the text story reference that fit information is calculated for.
		@return a text story reference.
	*/	
	virtual UIDRef GetStoryRef() = 0;
	
	/**
		Cause the fit information to be calculated and the fit widget to be updated.
		@param useCachedLineCount obsolete to be removed
		@param updateFit kTrue to invalidate the fit widget for draw
	*/
	virtual void SetFitControl(bool16 useCachedLineCount = kFalse, bool16 updateFit = kTrue) = 0;
	
	/**
		Get the current fit type used to decide what type string to display in the fit control (words, lines, depth).
		@param fitType - pass the type fit that the ui should display. Must have set the corresponding fields in this interface to use the correct values.
	*/
	virtual void SetFitType(IGalleyInfoUtils::FitType fitType) = 0;
	
	/**
		Get the current fit type used to decide what type string to display in the fit control (words, lines, depth).
		@return kDepthFit, kWordCountFit, kLineCountFit or kPageFit.
	*/
	virtual IGalleyInfoUtils::FitType GetFitType() = 0;

	
	/**
		How many characters are there in the story.
		Optional data, information required only if calling SetFitControl with useCachedLineCount == kTrue
		@param charCount - character count
	*/	
	virtual void SetCharCount(int32 charCount) = 0;
	
	/**
		Current cached character count
		@return character count.
	*/	
	virtual int32 GetCharCount() = 0;

	/**
		Set how many lines are there in the story.
		Optional data, information required only if calling SetFitControl with useCachedLineCount == kTrue
		@param lineCount - line count
	*/	
	virtual void SetLineCount(int32 lineCount) = 0;
	
	/**
		How many lines are there in the story.
		Optional data, information required only if calling SetFitControl with useCachedLineCount == kTrue
		@return line count.
	*/	
	virtual int32 GetLineCount() = 0;

	/**
		Not used. Vertical position of the last line of text extracted from waxLine->GetYPosition()
		@param lastLineVPos - position of line
	*/	
	virtual void SetLastLineVPos(PMReal lastLineVPos) = 0;
	
	/**
		Not used. Vertical position of the last line of text
		@return cached last line v pos
	*/	
	virtual PMReal GetLastLineVPos() = 0;

	/**
		Not used. Height of the last line in the story.
		@param lastLineHeight - last line in story height
	*/	
	virtual void SetLastLineHeight(PMReal lastLineHeight) = 0;
	
	/**
		Not used. Height of the last line in the story.
		@return cached last line in story height
	*/	
	virtual PMReal GetLastLineHeight() = 0;

	/**
		Not used. Last text frame that has text in it.
		@param frameRef - last valid frame ref
	*/	
	virtual void SetLastValidFrame(const UIDRef &frameRef) = 0;
	
	/**
		Not used. Last text frame that has text in it.
		@return cached last valid frame ref
	*/	
	virtual UIDRef GetLastValidFrame() = 0;

	/**
		Not used. Set index of first line in overset
		@param firstOverflowLine - index of first line in overset
	*/	
	virtual void SetFirstOverflowLine(int32 firstOverflowLine) = 0;
	
	/**
		Not used. Get index of first line in overset
		@return cached lindex of first line in overset
	*/
	virtual int32 GetFirstOverflowLine() = 0;

};

#endif 		// __IGalleyFitCalculator__