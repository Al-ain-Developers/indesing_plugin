//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkShapeContext.h $
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

/**	This interface provides context for a marking operation, group, or context. That is, 
	IPreflightArtworkMarkInfo and IPreflightArtworkGroupInfo can tell you all about the specifics 
	of the marking operation but this interface tells you what "high level" shape or shape subpart
	it's associated with.

	@see IPreflightArtworkContext for a longer description of the relationship between marking
		operations and contexts, and how you might use this interface. In particular you would
		normally use IPreflightArtworkContext::QueryParentShapeContext() to obtain this interface.
*/

class IPreflightArtworkShapeContext : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKSHAPECONTEXT };

	/** Returns whether this node is a metadata (context) node representing the shape information
		for a bunch of child marking operations. This is not usually that useful unless you're 
		inspecting the tree in a relatively advanced way. Typically you would use QueryShape()
		if what you want to know the shape associated with an arbitrary bit of artwork.

		@return kTrue if a shape node; kFalse otherwise.
	*/
	virtual bool IsShapeNode() const = 0;

	/** Get the shape UIDRef. Ie this is something you can query an IShape from. See also the 
		subpart (ie GetSubPart()) if you want to know whether it's referring to a specific part
		of that shape.

		Also note that the page item might be a page, or a spread, in unusual circumstances.

		@return The UIDRef of the shape, or UIDRef() if this is not a shape context.
	*/
	virtual UIDRef GetShapeRef() const = 0;

	/** Get the subpart referred to by this node. This is only valid if IsShapeNode() is true.
		The subpart is typically one of the kPreflightOSP_* constants in PackageAndPreflightID.h.

		@return The subpart code.
	*/
	virtual ClassID GetSubPart() const = 0;

	/** Get the spread this marking operation is associated with. This method gets the shaperef
		from this node, or any suitable parent, and from that determines the spread.

		@return A UIDRef of the spread. 
	*/
	virtual UIDRef GetSpreadRef() const = 0;
};

