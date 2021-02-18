//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IXPPageItemDrawSetup.h $
//  
//  Owner: Matt Phillips
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
//  Description:
//  A page item may implement this interface, in which case the interface will be
//  responsible for setting up the transparency attributes (opacity, blend mode, knockout
//  group, isolation group).
//  
//========================================================================================

#pragma once
#ifndef __IXPPageItemDrawSetup__
#define __IXPPageItemDrawSetup__

#include "IPMUnknown.h"
#include "XPID.h"
#include "BravoForwardDecl.h"

class GraphicsData;

class IXPPageItemDrawSetup : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXPPAGEITEMDRAWSETUP };

	// BeginObject()
	// EndObject()
	// -------------
	// These allow you full control over the setup and teardown of the xp 
	// attributes.  Return true to indicate that you've done the setup, false
	// to have the default setup applied (in which case you'll be called for
	// the isolation space, below).  Note: these are called even when the 
	// display preferences are for transparency "off".  So be sure to check
	// for that case if you want to follow the existing conventions.
	virtual bool32 BeginObject(GraphicsData* gd, int32 flags) = 0;
	virtual bool32 EndObject(GraphicsData* gd, int32 flags) = 0;

	// GetIsolationSpace()
	// ReleaseIsolationSpace()
	// -----------------------
	// For an isolation group, these are called to get the iso blend space.
	// Return nil to GetIsolationSpace to use the document blending space.
	virtual AGMColorSpace* GetIsolationSpace() = 0;
	virtual void ReleaseIsolationSpace(AGMColorSpace*) = 0;
};


#endif
