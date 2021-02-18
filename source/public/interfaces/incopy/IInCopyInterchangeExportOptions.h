//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyInterchangeExportOptions.h $
//  
//  Owner: Michele Stutzman
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
#ifndef __IInCopyInterchangeExportOptions__
#define __IInCopyInterchangeExportOptions__

#include "IPMUnknown.h"
#include "InCopySharedID.h"


/** Provides InCopy story interchange export options. Interface on kWorkspaceBoss for 
initial export and on kTextStoryBoss and kSplineItemBoss. */
class IInCopyInterchangeExportOptions : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYINTERCHANGEEXPORTOPTIONS };

	/** Set method to specify whether graphic proxy data should be included when export or not.
		@param includeProxies- A flag indicating whether to include graphic proxy data or not.
	*/
	virtual void SetIncludeGraphicProxyData(bool16 includeProxies) = 0;

	/** Get method for the include graphic proxy data export option.
		@return bool16 whether graphic proxy data is included.
	*/
	virtual bool16 GetIncludeGraphicProxyData() const = 0;

	/** Specifies whether all resources  of interest to InCopy (such as fonts, styles and swatches) should be forced to export.
		@param includeAllResources kTrue to force export of all resources , kFalse to only export the resources used by the story.
	*/
	virtual void SetIncludeAllResources(bool16 includeAllResources)= 0;

	/** Returns kTrue if resources of interest to InCopy (such as fonts, styles and swatches) should be forced to export,
		kFalse to only export resources used by the story.
	*/
	virtual bool16 GetIncludeAllResources() const = 0;
};
#endif // __IInCopyInterchangeExportOptions__
