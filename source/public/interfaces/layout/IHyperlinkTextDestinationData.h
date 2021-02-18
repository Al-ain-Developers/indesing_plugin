//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkTextDestinationData.h $
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
#ifndef __IHyperlinkTextDestinationData__
#define __IHyperlinkTextDestinationData__

#include "IPMUnknown.h"
#include "HyperlinkID.h"
#include "IHyperlinkTextDestinationMarker.h"

/**
	@ingroup layout_hyper
*/
class IHyperlinkTextDestinationData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKTEXTDESTINATIONDATA };

	/**	Setup this data structure
		@param *hyperlinkMarker - Text marker to associate with this destination
		@param isParagraph - kTrue if it is a pagraph destination
		@return  
	 */
	virtual void	Initialize(	const IHyperlinkTextDestinationMarker *hyperlinkMarker, bool16 isParagraph = kFalse) = 0;

	/**	Get the UID of the text marker associated with this text destination
		@param none
		@return UID - UID of the text marker
	 */
	virtual UID		GetTextMarkerUID() const = 0;

	/**	Set the UID of the text model associated with this text destination
		@param none
		@return UID - UID of the text model
	 */
	virtual UID		GetTextModelUID() const = 0;

	/** Return kTrue if the text destination is paragraph, kFalse if it is text anchor
	*/
	virtual bool16 		IsParagraphDestination() const = 0;
	virtual void 		SetIsParagraphDest(bool16 isParagraphDest) = 0;
};


#endif // __IHyperlinkTextDestinationData__

