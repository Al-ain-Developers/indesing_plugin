//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IToolbarSizeInfo.h $
//  
//  Owner:lance bushore
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
#ifndef __IToolbarSizeInfo__
#define __IToolbarSizeInfo__

#include "IPMUnknown.h"
#include "AppUIID.h"
#include "IUserInterfacePreferences.h"

/**	IToolbarSizeInfo is interface used to represent the various states that a toolbox/toolbar can be in.
	@see IUserInterfacePreferences, PaletteRefUtils
*/
class IToolbarSizeInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ITOOLBARSIZEINFO };

	/** Get the size that corresponds to a particular toolbox state */
	virtual PMPoint GetToolbarVariantSize(IUserInterfacePreferences::ToolboxState whichVariant) const = 0;
	
	/** Get the current state of the toolbox */
	virtual IUserInterfacePreferences::ToolboxState GetCurrentToolbarVariant() const = 0;

	/** Change the current state of the toolbox */
	virtual void SetCurrentToolbarVariant(IUserInterfacePreferences::ToolboxState newState) = 0;
		
};


#endif // __IToolbarSizeInfo__
