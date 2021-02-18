//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IUIFlagData.h $
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
//========================================================================================

#pragma once
#ifndef __IUIFlagData__
#define __IUIFlagData__

#include "DocumentID.h"

#include "IPMUnknown.h"
#include "IImportProvider.h"

/** Data interface storing UIFlag parameter common to commands
	@ingroup arch_coredata
*/
class IUIFlagData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IUIFLAGDATA };

	/** Initialize the settings of this object from the settings of another object */
	virtual void Set(const IUIFlagData &data) = 0;

	/** Set the flags */
	virtual void Set(UIFlags uiFlags = kFullUI) = 0;

	/** Get the flags */
	virtual UIFlags GetUIFlags() const = 0;
};

#endif
