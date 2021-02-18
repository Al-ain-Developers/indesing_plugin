//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLHierarchyCmdData.h $
//  
//  Owner: robin briggs
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
#ifndef __IXMLHierarchyCmdData__
#define __IXMLHierarchyCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

class UIDList;

/**  Data interface for adding elements to the logical structure tree.
	Similar to IHierarchyCmdData, but handles adding only one element
	at a time. Not likely to be used from client code, use IXMLElementCommands wrapper methods rather than
	processing low-level command.
*/
class IXMLHierarchyCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLHIERARCHYCMDDATA };

	/**	Specify where on the hierarchy to insert the new item; the parent
		element, and the index within the parent's list of children.

		@param newItem specifies item to add
		@param parent specifies its parent
		@param indexInParent specifies where in the parent the item should be added
	 */
	virtual void Set(const XMLReference& newItem, const XMLReference& parent, int32 indexInParent) = 0;
	
	/**	Return the item to add

		
		@return XMLReference of item to add 
	 */
	virtual const XMLReference& GetElementToAdd() const = 0;
	

	/**	Return the parent element for the new item
		
		@return XMLReference of parent of new item 
	 */
	virtual const XMLReference& GetParent() const = 0;
	
	/**	Return the index within the parent's list of children
		
		@return int32 giving the index within the parent's list of children
	 */
	virtual int32 GetIndexInParent() const = 0;
};

#endif	// __IXMLHierarchyCmdData__
