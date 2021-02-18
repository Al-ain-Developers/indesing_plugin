//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLMappingCmdData.h $
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
#ifndef __IXMLMappingCmdData__
#define __IXMLMappingCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"

/** Data interface for working with commands to implement style to tag and tag to style mappings;
	when writing client code, use IXMLMappingCommands methods rather than processing low-level commands. */
class IXMLMappingCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLMAPPINGCMDDATA };

	/**	Specify the style and tag that are to be used in a mapping relation
		@param map specifies the target map into which the style-tag pair will go
		@param styleUID UID of a style in one of the style name-tables
		@param tagUID UID of tag stored on this interface
	 */
	virtual void Set(const UIDRef& map, UID styleUID, UID tagUID) = 0;
	
	/**	Return the tag to style or style to tag map that contains the style and tag UIDs
		
		@return UIDRef of mapping 
	 */
	virtual const UIDRef& GetMap() const = 0;


	/**	Return the style UID
		
		@return UID of style stored on this interface
	 */
	virtual UID GetStyleUID() const = 0;

	/**	Return the tag UID
		
		@return UID of tag (IXMLTag) stored on this interface
	 */
	virtual UID GetTagUID() const = 0;
};

#endif
