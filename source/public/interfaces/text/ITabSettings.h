//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITabSettings.h $
//  
//  Owner: Ric Kamicar
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
#ifndef __ITabSettings__
#define __ITabSettings__

#include "IPMUnknown.h"

/** Interface for default tab table settings. Default tabs are the implicit tab stops within a paragraph.
	@ingroup text_tab
*/
class ITabSettings : public IPMUnknown
{
public:
	virtual	void		SetDefaultTabInterval(PMReal nInterval) = 0;
	/** @note The interval is the distance between each tab. */
	virtual	PMReal	GetDefaultTabInterval() const = 0;
};

#endif
