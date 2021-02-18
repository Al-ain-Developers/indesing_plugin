//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IDocPresetListMgr.h $
//  
//  Owner: Rich Gartland
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
#ifndef __IDocPresetListMgr__
#define __IDocPresetListMgr__

#include "IGenStlEdtListMgr.h"
#include "InCopyCoreID.h"

/** Subclass of IGenStlEdtListMgr. This interface adds nothing to its base class and
is preserved for historical reasons and to avoid changing client code that was
written against this interface.

This interface is InCopy only, to store/retrieve InCopy document style presets

@see IGenStlEdtListMgr
*/

class IDocPresetListMgr : public IGenStlEdtListMgr
{	
public:
	enum { kDefaultIID = IID_IDOCPRESETLISTMGR };
};

#endif
