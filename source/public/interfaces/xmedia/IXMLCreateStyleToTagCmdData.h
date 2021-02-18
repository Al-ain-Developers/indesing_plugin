//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLCreateStyleToTagCmdData.h $
//  
//  Owner: Will Lin
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
#ifndef __IXMLCreateStyleToTagElementsCmdData__
#define __IXMLCreateStyleToTagElementsCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"

/** Data interface for creating XML elements using style-to-tag mapping;
	for client code, preferable to use IXMLMappingCommands methods, not likely
	to require this interface.
*/
class IXMLCreateStyleToTagElementsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLCREATESTYLETOTAGELEMENTSCMDDATA };

	/**	XML tag UID to apply to stories that need to be tagged. If kInvalidUID
		is used, "Story" will be used (and created if necessary)
		@param storyTagUID specifies tag (IXMLTag) to use for the story itself  
	 */
	virtual void Set(UID storyTagUID = kInvalidUID) = 0;

	/**	Tag to use when applying tags to untagged stories
		@return UID of the tag (for the story) stored on this interface.
	 */
	virtual UID GetStoryTagUID(void) const = 0;
};

#endif	// __IXMLCreateStyleToTagElementsCmdData__

