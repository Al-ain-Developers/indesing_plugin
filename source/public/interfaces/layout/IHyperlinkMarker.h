//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IHyperlinkMarker.h $
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
#ifndef __IHyperlinkMarker__
#define __IHyperlinkMarker__

#include "IPMUnknown.h"
#include "HyperlinkID.h"

class	IHyperlinkTextSourceData;
class	IHyperlinkTextDestinationData;
class	ITextModel;

/** Obsolete as we don't use markers for hyperlink sources any more. For hyperlink
	destinations, we use IHyperlinkTextDestinationMarker instead.
	
	@ingroup layout_hyper
*/
class IHyperlinkMarker : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IHYPERLINKTEXTMARKER };


	// return the UID of the hyperlink source or destination that "owns" this text marker.
	// Caveat: 	One of the following two *will* return kInvalidUID

	/**	Get the hyperlink source UID (Will return kInvalidUID if GetHyperlinkDestinationUID()
		returns a valid UID)
		@param none
		@return UID - UID of the source
	 */
	virtual UID			GetHyperlinkSourceUID() const = 0;

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

	/**	Get the location of this marker as a TextIndex
		@param none
		@return TextIndex - This marker's location in the text strand
	 */
	virtual TextIndex	GetLocation() const = 0;

	/**	Get the UID of the marker that corresponds to this one
		@param none
		@return UID - UID of the related marker (kInvalid if this is a destination marker)
	 */
	virtual UID			GetOtherMarkerUID() const = 0;
};


#endif // __IHyperlinkMarker__

