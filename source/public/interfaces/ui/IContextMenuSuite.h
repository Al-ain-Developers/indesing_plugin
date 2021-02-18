//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/ui/IContextMenuSuite.h $
//  
//  Owner: Ryan Gano
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
#ifndef __IContextMenuSuite__
#define __IContextMenuSuite__

// Interfaces:
#include "IPMUnknown.h"

// Includes:

class IContextMenuSuite : public IPMUnknown
{
public:
	/**	Does this Suite have a context menu to display?
		@param none
		@return bool16 - kTrue means that there is a Context menu to display
	 */
	virtual bool16 HasContextMenu() const = 0;

	/**	Get the name of the Context Sensitive Menu to display
		@param none
		@return PMString - Name of the appropriate menu
	 */
	virtual PMString GetContextMenuName() const = 0;
};

#endif	// __IContextMenuSuite__

