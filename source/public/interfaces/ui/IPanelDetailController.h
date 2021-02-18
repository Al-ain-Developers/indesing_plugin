//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPanelDetailController.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IPanelDetailController__h_
#define __IPanelDetailController__h_

#include "widgetid.h"

//========================================================================================
// CLASS IPanelDetailController
//========================================================================================

/** Interface to allow varying level of detail exposed by a widget.
*/
class IPanelDetailController : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPANELDETAILCONTROLLER };
					 
	/** Switch the panel to show less detail, if at minimum detail
		level the show all detail. Return true if size of panel changed.
	*/
	virtual void	RotateDetailLevel() = 0;
					
	/** Show nth detail level, zero based. Previously, the ShowNthDetailLevel method was 1 based, with 0 meaning minimized.
		@param nthLevel specifies level of detail to show
	*/
	virtual void	ShowDetailLevel(int16 nthLevel) = 0;						 
	
	/** Accessor for current detail level, zero based. Previously, the GetCurrentDetailLevel method was 1 based, with 0 meaning minimized.
		@return the current detail level.
	*/
	virtual int16	GetDetailLevel() const = 0;
						
	/** Accessor for the number  of detail levels. The minimum is always 1.
		@return maximum detail level
	*/
	virtual int16	GetNumDetailLevels() const = 0;
						
	/** Accessor default detail level.
		@return the default detail level.
	*/
	virtual int16	GetDefaultDetailLevel() const = 0;
						 						
};

#endif // __IPanelDetailController__h_
