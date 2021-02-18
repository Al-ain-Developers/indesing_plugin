//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLStyleToTagOptionsData.h $
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
#ifndef __IXMLStyleToTagOptionsData__
#define __IXMLStyleToTagOptionsData__

#include "IPMUnknown.h"
#include "XMLID.h"

/** Data interface for specifying style to tag mapping options. */
class IXMLStyleToTagOptionsData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLSTYLETOTAGOPTIONSDATA };

	/** Specify the mapping options for master page stories, pasteboard stories and empty stories.
		@param includeMasterPage specifies whether or not master pages stories are included when mapping.
		@param includePasteboard specifies whether or not pasteboard stories are included when mapping.
		@param includeEmptyStories specifies whether or not empty stories are included when mapping.
	 */
	virtual void Set(bool16 includeMasterPage, bool16 includePasteboard, bool16 includeEmptyStories) = 0;

	/**	Return flag indicating if master page stories are included when mapping.		
		@return bool16 include master page stories or not.
	 */
	virtual bool16 GetIncludeMasterPageStories() const = 0;

	/**	Return flag indicating if pasteboard stories are included when mapping.		
		@return bool16 include pasteboard stories or not.
	 */
	virtual bool16 GetIncludePasteboardStories() const = 0;

	/**	Return flag indicating if empty stories are included when mapping.		
		@return bool16 include empty stories or not.
	 */
	virtual bool16 GetIncludeEmptyStories() const = 0;
};

#endif	// __IXMLStyleToTagOptionsData__
