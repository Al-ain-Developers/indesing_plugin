//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkTextDestinationMarker.h $
//  
//  Owner: Jianlan Song
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
#ifndef __IHyperlinkTextDestinationMarker__
#define __IHyperlinkTextDestinationMarker__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

class	IHyperlinkTextDestinationData;
class	ITextModel;

/**	Interface for hyperlink text destination marker object. This is the
	interface for kHyperlinkTextDestinationMarkerBoss to represent
	the text marker for hyperlink text destination.
	@ingroup layout_hyper
*/
class IHyperlinkTextDestinationMarker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKTEXTDESTINATIONMARKER };


	/**	Initilize this class using all of the information at once rather than
		having to call several methods one after the other
		@param textHyperlinkDestinationData - The destination that this marker is related to
		@param *textModel - Text model to point to
	 */
	virtual void 		Initialize(	const IHyperlinkTextDestinationData	*textHyperlinkDestinationData,
									const ITextModel *textModel) = 0;


	/**	Get the hyperlink destination UID (Will return kInvalidUID if GetHyperlinkSourceUID()
		returns a valid UID)
		@param none
		@return UID - UID of the destination
	 */
	virtual UID 		GetHyperlinkDestinationUID() const = 0;


	/**	Get the UID of the text model that this marker points to
		@param none
		@return UID - UID of the text model
	 */
	virtual UID			GetTextModel( ) const = 0;

	/**	Update this markers location
		@param newTextIndex - Setting this to a value other than -1 will set the new location to that value
		@return TextIndex - This marker's location in the text strand
	 */
	virtual TextIndex	UpdateLocation(TextIndex newTextIndex = -1) = 0;

	/**	Get the location of this marker as a TextIndex
		@param none
		@return TextIndex - This marker's location in the text strand
	 */
	virtual TextIndex	GetLocation() const = 0;

};


#endif // __IHyperlinkTextDestinationMarker__


