//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IGalleyInfoUtils.h $
//  
//  Owner: Matt Ramme
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
//  Purpose:
//  Utilities for use with GalleyInfo.
//  
//========================================================================================

#pragma once
#ifndef __IGalleyInfoUtils__
#define __IGalleyInfoUtils__

#include "Utils.h"
#include "InCopyCoreID.h"

class ITextModel;
class IWaxLine;
class IWaxIterator;
class StatsScope;


/** Class used to return fit information for the StoryCountFit routine.
*/
class FitInformation
{
public:
	FitInformation() : fFractionalFitValue(-1.0), fPercentFilled(1.0), fFitDataType(kUnknownFit) {}
	
	enum TypeFit { kUnderset, kExactFit, kOverset, kUnknownFit };
	
	/**
		0 if totally fit, positive (num lines/words/pages over), negative (num lines/words/pages under).
	*/
	PMReal fFractionalFitValue;
	
	/**
		1.0 for exactFit and overset if underset it will have a value between 0.0 and 1.0 that indicates the percentage of the fit
	*/	
	PMReal fPercentFilled;
	
	/**
		Will return whether the text is underset, an exact fit or overset.
	*/		
	TypeFit fFitDataType;
};



/** This interface contains methods for calculating text statistic like amount of text overset, underset etc.
*/
class IGalleyInfoUtils : public IPMUnknown 
{
	public:
	enum {kDefaultIID = IID_IGALLEYINFOUTILS};
	enum FitType{kDepthFit = 0, kWordCountFit, kLineCountFit, kPageCountFit, kGeometryFit, kCharacterFit, kDisableFit};

	/**
		No longer used by InCopy was used in 2.x to calculate the number of words has been replaced to use ITypeToolSuite::GetWordCountInfo
		instead and the new method is shared with InDesign.
		@param textModel story to count words of
		@param begin text index to start counting words at.
		@param end text index to stop counting words at.
		@return number of words in the range requested.
	*/
	virtual int32 StoryCountWords(ITextModel *textModel, TextIndex begin, TextIndex end) = 0;
	
	/**
		No longer used by InCopy was used in 2.x to calculate the number of lines has been replaced to use ITypeToolSuite::GetWordCountInfo
		instead and the new method is shared with InDesign.
		@param textModel story to count lines of
		@param begin text index to start counting lines at.
		@param end text index to stop counting lines at.
		@return number of lines in the range requested.
	*/
	virtual int32 StoryCountLines(ITextModel *textModel, TextIndex begin, TextIndex end) = 0;
	
	/**
		Will calculate the how well the text fits based on several methods. Recommend that the routine returning FitInformation
		be used instead although this one is provided for legacy.
		1. kDepthFit calculate how well the text fits based on standalone text statistics settings (document setup)
		2. kWordCountFit using the settings in document setup calculate how close the fit is based on user defined fit word count
		3. kLineCountFit using the settings in document setup calculate how close the fit is based on user defined line count
		4. kPageFit using the setting in document setup calculate fit based on user defined page count.
		5. kGeometryFit calculate how well the text fits based on geometry
		@param textModel story to measure the depth of
		@param pctFilled return parameter gives the total percentage fit 1.0 is totally fit smaller than 1.0 is a percentage
		@param fitMethod what type of fit calculation to perform
		@param can return a real value instead of a int32 in this parameter if more precision is needed
		@return 0 if totally fit, positive (num lines/words/pages over), negative (num lines/words/pages under).
	*/
	virtual int32 StoryCountFit(ITextModel *textModel, PMReal *pctFilled = nil, FitType fitMethod = kDepthFit, PMReal *fractionalFitValue = nil) = 0;

	/**
		Will calculate the how well the text fits based on several methods. Returns better information than the above StoryCountFit routine.
		1. kDepthFit calculate how well the text fits based on standalone text statistics settings (document setup)
		2. kWordCountFit using the settings in document setup calculate how close the fit is based on user defined fit word count
		3. kLineCountFit using the settings in document setup calculate how close the fit is based on user defined line count
		4. kPageFit using the setting in document setup calculate fit based on user defined page count.
		5. kGeometryFit calculate how well the text fits based on geometry
		@param textModel story to measure the depth of
		@param pctFilled return parameter gives the total percentage fit 1.0 is totally fit smaller than 1.0 is a percentage
		@param fitMethod what type of fit calculation to perform
		@param can return a real value instead of a int32 in this parameter if more precision is needed
		@return a FitInformation class filled out. See comments on that class above
	*/
	virtual FitInformation StoryCountFit(ITextModel *textModel, FitType fitMethod) = 0;
	
	/**
		Toggle the text statistics idle task on or off
		@param start kTrue to turn it on
		@param pIdleLoc an interface in the same boss as the idle task
		@return kTrue doesn't seem to mean anything
	*/
	virtual bool16 ToggleIdle(bool16 start = kTrue, IPMUnknown *pIdleLoc = nil) = 0;
	
	/**
		Returns whether a specific text line should be added to the line count when calling StoryCountLines() above.
		@param waxLine line to check if it should be counted
		@param waxIterator iterator used to get the waxline
		@return kTrue if line should be counted.
	*/
	virtual bool16 ShouldCountLine(IWaxLine **waxLine, IWaxIterator *waxIterator) = 0;
	
	/**
		Returns the physical composed (layout view) on screen depth of a story or part of a story if a range is
		asked for which is not the entire story. The depth is returned in default InDesign units. This will
		return -1.0 if it was unable to calculate the depth for some reason.
		@param textModel story to measure the depth of
		@param begin first textindex to measure depth from.
		@return end last TextIndex to measure depth to (if start and end are the total range of the
			story then the depth of the complete story is measured).
	*/
	virtual PMReal StoryCountDepth(ITextModel *textModel, const StatsScope &scope) = 0;

};

// This lives in each stats widget.  Have to do this to make this info 'global'
class StatsScope
{
public:
	/**
		Constructor initialize all variables to defaults
	*/
	StatsScope() { fWhichScope = kStoryStats; fBeginIndex = -1; fEndIndex = -1; 
				   fStoryUIDRef = UIDRef(NULL, kInvalidUID); 
				   fLastModelLength = 0; fLastChangedCounter = 0; fAssignedDepth = -1.0;
				   fAssignedDepthIndex = -1; fFitType = IGalleyInfoUtils::kDepthFit;
				   fIncludingFootnotes = kFalse; }

	/**
		Possible types of text stats.
		kStoryStats entire story text statistics
		kSelectionStats  stats for currents selection
		kToBeginStats from start of selection to story begin
		kToEndStats from start of selection to story end
		kFitStats does story fit frame
	*/
	enum WhichScope { kStoryStats, kSelectionStats, kToBeginStats, kToEndStats, kFitStats };

	/**
		fWhichScope Specify wich type of stats to calculate using WhichScope enum.
	*/
	WhichScope fWhichScope;
	
	/**
		fBeginIndex Specify start index to calculate stats on.
	*/	
	TextIndex fBeginIndex;
	
	/**
		fBeginIndex Specify end index to calculate stats on.
	*/	
	TextIndex fEndIndex;
	
	/**
		fStoryUIDRef Reference of the story to calculate stats on.
	*/	
	UIDRef fStoryUIDRef;
	
	/**
		fLastModelLength used internally to find out when to update stats.
	*/	
	int32 fLastModelLength;

	/**
		fLastChangedCounter used internally to find out when to update stats.
	*/	
	uint32 fLastChangedCounter;
	
	/**
		fAssignedDepth for standalone text stats -1 for normal stats if there is a goal length put it in here.
	*/	
	PMReal fAssignedDepth;
	
	/**
		fAssignedDepthIndex used internally to returned by stats functions if fAssigneDepth is filled out to say where to draw overset line.
	*/	
	int32 fAssignedDepthIndex;
	
	/**
		fFitType returned to indicate what type of fit is there after the stats are calculated.
	*/		
	IGalleyInfoUtils::FitType fFitType;
	
	/**
		fIncludingFootnotes set to kTrue to include footnotes in the text stats calculations.
	*/		
	bool16 fIncludingFootnotes;
};

#endif //__IGalleyInfoUtils__
