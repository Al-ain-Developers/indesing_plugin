//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/incopyfileactionsui/InCopyFileActionsUIPlugin.cpp $
//  
//  Owner: Chris Parrish
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

#include "VCPlugInHeaders.h"
#include "PlugIn.h"

static PlugIn gPlugIn;

// ----- This is the main entry point from the application to the plug-in.
//		 The application calls this function when the plug-in is installed 
//		 or loaded. This function is called by name, so it must be called 
//		 GetPlugIn, and defined as C linkage.

IPlugIn *GetPlugIn()
{
	return &gPlugIn;
}



