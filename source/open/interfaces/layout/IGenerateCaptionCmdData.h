//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/interfaces/layout/IGenerateCaptionCmdData.h $
//  
//  Owner: lance bushore
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
#ifndef __IGenerateCaptionCmdData__
#define __IGenerateCaptionCmdData__

#include "IPMUnknown.h"
#include "LinksID.h"

class IGenerateCaptionCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IGENERATECAPTIONCMDDATA };

		
	/** 	Set the data for the cmd.
		@param liveCaption if true, generates a live caption using text variables, else just inserts text.
		@param placeFrameInLayout if true, puts the new text frame(s) on the page near the image. If false, loads the new frame(s) into the place gun.
	*/
	virtual void Set(bool liveCaption, bool placeFrameInLayout) = 0;
	
	/** 	Return the live caption flag
	*/
	virtual bool GetUseLiveCaption() const = 0;
	
	/** 	Return the 'place frame in layout' flag
	*/
	virtual bool GetPlaceFrameInLayout() const = 0;
	
};


#endif // __IGenerateCaptionCmdData__
