//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IPaletteMgrService.h $
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
#ifndef __IPaletteMgrService_h__
#define __IPaletteMgrService_h__

#include "IPMUnknown.h"
#include "PMLocaleId.h"

class IPaletteMgr;

/** Interface available to clients that need to know when Palette Manager is starting up or is about to shut down.
*/
class IPaletteMgrService : public IPMUnknown
{
public:
	/** Called just after Palette manager has started up and opened/positioned it's palettes. */
	virtual void PaletteMgrStarted() = 0;
	/** Called as Palette manager is shutting down just before the palettes are closed. */
	virtual void PaletteMgrAboutToShutdown() = 0;
};

#endif // __IPaletteMgrService_h__

