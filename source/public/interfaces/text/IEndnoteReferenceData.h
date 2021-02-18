//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IEndnoteReferenceData.h $
//  
//  Owner: shagupta
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#pragma once

#include "IPMUnknown.h"
#include "IEndnoteTextRangeData.h"
#include "TextID.h"

/** This interface is used to access the endnote text details from an endnote reference.
@ingroup text_layout
*/
class IEndnoteReferenceData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IENDNOTEREFERENCEDATA};

	/**	INTERNAL USE: Set the UIDRef of the kEndnoteTextRangeBoss associated with the endnote.
	 */
	virtual void	SetEndnoteReferenceData(UIDRef endnoteRef) = 0;

	/** Get the reference counted IEndnoteTextRangeData pointer associated with the endnote text.
	 */
	virtual IEndnoteTextRangeData*		QueryEndnoteReference() const = 0;

	/** Get the UIDRef of the kEndnoteTextRangeBoss associated with the endnote
	*/
	virtual UIDRef	GetEndnoteRef() const = 0;
};

