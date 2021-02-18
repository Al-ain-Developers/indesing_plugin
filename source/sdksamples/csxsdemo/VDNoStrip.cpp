//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/csxsdemo/VDNoStrip.cpp $
//  
//  Owner: Timothy Brand-Spencer
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2013 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"
#include "InterfaceFactory.h"

extern bool16 gFalse;

// References all implementations to stop the compiler dead stripping them from the executable image.
void DontDeadStrip();

void DontDeadStrip()
{
	if (gFalse)
	{
#include "VDFactoryList.h"
	}
}
