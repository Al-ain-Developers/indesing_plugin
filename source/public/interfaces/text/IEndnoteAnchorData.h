//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IEndnoteAnchorData.h $
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
#include "IOwnedItem.h"
#include "IFootnoteNumber.h"
#include "TextID.h"

/** This interface is used to access the endnote anchor details from an endnote text range.
@ingroup text_layout
*/
class IEndnoteAnchorData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IENDNOTEANCHORDATA};

	/**	INTERNAL USE: Set the UIDRef of the kEndnoteAnchorBoss associated with the endnote text range.
	*/
	virtual void	SetEndnoteAnchorData(UIDRef anchorRef) = 0;

	/** Get a reference counted IOwnedItem pointer for the kEndnoteAnchorBoss associated with the endnote text range.
	 */
	virtual IOwnedItem*		QueryAnchor() const = 0;

	/** Get a reference counted IFootnoteNumber pointer for the kEndnoteAnchorBoss associated with the endnote text range.
	*/
	virtual IFootnoteNumber* QueryEndnoteNumber() const = 0;

	/**	Get the UID of the kEndnoteAnchorBoss associated with the endnote text range.
	*/
	virtual UID	GetEndnoteAnchorData() const = 0;

	/**	Get the UIDRef of the kEndnoteAnchorBoss associated with the endnote text range.
	*/
	virtual UIDRef GetEndnoteAnchorRef() const = 0;
};

