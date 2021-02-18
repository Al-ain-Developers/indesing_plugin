//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkTextSourceData.h $
//  
//  Owner: Brendan O'Shea
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
#include "itextRangeNode.h"
#include "HyperlinkID.h"

/**
	@ingroup layout_hyper
*/
class IHyperlinkTextSourceData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKTEXTSOURCEDATA };

	/**	Set the text range reference of the hyperlink that is associated with this source
		@param rangeRef - reference of the hyperlink text range
	 */
	virtual void	SetHyperlinkRangeReference(TextRangeReference rangeRef) = 0;
	/**	Get the hyperlink text range reference that is associated with this source
		@param none
		@return TextRangeReference - text range reference of the hyperlink
	 */
	virtual TextRangeReference		GetHyperlinkRangeReference() const = 0;	

	/**	Get the story which owns the hyperlink text source
		@param none
		@return UID - story UID
	 */
	virtual UID GetOwningStoryUID() const = 0;
	
	/** Set the character style to be applied to the hyperlink source
		@param charStyle - UID of the character style
	*/
	virtual void SetCharStyle(UID charStyle) = 0;
	/** Get the character style applied on the hyperlink text source
		@return UID - UID of the character style applied.
	*/
	virtual UID GetCharStyle() const = 0;
	
};

