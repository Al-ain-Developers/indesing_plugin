//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLCreateTagCmdData.h $
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
#ifndef __IXMLCreateTagCmdData__
#define __IXMLCreateTagCmdData__


#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

/** Data interface for creating XML tags and adding to the tag list;
	use IXMLTagCommands from client code to create tags rather than
	process low-level commands.
*/
class IXMLCreateTagCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLCREATETAGCMDDATA };

	/**	Set up data on this interface.
		@param tagName name of tag to create
		@param color UID of the color to be used by the tag
		@param tagListUIDRef UIDRef of the tag list to add the new tag to
	 */
	virtual void Set(const WideString& tagName, UID color, const UIDRef& tagListUIDRef) = 0;

	/**	Accessor for the get the tag name stored on this interface
		@return tagname specifies tag name stored on this interface.
	 */
	virtual const WideString& GetTagName(void) const = 0;

	/**	Accessor for the get the tag color stored on this interface
		@return color specifies tag color stored on this interface.
	 */
	virtual UID GetTagColor(void) const = 0;

	/**	Get the tag list UIDRef stored on this interface
		@return UIDRef of taglist
	 */
	virtual UIDRef GetTagListUIDRef(void) = 0;
};


#endif	// __IXMLCreateTagCmdData__

