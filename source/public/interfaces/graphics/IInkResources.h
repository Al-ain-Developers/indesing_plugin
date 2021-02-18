//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInkResources.h $
//  
//  Owner: jargast
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
//  Page items that have ink resources should include this interface
//  
//========================================================================================

#pragma once
#ifndef __IInkResources__
#define __IInkResources__

#include "IPMUnknown.h"
#include "ColorSystemID.h"

class IInkResourceData;

/**	Interface to report ink usage for a page item. For example, an EPS knows which
	inks it uses differently from a PDF. So, the EPSPageItem has its own version
	of GetUsedInks, which will record its own ink usage into the IInkResourceData.
	@see IInkResourceData
*/
class IInkResources : public IPMUnknown
{
public:
	/** Default enum
	*/
	enum { kDefaultIID = IID_IINKRESOURCES };

	/**	Adds the process and spot inks that this item uses.  The list will ignore duplicates
		so that the client does not have to check for existance before adding.

		@param iInkResourceData IN the interface that records ink usage
	 */
	virtual void GetUsedInks (IInkResourceData* iInkResourceData) = 0;
};

#endif
