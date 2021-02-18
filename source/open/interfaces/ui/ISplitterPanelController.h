//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/ui/ISplitterPanelController.h $
//  
//  Owner: Dave Burnard (was Ken Philbrick)
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
#ifndef __ISPITTERPANDLECONTROLLER__
#define __ISPITTERPANDLECONTROLLER__

#include "IPMUnknown.h"
#include "widgetid.h"

class ISplitterPanelController : public IPMUnknown
{
	public :			
		enum { kDefaultIID = IID_ISPLITTERPANELCONTROLLER };

		virtual void SyncPanelsToSplitter  (bool16 invalidateCursorRegions = true, bool16 invalFrames = true) = 0;
//		
//		// None of these will sync the panels to the position of the slider			 
		/* Value passed to SetSplitterEdge is absolute pixel value, not a percentage or anything clever like that...
			returns true if it snapped.*/
		virtual bool16 SetSplitterEdge   (int position)  const = 0; 			 
		virtual void SingleClickSplitterPosition	 ()  const = 0;			 
		virtual void ResizeSplitter (const PMRect& newFrame) const = 0;
		virtual void InitSplitterPosition  ()  const = 0;
//
		virtual bool16 IsSplitterBottom () const = 0;
		virtual bool16 IsSplitterTop () const = 0;
//		
		virtual void SetTopWidgetIndex (int index) = 0;
//		
		 virtual void SetSplitterDrawWidgetClassID(ClassID drawWidgetID) = 0;
		 virtual ClassID GetSplitterDrawWidgetClassID() = 0;
};

#endif
