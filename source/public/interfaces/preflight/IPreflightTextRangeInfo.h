//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightTextRangeInfo.h $
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

class ITextModel;
class ParcelKey;

/**	This interface provides text range information corresponding to a preflight text range
	or wax object. Text is referenced relative to its text story thread to make invalidation
	more reliable.

	You'd use this information if you needed to query the text model as part of writing 
	a preflight rule.
*/

class IPreflightTextRangeInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTTEXTRANGEINFO };

	/** Get a refcounted text model interface.
		@return The text model interface related to this text range.
	*/
	virtual ITextModel* QueryTextModel() const = 0;

	/** @return the text model. Returns UIDRef() if this is not a text context node.
	*/
	virtual UIDRef GetTextModelRef() const = 0;

	/** @return The UID of the story thread dictionary. kInvalidUID if not a text context node.
	*/
	virtual UID GetThreadDictUID() const = 0;

	/** @return The key of the story thread. 0 if not a text context node.
	*/
	virtual uint32 GetThreadDictKey() const = 0;

	/** @return The key of the parcel the text is contained in.
	*/
	virtual ParcelKey GetParcelKey() const = 0;

	/** @return The starting index of the text, relative to the parcel it's contained in. 0 if not a text context node.
	*/
	virtual TextIndex GetParcelRelativeStart() const = 0;

	/** @return The absolute (ie relative to model) starting index of the text. 0 if not a text context node.
	*/
	virtual TextIndex GetAbsoluteStart() const = 0;

	/** @return The span of the wax run. Returns 0 if this is not a text context node.
	*/
	virtual int32 GetSpan() const = 0;

	/** Initialize. Internal use only.
	*/
	virtual void Initialize() = 0;
};

