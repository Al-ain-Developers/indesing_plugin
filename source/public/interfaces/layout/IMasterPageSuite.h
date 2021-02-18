//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IMasterPageSuite.h $
//  
//  Owner: Brendan O'Shea
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
#ifndef __IMasterPageSuite__
#define __IMasterPageSuite__

// Interfaces:
#include "IPMUnknown.h"
#include "MasterPageID.h"

// Includes:

/** Suite interface to manipulate properties of master spreads (kMasterPagesBoss).

	@ingroup layout_spread
	@ingroup layout_util
	@ingroup layout_suite
	@see kMasterPagesBoss
*/
class IMasterPageSuite : public IPMUnknown
{
public:
	/**	Are any of the selected items master page overrides?
		@return bool16 - kTrue if some override is selected, kFalse otherwise
	 */
	virtual	bool16	CanRemoveMasterOverride() const = 0;

	/**	Can any of the selected items have their link to their controlling master item severed?
		@return bool16 - kTrue if some override is selected and link can be broken, kFalse otherwise
	 */
	virtual	bool16	CanBreakMasterOverrideLink() const = 0;

	/**	Unoverride the selected items - deletes local page item, allows master item to draw again
		@return none
	 */
	virtual	void	RemoveMasterOverride() = 0;

	/**	Sever the link of selected items to their owning master page item
		@return none
	 */
	virtual	void	BreakMasterOverrideLink() = 0;

};

#endif	// __IMasterPageSuite__

