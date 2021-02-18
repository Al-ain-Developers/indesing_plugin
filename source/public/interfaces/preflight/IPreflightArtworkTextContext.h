//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightArtworkTextContext.h $
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
#include "DrawPassInfo.h"

class ParcelKey;

/**	This interface provides context for a marking operation, group, or context. That is, 
	IPreflightArtworkMarkInfo and IPreflightArtworkGroupInfo can tell you all about the specifics 
	of the marking operation but this interface tells you what "high level" (ie wax run)
	operation it's associated with.

	@see IPreflightArtworkContext for a longer description of the relationship between marking
		operations and contexts.

	Typical usage:

		MyRule::Visit(IPreflightVisitInfo* iVisit)
		{
			if (iVisit->GetObjectID().GetClass() == kPrefligthOM_ArtworkMark)
			{
				InterfacePtr<IPreflightObject> iObj(iVisit->QueryObject());

				// Is this drawn as part of a table?
				InterfacePtr<IPreflightArtworkContext> iContext(iObj, UseDefaultIID());
				InterfacePtr<IPreflightArtworkTextContext> iTextContext(iContext->QueryParentTextContext());

				if (iTextContext)
				{
					// Yes, part of a a text run.. use text model to poke around more..
				}
			}
		}

*/

class IPreflightArtworkTextContext : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTARTWORKTEXTCONTEXT };

	/** Returns whether this node is a metadata (context) node representing the text information
		for a bunch of child marking operations. Normally you'd use this only if walking the
		context stack manually.

		@return kTrue if a shape node; kFalse otherwise.
	*/
	virtual bool IsTextNode() const = 0;

	/** @return the text model. Returns UIDRef() if this is not a text context node.
	*/
	virtual UIDRef GetTextModelRef() const = 0;

	/** @return The UID of the story thread dictionary. kInvalidUID if not a text context node.
	*/
	virtual UID GetThreadDictUID() const = 0;

	/** @return The key of the story thread. 0 if not a text context node.
	*/
	virtual uint32 GetThreadDictKey() const = 0;

	/** @return The key of the parcel the text is contained in. ParcelKey() if not a text context node.
	*/
	virtual ParcelKey GetParcelKey() const = 0;

	/** @return The starting index of the text, relative to the containing parcel. 0 if not a text context node.
	*/
	virtual TextIndex GetParcelRelativeStart() const = 0;

	/** @return The absolute (ie relative to model) starting index of the text. 0 if not a text context node.
	*/
	virtual TextIndex GetAbsoluteStart() const = 0;

	/** @return The span of the wax run. Returns 0 if this is not a text context node.
	*/
	virtual int32 GetSpan() const = 0;

	/** @return The pass of the text marking operation.
	*/
	virtual Text::DrawPassInfo::Pass GetPass() const = 0;

	/** @return The adornment class ID of the text marking operation, if the marking is done by an adornment.
			If not, returns kInvalidClass.
	*/
	virtual ClassID GetAdornmentClassID() const = 0;
};

