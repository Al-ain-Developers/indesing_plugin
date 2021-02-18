//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkTableContext.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "TableTypes.h"

/**	This interface provides context for a marking operation, group, or context. That is, 
	IPreflightArtworkMarkInfo and IPreflightArtworkGroupInfo can tell you all about the specifics 
	of the marking operation but this interface tells you what "high level" (ie table
	or table cell) drawing operation it's associated with.

	Typical use is something like this:

		MyRule::Visit(IPreflightVisitInfo* iVisit)
		{
			if (iVisit->GetObjectID().GetClass() == kPrefligthOM_ArtworkMark)
			{
				InterfacePtr<IPreflightObject> iObj(iVisit->QueryObject());

				// Is this drawn as part of a table?
				InterfacePtr<IPreflightArtworkContext> iContext(iObj, UseDefaultIID());
				InterfacePtr<IPreflightArtworkTableContext> iTableContext(iContext->QueryParentTableContext());

				if (iTableContext)
				{
					// Yes, part of a table..
					InterfacePtr<ITableModel> iModel(iTableContext->GetTableModelRef(), UseDefaultIID());
					//...
				}
			}
		}
*/

class IPreflightArtworkTableContext : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKTABLECONTEXT };

	/** Returns whether this node is a metadata (context) node representing the table information
		for a bunch of child marking operations. This is not usually that useful unless you're 
		inspecting the tree in a relatively advanced way. Typically you would use GetDepth()
		to see if this is being drawn as part of a table, and GetInfo() to get the innermost
		information.

		@return kTrue if a table node; kFalse otherwise.
	*/
	virtual bool IsTableNode() const = 0;

	/** Get the text and text-subpart depth. Since text and subparts can be nested the artwork 
		node may be "under" more than one context. This method returns the number of 
		text parent nodes in the tree walking up to the root.
	*/
	virtual int32 GetDepth(bool stopAtOne = kFalse) const = 0;

	/** Walks toward the root node looking for a node for which IsTextNode() is true. When it
		finds one, returns a refcounted context pointer to it.

		@return The first parent text context, or nil if there is no containing text context.
	*/
	virtual IPreflightArtworkTableContext* QueryParent() const = 0;

	/** @return the table model's UIDRef.
	*/
	virtual UIDRef GetTableModelRef() const = 0;

	/** @return the table frame's UIDRef.
	*/
	virtual UIDRef GetTableFrameRef() const = 0;

	/** @return the specified grid area (typically a cell). Will be empty if it's the entire table.
	*/
	virtual GridArea GetGridArea() const = 0;
};

