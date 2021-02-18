//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IInCopyInterchangeExportOptionsCmdData.h $
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
#ifndef __IInCopyInterchangeExportOptionsCmdData__
#define __IInCopyInterchangeExportOptionsCmdData__

#include "IPMUnknown.h"
#include "InCopySharedID.h"

/** Command data interface for kSetInCopyInterchangeExportOptionsCmdBoss.
*/
class IInCopyInterchangeExportOptionsCmdData  : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINCOPYINTERCHANGEEXPORTOPTIONSCMDDATA };

	/** Specifies whether graphic proxy data is included - only call this function if you want the command to set this option.
		@param includeAllResources kTrue to force export of all resources , kFalse to only export the resources used by the story.
	*/
	virtual void SetIncludeGraphicProxyData(bool16 includeProxies) = 0;

	/** Returns kTrue if SetIncludeGraphicProxyData has been called and the command should set this option, kFalse otherwise.
	*/
	virtual bool16 IsIncludeGraphicProxyDataSet() const = 0;

	/** Returns kTrue if graphic proxy data is included, kFalse otherwise.
		@pre IsIncludeGraphicProxyDataSet returns kTrue
	*/
	virtual bool16 GetIncludeGraphicProxyData() const = 0;

	/** Specifies whether all resources  of interest to InCopy (such as fonts, styles and swatches) should be forced to export
 		- only call this function if you want the command to set this option.
		@param includeAllResources kTrue to force export of all resources , kFalse to only export the resources used by the story.
	*/
	virtual void SetIncludeAllResources(bool16 includeAllResources)= 0;

	/** Returns kTrue if SetIncludeAllResources has been called and the command should set this option, kFalse otherwise.
	*/
	virtual bool16 IsIncludeAllResourcesSet() const = 0;

	/** Returns kTrue  if resources  of interest to InCopy (such as fonts, styles and swatches) should be forced to export,
		 kFalse to only export resources used by the story.
		@pre IsIncludeAllResourcesSet returns kTrue
	*/
	virtual bool16 GetIncludeAllResources() const = 0;
};

#endif
