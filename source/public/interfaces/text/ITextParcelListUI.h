//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITextParcelListUI.h $
//  
//  Owner: dwaterfa
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
#ifndef __ITextParcelListUI__
#define __ITextParcelListUI__

#include "IPMUnknown.h"
#include "TextID.h"

class IGraphicsContext;
class RangeData;

/**
	@ingroup text_layout
*/
class ITextParcelListUI : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ITEXTPARCELLISTUI };

		/**
        Draws a hilite on the text.
		Uses the given delta highlight, if possible.  Otherwise, uses the
		given full range.
        NOTE:	This method should only be called when the frame is redrawing.
		*/
		virtual void		DrawTextHighlight(IGraphicsContext* gc,
										const RangeData& newSelectionRange,
										const RangeData& oldSelectionRange) = 0;
					
		/**
        Inval the hilite area of the text.
		Uses the given delta highlight, if possible.  Otherwise, uses the
		given full range.
        NOTE:	This method is called during selection changes, like mouse tracking.
		*/
		virtual void		InvalTextHighlight(IGraphicsContext* gc,
										const RangeData& newSelectionRange,
										const RangeData& oldSelectionRange,
										bool drawImmediate) = 0;


};

#endif	// __ITextParcelListUI__

