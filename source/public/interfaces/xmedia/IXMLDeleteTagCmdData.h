//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLDeleteTagCmdData.h $
//  
//  Owner: Lonnie Millett
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
#ifndef __IXMLDeleteTagCmdData__
#define __IXMLDeleteTagCmdData__


#include "IPMUnknown.h"
#include "XMLID.h"

/**  Data interface for deleting XML tags and specifying replacement tags; use IXMLTagCommands::DeleteTag from client code
	rather than processing low-level commands.
*/
class IXMLDeleteTagCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLDELETETAGCMDDATA };
	
	/**	Set a replacement tag for one being deleted
		@param replacementTag replacementTag is tag to replace deleted tag with
		@param tagListUIDRef is the taglist you are deleting from 
	 */
	virtual void Set(UID replacementTag, const UIDRef& tagListUIDRef) = 0;

	/**	Get the replacement tag
		@return UID replacement tag
	 */
	virtual UID GetReplacementTag(void) const = 0;

	/**	Get the tag list UIDRef
		@return UIDRef tag-list
	 */
	virtual UIDRef GetTagListUIDRef(void) = 0;
};


#endif

