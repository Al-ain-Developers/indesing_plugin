//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLCopyMappingCmdData.h $
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
//  
//  Purpose:
//  
//========================================================================================

#pragma once
#ifndef __IXMLCopyMappingCmdData__
#define __IXMLCopyMappingCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"

/** Data interface for copying style to tag and tag to style mappings;
	if you're writing client code, use IXMLMappingCommands instead.

	@see IXMLMappingCommands
	@see kXMLCopyTagToParaStyleMapCmdBoss
	@see kXMLCopyParaStyleToTagMapCmdBoss
*/
class IXMLCopyMappingCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLCOPYMAPPINGCMDDATA };

	/**	Specify the source and target maps for the copy
		@param sourceMap identifies the source mapping for the copy
		@param targetMap identifies the destination where contents of the sourceMap will be copied to
	 */
	virtual void Set(const UIDRef& sourceMap, const UIDRef& targetMap) = 0;
	
	/**	Accessor for source map stored on this interface
		
		@return the source map
	 */
	virtual const UIDRef& GetSourceMap() const = 0;

	/**	Accessor for target map on this interface
		
		@return the style as UIDRef
	 */
	virtual const UIDRef& GetTargetMap() const = 0;
};

#endif
