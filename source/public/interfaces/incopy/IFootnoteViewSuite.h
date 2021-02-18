//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IFootnoteViewSuite.h $
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
//  
//  Note:
//  
//========================================================================================

#pragma once
#ifndef _ITextMiscellanySuite_
#define _ITextMiscellanySuite_

#include "IPMUnknown.h"
#include "WritingModeUIID2.h"
#include "WritingModeID2.h"
#include "CTextEnum.h"

class WideString;
class IPMFont;
class GraphicsData;
class IControlView;
class IActiveContext;

/**
	@ingroup text_suite
*/
class IFootnoteViewSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IFOOTNOTEVIEWSUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**
			Check if the current text selection is within a footnote
			@return true if the selection is in a footnote.
		**/
		virtual bool16 SelectionInFootnote(void) = 0;

		/**
			Move selection that is currently in a footnote outside the footnote and to the text index
			just before the footnote anchor index in the primary text story thread.
			@return true if selection was moved
		**/
		virtual bool16 MoveSelectionOutOfFootnote(void) = 0;

		/**
			Check the current footnotes in a story and see if they are collapsed or expanded. If all
			are uncollapsed then it will collapse them all. If all are collapsed then it will expand
			them all.
			@return kSuccess or kFailure
		**/
		virtual ErrorCode CollapseExpandAllFootnotes(void) = 0;
		
		/**
			Toggle the collapse/expand state at the given footnote anchor text index
			@param index of the footnote anchor character in text.
			@return kSuccess or kFailure
		**/		
		virtual ErrorCode CollapseExpandFootnote(TextIndex anchorIndex) = 0;
		
		
		/**
			See if a footnote at the given footnote anchor text index is collapsed or not. This routine
			assumes the caller has verified the existance of a footnote at a given anchor index.
			@param index of the footnote anchor character in text.
			@return kSuccess or kFailure
		**/		
		virtual bool16 IsFootnoteCollapsed(TextIndex anchorIndex) = 0;
		
		/**
			Determine whether footnotes are in a state where they can all be collapsed
 			or all expanded. This is a utility function that is called by CallapseExpandAllFootnotes
			to determine which action it should take.
			@return kTrue (should be able to collapse) kFalse (not able to collapse)
		**/		
		virtual bool16 ShouldCollapseAllFootnotes() = 0;

	};

#endif // _ITextMiscellanySuite_
