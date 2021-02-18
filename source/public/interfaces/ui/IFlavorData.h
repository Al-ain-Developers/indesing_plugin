//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IFlavorData.h $
//  
//  Owner: Dave Burnard
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
//  Interface for storing flavors (clipboard and drag drop data types).
//  
//========================================================================================

#pragma once
#ifndef __IFlavorData__
#define __IFlavorData__

#include "IPMUnknown.h"
#include "PMFlavorTypes.h"

#include "DragDropID.h"

/** Interface for storing an ExternalPMFlavor on a boss.
*/
class IFlavorData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IFLAVORDATA };

public:
	/** Set the data

		@param flavor IN the flavor to store
		@param flavorFlags IN to store with the flavor
	*/
	virtual void Set(ExternalPMFlavor flavor, PMFlavorFlags flavorFlags = kNormalFlavorFlag) = 0;
	/** Get the stored ExternalPMFlavor */
	virtual ExternalPMFlavor GetFlavor() const = 0;
	/** Get the PMFlavorFlags for the stored flavor */
	virtual PMFlavorFlags GetFlavorFlags() const = 0;
};

#endif // __IFlavorData__
