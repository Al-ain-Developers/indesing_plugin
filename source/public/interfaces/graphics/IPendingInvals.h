//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPendingInvals.h $
//  
//  Owner: zwilliam
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
#ifndef __IPendingInvals__
#define __IPendingInvals__

#include "IPMUnknown.h"
#include "PMRect.h"
#include "TextID.h"

class IGraphicsContext;

/** IPendingInvals: Used to record text invalidations areas to be drawn at a later time.  Invalidation
areas are redrawn via a call to PlayPendingInvals().
*/
class IPendingInvals : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPENDINGINVALS };

	/** Are there Pending Invals recorded?
	*/
	virtual bool16 HasPendingInvals() = 0;

	/** Record an area (in Parcel Content Coordinates) to later be inval'ed.
	*/
	virtual void RecordPendingInval(const PMRect& invalRect) = 0;
	
	/** Simply removes all inval areas from the list of pending inval's.
	*/
	virtual void ClearPendingInvals() = 0;
	
	/** Actually Inval's the screen area associated with each of the pending inval rects.
		Returns kTrue if it drew into the TextOffscreen.
		*/
	virtual bool16 PlayPendingInvals(IGraphicsContext * gc) = 0;
		
	/** Called if/when a container is asked to draw when it contains obsolete composition information.
		In this case, any subsequent composition of the container will inval the entire container, since the
		draw that occurred while the container was damaged may not have actually drawn any text.
	*/
	virtual void SetDrawnWhileDamaged(bool16 drawnWhileDamaged, IGraphicsContext * gc) = 0;
};

#endif
