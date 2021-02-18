//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/IApplyCJKGridDirection.h $
//  
//  Owner: Heath Lynn
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
//  Notes: The ApplyCJKGridCmd applies the attributes of the CJKGrid to a 
//  specified range of text.  Due to constraints on scaling attributes
//  the attributes are applied differently depending on the direction
//  of the story.  This optional data interface allows you to force
//  the attributes to be applied using a particular direction.  By 
//  default, this data merely uses the story direction.
//  
//========================================================================================

#pragma once
#ifndef __ApplyCJKGridDirection__
#define __ApplyCJKGridDirection__

#include "IPMUnknown.h"
#include "ICompositionStyle.h"
#include "CTextEnum.h"
#include "IDrawingStyle.h"

class ICJKGridData;
class ICJKLayoutGridDefaults;

/** IApplyCJKGridDirection is an interface on kApplyCJKGridFormatCmdBoss.  This command applies
attributes from the grid to the specified range.  The scaling attributes need to be applied differently
based on orientation.  There were cases, such as place and import, where a temporary story was used
that didn't have the desired orientation.  This data allows you either use the story's direction, or
you can force it to use the desired direction.
*/
class IApplyCJKGridDirection  : public IPMUnknown
{

public:

	/** When attributes are applied they can be applied in either direction, or in the direction of the story.
	*/
	enum ApplyDirection
	{
		kApplyStoryDirection,
		kForceVerticalDirection,
		kForceHorizontalDirection
	};



	/** Gets the direction option.
	@return A value in ApplyDirection enumeration that specifies the option.
	*/
	virtual ApplyDirection GetDirectionOption() = 0;
	
	/** Sets the direction option.
	@param applyDirection IN The ApplyDirection value.
	*/
	virtual void SetDirectionOption( ApplyDirection applyDirection ) = 0;

};

#endif
