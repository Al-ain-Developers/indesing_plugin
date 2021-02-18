//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/ITip.h $
//  
//  Owner: Craig Hotchkiss
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
#ifndef __ITip__
#define __ITip__

#include "IPMUnknown.h"
#include "PMPoint.h"
#include "PMString.h"

/** Defines the tip inteface
*/
class ITip : public IPMUnknown
{
public:
	/** Tips are expected to return a PMString to use as their tip. To have no tip, return PMString(). You may also fill in the WindowPlacementAdvice,
		if you have a preference about where the tip window appears.
		@param mouseLocation
		@return string to use as tip, or PMString() if no tip
	*/
	virtual PMString  GetTipText(const PMPoint& mouseLocation) = 0;
	
#ifdef ID_DEPRECATED
	/** Controls which want to different display tool tip for a single control when the mouse is moved within the widget
		 from one mouse location to another.
		@return kTrue to signify that this control will display different tip when mouse is moved.
	 */
	virtual bool16 UpdateToolTipOnMouseMove() = 0;
#endif
	/** ***This API is currently not implemented in general case. Only implement in (IID_ITIP,  kGeneratedGraphicTipImpl) for a specific case***
		Set the tooltip text
		@param newTipText - string to use as tip		
	*/
	virtual void SetTipText(const PMString tipText) = 0;
};
#endif /* __ITip__ */
