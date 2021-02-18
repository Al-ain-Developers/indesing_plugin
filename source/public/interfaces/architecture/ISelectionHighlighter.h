//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ISelectionHighlighter.h $
//  
//  Owner: Richard Rodseth
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
#ifndef _ISelectionHighlighter_
#define _ISelectionHighlighter_

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "PMRect.h"

class IControlView;
class ISelectionHighlightMessage;
class IGraphicsContext;

/**	IID_ISELECTIONHIGHLIGHTER interface; ISelectionHighlighter is a suite for drawing the selection highlighting in a view.
 */
class ISelectionHighlighter : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_ISELECTIONHIGHLIGHTER };

	public:
		
	/**	Highlight the current selection (eg. when a window is redrawn).
		@param gc IGraphicsContext
		@param bbox PBPMRect*
		@return  
	 */
		virtual void HighlightSelection(IGraphicsContext* gc, const PBPMRect* bbox = nil) = 0;
			
	/**	Update the highlighting in response to a selection change. The message containsa CSB-specific message which is passed along to the CSB (concrete selection boss)
		@param view IControlView
		@param message ISelectionHighlightMessage*
		@return  
	 */
		virtual void ChangeHighlighting(IControlView* view, ISelectionHighlightMessage* message) = 0;
			
	/**	Invalidate the current selection in the specified view.
		@param iControlView IControlView
		@return  
	 */
		virtual void InvalidateSelection (IControlView* iControlView) = 0;

	};

#endif // _ISelectionHighlighter_