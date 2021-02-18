//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IDupHyperlinkTextSourceData.h $
//  
//  Owner: Ryan Gano
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
#ifndef __IDupHyperlinkTextSourceData__
#define __IDupHyperlinkTextSourceData__

#include "HyperlinkID.h"
#include "itextRangeNode.h"

/** This class stores information needed in order to
	duplicate a text source (used in conjunction with
	the DupHyperlinkTextSourceCmd.)
*/
class IDupHyperlinkTextSourceData : public IPMUnknown
{
public:
	enum {kDefaultIID = IID_IDUPHYPERLINKTEXTSOURCEDATA};

	/** Use this method to setup of the data
		@param &hyperLinkSource - the source to be duplicated
		@param &newRangeRef - The range reference this source should be duplicated to
		@param &targetStory - The UIDRef of the story that this hyperlink should be duplicated to
	*/
	virtual void Set(	const UIDRef	&hyperLinkSource, 
						TextRangeReference newRangeRef,
						const UIDRef	&targetStory) = 0;

	/** Get the UIDRef of the source that we are duplicating
		@return - The source UIDRef
	*/
	virtual const UIDRef	&GetSource() const = 0;

	/** Get the text range reference to duplicate to
		@return - The text range reference
	*/
	virtual TextRangeReference	GetNewHyperlinkRangeReference() const = 0;

	/** Get the UIDRef of the story that we are duplicating into
		@return - The target story UIDRef
	*/
	virtual const UIDRef	&GetTargetStory() const = 0;
};


#endif // __IDupHyperlinkTextSourceData__

