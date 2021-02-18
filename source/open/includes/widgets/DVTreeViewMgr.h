//========================================================================================
//  
//  $File $
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
#ifndef __CDVTreeViewMgr_h__
#define __CDVTreeViewMgr_h__


#include "CTreeViewMgr.h"

//----------------------------------------------------------------------------------------
// Class Info
//----------------------------------------------------------------------------------------
class DV_WIDGET_DECL DVTreeViewMgr : public CTreeViewMgr
{
	typedef CTreeViewMgr inherited;
	
public:
	DVTreeViewMgr(IPMUnknown *boss);
	virtual ~DVTreeViewMgr();

protected:
	virtual void ScrollHorizontal( int32 amount, bool16 forceRedraw = kTrue );
	virtual void ScrollVertical( int32 amount, bool16 forceRedraw = kTrue );
	virtual PMReal AdjustScrollIncrements(WidgetID whichScrollBar, const PMReal& scrollerTop, const PMReal& scrollerBottom, const PMReal& viewSize);
	virtual void MoveScroller( const PMPoint& moveTo );

public:
	virtual void		ScrollVerticalAbsoluteAmount(int32 amount, bool16 forceRedraw = kTrue);

};

#endif
