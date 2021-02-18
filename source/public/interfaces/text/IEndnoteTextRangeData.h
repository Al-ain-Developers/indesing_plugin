//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IEndnoteTextRangeData.h $
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
#include "itextRangeNode.h"
#include "TextID.h"

/** This interface is used to set or retrieve the endnotes text range details associated with an endnote.
@ingroup text_layout
*/
class IEndnoteTextRangeData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IENDNOTETEXTRANGEDATA};

	/**	INTERNAL USE: Set the text range reference for the endnote text.
	 */
	virtual void	SetEndnoteRangeReference(TextRangeReference rangeRef) = 0;

	/**	INTERNAL USE: Get the text range reference for the endnote text.
	*/
	virtual TextRangeReference		GetEndnoteRangeReference() const = 0;

	/**	Get the UIDRef of the story in which the endnote text is located.
	 */
	virtual UIDRef GetOwningStoryRef() const = 0;

	/** Get the reference counted ITextModel pointer for the story in which the endnote text is located.
	*/
	virtual ITextModel*	QueryOwningStory() const = 0;

	/** Get the starting text index for the endnote text.
		This is actually the text index of the left XML-like marker before the endnote text. The endnote number is at
		the next text index, followed by the separator characters and then the actual endnote text.
	*/
	virtual TextIndex GetStartTextIndex() const = 0;

	/** Get the ending text index for the endnote text.
	This is actually the text index of the right XML-like marker after the endnote text.
	*/
	virtual TextIndex GetEndTextIndex() const = 0;
};

