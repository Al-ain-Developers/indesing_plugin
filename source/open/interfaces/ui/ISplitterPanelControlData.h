//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/ui/ISplitterPanelControlData.h $
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
#ifndef __ISplitterPanelControlData__
#define __ISplitterPanelControlData__

#include "IPMUnknown.h"
#include "widgetid.h"

/** This thing works in concert with ISplitterPanelController to let you get/set various splitter attributes.
	@see SplitterPanelDefs.h */
	
class ISplitterPanelControlData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISPLITTERPANELCONTROLDATA };

	virtual bool16 IsVerticalSplitter () const = 0; 
	virtual void SetIsVerticalSplitter(bool16 vertical) = 0;
//	
//	// virtual int	 GetSplitterPos			   () const = 0;  This function has been replaced by GetSplitterEdge
//	// virtual void SetSplitterAboslutePos     (int pos, bool UpdateSplitterPercent, bool shouldassert = true) = 0;  This function has been replaced by SetSplitterEdgeAbsolutePos
//	// virtual int  GetSplitterRadius  () const;  // Has been replaced by Get Splitter Size
//	
	virtual int	 GetSplitterEdge     () const = 0;	//Left Edge for hoizonal Splitters, top edge for vertical Splitters
//	// SetSplitterEdgeAbsolutePos should only be called by the ISplitterPanelController, use the controllers setPosition to set the position of the splitter
	virtual void SetSplitterEdgeAbsolutePos     (int pos,  bool16 UpdateSplitterPercent, bool16 shouldassert = true) = 0; // 
	virtual int  GetSplitterSize  () const = 0;  // Width of Splitter for hoizonal Splitters, Height of 	
	virtual bool16 IsLocalPointOnSplitter (const PMPoint &point) const = 0;
//
	/** If user positions splitter less than GetSplitterSnapTop amount, it will snap closed, if this splitter does snapping.
	Note: this is expressed in # of pixels for min size of top/left section */
	virtual int  GetSplitterSnapTop    () const = 0;
//
	/** If user positions splitter greater than GetSplitterSnapBottom amount, it will snap closed, if this splitter does snapping. 
	Note: this is expressed in # of pixels for min size of bottom/right section */
	virtual int  GetSplitterSnapBottom () const = 0;
//	
	virtual bool16 ShouldSnapUp          () const = 0;
	virtual bool16 ShouldSnapDown          () const = 0;
//
//	/* SetPanelVisible: panelIndex 0 = top/left. 1 = bottom/right */
	virtual	void   SetPanelVisible		(int panelIndex, bool16 visible) = 0;
	virtual bool16   IsSinglePanelVisible () const = 0;
	virtual int    GetVisiblePanel () const      = 0;
	virtual int    GetHiddenPanel () const       = 0;
	virtual double GetSplitterInitPercent () const = 0;
	virtual int	GetSingleClickAction () const = 0;
//	
	virtual void SetResizeMode (int ResizeMode) =0;
	virtual int  GetResizeMode () const = 0;
//
	virtual bool16  DrawXORSplitter () const = 0;
//
	virtual int	  GetTopWidgetIndex () const = 0;
	virtual int	  GetBottomWidgetIndex () const = 0;
	virtual void  SetTopWidgetIndex (int index, bool16 shouldassert = true) = 0;
//
	virtual double GetSplitterPercent () const = 0;
//	virtual void UpdateSplitterPercent () = 0;
//	
	virtual int GetSingleClickRestoreSplitterPoint () const = 0;
	virtual void SetSingleClickRestoreSplitterPoint (int point) = 0;

	enum SplitterMinimizedSetting 
	{
			kSplitterNotMinimized = 0,
			kSplitterMinimizedByUser,
			kSplitterAutoMinimized
	};

	virtual SplitterMinimizedSetting GetSplitterMinimizedByUser () const = 0;
	virtual void SetSplitterMinimizedByUser (SplitterMinimizedSetting  minizedbyuser) =0;
    
    /*
     * Sets Width of Splitter
     * For INTERNAL USAGE ONLY
     */
    virtual void SetSplitterSize  (int width) =0;
};

#endif
